function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};

  // if (port === 1) decoded.led = bytes[0];function Decoder(bytes, port) {
  var TEMP    = (bytes[0] << 4);
  var HUM     = (bytes[4] << 8);  
  var ALT     = (bytes[10] << 11);
  var IAQ     = (bytes[11] << 12);
  var CO2     = (bytes[15] << 17);
  
  return {
  Temperature:     TEMP,
  Humidity:        HUM,
  Alt:             ALT,
  IAQ:             IAQ,
  CO2:             CO2,
  
  };
  
}
