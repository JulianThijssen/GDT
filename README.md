# GDT
Graphics Development Tools (GDT) A collection of utility classes for graphics development

## Building
### Requirements
* Git (https://git-scm.com/)
* CMake 3.9+ (https://cmake.org/)
* Visual Studio 2017 or higher (Windows https://visualstudio.microsoft.com/downloads/)

### Setting up
The first step is to pull the repository from GitHub. You can do this in any way you like, but here is one possible way:

1. Create a local folder called `GDT` for the project on your computer
2. Go into the folder and open GitBash or a terminal with git enabled
3. Execute the command `git init` to initialize the Git repository
4. Execute the command `git remote add origin git@github.com:JulianThijssen/GDT.git` to link your local repository to the remote GitHub one.
5. Fetch all branches from the repository using `git fetch -a`
5. Now you can pull in the source files from the `master` branch by executing `git pull origin master`
6. If you get a permission denied message on the last step be sure that you have an SSH-key pair and have added the public one to your GitHub account. See: https://help.github.com/en/github/authenticating-to-github/connecting-to-github-with-ssh

### Building
1. Launch CMake (available here: https://cmake.org/)
2. In the source code field browse to the local folder from the last section (which contains CMakeLists.txt).
3. In the build field copy the source code field but append `/Build` at the end. This will put all files necessary for building in the `Build` folder (it will create it if it doesn't exist).
4. Press `Configure` and select the generator for your IDE of choice with the platform of `x64`. Press Finish to configure the project.
5. If no errors appear in the CMake log on the bottom, press `Generate` to generate the solution for your given IDE.
6. Press `Open Project` to launch the IDE and the project.

## Compilation

### Visual Studio
1. At the top of Visual Studio set the build mode to your desired configuration `Debug` or `Release`.
2. Right click the solution `Solution GDT` and press `Build Solution`.
3. If all is well it should output `4 succeeded, 0 failed` at the end, and have produced a folder called Output in the GDT folder which contains the library and include files.
