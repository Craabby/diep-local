#include <Native/Component/Score.h>

ScoreComponent::ScoreComponent(entityId entity)
    : entity(entity)
{
}

void ScoreComponent::Wipe()
{
    state.score = 0;
}
