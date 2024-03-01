#include "Util/TransformUtils.hpp"
#include "Util/Logger.hpp"
#include "config.hpp"

namespace Util {
Core::Matrices ConvertToUniformBufferData(const Util::Transform &transform,
                                          const glm::vec2 &size,
                                          const float zIndex, glm::vec3 m_View,
                                          Core::Drawable::World state) {
    constexpr glm::mat4 eye(1.F);
    struct glm::mat<4, 4, glm::f32, glm::packed_highp> view;
    struct glm::mat<4, 4, glm::f32, glm::packed_highp> projection;

    if (state == Core::Drawable::World::OBJECT) {
        view = glm::translate(eye, m_View);
        projection =
            glm::perspective(glm::radians(90.0f),
                                static_cast<float>(WINDOW_WIDTH) /
                                    static_cast<float>(WINDOW_HEIGHT),
                                -200.0f - m_View.z, 100.0f - m_View.z);
        
    } else {
        projection = glm::ortho<float>(0.0F, 1.0F, 0.0F, 1.0F, -100.0f, 100.0f);
        view =
            glm::scale(eye,
                        {1.F / WINDOW_WIDTH, 1.F / WINDOW_HEIGHT, 1.F}) *
            glm::translate(eye, {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0});
        
    }
    auto model =
        glm::translate(eye, {transform.translation.x, transform.translation.y,
                             transform.translation.z + zIndex / 50}) *
        glm::rotate(eye, transform.rotation, glm::vec3(0, 0, 1)) *
        glm::scale(eye, {transform.scale * size, 1});

    Core::Matrices data = {
        model,
        projection * view,
    };
    return data;

    // TODO: TRS comment
    
}

} // namespace Util
