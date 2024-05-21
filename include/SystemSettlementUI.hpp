#ifndef SYSTEMSETTLEMENTUI_HPP
#define SYSTEMSETTLEMENTUI_HPP
#include "Util/GameObject.hpp"
#include "Background.hpp"
#include "GiraffeText.hpp"
class SystemSettlementUI : public Util::GameObject {
private:
	std::vector<std::shared_ptr<Background>> m_TimeProgressBar = { std::make_shared<Background>(),std::make_shared<Background>() };
	std::vector<std::shared_ptr<GiraffeText>> m_GiraffeText = { std::make_shared<GiraffeText>(),std::make_shared<GiraffeText>(), std::make_shared<GiraffeText>(), };
	float m_Time = 0.5;
	const float m_MoonTime = 150;
public:
	bool Settlement = 0;
	float m_MoonTimeCount = 0;
	static int MoonCount;
	static int MaxStorageCapacity;
	static int CurrentStorageCapacity;
	static int AmountFoodRequired;
	static int AmountfoodCurrentAvailable;
	static float  m_TimeCount;
	static bool IsSystemUpdta;
	bool IsSettlement() { return Settlement; };
	SystemSettlementUI();
	~SystemSettlementUI() = default;
	void SystemSettlementUIUpdata();
	void Update() override;



};

#endif // !1
