# PA4: Model Loading

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

## Building and Running
To build this project there are two options. One is to use CMake which makes including new libraries easier, and handles new files added automatically to the src and include directory. CMake is a small new learning curve but makes things easier in the future.
The second option is to use the provided Makefile which is used as usual.

Running the make in a separate directory will allow easy cleanup of the build data, and an easy way to prevent unnecessary data to be added to the git repository.  

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary. Later use with CMake and Shader files will be require the copy of a directory where those files are stored (ex. shaders). To do this in the ```add_custom_target``` function place 
```cmake
COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/shaders/ ${CMAKE_CURRENT_BINARY_DIR}/shaders
COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/models/ ${CMAKE_CURRENT_BINARY_DIR}/models
```

```bash
mkdir build
cd build
cmake ..
make
./Tutorial -v shaders/cubeVertexShader.glsl -f shaders/cubeFragmentShader.glsl -m model/[Object].obj
```

### Makefile Instructions 
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./Tutorial -v shaders/cubeVertexShader.glsl -f shaders/cubeFragmentShader.glsl -m model/[Object].obj
```
### Running different .obj File Formats

Some .obj files for their faces has a single white space, a "/" or "//" slashes. To accomadate for that for this project, you have to go into the object.cpp file, go to near line 127 and uncomment or comment out the fscanf calls. Only 1 fscanf should be called. For the dragon.obj, use the default call on line 127. For my particular board, uncomment line 130 and comment out line 127. This is all the modifications you will need.

### Running Program with Command Line Arguments

To run this program, provide the location of the shaders of -v and -f

-v Specifies file path for the Vertex Shader.  
-f Specifies file path for the Fragment Shader.  
-m Specifies file path for the obj file. 

Failure to provide all three file paths will result in program termination.

Usage
```bash
./Tutorial -v shaders/cubeVertexShader.glsl -f shaders/cubeFragmentShader.glsl -m model/[Object].obj
```
### Overall Controls
Controls for this program will be using the SDL Library with Keyboard.
See usage as described below.

## Keyboard Usage

### Universal Usage
* Quit Program - Escape Key
