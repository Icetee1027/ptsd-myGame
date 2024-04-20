#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"
class Camera : public Util::GameObject {
public:
    Camera();
    ~Camera() override = default;
    void MoveCamera(float x, float y, float z);
    void Update() override;
    void ClickDown() override;
    void ClickUp() override;
    static void CameraShake();
    static glm::vec3 ShakeUpdate();

private:
    static double m_time; 
};


#endif // !CAMERA_HPP
