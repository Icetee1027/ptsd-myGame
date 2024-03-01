#ifndef MOUSE_HPP
#define MOUSE_HPP
 
#include "Util/GameObject.hpp"

class Mouse : public Util::GameObject {
private:
    std::shared_ptr<Util::GameObject> m_BindObject = nullptr;

public:
    void Start();
    void Update();
    void ClickDown();
    void ClickUp();
    void ObjectBind(std::shared_ptr<Util::GameObject> &Object);
    void ObjectUmBind();

};

#endif // !MOUSE_HPP
