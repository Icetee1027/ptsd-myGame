#include "Util/Time.hpp"
#include "Camera.hpp"
#include "Core/Drawable.hpp"
#include "Util/Time.hpp"
#include <random>
Camera::Camera() {
    m_Moveable = true;
    m_Transform.translation = { 0,0,-150 };
}
void Camera::MoveCamera(float x, float y, float z) {
    m_Transform.translation -= glm::vec3(x, y, -z)* float(Util::Time::GetDeltaTime()*240);
}
void Camera::Update() {
    auto shake_offset = ShakeUpdate();
    Core::Drawable::SetView(m_Transform.translation + shake_offset);
}
double rand_normal(double mean, double stddev) {
    static std::default_random_engine generator(Util::Time::GetElapsedTimeMs());
    std::normal_distribution<double> distribution(mean, stddev);
    return distribution(generator);
}

glm::vec3 Camera::ShakeUpdate() {
    if (m_time >= 0.15) {
        return glm::vec3();
    }
    
    m_time += Util::Time::GetDeltaTime();
    
       
    double shake_offset_x = rand_normal(0.0, 4);
    double shake_offset_y = rand_normal(0.0, 3);
    double shake_offset_z = rand_normal(0.0, 5);
    //LOG_DEBUG("{}:{}:{}", shake_offset_x, shake_offset_y, shake_offset_z);
        
    return glm::vec3(shake_offset_x, shake_offset_y, shake_offset_z);

    
}
void Camera::ClickDown() {

}
void Camera::ClickUp() {

}
void Camera::CameraShake() { m_time = 0; }
double Camera::m_time = 1;