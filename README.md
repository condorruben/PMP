# PMP

```
About:
    ## This is a small little project: Interacting with Arduino using vocal commands.
    -> There are two major components. 
        1) The arduino side in C/C++
        2) The computer/ laptop side in Python
    -> These components commicate using a sub custom serial protocol (Using the USB port)
    -> Designed to be easly extended: Follow the patters presented in the controller/controller.py and scr/main.cpp files

Setup:
    You need to install:
    -> Arduino IDE from the official site. Do not install it from the Microsoft Store as an application
    -> Python 3 (Tested on version 3.8x)
    -> Microsoft Visual Studio Code (vscode)
    -> PlatformIO vscode extention and any other extentions recommended by vscode for python and C/C++

Usage:
    -> Open this repo as a vscode Workspace
    -> Connect the Arduino Board and click on the right arrow on the lower vscode bar in order to upload the code to the board
        The board and the COM will be detected automatically by PlatformIO and printed in the termial, remember the COM number
    -> Change the COM port specified by PlatformIO in the controller/controller.py file
    -> Run the python script using the triangle from the upper right to run the script in the terminal using the workspace as the
        current working directory

    -> Now you may interact with the project, it expects vocal commands in english:
        E.g.:
            $> Hello, Arduino!
            $> What's the temperature?
            $> Show me a magic trick
            $> What's the humidity level?
            $> Do you sense any fire in here?
            $> Play a game
            $> Is there any flame?
            $> Thank you very much
            $> You may exit the program now
```
