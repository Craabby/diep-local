#include <Native/Component/Camera.h>

#include <Native/Entity.h>

CameraComponent::CameraComponent(Entity *entity)
    : entity(entity)
{
}

void CameraComponent::Tick(uint32_t tick)
{
}

void CameraComponent::Wipe()
{
    state.GUIunknown = 0;
    state.camera = 0;
    state.player = 0;
    state.FOV = 0;
    state.level = 0;
    state.tank = 0;
    state.levelbarProgress = 0;
    state.levelbarMax = 0;
    state.statsAvailable = 0;
    state.statNames = 0;
    state.statLevels = 0;
    state.statLimits = 0;
    state.cameraX = 0;
    state.cameraY = 0;
    state.scorebar = 0;
    state.respawnLevel = 0;
    state.killedBy = 0;
    state.spawnTick = 0;
    state.deathTick = 0;
    state.tankOverride = 0;
    state.movementSpeed = 0;
}

float CameraComponent::CameraX()
{
    return netProperties.cameraX;
}

float CameraComponent::CameraY()
{
    return netProperties.cameraY;
}
