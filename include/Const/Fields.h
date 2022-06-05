#pragma once

#include <Native/Entity.h>

enum class EncodingType
{
    Vu,
    StringNT,
    EntityId,
    Float,
    Vi,
    Radians
};

enum class FieldId
{
    Y,
    X,
    Angle,
    Size,
    Player,
    Gui,
    Color,
    ScoreboardColors,
    KilledBy,
    PlayersNeeded,
    Sides,
    Mothership,
    Healthbar,
    ScoreboardTanks,
    RespawnLevel,
    LevelbarProgress,
    SpawnTick,
    AbsorbtionFactor,
    LeaderX,
    MaxHealth,
    StyleFlags,
    Unknown,
    TrapezoidalDir,
    Motion,
    ScoreboardNames,
    Scorebar,
    MothershipY,
    ScoreboardSuffixes,
    Nametag,
    MovementSpeed,
    LeaderY,
    BottomY,
    Team,
    Level,
    TeamColor,
    Fov,
    StatLimits,
    LeftX,
    ScoreboardScores,
    StatLevels,
    TankOverride,
    Tank,
    BorderThickness,
    DeathTick,
    Width,
    StatsAvailable,
    Shooting,
    LevelbarMax,
    Name,
    Owner,
    Health,
    CameraY,
    Opacity,
    ReloadTime,
    StatNames,
    CameraX,
    MothershipX,
    GuiUnknown,
    Parent,
    Zindex,
    Camera,
    RightX,
    PushFactor,
    ObjectFlags,
    ScoreboardAmount,
    TicksUntilStart,
    TopY,
    Score,

    kMaxFieldId
};

struct FieldDefinition
{
    FieldGroupId component;
    uint8_t id;
    EncodingType encodingType;
    uint8_t index;
    int32_t amount;
};

std::array<FieldDefinition, static_cast<size_t>(FieldId::kMaxFieldId)> &GetFieldList();