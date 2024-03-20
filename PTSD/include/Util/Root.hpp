#ifndef UTIL_ROOT_HPP
#define UTIL_ROOT_HPP

#include <memory>
#include <vector>

#include "Util/GameObject.hpp"

class App;

namespace Util {
class Root final {
public:
    /**
     * @brief Parameterized constructor.
     *`
     *
     * @param children The GameObject needing to be managed by the root.
     */
    Root(const std::vector<std::weak_ptr<GameObject>> children={});

    /**
     * @brief Add a child to the root.
     *
     * @param child The GameObject needing to be managed by the root.
     */
    void AddChild(const std::weak_ptr<GameObject> child);

    /**
     * @brief Add children to the root.
     *
     * @param children The GameObjects needing to be managed by the root.
     */
    void AddChildren(const std::vector<std::shared_ptr<GameObject>> &children);

    /**
     * @brief Remove the child.
     *
     * @param child The GameObject being removed.
     */
    void RemoveChild(const std::weak_ptr<GameObject> child);

    /**
     * @brief Draw children according to their z-index.
     *
     * @note The user is not recommended to modify this function.
     */
    void Update();

private:
    std::vector<std::weak_ptr<GameObject>> m_Children;
};
} // namespace Util

#endif
