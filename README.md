# Snake Game

This is a remake of the classic snake game, written in C++ using the SDL library and with minimalistic geometric figures as graphics.

Once the program is run, the initial state of the game is displayed. The user can press `SPACE` to start the game. At any point, the user can press `Q` or close the window to exit the game. The snake is controlled by pressing the buttons `W`, `A`, `S`, and `D` on the keyboard, which correspond to directions up, left, down, and right, respectively. The goal is to eat as much food as possible. The game ends when the snake hits a wall or itself.

The speed of the snake increases after every 10 points, which increases the difficulty. The maximum speed is achieved after 50 points.

The source code is located in the `src` folder. The resources used by the game (textures and the font) are located in the `res` folder.


## Build ##

Download the files from this repository and open the terminal in the main directory. Type `make` and hit enter. If everything goes okay, you should see a message `Build successful!` displayed on the screen. Then, you can use `./snake_game` in the terminal, or double-click the executable to run the game. See **Dependencies** below for more on what you need to in order to compile the game.

The compilation stores object files in the `obj` folder, and dependencies in  the `.deps` folder. The executable is stored in the main directory.

To delete all object files, the executable, and the dependencies, run `make clean`.


## Dependencies ##

The game requires the `SDL 2` library to compile, as well as `SDL_ttf 2`. For Debian-based distributions of Linux, such as Ubuntu, you can obtain these by running the following command: `sudo apt-get install libsdl2-dev libsdl2-ttf-dev`. For RPM-based distributions of Linux, you can obtain it by running `sudo yum install SDL2-devel SDL2_ttf-devel`. You can easily look up install instructions for other distributions.

The default compiler is `GCC`. The minimal required version is `C++11`. You can also use `clang`, in which case you need to replace the first line in `makefile`, which is currently `CC=g++`, with `CC=clang++`.
If your compiler doesn't support `C++11`, you will need to upgrade. If your compiler supports `C++11`, but not by default, you can edit the `CFLAGS` line in `makefile` by adding a `std=c++11` flag.

Currently, the game has only been tested to work on Linux. `SDL 2` is cross-platform, so the game should also be able to work on other platforms with some tweaks to the `makefile`. There will be more information on this in a future update.


## Demo ##

Check the screenshots in the `demo` folder!


## Font ##

The font used in the game, [Roboto Mono], was designed by Christian Robertson. The copy of the original license (`LICENSE.txt`) is included in the `res/font` folder.


## Older versions ##

Versions prior to v2.0 were console-based and used the `ncurses` library. These versions are still available for download as releases. The latest such release is [v1.2].


[v1.2]: https://github.com/darkwood101/snake_game/releases/tag/v1.2
[Roboto Mono]: https://fonts.google.com/specimen/Roboto+Mono
