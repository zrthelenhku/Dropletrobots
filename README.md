# Dropletrobots
1. System requirements: 
System: Windows 11;
Software: Arduino 1.8.19 (Windows store 1.8.57.0);
Hardware: Arduino Uno connected with the proposed programmable control matrix established on PCB.

2. Installation guide:
Instructions: Download Arduino IDE from the official website. Double click the installation package to install Arduino IDE. Double click the attached code file to open it in Arduino IDE.
Typical install time: Several minutes.

3. Demo:
Instructions to run on data: Click the "upload" button to send the code to the connected Arduino Uno. Open the Serial monitor and input the command to change the coordinate of activated coils.
Expected output: The current coordinate of the activated coil will be displayed in the serial monitor.
Expected run time: Several minutes.

4. Instructions for use: 
The attached file "routine.ino" is for the general control of the programmable control matrix to explore the coordinate of grippers' moving path. By inputting command in the serial monitor, the coordinate of activated coils can change accordingly to move grippers. The moving path of grippers will be displayed in the serial monitor and recorded for further usage. The initial coordination can be modified in the attached code file.
