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
    void SetText(std::string path,int t,std::string str, glm::vec3 c);
    void Update() override;
    void ClickDown() override;
    void ClickUp() override;
private:
    
};

#endif
