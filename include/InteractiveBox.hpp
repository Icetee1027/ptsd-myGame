#ifndef INTERACTIVEBOX_HPP
#define INTERACTIVEBOX_HPP
#include "Util/GameObject.hpp"
#include "GiraffeText.hpp"
#include "pch.hpp"
class InteractiveBox :public Util::GameObject {
private:
	std::vector<std::shared_ptr<GiraffeText>> m_GiraffeText = { std::make_shared< GiraffeText>(),std::make_shared< GiraffeText>() };
	std::vector<glm::vec3> m_vec3s = {};

public:
	InteractiveBox();
	~InteractiveBox() = default;
	void Update() override;
	void SetText(int a,std::string str=" ");
	void SetVisible(const bool visible) override;

};






#endif // !INTERACTIVETEXT_HPP

