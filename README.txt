Read Me:
This is my Compulsory two source code. As of 06/03/2024 the code is functional. If it does not work check visual studio version or check for additional package dependencies. I have run into errors where the library file is not included in the github download. If not, under dependencies create a file called “Libraries” and in that folder put 
glfw3.dll
glfw3.lib
glfw3_mt.lib
glfw3dll.lib
These four files can be downloaded from “https://www.glfw.org/download”. Get the 64 bit windows binaries, unzip the folder and copy the four files located under “lib-vc2022”.

Note:
Both paths followed by the NPC is taken from Math3 Compulsory 2, it can be found at this repository: https://github.com/Shrimpy02/SebastianZapart_Math3_Compulsory2.git 

Additionally the collision detection between player and static geometry is implemented, but disabled as it's not a requirement of the compulsory and works poorly as of yet. 

Controls: 
W,A,S,D – Movement.
E - Interact with door to open
tab - Changes path of the NPC from approximate to interpolated (or inverse)
Mouse movement – view camera. 
