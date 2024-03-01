#ifndef GIRAFFE_TEXT_HPP
#define GIRAFFE_TEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class GiraffeText : public Util::GameObject {
public:
    GiraffeText() = default;

   /* GiraffeText(std::string font, const int size)
        : m_Font(std::move(font)),
          m_Size(size) {}*/

    ~GiraffeText() override = default;

    void Start();

    void Update();

private:
    
};

#endif
