#pragma once

#include <cstdint>

#include <Native/Entity.h>
#include <Coder/Writer.h>

namespace diep::server
{
    class GameServer;
    namespace client
    {
        class Client;
    };
};

namespace
{
    struct Deletion
    {
        entityId id;
        entityId hash;
        bool noDelete = false;
    };
};

class CameraEntity : public Entity
{
public: 
    int32_t sizeFactor = 1;
    bool isClientCamera = false;

    CameraEntity(diep::server::GameServer *gameServer);

    void SetLevel(uint32_t level);
    void SetFieldFactor(float fieldFactor);
    void Tick(uint32_t tick);
};

class Camera : public CameraEntity
{
    void AddToView(Entity *entity);
    void RemoveFromView(entityId id);
    void UpdateView(uint32_t tick);
    void CompileCreation(diep::coder::writer::Writer *writer, Entity *entity);
    void CompileUpdate(diep::coder::writer::Writer *writer, Entity *entity);

public:
    diep::server::client::Client *client;
    std::vector<Entity *> view;

    Entity *spectatee = nullptr;

    Camera(diep::server::client::Client *client);

    static uint32_t CalculateStatCount(int32_t level);

    void Tick(uint32_t tick);
};