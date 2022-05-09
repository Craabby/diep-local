#pragma once

#include <Native/Component/types.h>

template <typename T>
class CameraTable
{
    uint8_t state[8];
    T values[8];

public:
    CameraTable(T defaultValue, entityId owner){};
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
            uint8_t tan;
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
            Tank tank = Tank::Basic;
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
            std::string tan = "";
            float movementSpeed = 0;

            Values(CameraComponent *owner) : owner(owner) {}
        } values{this};

    public:
        entityId entity;

        static constexpr FieldGroupId id = FieldGroupId::camera;
        std::vector<std::string> fields{"GUIunknown", "camera", "player", "FOV", "level", "tank", "levelbarProgress", "levelbarMax", "statsAvailable", "statNames", "statLevels", "statLimits", "cameraX", "cameraY", "scorebar", "respawnLevel", "killedBy", "spawnTick", "deathTick", "tan", "movementSpeed"};

        CameraComponent(entityId entity);

        void wipe();

        int16_t GUIunknown();
        uint32_t camera();
        entityId player();
        float FOV();
        int32_t level();
        Tank tank();
        float levelbarProgress();
        float levelbarMax();
        int32_t statsAvailable();
        CameraTable<std::string> *statNames();
        CameraTable<uint32_t> *statLevels();
        CameraTable<uint32_t> *statLimits();
        float cameraX();
        float cameraY();
        float scorebar();
        int32_t respawnLevel();
        std::string killedBy();
        uint32_t spawnTick();
        uint32_t deathTick();
        std::string tan();
        float movementSpeed();

        void GUIunknown(int16_t guiUnknown);
        void camera(uint32_t camera);
        void player(entityId player);
        void FOV(float FOV);
        void level(int32_t level);
        void tank(Tank tank);
        void levelbarProgress(float levelbarProgress);
        void levelbarMax(float levelbarMax);
        void statsAvailable(int32_t statsAvailable);
        void statNames(CameraTable<std::string> *statNames);
        void statLevels(CameraTable<uint32_t> *statLevels);
        void statLimits(CameraTable<uint32_t> *statLimits);
        void cameraX(float cameraX);
        void cameraY(float cameraY);
        void scorebar(float scorebar);
        void respawnLevel(int32_t respawnLevel);
        void killedBy(std::string killedBy);
        void spawnTick(uint32_t spawnTick);
        void deathTick(uint32_t deathTick);
        void tan(std::string tan);
        void movementSpeed(float movementSpeed);
    };
