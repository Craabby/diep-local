#pragma once

#include <Native/Component/types.h>

class Entity;

class ScoreComponent
{
    struct
    {
        uint8_t score = 0;
    } state;
    struct
    {
        float score = 0;
    } netProperties;

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::score;

    ScoreComponent(Entity *entity);

    void Wipe();

    float Score();
    void Score(float score);
};
