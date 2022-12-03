/**
   @file EnvironMeter.ino
   @author Christopher Mendez @ RAKwireless
   @brief This sketch demonstrate reading data from a RAK1906 Environment Sensor and send it to cellphone through BLE and LoRaWAN using the Helium Network.
   @version 0.2
   @date 2022-12-02

   @copyright Copyright (c) 2022
 **/

#include <bluefruit.h>       // This one is already installed by the BSP.
#include "bsec.h"            // Click to install library: http://librarymanager/All#bsec
#include <U8g2lib.h>         // Click to install library: http://librarymanager/All#u8g2
#include <LoRaWan-RAK4630.h> // Click to install library: http://librarymanager/ALL#SX126x-Arduino
#include <SPI.h>

// Helper functions declarations
void checkIaqSensorStatus(void);
void errLeds(void);


// Forward declarations for functions
void ble_connect_callback(uint16_t conn_handle);
void ble_disconnect_callback(uint16_t conn_handle, uint8_t reason);

#define PIN_VBAT WB_A0

uint32_t vbat_pin = PIN_VBAT;
float vbat_mv;
uint8_t vbat_per;

#define VBAT_MV_PER_LSB (0.73242188F) // 3.0V ADC range and 12 - bit ADC resolution = 3000mV / 4096
#define VBAT_DIVIDER_COMP (1.73)      // Compensation factor for the VBAT divider, depend on the board

#define REAL_VBAT_MV_PER_LSB (VBAT_DIVIDER_COMP * VBAT_MV_PER_LSB)

/**
   @brief  BLE UART service
   @note   Used for BLE UART communication
*/
BLEUart g_BleUart;

/** Flag if BLE UART client is connected */
bool g_BleUartConnected = false;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2); // U8G2_R0 flip the screen

// Sensor data
String sensordata1, sensordata2;

// float temp, pres, hum, iaqq, co2;

double temp, pres, hum, iaqq, co2;

char data[32] = {0};

// Create an object of the class Bsec
Bsec iaqSensor;

String output;

bool doOTAA = true;                                               // OTAA is used by default.
#define SCHED_MAX_EVENT_DATA_SIZE APP_TIMER_SCHED_EVENT_DATA_SIZE /**< Maximum size of scheduler events. */
#define SCHED_QUEUE_SIZE 60                                       /**< Maximum number of events in the scheduler queue. */
#define LORAWAN_DATERATE DR_3                                     /*LoRaMac datarates definition, from DR_0 to DR_5*/
#define LORAWAN_TX_POWER TX_POWER_0                               /*LoRaMac tx power definition, from TX_POWER_0 to TX_POWER_15*/
#define JOINREQ_NBTRIALS 5                                        /**< Number of trials for the join request. */
DeviceClass_t g_CurrentClass = CLASS_A;                           /* class definition*/
LoRaMacRegion_t g_CurrentRegion = LORAMAC_REGION_US915;           /* Region:US915 | select the one of your country*/
lmh_confirm g_CurrentConfirm = LMH_UNCONFIRMED_MSG;               /* confirm/unconfirm packet definition*/
uint8_t gAppPort = LORAWAN_APP_PORT;                              /* data port*/

/**@brief Structure containing LoRaWan parameters, needed for lmh_init()
 */
static lmh_param_t g_lora_param_init = {LORAWAN_ADR_OFF, LORAWAN_DATERATE, LORAWAN_PUBLIC_NETWORK, JOINREQ_NBTRIALS, LORAWAN_TX_POWER, LORAWAN_DUTYCYCLE_OFF};

// Foward declaration
static void lorawan_has_joined_handler(void);
void lorawan_join_fail(void);
static void lorawan_rx_handler(lmh_app_data_t *app_data);
static void lorawan_confirm_class_handler(DeviceClass_t Class);
static void send_lora_frame(void);

/**@brief Structure containing LoRaWan callback functions, needed for lmh_init()
 */
