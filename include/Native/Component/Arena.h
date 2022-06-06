#pragma once

#include <Native/Component/types.h>
#include <Const/Fields.h>

class Entity;

template <typename T>
class ScoreboardTable
{
    uint8_t state[10]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    T values[10];

public:
    ScoreboardTable(T defaultValue, Entity *arena){};

    const T &At(uint8_t x) const
    {
        return values[x];
    }
};
class ArenaComponent
{
    struct
    {
        uint8_t gui = 0;
        uint8_t leftX = 0;
        uint8_t topY = 0;
        uint8_t rightX = 0;
        uint8_t bottomY = 0;
        uint8_t scoreboardAmount = 0;
        uint8_t scoreboardNames = 0;
        uint8_t scoreboardScores = 0;
        uint8_t scoreboardColors = 0;
        uint8_t scoreboardSuffixes = 0;
        uint8_t scoreboardTanks = 0;
        uint8_t leaderX = 0;
        uint8_t leaderY = 0;
        uint8_t playersNeeded = 0;
        uint8_t ticksUntilStart = 0;
    } state;
    struct Values
    {
        ArenaComponent *owner;

        uint32_t gui = 2;
        float leftX = 0;
        float topY = 0;
        float rightX = 0;
        float bottomY = 0;
        uint8_t scoreboardAmount = 0;
        ScoreboardTable<std::string> scoreboardNames = ScoreboardTable<std::string>("", owner->entity);
        ScoreboardTable<uint32_t> scoreboardScores = ScoreboardTable<uint32_t>(0, owner->entity);
        ScoreboardTable<ColorId> scoreboardColors = ScoreboardTable<ColorId>(ColorId::ScoreboardBar, owner->entity);
        ScoreboardTable<std::string> scoreboardSuffixes = ScoreboardTable<std::string>("", owner->entity);
        ScoreboardTable<TankId> scoreboardTanks = ScoreboardTable<TankId>(TankId::Basic, owner->entity);
        float leaderX = 0;
        float leaderY = 0;
        uint32_t playersNeeded = 1;
        uint32_t ticksUntilStart = 250;

        Values(ArenaComponent *owner) : owner(owner) {}
    } netProperties{this};

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::arena;
    static inline std::array<FieldId, 15> fields = {FieldId::Gui, FieldId::LeftX, FieldId::TopY, FieldId::RightX, FieldId::BottomY, FieldId::ScoreboardAmount, FieldId::ScoreboardNames, FieldId::ScoreboardScores, FieldId::ScoreboardColors, FieldId::ScoreboardSuffixes, FieldId::ScoreboardTanks, FieldId::LeaderX, FieldId::LeaderY, FieldId::PlayersNeeded, FieldId::TicksUntilStart};

    ArenaComponent(Entity *entity);

    void Wipe();
    std::vector<FieldId> FindUpdates();

    uint32_t Gui();
    float LeftX();
    float TopY();
    float RightX();
    float BottomY();
    uint8_t ScoreboardAmount();
    float LeaderX();
    float LeaderY();
    uint32_t PlayersNeeded();
    uint32_t TicksUntilStart();
    ScoreboardTable<std::string> *ScoreboardNames();
    ScoreboardTable<uint32_t> *ScoreboardScores();
    ScoreboardTable<ColorId> *ScoreboardColors();
    ScoreboardTable<std::string> *ScoreboardSuffixes();
    ScoreboardTable<TankId> *ScoreboardTanks();

    void Gui(uint32_t GUI);
    void LeftX(float leftX);
    void TopY(float topY);
    void RightX(float rightY);
    void BottomY(float bottomY);
    void ScoreboardAmount(uint8_t scoreboardAmount);
    void ScoreboardNames(ScoreboardTable<std::string> *scoreboardNames);
    void ScoreboardScores(ScoreboardTable<uint32_t> *scoreboardScores);
    void ScoreboardColors(ScoreboardTable<ColorId> *scoreboardColors);
    void ScoreboardSuffixes(ScoreboardTable<std::string> *scoreboardSuffixes);
    void ScoreboardTanks(ScoreboardTable<TankId> *scoreboardTanks);
    void LeaderX(float leaderX);
    void LeaderY(float leaderY);
    void PlayersNeeded(uint32_t playersNeeded);
    void TicksUntilStart(uint32_t ticksUntilStart);
};
