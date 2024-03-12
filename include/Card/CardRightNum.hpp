#ifndef CARDRIGHTNUM_HPP
#define CARDRIGHTNUM_HPP
#include "Card/Garden.hpp"
#include "pch.hpp"

namespace card {
	class CardRightNum :public Util::GameObject {
	private:
	public:
		CardRightNum() { m_Moveable = true; }
		void Update() override;
	};
}
#endif // !CARDRIGHTNUM_HPP
