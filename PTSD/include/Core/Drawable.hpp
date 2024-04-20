#ifndef CORE_DRAWABLE_HPP
#define CORE_DRAWABLE_HPP

#include "pch.hpp" // IWYU pragma: export

#include <functional>

#include "Core/Program.hpp"
#include "Core/UniformBuffer.hpp"
#include "Core/VertexArray.hpp"

#include "Texture.hpp"
#include "Util/Transform.hpp"
#include "config.hpp"
namespace Core {
struct Matrices {
    glm::mat4 m_Model;
    glm::mat4 m_Projection;
};
class Drawable {
protected:
    static glm::vec3 m_View;

public:
    enum class World {
        OBJECT,
        UI
    };
    virtual ~Drawable() = default;
    virtual void Draw(const Util::Transform &transform, const float zIndex) = 0;
    virtual glm::vec2 GetSize() const = 0;
    static void SetView(const glm::vec3 &camera);
    static glm::vec3 GetView();
    virtual void SetWorld(const World world) { m_world = world; }

protected:
    World m_world = World::OBJECT;
};

} // namespace Core


#endif
