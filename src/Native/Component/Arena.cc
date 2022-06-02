#include <Native/Component/Arena.h>

#include <Native/Entity.h>

ArenaComponent::ArenaComponent(Entity *entity)
    : entity(entity)
{
}

void ArenaComponent::Wipe()
{
    state.gui = 0;
    state.leftX = 0;
    state.topY = 0;
    state.rightX = 0;
    state.bottomY = 0;
    state.scoreboardAmount = 0;
    state.scoreboardNames = 0;
    state.scoreboardScores = 0;
    state.scoreboardColors = 0;
    state.scoreboardSuffixes = 0;
    state.scoreboardTanks = 0;
    state.leaderX = 0;
    state.leaderY = 0;
    state.playersNedded = 0;
    state.ticksUntilStart = 0;
}


uint32_t ArenaComponent::Gui()
{
    return netProperties.gui;
}

float ArenaComponent::LeftX()
{
    return netProperties.leftX;
}

float ArenaComponent::TopY()
{
    return netProperties.topY;
}

float ArenaComponent::RightX()
{
    return netProperties.rightX;
}

float ArenaComponent::BottomY()
{
    return netProperties.bottomY;
}

uint8_t ArenaComponent::ScoreboardAmount()
{
    return netProperties.scoreboardAmount;
}

float ArenaComponent::LeaderX()
{
    return netProperties.leaderX;
}

float ArenaComponent::LeaderY()
{
    return netProperties.leaderY;
}

uint32_t ArenaComponent::PlayersNeeded()
{
    return netProperties.playersNeeded;
}

uint32_t ArenaComponent::TicksUntilStart()
{
    return netProperties.ticksUntilStart;
}

ScoreboardTable<std::string> *ArenaComponent::ScoreboardNames()
{
    return &netProperties.scoreboardNames;
}
ScoreboardTable<uint32_t> *ArenaComponent::ScoreboardScores()
{
    return &netProperties.scoreboardScores;
}
ScoreboardTable<ColorId> *ArenaComponent::ScoreboardColors()
{
    return &netProperties.scoreboardColors;
}
ScoreboardTable<std::string> *ArenaComponent::ScoreboardSuffixes()
{
    return &netProperties.scoreboardSuffixes;
}
ScoreboardTable<TankId> *ArenaComponent::ScoreboardTanks()
{
    return &netProperties.scoreboardTanks;
}
