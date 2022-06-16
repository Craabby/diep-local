#pragma once

#include <cstdint>

#include <Physics/Vector.h>

struct UserInput
{
    uint32_t flags;
    Vector<int32_t> mouse = Vector<int32_t>(0, 0);
};
