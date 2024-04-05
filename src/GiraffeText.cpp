#include "GiraffeText.hpp"


#include "Util/Time.hpp"


void GiraffeText::Start() {
   
}
void GiraffeText::SetText(std::string path, int t,std::string str, glm::vec3 c) {
    m_Moveable = true;
    m_Drawable = std::make_shared<Util::Text>(path, t, str,
        Util::Color::FromRGB(c.x, c.y, c.z));

    m_Drawable->SetWorld(Core::Drawable::World::UI);
    m_Visible = true;
}
void GiraffeText::Update() {

}
void GiraffeText::ClickDown() {
  
}
void GiraffeText::ClickUp() {

}
