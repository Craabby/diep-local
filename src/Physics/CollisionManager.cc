#include <Physics/CollisionManager.h>

#include <cstdint>

Box::Box(int32_t x, int32_t y, int32_t w, int32_t h, int16_t id)
            : x(x),
              y(y),
              w(w),
              h(h),
              id(id)
        {
        }

uint32_t SpatialHashing::getHash(int32_t x, int32_t y)
{
    uint32_t hash = 41'332'271;
    hash ^= x * 21'201'979;
    hash ^= y * 19'755'691;

    return hash % HASH_TABLE_SIZE;
}

void SpatialHashing::clear()
{
    for (size_t i = 0; i < HASH_TABLE_SIZE; i++)
    {
        cells[i].clear();
    }
}

void SpatialHashing::insert(Box *box)
{
    int32_t startX = (box->x - box->w) >> CELL_FACTOR;
    int32_t startY = (box->y - box->h) >> CELL_FACTOR;
    int32_t endX = (box->x + box->w) >> CELL_FACTOR;
    int32_t endY = (box->y + box->h) >> CELL_FACTOR;

    for (int32_t x = startX; x <= endX; x++)
    {
        for (int32_t y = startY; y <= endY; y++)
        {
            int32_t key = getHash(x, y);

            cells[key].push_back(box);
        }
    }
}

std::vector<int16_t> SpatialHashing::query(Box &box)
{
    std::vector<int16_t> found{};

    int32_t startX = (box.x - box.w) >> CELL_FACTOR;
    int32_t startY = (box.y - box.h) >> CELL_FACTOR;
    int32_t endX = (box.x + box.h) >> CELL_FACTOR;
    int32_t endY = (box.y + box.h) >> CELL_FACTOR;

    int32_t queryId = this->queryId++;

    for (int32_t x = startX; x <= endX; x++)
    {
        for (int32_t y = startY; y <= endY; y++)
        {
            uint32_t key = getHash(x, y);

            std::vector<Box *> *cell = cells + key;

            for (size_t i = 0; i < cell->size(); i++)
            {
                Box *box = cell->at(i);
                if (box->queryId != queryId)
                {
                    box->queryId = queryId;
                    found.push_back(box->id);
                }
            }
        }
    }
    return found;
}

void DiepSpatialHashing::reset()
{
    clear();
}