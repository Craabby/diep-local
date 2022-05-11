#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

namespace
{
    uint8_t convo[4];
    uint8_t *u8 = convo;
    uint16_t *u16 = (uint16_t *)convo;
    int32_t *i32 = (int32_t *)convo;
    uint32_t *u32 = (uint32_t *)convo;
    float *f32 = (float *)convo;
    uint8_t *OUTPUT_BUFFER = new uint8_t[1 << 20];

    int32_t SwapEndian(int32_t number);
}

namespace diep::writer
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
        Writer();

        void U8(uint8_t value);
        void U16(uint16_t value);
        void U32(uint32_t value);
        void Float(float value);
        void Vf(float value);
        void Vu(uint32_t value);
        void Vi(int32_t value);
        void Bytes(uint8_t *value, size_t size);
        void Radians(float value);
        void Degrees(float value);
        void StringNT(uint8_t *value, size_t size);
        void EntityId(int16_t id, int16_t hash = 0);
        WriterOutput Write();
        size_t Size();
    };
}