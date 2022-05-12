#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace
{
    uint8_t *OUTPUT_BUFFER = new uint8_t[1 << 20];

    int32_t SwapEndian(int32_t number);
}

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
        Writer *Vi(int32_t value);
        Writer *Bytes(uint8_t *value, size_t size);
        Writer *Radians(float value);
        Writer *Degrees(float value);
        Writer *StringNT(std::string string);
        Writer *EntityId(int16_t id, int16_t hash = 0);
        WriterOutput Write() const;
        size_t Size();
    };
}