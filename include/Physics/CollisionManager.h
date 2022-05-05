#pragma once

#include <cstdint>
#include <unordered_set>
#include <vector>

#include <Entity/Object.h>

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

        static uint32_t getHash(int32_t x, int32_t y);

    public:
        void insert(Box *box);
        std::vector<int16_t> query(Box &box);
        void clear();
    };
};

class DiepSpatialHashing : private SpatialHashing
{
public:
    void insertEntity(ObjectEntity entity);
    void reset();
};
