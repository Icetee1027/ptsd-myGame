#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Util/Root.hpp"

#include "Cat.hpp"
#include "Giraffe.hpp"
#include "GiraffeText.hpp"
#include "Camera.hpp"
#include "Mouse.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;
    std::shared_ptr<Giraffe> m_Giraffe = std::make_shared<Giraffe>();
    //    std::shared_ptr<GiraffeText> m_GiraffeText =
    //    std::make_shared<GiraffeText>();
    std::shared_ptr<Camera> m_Camera = std::make_shared<Camera>();
  
    std::shared_ptr<Mouse> m_Mouse = std::make_shared<Mouse>();
    Util::Root m_Root;
};

#endif
