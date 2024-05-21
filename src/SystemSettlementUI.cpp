#include "SystemSettlementUI.hpp"
#include "Util/Time.hpp"
#include "Background.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"

SystemSettlementUI::SystemSettlementUI() {
	m_Transform.scale = { 0.5,0.5 };
	m_Transform.translation = { 430,333,-1 };
	m_Drawable = std::make_shared<Util::Image>(RESOURCE_DIR"/sprites/t123.png");
	m_Drawable->SetWorld(Core::Drawable::World::UI);
	m_TimeProgressBar[0]->SetImage(RESOURCE_DIR"/sprites/BarBackground.png");
	m_TimeProgressBar[1]->SetImage(RESOURCE_DIR"/sprites/ProgressBar.png");
	m_TimeProgressBar[0]->SetMoveable(1);
	m_TimeProgressBar[1]->SetMoveable(1);
	m_TimeProgressBar[0]->SetScaledSize(glm::vec2(0.7, 1.1));
	m_TimeProgressBar[1]->SetScaledSize(glm::vec2(0.7, 1.2));
	m_TimeProgressBar[0]->SetTranslation(glm::vec3(562, 333, -1));
	m_TimeProgressBar[1]->SetTranslation(glm::vec3(562, 333, -1));
	m_TimeProgressBar[0]->SetZIndex(2);
	m_TimeProgressBar[1]->SetZIndex(1);
	m_Children.push_back(m_TimeProgressBar[0]);
	m_Children.push_back(m_TimeProgressBar[1]);

	m_GiraffeText[0]->InitText(RESOURCE_DIR"/fonts/Inter.ttf", 20,
		std::to_string(AmountfoodCurrentAvailable)+"/"+ std::to_string(AmountFoodRequired),//
		glm::vec3(0, 0, 0));
	m_GiraffeText[0]->SetTranslation(glm::vec3(290, 333, -1));
	m_GiraffeText[0]->SetZIndex(1);
	m_Children.push_back(m_GiraffeText[0]);

	m_GiraffeText[1]->InitText(RESOURCE_DIR"/fonts/Inter.ttf", 20,
		std::to_string(CurrentStorageCapacity) + "/" + std::to_string(MaxStorageCapacity),//
		glm::vec3(0, 0, 0));
	m_GiraffeText[1]->SetTranslation(glm::vec3(380, 333, -1));
	m_GiraffeText[1]->SetZIndex(1);
	m_Children.push_back(m_GiraffeText[1]);

	m_GiraffeText[2]->InitText(RESOURCE_DIR"/fonts/Inter.ttf", 18,
		"moon " + std::to_string(MoonCount),//
		glm::vec3(0, 0, 0));
	m_GiraffeText[2]->SetTranslation(glm::vec3(465, 333, -1));
	m_GiraffeText[2]->SetZIndex(1);
	m_Children.push_back(m_GiraffeText[2]);
}
void SystemSettlementUI::Update() {
	if (m_TimeCount >= m_Time) {
		SystemSettlementUIUpdata();
	}
	else {
		m_TimeCount += Util::Time::GetDeltaTime();
	}
	if (m_MoonTimeCount >= m_MoonTime) {
		Settlement = 1;
	}
	else {
		m_TimeProgressBar[0]->SetScaledSize(glm::vec2(0.7*(m_MoonTimeCount/ m_MoonTime),1.1));
		m_TimeProgressBar[0]->SetTranslation(glm::vec3(562-(119-m_TimeProgressBar[0]->GetScaledSize().x)/2, 333, -1));
		m_MoonTimeCount += Util::Time::GetDeltaTime()* (Util::Input::IsKeyPressed(Util::Keycode::X) ? 10 : 1);
	}
	for (auto& a : m_Children) {
		a->Update();
	}
}
void SystemSettlementUI::SystemSettlementUIUpdata() {
	if (IsSystemUpdta == 1) {
		if (MaxStorageCapacity <CurrentStorageCapacity) {
			m_GiraffeText[1]->SetColor(glm::vec3(255, 0, 0));
		}
		else {
			m_GiraffeText[1]->SetColor(glm::vec3(0, 0, 0));
		}
		if (AmountFoodRequired >AmountfoodCurrentAvailable) {
			m_GiraffeText[0]->SetColor(glm::vec3(255, 0, 0));
		}
		else {
			m_GiraffeText[0]->SetColor(glm::vec3(0, 0, 0));
		}
		m_GiraffeText[0]->SetText(std::to_string(AmountfoodCurrentAvailable) + "/" + std::to_string(AmountFoodRequired));
		m_GiraffeText[1]->SetText(std::to_string(CurrentStorageCapacity) + "/" + std::to_string(MaxStorageCapacity));
		m_GiraffeText[2]->SetText("moon " + std::to_string(MoonCount));
		MaxStorageCapacity = 20;
		CurrentStorageCapacity = 0;
		AmountFoodRequired = 0;
		AmountfoodCurrentAvailable = 0;
		m_TimeCount = 0;
		IsSystemUpdta = 0;
	}
	else {
		if (IsSystemUpdta == 0) {
			IsSystemUpdta = 1;
		}
	}
}
int SystemSettlementUI::MaxStorageCapacity=20;
int SystemSettlementUI::CurrentStorageCapacity=0;
int SystemSettlementUI::AmountFoodRequired=0;
int SystemSettlementUI::AmountfoodCurrentAvailable=0;
float SystemSettlementUI::m_TimeCount = 0;
bool SystemSettlementUI::IsSystemUpdta=0;
int SystemSettlementUI::MoonCount=1;