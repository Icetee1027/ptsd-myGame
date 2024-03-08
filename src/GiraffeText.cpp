#include "GiraffeText.hpp"

#include "Util/Color.hpp"
#include "Util/Time.hpp"


void GiraffeText::Start() {
    m_Drawable = std::make_shared<Util::Text>(RESOURCE_DIR"/fonts/Inter.ttf", 75, "PAUSE",
                                          Util::Color::FromRGB(255, 225, 255));
    m_Drawable->SetWorld(Core::Drawable::World::UI);
    m_Visible = false;
}

void GiraffeText::Update() {

}
void GiraffeText::ClickDown() {

}
void GiraffeText::ClickUp() {

}
