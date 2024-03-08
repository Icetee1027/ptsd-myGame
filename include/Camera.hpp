#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"
class Camera : public Util::GameObject {
public:
    Camera();
    ~Camera() override = default;
    void MoveCamera(float x, float y, float z);
    void Update();
    void ClickDown() override;
    void ClickUp() override;
private:
    glm::vec3 m_CameraPosition;
};


#endif // !CAMERA_HPP
