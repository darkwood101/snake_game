# Snake Game

This is a remake of the classic snake game, written in C++ using the SDL library and with minimalistic geometric figures as graphics.

## Build ##

Download the files from this repository and open the terminal in the main directory. Type `make` and hit enter. If everything goes okay, you should see a message `Build successful!` displayed on the screen. Then, you can use `./snake_game` to run the game. See **Dependencies** below for more on what you need to in order to compile the game.

The compilation stores object files in the `obj` folder, and dependencies in  the `.deps` folder. The executable is stored in the main directory.

To delete all object files, the executable, and the dependencies, run `make clean`.

## Dependencies ##

The game requires the `SDL 2` library to compile, as well as `SDL_ttf 2`. For Debian-based distributions of Linux, such as Ubuntu, you can obtain these by running the following command: `sudo apt-get install libsdl2-dev libsdl2-ttf-dev`. For RPM-based distributions of Linux, you can obtain it by running `sudo yum install SDL2-devel SDL2_ttf-devel`. You can easily look up install instructions for other distributions.

The default compiler is `GCC`. The minimal required version is `C++11`. You can also use `clang`, in which case you need to replace the first line in `makefile`, which is currently `CC=g++`, with `CC=clang++`.
If your compiler doesn't support `C++11`, you will need to upgrade. If your compiler supports `C++11`, but not by default, you can edit the `CFLAGS` line in `makefile` by adding a `std=c++11` flag.

Currently, the game has only been tested to work on Linux. `SDL 2` is cross-platform, so the game should also be able to work on other platforms with some tweaks. There will be more information on this in a future update.

## Demo ##

Check the screenshots in the `demo` folder!

## Font ##

The font used in the game, Roboto Mono, was designed by Christian Robertson and downloaded from here: https://fonts.google.com/specimen/Roboto+Mono. The copy of the license (`LICENSE.txt`) is included in the `res/font` folder.

## Older versions ##

Versions prior to v2.0 were console-based and used the `ncurses` library. These versions are still available for download as releases. The latest such release is [v1.2].

[v1.2]: https://github.com/darkwood101/snake_game/releases/tag/v1.2
