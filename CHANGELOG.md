# Change log

## [v1.1] - 13-Dec-2020

### Changed

- The snake now dies if you try to reverse direction.

### Fixed

- There was a bug which caused the snake to die if you pressed different keys rapidly. This has been fixed.
- The use of `ncurses` library caused some rare issues with the terminal display. This is due to the lack of `ncurses` support for multithreading applications. The game has been switched to a single thread.
