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

    int32_t SwapEndian(int32_t number);
}

class Reader
{
public:
    size_t at = 0;
    size_t size;
    uint8_t *buffer;

    Reader(uint8_t *buffer, size_t size);

    uint8_t U8();
    uint16_t U16();
    uint32_t U32();
    uint32_t Vu();
    int32_t Vi();
    float Vf();
    std::string StringNT();
    std::string String(uint32_t length);
    float Float();

    uint8_t operator[](size_t i);
};
