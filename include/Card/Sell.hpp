#ifndef SELL_HPP
#define SELL_HPP
#include "pch.hpp"
#include "Card/Card.hpp"
namespace card {
class Sell :public Card{
private:
	int m_BasicPrice;
	glm::vec3 m_dic;
public:
	bool m_StaticUpdate = false;
	Sell(Type type, std::string name, unsigned int id, const std::vector<std::shared_ptr<Util::SFX>> sfxs, const std::shared_ptr<Util::Image> image, const bool iconcolor);
	virtual ~Sell() override = default;
	void CreatCoinStack();
	
	virtual bool CanHaveCard(std::shared_ptr<Card> otherCard) override;
	void UpdateCard() override;
};
}
#endif // !SELL_HPP
