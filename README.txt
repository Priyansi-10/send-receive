
============================================================
Description : Sending and Receiving network packets using Sockets
============================================================

Date: November 6, 2023

------------------------------------------------------------
Compiling Instructions 
------------------------------------------------------------
	
	1. Make sure to have a folder with files sender.cc, receiver.cc, and makefile
	2. Open terminal and navigate to the directory where the files are located. 
	3. Compile programs by running the following command, that will use the makefile to compile both the sender and receiver progams:
	
	make

	4. The make command will then generate executable files 'sender' and 'receiver'.
	5. To run executable files we need a different port where the incoming messages will be received. We have given the following ports for each IPv4 and IPv6

		IPv4: localhost 3000 -4
		IPv6: ::1 3000 -6

	6. So now to run the files we will type in ./sender ::1 3000 -6 or ./sender localhost 3000 -4.   
	   And ./receiver 3000 -4 or ./receiver 3000 -6.
	7. In a separate window we will first run receiver for IPv4 by using ./receiver 3000 -4. 
	   In another window we will run sender for IPv4 by using ./sender localhost 3000 -4. 
	OR
	   In a separate window we will first run receiver for IPv6 by using ./receiver 3000 -6. 
	   In another window we will run sender for IPv6 by using ./sender ::1 3000 -4.
	8. Now after running all these commands we should be able to input messages in the sender terminal window which should be seen in the sender and receiver windows. This will be made sure when we receive the messages that indicate the sender messages were received. 
	
