# The Lost Girl and Six Coins

2D RPG Game Made With C and EasyX Graphical Library

## Table of Contents

1. [General Info](#general-info)
2. [Technologies](#technologies)
3. [Installation and Navigation](#installation-and-navigation)
4. [Directory Structure](#directory-structure)
5. [Naming Scheme and Convention](#naming-scheme-and-convention)
6. [Code Explanation](#code-explanation)
7. [FAQs](#faqs)
8. [Code Contributors](#code-contributors)

## General Info

"The Lost Girl and Six Coins" is largely inspired by the movie Jumanji with a simplified story and
rich game plot to attract players’ interest. The game is a 2d-top-down style classic game with
pixel-art style art. As per the current development stage, the game is planned to have 4 stages,
each with its unique challenges. The player must survive all the challenges and obstacles to
complete the game.

## Technologies

A list of technologies used within the project:
- [Dev-C++ released by Embarcadero](https://appzip.cn/devcpp/w): Version 6.3
- [EasyX Graphic Library For MinGW](https://codebus.cn/f/a/0/0/488/easyx4mingw.zip): Version
4.88
Other external packages and libraries:
- [MinGW-W64](https://www.mingw-w64.org/): Version 11.2.0/9.0.0
- [msimg.dll](https://www.dlldownloader.com/msimg32-dll/): Version 6.1.7600.16385
- [winmm.dll](https://www.dll-files.com/winmm.dll.html): Version 10.0.18362.1

## Installation and Navigation

For general purposes and navigations:
- the .exe file allows the game to run in a new window
- the "resources" folder stores all necessary images and videos
- the .cpp and .h files are used to run the game code
- the .dev file is the parent file that compiles all the .cpp files
For the best and most optimized gameplay experience:
- run the .exe file directly from the downloaded zip file without unzipping it to another folder
- close all other resource-heavy applications
EasyX for Dev-C++ setup and installation tutorial:
- https://codebus.cn/bestans/easyx-for-mingw
These libraries need to be added to Project>Project Options>Parameters>Linkers>Add library
or object:
- libEasyX.a
- libgdi32.a
- libole32.a
(This step can also be entered directly in Link libraries -lEasyX -lgdi32 -lole32)
- msimg.dll
- winmm.dll

## Directory Structure

This zip file contains several file types, namely .dev, .cpp, .h, .exe, and .txt. The “.h” extension
file stands for the library to be written in the code using “#include”. Meanwhile, the “.cpp”
extension stores the C code. The “.exe” executes the C code and runs the game. This
‘readme.txt” declares the general info, instructions to run the game, frequently asked questions,
and much more useful information. Lastly, a subfolder titled “resources” stores the images,
sound effects, and videos used in the game.
In addition, The Lost Girl and Six Coins.dev” is the main project file that stores all the .cpp code,
load all external libraries, build & compile the game, and many other crucial functions. Note that
the project was built in Dev C++ 6.3 build systems. As for now, there are 12 files under the
directory structure, namely functions.cpp, functions.h, header.h, level1.cpp, level1.h, level2.cpp,
level2.h, level3.cpp, level3.h, level4.cpp, level4.h, main.cpp. Other external game development
libraries include libEasyX.a, Libgdi32.a, libole32.a, msimg.dll, and winmm.dll.

## Naming Scheme and Convention

The code adapted a pre-defined naming rule and convention for all the variables and functions
used. This ensures the code is tidy and readable. The agreed name rule is to capitalize the first
letter of each word (except the first word) and use no space between words, for instance,
livesLeft, playerWalk, etc.

## Code Explanation

The full code explanation document is available in the attached “Code Explanation.pdf” file.
Clearer and step-by-step comments are also provided in the .cpp code to increase its readability
and maintainability.

## FAQs

Q: Should I download and import all the libraries and applications mentioned above to run the
game?
A: No, generally user can just run the .exe file to play the game. The libraries and applications
above are used for changing and testing the source code.
Q: What is the difference between the .cpp and .h files included in the zip folder?
A: .cpp files contains the C code for the game, while .h files contain the header used for
accessing a function from different .cpp file
Q: My game is blinking and does not run smoothly, what is wrong?
A: Make sure to close other resource-heavy apps, such as Google Chrome, Zoom Meeting, or
other demanding apps to get the best gameplay experience. If such a problem still occurs, try
running the game on devices with better spec and memory.
Q: Some resources, like music or images, are not loaded in the game, what can I do?
A: An unsuccessful unzipping process of the code might be one of the possible causes for this
error. To solve it, try running the .exe file directly from the downloaded zip file and do not unzip
it to another folder. Make sure that all required files (the resources folder, the .cpp file, the .h,
etc.) are all in the same zipped file to avoid relative path problems.
Q: .cpp file not found while running the .dev file, what can I do?
A: Try unzipping the file into a dedicated folder with the same exact name as the current zip
folder. Then, you should be able to load the .dev for the dev++ file.
Q: ID returned 1 exit status, ID returned 5 exit status, and other dev++ problems, what can I do?
A: For ID returned 1 exit status is probably caused by not closing the game window first before
compiling and running the code again. ID returned 5 exit status is caused by an unsuccessful
linking to the added linkers, try to locate which .dll files are broken or wrongly added. Other
dev++ problem solutions can be found by typing the error message in google.

## Code Contributors

- Bonifacio Ronald
- Chandra Geraldy
C Programming Module - Beijing Institute of Technology @2022
