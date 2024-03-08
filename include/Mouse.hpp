#ifndef MOUSE_HPP
#define MOUSE_HPP
 
#include "Util/GameObject.hpp"

class Mouse : public Util::GameObject {
private:
    std::shared_ptr<Util::GameObject> m_BindObject = nullptr;
    glm::vec2 m_Distance;
    glm::vec2 m_LastPosition;

public:
    void Start();
    void Update();
    void ClickDown() override;
    void ClickUp() override;
    void ObjectBind(std::shared_ptr<Util::GameObject> Object);
    void ObjectUmBind();
    void ObjectDrag();

};

#endif // !MOUSE_HPP
