#include <Native/Component/Score.h>

#include <Native/Entity.h>

ScoreComponent::ScoreComponent(Entity *entity)
    : entity(entity)
{
}

void ScoreComponent::Wipe()
{
    state.score = 0;
}

float ScoreComponent::Score()
{
    return netProperties.score;
}
