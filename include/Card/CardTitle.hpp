#ifndef CARDTITLE_HPP
#define CARDTITLE_HPP

#include "pch.hpp"
#include "Util/GameObject.hpp"
namespace card {
	class CardTitle :public Util::GameObject {
	private:
	public:
		CardTitle() { m_Moveable = true; }
		void Update() override;

	};
}
#endif // !CARDTITLE_HPP
