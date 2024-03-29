#pragma once

#include <Native/Component/types.h>
#include <Const/Fields.h>

class Entity;

template <typename T>
class CameraTable
{
    uint8_t state[8];
    T values[8];

public:
    CameraTable(T defaultValue, Entity *owner){};

    std::vector<uint8_t> FindUpdates()
    {
        std::vector<uint8_t> updated;
        for (uint8_t i = 0; i < 8; i++)
            if (state[i] != 0) updated.push_back(i);

        return updated;
    }

    const T &At(uint8_t x) const
    {
        return values[x];
    }

    void Set(uint8_t i, T x)
    {
        values[i] = x;

        state[i] |= 1;
    }
};

class CameraComponent
{
    struct
    {
        uint8_t guiUnknown = 0;
        uint8_t camera = 0;
        uint8_t player = 0;
        uint8_t fov = 0;
        uint8_t level = 0;
        uint8_t tank = 0;
        uint8_t levelbarProgress = 0;
        uint8_t levelbarMax = 0;
        uint8_t statsAvailable = 0;
        uint8_t statNames = 0;
        uint8_t statLevels = 0;
        uint8_t statLimits = 0;
        uint8_t cameraX = 0;
        uint8_t cameraY = 0;
        uint8_t scorebar = 0;
        uint8_t respawnLevel = 0;
        uint8_t killedBy = 0;
        uint8_t spawnTick = 0;
        uint8_t deathTick = 0;
        uint8_t tankOverride = 0;
        uint8_t movementSpeed = 0;
    } state;
    struct Values
    {
        CameraComponent *owner;

        int16_t guiUnknown = 2;
        uint32_t camera = 1;
        Entity *player = nullptr;
        float fov = 0.35;
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
    } netProperties{this};

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::camera;
    static inline std::array<FieldId, 21> fields = {FieldId::GuiUnknown, FieldId::Camera, FieldId::Player, FieldId::Fov, FieldId::Level, FieldId::Tank, FieldId::LevelbarProgress, FieldId::LevelbarMax, FieldId::StatsAvailable, FieldId::StatNames, FieldId::StatLevels, FieldId::StatLimits, FieldId::CameraX, FieldId::CameraY, FieldId::Scorebar, FieldId::RespawnLevel, FieldId::KilledBy, FieldId::SpawnTick, FieldId::DeathTick, FieldId::TankOverride, FieldId::MovementSpeed};

    CameraComponent(Entity *entity);

    void Wipe();
    std::vector<FieldId> FindUpdates();
    void Tick(uint32_t tick);

    int16_t GuiUnknown();
    uint32_t Camera();
    Entity *Player();
    float Fov();
    int32_t Level();
    TankId Tank();
    float LevelbarProgress();
    float LevelbarMax();
    int32_t StatsAvailable();
    float CameraX();
    float CameraY();
    float Scorebar();
    int32_t RespawnLevel();
    std::string KilledBy();
    uint32_t SpawnTick();
    uint32_t DeathTick();
    std::string TankOverride();
    float MovementSpeed();
    CameraTable<std::string> *StatNames();
    CameraTable<uint32_t> *StatLevels();
    CameraTable<uint32_t> *StatLimits();

    void GuiUnknown(int16_t guiUnknown);
    void Camera(uint32_t camera);
    void Player(Entity *player);
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
