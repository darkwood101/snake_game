# Change log

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
[v1.1]: https://github.com/darkwood101/snake_game/releases/tag/v1.1
