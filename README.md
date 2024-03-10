# open-iot-stem
One Planet Education Network IoT STEM Education Kit


<img width="248" alt="OPENglobe" src="https://user-images.githubusercontent.com/17368055/199580276-4e5cb63f-2cf8-4e95-b6a8-bd3511b393b7.png">

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
   
### Workspace 

- Install Arduino interactive desktop environment (IDE)
  
  - Navigate to the [Arduino Desktop Download](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE)
    
  - Download the installation for your assocated operating system (Windows, macOS, or Linux)
    
  - Complete the installation instructions on the previous page
  	- Accept agreement
     
     	![EULA](https://github.com/GrayHatGuy/open-iot-stem/blob/dd037156e10cf8012d80651c72ed1127b8dd8774/img/install_accept_eula.png)

	- Select local install only USER
 
    	![local user install only](https://github.com/GrayHatGuy/open-iot-stem/blob/286e78ae7300664053bf196812677572951bfd85/img/install_onlyme.png)

	- Choose defauls install location under USER home
 
    	![install location](https://github.com/GrayHatGuy/open-iot-stem/blob/286e78ae7300664053bf196812677572951bfd85/img/install_location.png)

	- Choose Run after installation

	![run install](https://github.com/GrayHatGuy/open-iot-stem/blob/286e78ae7300664053bf196812677572951bfd85/img/install_run.png)

	- The following screen will appear if installation is successful
 
  	![run ok](https://github.com/GrayHatGuy/open-iot-stem/blob/b9773bcb26dc30eb709d180c0b20ddd3482262ba/img/install_run_OK.png)

  
### Copy code repository

- Download a compressed ZIP of the code
  
  - Click the green CODE button at the top
    
  - Select Download ZIP
    
    ![ZIP download](https://github.com/GrayHatGuy/open-iot-stem/blob/3617701d3dec65c0ebc42911ac7744f3bd4ea87b/img/repo_zip.png?raw=true)
    
  - The default ZIP file will be downloaded to your *../USER/Downloads* directory for both Windows or macOS
    
- Uncompress the ZIP by double clicking the file

	![zip extract](https://github.com/GrayHatGuy/open-iot-stem/blob/32fa7c079bdea24ce6d8be11ccd1ddb109cb30c9/img/zip_extract.png)  
    
  - The file will extract to the same directory *../USER/Downloads* by default

  	![zip extract default](https://github.com/GrayHatGuy/open-iot-stem/blob/fb390c07799f70c12bb6786b487a4dc299155276/img/zip_extract_default2.png)  
    
  - Navigate to the extracted folder and open the *../src/* folder to find the *open-iot-stem.ino* program

	![zip open_src](https://github.com/GrayHatGuy/open-iot-stem/blob/610b9e9982f8e551d0c58b1c6defaf6dc214445e/img/zip_open_src.png)

  - Double click *open-iot-stem.ino* to open it in Arduino

	![open_ino](https://github.com/GrayHatGuy/open-iot-stem/blob/610b9e9982f8e551d0c58b1c6defaf6dc214445e/img/open_ino.png)

  - You will then be prompted to import the sketch and create a project click OK

	![create sketch](https://github.com/GrayHatGuy/open-iot-stem/blob/610b9e9982f8e551d0c58b1c6defaf6dc214445e/img/create_sketch_folder.png)

  - Select from the **File>Save As** from the title menu and save the project to your *../USER/../Ardunio/* directory this is the default location for all project

	![save as](https://github.com/GrayHatGuy/open-iot-stem/blob/610b9e9982f8e551d0c58b1c6defaf6dc214445e/img/file_saveas_select.png)

  - Confirm the location and save 

	![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/d7d34cd8ccd30538eb157ca6c7fc09528751a928/img/save_as_arduino_location2.png)
    
- Post installation set-up

	- Update Boards
    
    	*We are using an nRF52 third-party board for this training session you will need to add board support*
        *Arduino has built in board support for many boards but if you use other [third-party boards in](https://github.com/arduino/Arduino/wiki/Unofficial-list-of-3rd-party-boards-support-urls) in the future they can also be appended in this location*
    
   		- Verify Arduino is open and use title menu to navigate to: **File>Prefernces>Additional Board Support**
      
    		- Paste the following into the location and click OK to accept

   		  	```https://raw.githubusercontent.com/RAKwireless/RAKwireless-Arduino-BSP-Index/main/package_rakwireless_index.json```
       
			```https://raw.githubusercontent.com/RAKwireless/RAKwireless-Arduino-BSP-Index/main/package_rakwireless_com_rui_index.json```
       

    		- Open board manager

		![notext]()

		- Search for RAK boards

    		![notext]()
  
		- Install all boards starting with the following:
  
  		![notext]()
  
    		- After installation completes install the others
  
		![notext]()
      
      		- Select the board for your project
		*Note: RAK nRF board shown as an example boards will vary based on your project*
  
		![notext]()

		- Save and quit the project to update boards

		![notext]()
  
 	- Update libraries and dependancies
    
		- Automatic using code links (preferred)
       
			- Scroll to the top of the code window in Arduino you will see the following
         
	 		picture of required libraries			

			- Click each of the links to auto install using the library manager
     
			*If all library links are successfully installed continue to Save and reload project below*
     			*If library links fail to install then try manually install with alternate method below*
         
 		- Manually Search Arduino Library manager (alternate)
     
   			- Select title menu library manager
        
   			- Search
        
			- Install
     
	- Save and reload project
   
 		- Save a working copy of the project file to your /USER/ directory from title menu **File>Save As**  
   
## Edit code
*[5 min]*
*In order for the IoT device to be recognized within the LoRaWAN network you will need to add secret keys to the code these are similar to a username and password*

- Edit code and add secrets and keys

  Show code screen
  
## Compile and build code
*[5 min]*
*To run the code we need to verify the code for errors and check that all necessary libraries and components are installed this is referred as building and/or compiling*

- Click Build button to compile 

  screenshot of build button

- Wait until compile is complete

  	- if compile is complete continue on to [Flash code]	
  	screenshot of good compile

	- if compile fails then see debug

## Flash code
*After the code has completed a successful build/compile we need to upload the program and flash the iot device with the code*

- Verify USB is connected to IoT
  
- Verify IoT is detected

	- If connected COM port will be shown in status bar

  	- If not connected click on status and select port for your IoT
  
- Flash program device

  	- Click Upload button to flash

     	  screenshot of upload button

- Wait for flash to complete
  
	- If successful you will see the following screen and continue to [Verification]

  	screenshot

	- If fails see debug 

  
## Verification
*[10 min]*
- Serial terminal
  - GPS data
  - Sensor data
    
## Debug
*[+15 min]*
*Only necessary if prior steps are unsuccessful*

EXTRAS

*If libraries are missing*

- Download and import using ZIP (alternate expert)- Select title menu ZIP
- Navigate to the ZIP file typically located in *../USER/Downloads/*
- Search the internet (alternate expert)
       
- Check repository /lib

  
Adafruit nrf utility installed via PIP (Python3).
https://github.com/adafruit/Adafruit_nRF52_nrfutil

All of the Adafruit board definitions in the sketch are installed via library manager.

Adafruit Bluefruit nrf51 library installed via library manager.


  		- SAVE and RELOAD
			- Save a working copy of the project file to your /USER/ directory from title menu **File>Save As**
			- Exit and restart Arduino the project should auto load if not use **File>Open** from the tile menu to reload the project

 
  
