# Snake Game

This is a console-based version of the snake game written in C++, using the `ncurses` library. It runs on the terminal, using basic characters as display. Currently, it is only supported for Linux.

## Build ##

Download the files in this repository and open the terminal in the main directory. Type `make` and hit enter. If everything goes okay, you should see a message `Build successful!` displayed on the screen. Then, you can use `./snake_game` to run the game.

The compilation stores object files in the `obj` folder, and dependencies in  the `.deps` folder. The executable is stored in the main directory.

To delete all object files and the executable, run `make clean`.

## Dependencies ##

The game requires the `ncurses` library to compile. For Debian-based distributions of Linux, such as Ubuntu, you can obtain it by running the following command: `sudo apt-get install libncurses5-dev libncursesw5-dev`. For RPM-based distributions of Linux, you can obtain it by running `sudo yum install ncurses-devel`. You can easily look up install instructions for other distributions.

The default compiler is `GCC`. The minimal required version is C++11. You can also use `clang`, in which case you need to replace the first line in `makefile`, which is currently `CC=g++`, with `CC=clang++`.

## Demo ##

Check the screenshots in the `demo` folder!
