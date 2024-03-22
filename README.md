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

	- Choose default install location under USER home
 
    	![install location](https://github.com/GrayHatGuy/open-iot-stem/blob/286e78ae7300664053bf196812677572951bfd85/img/install_location.png)

	- Choose Run Arduino after installation

	![run install](https://github.com/GrayHatGuy/open-iot-stem/blob/286e78ae7300664053bf196812677572951bfd85/img/install_run.png)

	- The following screen will appear if installation is successful
 
  	![run ok](https://github.com/GrayHatGuy/open-iot-stem/blob/b9773bcb26dc30eb709d180c0b20ddd3482262ba/img/install_run_OK.png)

  
### Copy code repository

- Download a compressed ZIP of the code
  
  - Click the green CODE button at the top
    
  - Select Download ZIP
    
    ![ZIP download](https://github.com/GrayHatGuy/open-iot-stem/blob/3617701d3dec65c0ebc42911ac7744f3bd4ea87b/img/repo_zip.png?raw=true)
    
  - The default ZIP file will be downloaded to your *../USER/Downloads* directory for both Windows or macOS
    
- Extract the ZIP by double clicking the file

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

  - Confirm the location and save **File>Save** or press CTRL+S

	![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/d7d34cd8ccd30538eb157ca6c7fc09528751a928/img/save_as_arduino_location2.png)
    
- Post installation set-up

	- Update Boards
    
    	*We are using an Wisblock nRF52 for this training session you will need to add third party board support*
        *Arduino has built in board support for many boards but if you use others see [third-party boards in](https://github.com/arduino/Arduino/wiki/Unofficial-list-of-3rd-party-boards-support-urls) they will be appended to this same location*
    
   		- Verify Arduino is open and use title menu to navigate to: **File>Prefernces>Additional Board Support**
      
    		- Paste the following into the location and click OK to accept

   		  	```https://raw.githubusercontent.com/RAKwireless/RAKwireless-Arduino-BSP-Index/main/package_rakwireless_index.json```
       
			```https://raw.githubusercontent.com/RAKwireless/RAKwireless-Arduino-BSP-Index/main/package_rakwireless_com_rui_index.json```
       

    		- Open board manager **Tools>Board>Boards Manager** or CTRL+SHIFT+B

			![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/d146fc328c1f31d01d466f0dbd26be65ca9af403/img/boardmgr-select.png)

		- Search for RAK boards and install the following

			![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/d146fc328c1f31d01d466f0dbd26be65ca9af403/img/board%20search%20RAK.png)
   
   		- After installation completes install the others

   			![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/d146fc328c1f31d01d466f0dbd26be65ca9af403/img/board%20search%20RAK2.png)

		- Select the board for your project
		*Note: Wisblock RAK nRF board is shown as an example boards may vary based on your project*
  
		![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/d146fc328c1f31d01d466f0dbd26be65ca9af403/img/board_select.png)

		![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/4cbab286550564bde282afb667007109a1679a26/img/selectboard2.png)

		- Save and quit the project to update boards **File>Save** CTRL+S and **File>Quit** CTRL+Q

			![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/410a55094f25b8dad8bfc0a350c4d99f98e89992/img/save%20and%20quit.png)
  
 	- Update libraries and dependancies

		- Open Arduino and sketch will auto load
    
		- Install libraries using links from code to automatically open Library manager 
       
			- Scroll to the top of the code window in Arduino you will see the following

				![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/e1e39109b260238441e1cc3684ff06a48de22548/img/library_list.png)

			- Hold down the <CTRL> key and click on each of the links to search for the library

    			- AFter the library is found press INSTALL repeat until all libraries are installed
       - 
				![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/e1e39109b260238441e1cc3684ff06a48de22548/img/lib_bsec.png)  
   
		- Save and quit **File>Save** CTRL+S and **File>Quit** CTRL+Q 

  		- Open Arduino again to update changes 

   
## Edit code
*[5 min] In order for the IoT device to be recognized within the LoRaWAN network you will need to add secret keys to the code these are similar to a username and password*

- Edit code and to add LoRaWAN secrets and keys for the IoT

	- Navigate to the code window hold the CTRL key and press F to search the code

 	- Type 'deviceEUI' to locate the secrets that require updating
 
  	- Update the 00000s in the code to reflect the secrets for your IoT device

		![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/ffa3bece4b30c3b41f0eb4d35138f64f3d5a86ac/img/secrets.png)
  	
   	-  Save the sketch **File>Save** CTRL+S 
  
## Compile and build code
*[5 min] To run the code we need to verify the code for errors and check that all necessary libraries and components are installed this is referred as building and/or compiling*

- Click the Verify button to compile and build code 

  	![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/ffa3bece4b30c3b41f0eb4d35138f64f3d5a86ac/img/compile.png)

- You will see the following if the code has succesffully been Verified

  	![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/ffa3bece4b30c3b41f0eb4d35138f64f3d5a86ac/img/compile_success.png)

## Flash code
*After the code has completed a successful build/compile we need to upload the program and flash the iot device with the code*

- Verify USB is connected to IoT

- Check that correct board and port is selected

	![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/ffa3bece4b30c3b41f0eb4d35138f64f3d5a86ac/img/port%20select.png)

  	*Note In some cases when using Window the IoT is not detected and/or port is not shown. This requires a driver installation to detect the board and port.
  	Use the following hyperlink to update and install appropriate driver. A restart of Arduino and or a reboot of windows may be required if IoT is still not 	detected after driver install.  You can also check Windows Device Manager to verify if the board is detected and confirm that the driver is installed 		properly*

  		[Update FTDI driver](https://support.arduino.cc/hc/en-us/articles/4411305694610-Install-or-update-FTDI-drivers)
  
- Select the Upload button to flash program the device

	![notext](https://github.com/GrayHatGuy/open-iot-stem/blob/ffa3bece4b30c3b41f0eb4d35138f64f3d5a86ac/img/flash.png)

- The terminal window at the bottom of the screen will update with the Upload results

- The device will automatically start when flash is complete
  
## Verification
*[10 min]*

- Open the serial monitor using the menu title bar **Tools>Serial Monitor** or pressing CTRL+SHIFT+M keys

- The serial monitor will show the sensor information below the code window
    

 
  
