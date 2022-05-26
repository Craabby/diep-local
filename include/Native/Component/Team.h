#pragma once

#include <Native/Component/types.h>

class Entity;

class TeamComponent
{
    struct
    {
        uint8_t teamColor = 0;
        uint8_t mothershipX = 0;
        uint8_t mothershipY = 0;
        uint8_t mothership = 0;
    } state;
    struct
    {
        ColorId teamColor;
        float mothershipX;
        float mothershipY;
        uint32_t mothership;
    } netProperties;

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::team;

    TeamComponent(Entity *entity);

    void Wipe();
};
