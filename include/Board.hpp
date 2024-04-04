#ifndef  BOARD_HPP
#define BOARD_HPP
#include "pch.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
class Board :public Util::GameObject {
private:
	

public:
	Board();
	~Board() override = default;
};
class BoardCild : public Util::GameObject {
private:
public:

};
#endif // ! BOARD_HPP
