# Change log


## v2.0 - 25-Dec-2020

### Changed
- The look has been completely changed! Instead of using the console as a way of drawing the state of the game, the game has been switched to use the `SDL 2` library. Now, instead of basic character output, the game is rendered using simple textures and geometric shapes. This also helps the game be portable across multiple platforms, although it's currently much easier to build the game on Linux than on Windows. There will be more details about cross-platform portability in a future update.
- Previously, the snake used to grow as soon as it hit the food. This has been changed, and the growing is now delayed, so that the snake grows when it moves after eating the food, which makes more sense.

### Added 
- A starting screen has been added, which gives the user a chance to read the instructions before the snake starts moving (issue [#5]).


## [v1.2] - 14-Dec-2020

### Fixed
- In the previous version, the entire board was re-drawn on each iteration. This has been fixed and now only the objects that change are re-drawn (issue [#2]).
- There was a bug which caused the snake to become unresponsive if the player pressed and held the same direction key for a longer time. This has been fixed (issue [#3]).


## [v1.1] - 13-Dec-2020

### Changed

- The snake now dies if you try to reverse direction.

### Fixed

- There was a bug which caused the snake to die if you pressed different keys rapidly. This has been fixed.
- The use of `ncurses` library caused some rare issues with the terminal display. This is due to the lack of `ncurses` support for multithreading applications. The game has been switched to a single thread.

[#2]: https://github.com/darkwood101/snake_game/issues/2
[#3]: https://github.com/darkwood101/snake_game/issues/3
[#5]: https://github.com/darkwood101/snake_game/issues/5
[v1.1]: https://github.com/darkwood101/snake_game/releases/tag/v1.1
[v1.2]: https://github.com/darkwood101/snake_game/releases/tag/v1.2
