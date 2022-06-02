#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include <Const/Enums.h>

namespace
{
    uint8_t *OUTPUT_BUFFER = new uint8_t[1 << 20];

    int32_t SwapEndian(int32_t number);
}

class Entity;

namespace diep::coder::writer
{
    struct WriterOutput
    {
        uint32_t size;
        uint8_t *output;
    };

    class Writer
    {
        size_t at = 0;

    public:
        Writer *U8(uint8_t value);
        Writer *U16(uint16_t value);
        Writer *U32(uint32_t value);
        Writer *Float(float value);
        Writer *Vf(float value);
        Writer *Vu(uint32_t value);
        Writer *Vu(ColorId value); // hack to be able to send colors
        Writer *Vi(int32_t value);
        Writer *Vi(TankId value);
        Writer *Bytes(uint8_t *value, size_t size);
        Writer *Radians(float value);
        Writer *Degrees(float value);
        Writer *StringNT(std::string string);
        Writer *EntityId(int16_t id, int16_t hash = 0);
        Writer *EntityId(Entity *entity);
        WriterOutput Write() const;
        size_t Size();
    };
}