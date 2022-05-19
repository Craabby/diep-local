#pragma once

#include <Native/Component/types.h>

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
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::score;
    std::vector<std::string> fields{"score"};

    ScoreComponent(entityId entity);

    void Wipe();

    float Score();
    void Score(float score);
};
