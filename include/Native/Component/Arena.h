#pragma once

#include <Native/Component/types.h>

template <typename T>
class ScoreboardTable
{
    uint8_t state[10]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    T values[10];

public:
    ScoreboardTable(T defaultValue, entityId arena){};
};
class ArenaComponent
{
    struct
    {
        uint8_t GUI = 0;
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
        uint8_t playersNedded = 0;
        uint8_t ticksUntilStart = 0;
    } state;
    struct Values
    {
        ArenaComponent *owner;

        uint32_t GUI = 2;
        float leftX = 0;
        float topY = 0;
        float rightX = 0;
        float bottomY = 0;
        uint8_t scoreboardAmount = 0;
        ScoreboardTable<std::string> scoreboardNames = ScoreboardTable<std::string>("", owner->entity);
        ScoreboardTable<uint32_t> scoreboardScores = ScoreboardTable<uint32_t>(0, owner->entity);
        ScoreboardTable<Color> scoreboardColors = ScoreboardTable<Color>(Color::ScoreboardBar, owner->entity);
        ScoreboardTable<std::string> scoreboardSuffixes = ScoreboardTable<std::string>("", owner->entity);
        ScoreboardTable<Tank> scoreboardTanks = ScoreboardTable<Tank>(Tank::Basic, owner->entity);
        float leaderX = 0;
        float leaderY = 0;
        uint32_t playersNeeded = 1;
        uint32_t ticksUntilStart = 250;

        Values(ArenaComponent *owner) : owner(owner) {}
    } values{this};

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::arena;
    std::vector<std::string> fields{"GUI", "leftX", "topY", "rightX", "bottomY", "scoreboardAmount", "scoreboardNames", "scoreboardScores", "scoreboardColors", "scoreboardSuffixes", "scoreboardTanks", "leaderX", "leaderY", "playersNeeded", "ticksUntilStart"};

    ArenaComponent(entityId entity);

    void wipe();

    uint32_t GUI();
    float leftX();
    float topY();
    float rightX();
    float bottomY();
    uint8_t scoreboardAmount();
    ScoreboardTable<std::string> *scoreboardNames();
    ScoreboardTable<uint32_t> *scoreboardScores();
    ScoreboardTable<Color> *scoreboardColors();
    ScoreboardTable<std::string> *scoreboardSuffixes();
    ScoreboardTable<Tank> *scoreboardTanks();
    float leaderX();
    float leaderY();
    uint32_t playersNeeded();
    uint32_t ticksUntilStart();

    void GUI(uint32_t GUI);
    void leftX(float leftX);
    void topY(float topY);
    void rightX(float rightY);
    void bottomY(float bottomY);
    void scoreboardAmount(uint8_t scoreboardAmount);
    void scoreboardNames(ScoreboardTable<std::string> *scoreboardNames);
    void scoreboardScores(ScoreboardTable<uint32_t> *scoreboardScores);
    void scoreboardColors(ScoreboardTable<Color> *scoreboardColors);
    void scoreboardSuffixes(ScoreboardTable<std::string> *scoreboardSuffixes);
    void scoreboardTanks(ScoreboardTable<Tank> *scoreboardTanks);
    void leaderX(float leaderX);
    void leaderY(float leaderY);
    void playersNeeded(uint32_t playersNeeded);
    void ticksUntilStart(uint32_t ticksUntilStart);
};
