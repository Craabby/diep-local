#pragma once

#include <cstdint>
#include <unordered_set>
#include <vector>

#include <Native/Entity.h>

namespace diep::server
{
    class GameServer;
}

namespace
{
    struct Box
    {
        int32_t x;
        int32_t y;
        int32_t w;
        int32_t h;
        int16_t id;
        int32_t queryId = -1;

        Box(int32_t x, int32_t y, int32_t w, int32_t h, int16_t id);
    };

    class SpatialHashing
    {
    private:
        static constexpr int32_t CELL_FACTOR = 9;
        static constexpr size_t HASH_TABLE_SIZE = 1 << 16;
        std::vector<Box *> *cells = new std::vector<Box *>[HASH_TABLE_SIZE];

        int32_t queryId = 0;

        static uint32_t GetHash(int32_t x, int32_t y);

    public:
        void Insert(Box &&box);
        std::vector<int16_t> Query(Box &&box);
        void Clear();
    };
};

class DiepSpatialHashing : private SpatialHashing
{
public:
    diep::server::GameServer *gameServer;
    void InsertEntity(Entity *entity);
    void Reset();
    std::vector<Entity *> Retrieve(int32_t x, int32_t y, int32_t w, int32_t h);
};
