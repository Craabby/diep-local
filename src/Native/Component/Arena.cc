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
    state.playersNeeded = 0;
    state.ticksUntilStart = 0;
}

std::vector<FieldId> ArenaComponent::FindUpdates()
{
    std::vector<FieldId> found;

    if (state.gui != 0)
        found.push_back(FieldId::Gui);
    if (state.leftX != 0)
        found.push_back(FieldId::LeftX);
    if (state.topY != 0)
        found.push_back(FieldId::TopY);
    if (state.rightX != 0)
        found.push_back(FieldId::RightX);
    if (state.bottomY != 0)
        found.push_back(FieldId::BottomY);
    if (state.scoreboardAmount != 0)
        found.push_back(FieldId::ScoreboardAmount);
    if (state.scoreboardNames != 0)
        found.push_back(FieldId::ScoreboardNames);
    if (state.scoreboardScores != 0)
        found.push_back(FieldId::ScoreboardScores);
    if (state.scoreboardColors != 0)
        found.push_back(FieldId::ScoreboardColors);
    if (state.scoreboardSuffixes != 0)
        found.push_back(FieldId::ScoreboardSuffixes);
    if (state.scoreboardTanks != 0)
        found.push_back(FieldId::ScoreboardTanks);
    if (state.leaderX != 0)
        found.push_back(FieldId::LeaderX);
    if (state.leaderY != 0)
        found.push_back(FieldId::LeaderY);
    if (state.playersNeeded != 0)
        found.push_back(FieldId::PlayersNeeded);
    if (state.ticksUntilStart != 0)
        found.push_back(FieldId::TicksUntilStart);

    return found;
}

void ArenaComponent::LeftX(float x)
{
    if (LeftX() == x)
        return;
    
    state.leftX |= 1;
    entity->state |= 1;
    netProperties.leftX = x;
}

void ArenaComponent::TopY(float x)
{
    if (TopY() == x)
        return;
    
    state.topY |= 1;
    entity->state |= 1;
    netProperties.topY = x;
}

void ArenaComponent::RightX(float x)
{
    if (RightX() == x)
        return;
    
    state.rightX |= 1;
    entity->state |= 1;
    netProperties.rightX = x;
}

void ArenaComponent::BottomY(float x)
{
    if (BottomY() == x)
        return;
    
    state.bottomY |= 1;
    entity->state |= 1;
    netProperties.bottomY = x;
}

void ArenaComponent::LeaderX(float x)
{
    if (LeaderX() == x)
        return;
    
    state.leaderX |= 1;
    entity->state |= 1;
    netProperties.leaderX = x;
}

void ArenaComponent::Gui(uint32_t x)
{
    if (Gui() == x)
        return;
    
    state.gui |= 1;
    entity->state |= 1;
    netProperties.gui = x;
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
