#pragma once

#include <Native/Component/types.h>

class TeamComponent
{
    struct
    {
        uint8_t teamColor;
        uint8_t mothershipX;
        uint8_t mothershipY;
        uint8_t mothership;
    } state;
    struct
    {
        ColorId teamColor;
        float mothershipX;
        float mothershipY;
        uint32_t mothership;
    } values;

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::team;
    std::vector<std::string> fields{"teamColor", "mothershipX", "mothershipY", "mothership"};

    TeamComponent(entityId entity);

    void Wipe();
};
