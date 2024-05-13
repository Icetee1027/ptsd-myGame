#ifndef GIRAFFE_TEXT_HPP
#define GIRAFFE_TEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include "Util/Color.hpp"

class GiraffeText : public Util::GameObject {
public:
    GiraffeText() = default;

   /* GiraffeText(std::string font, const int size)
        : m_Font(std::move(font)),
          m_Size(size) {}*/

    ~GiraffeText() override = default;
   
    void Start();
    void SetScale(glm::vec2 s) { m_Transform.scale = s; }
    void InitText(std::string path,int t,std::string str, glm::vec3 c=glm::vec3());
    void SetText(std::string str) {
        auto a = std::dynamic_pointer_cast<Util::Text>(m_Drawable);
        if (a)a->SetText(str);
        else LOG_ERROR("GiraffeText->SetText() ERROR!!");
    }
    void Update() override;
    void ClickDown() override;
    void ClickUp() override;
    void BluePrintINIT();
    void AddBluePrint(std::string str);
private:
    std::vector<std::string> ShowBluePrint = {};
};

#endif
