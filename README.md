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
   *At minimum 2 video conferencing devices*
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
    - OPEN approved educational IoT kit
 
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

- Install Arduino interactive desktop environment (IDE)
  
  - Navigate to the [Arduino Desktop Download](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE)
    
  - Download the installation for your assocated operating system (Windows, macOS, or Linux)
    
  - Complete the installation instructions on the previous page
    
  - Launch Arduino IDE
    
- Post installation set-up
  
  - Load the example program from title menu **File>/Load**
    The example program is located within the extracted ZIP extracted during the earlier steps typcially your */USER/Downloads* directory in *../open-iot-stem/src/open-iot-stem.ino*

    - Save a working copy of the project file to your */USER/* directory from title menu **File>Save As**
      
    - This preserves a clean copy of the file in the extracted ZIP location in case your working copy is corrupted during edits
      
  - Update Boards
    
    *We are using an nRF52 third-party board for this training session you will need to add board support*
        *Arduino has built in board support for many boards but if you use other third-party boards in the future they can also be appended in this location*
    
    - Verify Arduino is open and use title menu to navigate to: **File>Prefernces>Additional Board Support**
      
    - Paste the following into the location and click OK to accept

   		```https://raw.githubusercontent.com/RAKWireless/RAKwireless-Arduino-BSPIndex/main/package_rakwireless.com_rui_index.json```

    - Save a working copy of the project file to your /USER/ directory from title menu **File>Save As**
  
   - Update libraries and dependancies
     
     - Automatic using code links (preferred)
       
       - Scroll to the tope of the code window in Arduino you will see the following
         <picture of required libraries
         
       - Click each of the links to auto install using the library manager
         *If links fail to install libraries the try the following alternative methods*
         
     - Manually Search Arduino Library manager (alternate)
       
	- Select title menu library manager
   
     	- Search
        
     	- Install

     	***If all required libraries have been installed does not exist in the Arduino Library manager try the following expert alternatives:***  
       
     - Download and import using ZIP (alternate expert)
       
     	- Select title menu ZIP

      	- Navigate to the ZIP file typically located in *../USER/Downloads/*

    - Search the internet (alternate expert)
       
     - IF all libraries have been successfully installed then 
       
     	- Save a working copy of the project file to your /USER/ directory from title menu **File>Save As**
      
        - Exit and restart Arduino the project should auto load if not use **File>Open** from the tile menu to reload the project

     
    
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
  
