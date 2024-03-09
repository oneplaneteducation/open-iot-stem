# open-iot-stem
One Planet Education Network IoT STEM Education Kit


<img width="248" alt="OPENglobe" src="https://user-images.githubusercontent.com/17368055/199580276-4e5cb63f-2cf8-4e95-b6a8-bd3511b393b7.png">

Adafruit nrf utility installed via PIP (Python3).
https://github.com/adafruit/Adafruit_nRF52_nrfutil

All of the Adafruit board definitions in the sketch are installed via library manager.

Adafruit Bluefruit nrf51 library installed via library manager.

## Prerequisites

The following are a list of **requirements** for the training session

- Video conferencing: 
   *At minium 2 video conferencing devices*
	- Primary video conference device that is able to share the screen of the workstation computer and communicate with the team
	- Hand held or mobile device to show the assembly of the IoT
   	- Mute the sound on all devices other than the primary video to avoid interference (preferred)
- Workstation computer:
    - Windows 64 bit – 10 or newer
    - MacOS 64 bit - 10.14 mojave or newer 
    - Linux 64 bit
    - User has adminstrator privileges for the local workstation (preferred) 
- Internet connectivity:
    - Web or http access to the internet (port 443 and 80 unrestricted)
    - File downloads unrestricted
    - USB ports unrestricted
- IoT Hardware
    - USB cables
    - OPEN approved IoT kit
 
The following are a list of **recommendations** for the training session but are not required

- Disable local virtual private networking (VPN)
- Disable all cloud syncronization via iCloud MSLive or OneDrive

## Installation
*[35 min]*
### Repository

- Download a compressed ZIP
  - Click the green CODE button at the top
  - Select Download ZIP
    ![ZIP download](https://github.com/GrayHatGuy/open-iot-stem/blob/3617701d3dec65c0ebc42911ac7744f3bd4ea87b/img/repo_zip.png?raw=true)
  - The default ZIP file will be downloaded to your *../USER/Downloads* directory for both Windows or macOS
  - Uncompress the ZIP by double clicking the file
  - The file will extract to the same directory *../USER/Downloads* by default
  - Navigate to the extracted folder and open it for later use
### Workspace 
- Arduino interactive desktop environment (IDE)
  - Navigate to the [Arduino Desktop Download](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE)
  - Download the installation for your assocated operating system (Windows, macOS, or Linux)
  - Complete the instruction for installing
  - Laund Arduino IDE
- Post installation set-up
  - Update Boards
    *If a third-party board template is needed you will need to update it accordingly this template varies depenging on the board being used*
    *We are using and nRF52 third-party board for this training session if you use other boards in the future they will need to be added*
  	- Verify Arduino is open and navigate to menu **File>Prefernces>Additional Board Support**
   	- Paste the following into the locations and click OK to accept
        	```https://raw.githubusercontent.com/RAKWireless/RAKwireless-Arduino-BSPIndex/main/package_rakwireless.com_rui_index.json```
  - Update libs
    
## Coding
*[15 min]*
- Add LoRaWAN secrets and keys
- Compile and build 
- Flash program device
- ?LoRaWAN integration?
## Verification
*[10 min]*
- Serial terminal
  - GPS data
  - Sensor data
## Debug
*[+15 min]*
*Only necessary if **Verification** is unsuccessful*
  
