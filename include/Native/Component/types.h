#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <Const/Enums.h>

enum class FieldGroupId
{
    relations = 0,
    unused0,
    barrel,
    physics,
    health,
    unused1,
    unused2,
    arena,
    name,
    camera,
    position,
    style,
    unused3,
    score,
    team
};

using entityId = int16_t;
