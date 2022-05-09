#pragma once

#include <Native/Component/types.h>

template <typename T>
class CameraTable
{
    uint8_t state[8];
    T values[8];

public:
    CameraTable(T defaultValue, entityId owner){};
};

class CameraComponent
{
    struct
    {
        uint8_t GUIunknown;
        uint8_t camera;
        uint8_t player;
        uint8_t FOV;
        uint8_t level;
        uint8_t tank;
        uint8_t levelbarProgress;
        uint8_t levelbarMax;
        uint8_t statsAvailable;
        uint8_t statNames;
        uint8_t statLevels;
        uint8_t statLimits;
        uint8_t cameraX;
        uint8_t cameraY;
        uint8_t scorebar;
        uint8_t respawnLevel;
        uint8_t killedBy;
        uint8_t spawnTick;
        uint8_t deathTick;
        uint8_t tankOverride;
        uint8_t movementSpeed;
    } state;
    struct Values
    {
        CameraComponent *owner;

        int16_t GUIunknown = 2;
        uint32_t camera = 1;
        entityId player = -1;
        float FOV = 0.35;
        int32_t level = 1;
        TankId tank = TankId::Basic;
        float levelbarProgress = 0;
        float levelbarMax = 0;
        int32_t statsAvailable = 0;
        CameraTable<std::string> statNames = CameraTable<std::string>("", owner->entity);
        CameraTable<uint32_t> statLevels = CameraTable<uint32_t>(0, owner->entity);
        CameraTable<uint32_t> statLimits = CameraTable<uint32_t>(7, owner->entity);
        float cameraX = 0;
        float cameraY = 0;
        float scorebar = 0;
        int32_t respawnLevel = 0;
        std::string killedBy = "";
        uint32_t spawnTick = 0;
        uint32_t deathTick = -1;
        std::string tankOverride = "";
        float movementSpeed = 0;

        Values(CameraComponent *owner) : owner(owner) {}
    } values{this};

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::camera;
    std::vector<std::string> fields{"GUIunknown", "camera", "player", "FOV", "level", "tank", "levelbarProgress", "levelbarMax", "statsAvailable", "statNames", "statLevels", "statLimits", "cameraX", "cameraY", "scorebar", "respawnLevel", "killedBy", "spawnTick", "deathTick", "tankOverride", "movementSpeed"};

    CameraComponent(entityId entity);

    void wipe();

    int16_t GuiUnknown();
    uint32_t Camera();
    entityId Player();
    float Fov();
    int32_t Level();
    TankId Tank();
    float LevelbarProgress();
    float LevelbarMax();
    int32_t StatsAvailable();
    CameraTable<std::string> *StatNames();
    CameraTable<uint32_t> *StatLevels();
    CameraTable<uint32_t> *StatLimits();
    float CameraX();
    float CameraY();
    float Scorebar();
    int32_t RespawnLevel();
    std::string KilledBy();
    uint32_t SpawnTick();
    uint32_t DeathTick();
    std::string TankOverride();
    float MovementSpeed();

    void GuiUnknown(int16_t guiUnknown);
    void Camera(uint32_t camera);
    void Player(entityId player);
    void Fov(float FOV);
    void Level(int32_t level);
    void Tank(TankId tank);
    void LevelbarProgress(float levelbarProgress);
    void LevelbarMax(float levelbarMax);
    void StatsAvailable(int32_t statsAvailable);
    void StatNames(CameraTable<std::string> *statNames);
    void StatLevels(CameraTable<uint32_t> *statLevels);
    void StatLimits(CameraTable<uint32_t> *statLimits);
    void CameraX(float cameraX);
    void CameraY(float cameraY);
    void Scorebar(float scorebar);
    void RespawnLevel(int32_t respawnLevel);
    void KilledBy(std::string killedBy);
    void SpawnTick(uint32_t spawnTick);
    void DeathTick(uint32_t deathTick);
    void TankOverride(std::string tan);
    void MovementSpeed(float movementSpeed);
};
