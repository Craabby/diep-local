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
    state.guiUnknown = 0;
    state.camera = 0;
    state.player = 0;
    state.fov = 0;
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

int16_t CameraComponent::GuiUnknown()
{
    return netProperties.guiUnknown;
}

uint32_t CameraComponent::Camera()
{
    return netProperties.camera;
}

Entity *CameraComponent::Player()
{
    return netProperties.player;
}

float CameraComponent::Fov()
{
    return netProperties.fov;
}

int32_t CameraComponent::Level()
{
    return netProperties.level;
}

TankId CameraComponent::Tank()
{
    return netProperties.tank;
}

float CameraComponent::LevelbarProgress()
{
    return netProperties.levelbarProgress;
}

float CameraComponent::LevelbarMax()
{
    return netProperties.levelbarMax;
}

int32_t CameraComponent::StatsAvailable()
{
    return netProperties.statsAvailable;
}

float CameraComponent::CameraX()
{
    return netProperties.cameraX;
}

float CameraComponent::CameraY()
{
    return netProperties.cameraY;
}

float CameraComponent::Scorebar()
{
    return netProperties.scorebar;
}

int32_t CameraComponent::RespawnLevel()
{
    return netProperties.respawnLevel;
}

std::string CameraComponent::KilledBy()
{
    return netProperties.killedBy;
}

uint32_t CameraComponent::SpawnTick()
{
    return netProperties.spawnTick;
}

uint32_t CameraComponent::DeathTick()
{
    return netProperties.deathTick;
}

std::string CameraComponent::TankOverride()
{
    return netProperties.tankOverride;
}

float CameraComponent::MovementSpeed()
{
    return netProperties.movementSpeed;
}

CameraTable<std::string> *CameraComponent::StatNames()
{
    return &netProperties.statNames;
}

CameraTable<uint32_t> *CameraComponent::StatLevels()
{
    return &netProperties.statLevels;
}

CameraTable<uint32_t> *CameraComponent::StatLimits()
{
    return &netProperties.statLimits;
}
