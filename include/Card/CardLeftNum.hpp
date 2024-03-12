#ifndef CARDLEFTNUM_HPP
#define CARDLEFTNUM_HPP
#include "pch.hpp"
#include "Util/GameObject.hpp"
namespace card {
	class CardLeftNum : public Util::GameObject {
	private:
	public:
		CardLeftNum() { m_Moveable = true; }
		void Update() override;

	};
}

#endif