#ifndef FOOD_H
#define FOOD_H

#include <utility>

class Food {
private:
	std::pair<unsigned, unsigned> food_pos_;
	const char* food_char_ = "$";

public:
	std::pair<unsigned, unsigned> get_food_pos();
	bool is_food(unsigned y, unsigned x);
	void generate();
	void print();
};

#endif