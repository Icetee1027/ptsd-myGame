#ifndef MOUSE_HPP
#define MOUSE_HPP
 
#include "Util/GameObject.hpp"

class Mouse : public Util::GameObject {
private:
    std::shared_ptr<Util::GameObject> m_BindObject = nullptr;
    glm::vec2 m_Distance;
    glm::vec2 m_Offset;
    glm::vec2 m_LastPosition;
    int m_CardOldX;

public:
    void Start();

    void Update() override;
    void ClickDown() override;
    void ClickUp() override;
    void ObjectBind(std::shared_ptr<Util::GameObject> Object);
    void ObjectUmBind();
    void ObjectDrag();
    bool HasObjectBind() const { return m_BindObject != nullptr; }
    int GetCardOldX() { return m_CardOldX; }
    std::shared_ptr<Util::GameObject> GetBindObject() { return m_BindObject; }
    glm::vec2 GetMousePosition(const std::shared_ptr<Util::GameObject>& object);
    glm::vec2 GetMousePosition(int a);
};

#endif // !MOUSE_HPP
