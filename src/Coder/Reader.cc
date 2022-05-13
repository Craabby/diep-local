#include <Coder/Reader.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace
{
    int32_t SwapEndian(int32_t number)
    {
        return ((number & 0xff) << 24) |
               ((number & 0xff00) << 8) |
               ((number >> 8) & 0xff00) |
               ((number >> 24) & 0xff);
    }
}

diep::coder::reader::Reader::Reader(uint8_t *buffer, size_t size)
    : buffer(buffer),
      size(size)
{
}

uint8_t diep::coder::reader::Reader::U8()
{
    uint8_t value = (*this)[at];
    at++;
    return value;
}

uint16_t diep::coder::reader::Reader::U16()
{
    uint16_t value = ((*this)[at] << 0) | ((*this)[at + 1] << 8);
    at += 2;
    return value;
}

uint32_t diep::coder::reader::Reader::U32()
{
    uint32_t value = (*this)[at] << ((*this)[at + 1] << 0) | ((*this)[at + 2] << 16) | ((*this)[at + 3] << 24);
    at += 4;
    return value;
}

uint32_t diep::coder::reader::Reader::Vu()
{
    uint32_t out = 0;
    uint8_t i = 0;

    while ((*this)[at] & 0x80)
    {
        out |= ((*this)[at++] & 0x7f) << i;
        i += 7;
    }
    out |= ((*this)[at] & 0x7f) << i;

    return out;
}

int32_t diep::coder::reader::Reader::Vi()
{
    uint32_t out = Vu();
    return (0 - (out & 1)) ^ (out >> 1);
}

float diep::coder::reader::Reader::Vf()
{
    int32_t out = SwapEndian(Vi());
    return *(float *)&out;
}

std::string diep::coder::reader::Reader::StringNT()
{
    std::string string;
    while ((*this)[at] != 0)
    {
        string += (*this)[at];
        at++;
    };

    return string;
}

std::string diep::coder::reader::Reader::String(uint32_t length = 0xdeadbeef)
{
    if (length == 0xdeadbeef)
        length = Vu();
    std::string string;
    for (uint32_t i = 0; i < length; i++)
    {
        string += U8();
    }

    return string;
}

uint8_t diep::coder::reader::Reader::operator[](size_t i)
{
    if (i > size)
        return 0;
    return buffer[i];
}
