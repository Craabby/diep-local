#pragma once

#include <Native/Component/types.h>
#include <Const/Fields.h>

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
        ColorId teamColor = ColorId::EnemyTank;
        float mothershipX = 0;
        float mothershipY = 0;
        uint32_t mothership = 0;
    } netProperties;

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::team;
    static inline std::array<FieldId, 4> fields = {FieldId::TeamColor, FieldId::MothershipX, FieldId::MothershipY, FieldId::Mothership};

    TeamComponent(Entity *entity);

    void Wipe();
    std::vector<FieldId> FindUpdates();

    uint32_t Mothership();
    float MothershipX();
    float MothershipY();
    ColorId TeamColor();
};