static lmh_callback_t g_lora_callbacks = {BoardGetBatteryLevel, BoardGetUniqueId, BoardGetRandomSeed,
                                          lorawan_rx_handler, lorawan_has_joined_handler, lorawan_confirm_class_handler, lorawan_join_fail};

// OTAA keys !!!! KEYS ARE MSB !!!!
uint8_t nodeDeviceEUI[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t nodeAppEUI[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t nodeAppKey[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Private defination
#define LORAWAN_APP_DATA_BUFF_SIZE 64                                         /**< buffer size of the data to be transmitted. */
#define LORAWAN_APP_INTERVAL 20000                                            /**< Defines for user timer, the application data transmission interval. 20s, value in [ms]. */
static uint8_t m_lora_app_data_buffer[LORAWAN_APP_DATA_BUFF_SIZE];            //< Lora user application data buffer.
static lmh_app_data_t m_lora_app_data = {m_lora_app_data_buffer, 0, 0, 0, 0}; //< Lora user application data structure.

TimerEvent_t appTimer;
static uint32_t timers_init(void);
static uint32_t count = 0;
static uint32_t count_fail = 0;

/**
   @brief Get RAW Battery Voltage
*/
float readVBAT(void)
{
    float raw;

    // Get the raw 12-bit, 0..3000mV ADC value
    raw = analogRead(vbat_pin);

    return raw * REAL_VBAT_MV_PER_LSB;
}

/**
   @brief Convert from raw mv to percentage
   @param mvolts
      RAW Battery Voltage
*/
uint8_t mvToPercent(float mvolts)
{
    if (mvolts < 3300)
        return 0;

    if (mvolts < 3600)
    {
        mvolts -= 3300;
        return mvolts / 30;
    }

    mvolts -= 3600;
    return 10 + (mvolts * 0.15F); // thats mvolts /6.66666666
}

void bt_init()
{
    // Config the peripheral connection with maximum bandwidth
    // more SRAM required by SoftDevice
    // Note: All config***() function must be called before begin()
    Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);
    Bluefruit.configPrphConn(92, BLE_GAP_EVENT_LENGTH_MIN, 16, 16);

    Bluefruit.begin(1, 0);
    // Set max power. Accepted values are: -40, -30, -20, -16, -12, -8, -4, 0, 4
    Bluefruit.setTxPower(4);
    // Set the BLE device name
    Bluefruit.setName("RAK4631_UART");

    Bluefruit.Periph.setConnectCallback(ble_connect_callback);
    Bluefruit.Periph.setDisconnectCallback(ble_disconnect_callback);

    // Configure and Start BLE Uart Service
    g_BleUart.begin();

    // Set up and start advertising
    // Advertising packet
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();
    Bluefruit.Advertising.addName();

    /* Start Advertising
      - Enable auto advertising if disconnected
      - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
      - Timeout for fast mode is 30 seconds
      - Start(timeout) with timeout = 0 will advertise forever (until connected)

      For recommended advertising interval
      https://developer.apple.com/library/content/qa/qa1931/_index.html
    */
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244); // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);   // number of seconds in fast mode
    Bluefruit.Advertising.start(0);             // 0 = Don't stop advertising after n seconds
}

// Configuration
void setup(void)
{
    // Initialize the built in LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(WB_IO2, OUTPUT);
    digitalWrite(WB_IO2, LOW);

    Serial.begin(115200);
    Wire.begin();

    // Set the analog reference to 3.0V (default = 3.6V)
    analogReference(AR_INTERNAL_3_0);

    // Set the resolution to 12-bit (0..4095)
    analogReadResolution(12); // Can be 8, 10, 12 or 14

    // Let the ADC settle
    delay(1);

    // Get a single ADC sample and throw it away
    readVBAT();

    time_t serial_timeout = millis();
    // On nRF52840 the USB serial is not available immediately
    while (!Serial)
    {
        if ((millis() - serial_timeout) < 5000)
        {
            delay(100);
            digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        }
        else
        {
            break;
        }
    }

    Serial.println("=====================================");
    Serial.println("Welcome to RAK4630 LoRaWan!!!");
    if (doOTAA)
    {
        Serial.println("Type: OTAA");
    }

    switch (g_CurrentRegion)
    {
    case LORAMAC_REGION_AS923:
        Serial.println("Region: AS923");
        break;
    case LORAMAC_REGION_AU915:
        Serial.println("Region: AU915");
        break;
    case LORAMAC_REGION_CN470:
        Serial.println("Region: CN470");
        break;
    case LORAMAC_REGION_CN779:
        Serial.println("Region: CN779");
        break;
    case LORAMAC_REGION_EU433:
        Serial.println("Region: EU433");
        break;
    case LORAMAC_REGION_IN865:
        Serial.println("Region: IN865");
        break;
    case LORAMAC_REGION_EU868:
        Serial.println("Region: EU868");
        break;
    case LORAMAC_REGION_KR920:
        Serial.println("Region: KR920");
        break;
    case LORAMAC_REGION_US915:
        Serial.println("Region: US915");
        break;
    case LORAMAC_REGION_RU864:
        Serial.println("Region: RU864");
        break;
    case LORAMAC_REGION_AS923_2:
        Serial.println("Region: AS923-2");
        break;
    case LORAMAC_REGION_AS923_3:
        Serial.println("Region: AS923-3");
        break;
    case LORAMAC_REGION_AS923_4:
        Serial.println("Region: AS923-4");
        break;
    }
    Serial.println("=====================================");

    // Initialize LoRa chip.
    lora_rak4630_init();

    // creat a user timer to send data to server period
    uint32_t err_code;

    err_code = timers_init();
    if (err_code != 0)
    {
        Serial.printf("timers_init failed - %d\n", err_code);
        return;
    }

    // Setup the EUIs and Keys
    if (doOTAA)
    {
        lmh_setDevEui(nodeDeviceEUI);
        lmh_setAppEui(nodeAppEUI);
        lmh_setAppKey(nodeAppKey);
    }

    // Initialize LoRaWan
    err_code = lmh_init(&g_lora_callbacks, g_lora_param_init, doOTAA, g_CurrentClass, g_CurrentRegion);
    if (err_code != 0)
    {
        Serial.printf("lmh_init failed - %d\n", err_code);
        return;
    }

    lmh_join();

    u8g2.begin(); // OLED display init
    bt_init();    // BlE init

    iaqSensor.begin(BME680_I2C_ADDR_PRIMARY, Wire);
    output = "\nBSEC library version " + String(iaqSensor.version.major) + "." + String(iaqSensor.version.minor) + "." + String(iaqSensor.version.major_bugfix) + "." + String(iaqSensor.version.minor_bugfix);
    Serial.println(output);
    checkIaqSensorStatus();

    bsec_virtual_sensor_t sensorList[5] = {
        //BSEC_OUTPUT_RAW_TEMPERATURE,
        BSEC_OUTPUT_RAW_PRESSURE,
        //BSEC_OUTPUT_RAW_HUMIDITY,
        //BSEC_OUTPUT_RAW_GAS,
        BSEC_OUTPUT_IAQ,
        //BSEC_OUTPUT_STATIC_IAQ,
        BSEC_OUTPUT_CO2_EQUIVALENT,
        //BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    };

    iaqSensor.updateSubscription(sensorList, 5, BSEC_SAMPLE_RATE_LP);
    checkIaqSensorStatus();
}

/**
   @brief  Callback when client connects
   @param  conn_handle: Connection handle id
*/
void ble_connect_callback(uint16_t conn_handle)
{
    (void)conn_handle;
    g_BleUartConnected = true;

    Serial.println("BLE client connected");
}

/**
   @brief  Callback invoked when a connection is dropped
   @param  conn_handle: connection handle id
   @param  reason: disconnect reason
*/
void ble_disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
    (void)conn_handle;
    (void)reason;
    g_BleUartConnected = false;

    Serial.println("BLE client disconnected");
}

// Function that is looped forever
void loop(void)
{
    unsigned long time_trigger = millis();
    if (iaqSensor.run())
    { // If new data is available
        temp = iaqSensor.temperature;
        hum = iaqSensor.humidity;
        pres = iaqSensor.pressure / 100.0;
        iaqq = iaqSensor.iaq;
        co2 = iaqSensor.co2Equivalent;

        sensordata1 = "1," + String(temp) + "," + String(hum, 1) + "," + String(pres, 1);
        sensordata2 = "2," + String(iaqq, 0) + "," + String(co2, 0);

        //  Get a raw ADC reading
        vbat_mv = readVBAT();

        // Convert from raw mv to percentage (based on LIPO chemistry)
        vbat_per = mvToPercent(vbat_mv);

        displaying();

        if (g_BleUartConnected)
        {
            g_BleUart.print(sensordata1);
            delay(100);
            g_BleUart.print(sensordata2);
        }
    }
    else
    {
        checkIaqSensorStatus();
    }
}

/**@brief LoRa function for failed Join event
 */
void lorawan_join_fail(void)
{
    Serial.println("OTAA join failed!");
}

/**@brief LoRa function for handling HasJoined event.
 */
void lorawan_has_joined_handler(void)
{
    if (doOTAA == true)
    {
        Serial.println("OTAA Mode, Network Joined!");
    }
    else
    {
        Serial.println("ABP Mode");
    }

    u8g2.clearBuffer();             // clear the internal memory
    u8g2.setFont(u8g2_font_5x8_tf); // choose a suitable font

    u8g2.drawStr(20, 39, "Joined");
    u8g2.sendBuffer(); // transfer internal memory to the display

    delay(2000);

    lmh_error_status ret = lmh_class_request(g_CurrentClass);
    if (ret == LMH_SUCCESS)
    {
        delay(1000);
        TimerSetValue(&appTimer, LORAWAN_APP_INTERVAL);
        TimerStart(&appTimer);
    }
}

/**@brief Function for handling LoRaWan received data from Gateway
   @param[in] app_data  Pointer to rx data
*/
void lorawan_rx_handler(lmh_app_data_t *app_data)
{
    Serial.printf("LoRa Packet received on port %d, size:%d, rssi:%d, snr:%d, data:%s\n",
                  app_data->port, app_data->buffsize, app_data->rssi, app_data->snr, app_data->buffer);
}

void lorawan_confirm_class_handler(DeviceClass_t Class)
{
    Serial.printf("switch to class %c done\n", "ABC"[Class]);
    // Informs the server that switch has occurred ASAP
    m_lora_app_data.buffsize = 0;
    m_lora_app_data.port = gAppPort;
    lmh_send(&m_lora_app_data, g_CurrentConfirm);
}

void send_lora_frame(void)
{
    if (lmh_join_status_get() != LMH_SET)
    {
        // Not joined, try again later
        return;
    }

    bme680_get();

    lmh_error_status error = lmh_send(&m_lora_app_data, g_CurrentConfirm);
    if (error == LMH_SUCCESS)
    {
        count++;
        Serial.printf("lmh_send ok count %d\n", count);
    }
    else
    {
        count_fail++;
        Serial.printf("lmh_send fail count %d\n", count_fail);
    }
}

/**@brief Function for handling user timerout event.
 */
void tx_lora_periodic_handler(void)
{
    TimerSetValue(&appTimer, LORAWAN_APP_INTERVAL);
    TimerStart(&appTimer);
    Serial.println("Sending frame now...");
    send_lora_frame();
}

/**@brief Function for the Timer initialization.
   @details Initializes the timer module. This creates and starts application timers.
*/
uint32_t timers_init(void)
{
    TimerInit(&appTimer, tx_lora_periodic_handler);
    return 0;
}

void bme680_get()
{
    uint32_t i = 0;
    memset(m_lora_app_data.buffer, 0, LORAWAN_APP_DATA_BUFF_SIZE);
    m_lora_app_data.port = gAppPort;

    uint16_t t = temp * 100;
    uint16_t h = hum * 100;
    uint32_t p = pres * 100;
    uint32_t aq = iaqq * 100;
    uint32_t co = co2 * 100;

    // result: T=28.25C, RH=50.00%, P=958.57hPa, G=100406 Ohms
    m_lora_app_data.buffer[i++] = 0x01;
    m_lora_app_data.buffer[i++] = (uint8_t)(t >> 8);
    m_lora_app_data.buffer[i++] = (uint8_t)t;
    m_lora_app_data.buffer[i++] = (uint8_t)(h >> 8);
    m_lora_app_data.buffer[i++] = (uint8_t)h;
    m_lora_app_data.buffer[i++] = (uint8_t)((p & 0xFF000000) >> 24);
    m_lora_app_data.buffer[i++] = (uint8_t)((p & 0x00FF0000) >> 16);
    m_lora_app_data.buffer[i++] = (uint8_t)((p & 0x0000FF00) >> 8);
    m_lora_app_data.buffer[i++] = (uint8_t)(p & 0x000000FF);
    m_lora_app_data.buffer[i++] = (uint8_t)((aq & 0xFF000000) >> 24);
    m_lora_app_data.buffer[i++] = (uint8_t)((aq & 0x00FF0000) >> 16);
    m_lora_app_data.buffer[i++] = (uint8_t)((aq & 0x0000FF00) >> 8);
    m_lora_app_data.buffer[i++] = (uint8_t)(aq & 0x000000FF);
    m_lora_app_data.buffer[i++] = (uint8_t)((co & 0xFF000000) >> 24);
    m_lora_app_data.buffer[i++] = (uint8_t)((co & 0x00FF0000) >> 16);
    m_lora_app_data.buffer[i++] = (uint8_t)((co & 0x0000FF00) >> 8);
    m_lora_app_data.buffer[i++] = (uint8_t)(co & 0x000000FF);
    m_lora_app_data.buffsize = i;
}

// Helper function definitions
void checkIaqSensorStatus(void)
{
    if (iaqSensor.status != BSEC_OK)
    {
        if (iaqSensor.status < BSEC_OK)
        {
            output = "BSEC error code : " + String(iaqSensor.status);
            Serial.println(output);
            for (;;)
                errLeds(); /* Halt in case of failure */
        }
        else
        {
            output = "BSEC warning code : " + String(iaqSensor.status);
            Serial.println(output);
        }
    }

    if (iaqSensor.bme680Status != BME680_OK)
    {
        if (iaqSensor.bme680Status < BME680_OK)
        {
            output = "BME680 error code : " + String(iaqSensor.bme680Status);
            Serial.println(output);
            for (;;)
                errLeds(); /* Halt in case of failure */
        }
        else
        {
            output = "BME680 warning code : " + String(iaqSensor.bme680Status);
            Serial.println(output);
        }
    }
}

void errLeds(void)
{
    delay(100);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void displaying()
{
    u8g2.clearBuffer(); // clear the internal memory

    // Battery percentage showing
    u8g2.setFont(u8g2_font_5x8_tf); // choose a suitable font u8g2_font_ncenB10_tr

    memset(data, 0, sizeof(data));
    sprintf(data, "%d%%", vbat_per);
    u8g2.drawStr(110, 10, data);

    // Environment data showing
    u8g2.setFont(u8g2_font_7x13_tf); // choose a suitable font u8g2_font_ncenB10_tr -- u8g2_font_profont11_tf

    memset(data, 0, sizeof(data));
    sprintf(data, "T:%.2f C", temp);
    u8g2.drawStr(3, 10, data);

    memset(data, 0, sizeof(data));
    snprintf(data, 64, "RH:%.2f %%", hum);
    u8g2.drawStr(3, 23, data);

    memset(data, 0, sizeof(data));
    sprintf(data, "P:%.2f mbar", pres);
    u8g2.drawStr(3, 36, data);

    memset(data, 0, sizeof(data));
    sprintf(data, "IAQ:%.2f ", iaqq);
    u8g2.drawStr(3, 49, data);

    memset(data, 0, sizeof(data));
    sprintf(data, "CO2:%.2f ppm", co2);
    u8g2.drawStr(3, 62, data);

    u8g2.sendBuffer(); // transfer internal memory to the display
}

