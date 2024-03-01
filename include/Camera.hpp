#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"
class Camera : public Util::GameObject {
private:


public:
    Camera();
    ~Camera() override = default;
    void MoveCamera(float x, float y, float z);
    void Update();
};

#endif // !CAMERA_HPP
