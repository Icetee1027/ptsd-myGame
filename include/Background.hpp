#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP
#include "Util/GameObject.hpp"
#include "Core/Drawable.hpp"
#include "Util/Image.hpp"
class Background :public Util::GameObject {
private:
public:
	Background() {}
	~Background() = default;
	void SetImage(std::string str) {
		SetDrawable(
			std::make_shared<Util::Image>(str));
		m_Drawable->SetWorld(Core::Drawable::World::UI);
	}
};
#endif // !BACKGROUND_HPP
