#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <mutex>
#include <utility>

class Snake {
private:
	std::vector<std::pair<unsigned, unsigned>> snake_pos_;
	const unsigned init_length_ = 8;
	const unsigned init_y_ = 20 / 2;
	const unsigned init_x_ = (50 / 2) - (init_length_ / 2);
	const char* head_char_ = "o";
	const char* body_char_ = "x";
	int direction = up;
	std::pair<unsigned, unsigned> head_;
	std::pair<unsigned, unsigned> tail_;

public:
	Snake();
	void draw();
	bool is_in_snake(std::pair<unsigned, unsigned> coords);
	bool is_snake_head(std::pair<unsigned, unsigned> coords);
	void move(bool grow);
	void set_direction(int dir);
	std::pair<unsigned, unsigned> get_head();	
	static constexpr int up = 0;
	static constexpr int down = 3;
	static constexpr int left = 1;
	static constexpr int right = 2;
	std::mutex direction_mutex;
};

#endif