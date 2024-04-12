#include "Board.hpp"
Board::Board(){
	m_Drawable = std::make_shared<Util::Image>(RESOURCE_DIR"/sprites/Board.png");
	m_Transform.scale = {4,15};
	m_Transform.translation = { -1400, 0, -2 };

	auto a = std::make_shared<BoardCild>();
	Util::Transform  transform;
	transform.scale = { 4,15 };
	transform.translation = { 1400,0,-2 };
	a->SetDrawable(m_Drawable);
	a->SetTransform(transform);

	m_Children.push_back(a);


	auto b= std::make_shared<BoardCild>();
	transform.scale = { 28*25 ,0.16 };
	transform.translation = { 0,750,-2 };
	b->SetDrawable(m_Drawable);
	b->SetTransform(transform);

	m_Children.push_back(b);

	auto c = std::make_shared<BoardCild>();
	transform.scale = { 28 * 25 ,0.16 };
	transform.translation = { 0,-750,-2 };
	c->SetDrawable(m_Drawable);
	c->SetTransform(transform);

	m_Children.push_back(c);
}