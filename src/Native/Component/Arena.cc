#include <Native/Component/Arena.h>

#include <Native/Entity.h>

ArenaComponent::ArenaComponent(Entity *entity)
    : entity(entity)
{
}

void ArenaComponent::Wipe()
{
    state.GUI = 0;
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
