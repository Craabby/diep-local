#pragma once

#include <cstdint>

#include <Physics/Vector.h>

struct UserInput
{
    uint32_t flags;
    Vector<float> force = Vector<float>(0, 0);
    Vector<float> mouse = Vector<float>(0, 0);
};
