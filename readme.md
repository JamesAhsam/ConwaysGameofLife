#Conway's Game Of Life Demo
This is my (James Ahsam's) demo of Conway's Game of Life in C++ for the BBC TECHNICAL TEST. 

It is made in C++ and uses a OpenGL forward renderer, and was made on a mac (and partially a window pc). This will explain potentially some of the peculiarities with the code e.g. redefining 'FALSE' to 0 and 'TRUE' to 1 as all-caps false and true are not valid on macOS' base compiler.

Here are some of the assumptions I made: 
> * That each map is finite in size. I set this to 50x50.
* That each nodes state is logged and then changed in bulk after all changes have been made. Allowing for the whole state of each tick to be considered in entirety before any changes are made.
* That the state can be initialised in code, or changed whilst the simulation is paused. **Press Space to Pause**
* SOIL and OpenGL are installed on my mac and in the games framework using [this](https://github.com/DeVaukz/SOIL) and CMake. SOIL is just an image loading library for Open GL.
* The renderer was prewritten (on a windows machine) and minor changes have been made to make it more usable, and work on a mac compiler.
* The project is called SOILTEST - that is because SOIL can be a nightmare to install and I did not want to destroy the hours I had poured in trying to get it to work - so I stuck with this workspace. **This is the correct project.**

If there are any problems with the code feel free to contact me for any more information, or if you feel i have missed anything out.