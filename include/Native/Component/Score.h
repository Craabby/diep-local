#pragma once

#include <Native/Component/types.h>
#include <Const/Fields.h>

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
    static inline std::array<FieldId, 1> fields = {FieldId::Score};

    ScoreComponent(Entity *entity);

    void Wipe();
    std::vector<FieldId> FindUpdates();

    float Score();
    void Score(float score);
};
