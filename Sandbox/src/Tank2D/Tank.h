#pragma once

#include <glm/glm.hpp>

class Tank
{
public:
    Tank();
    ~Tank();

    void Update(float elapsedTime);
    void Render();

public:
    glm::vec2 pos;
    glm::vec2 vel;
    float rotation;
    float barrelRotation;
};
