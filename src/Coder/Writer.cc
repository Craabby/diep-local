#include <Coder/Writer.h>

#include <cstdint>
#include <cstddef>
#include <stdexcept>

#include <Native/Entity.h>

using entityId = int16_t;

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

diep::coder::writer::Writer *diep::coder::writer::Writer::U8(uint8_t value)
{
    if (at > (1 << 20))
        throw std::runtime_error("Writer::OOB");
    OUTPUT_BUFFER[at++] = value;
    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::U16(uint16_t value)
{
    U8(value & 0xff);          // lower 8 bits
    U8((value & 0xffff) >> 8); // upper 8 bits
    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::U32(uint32_t value)
{
    U8((value & 0xff) >> 0);
    U8((value & 0xffff) >> 8);
    U8((value & 0xffffff) >> 16);
    U8((value & 0xffffffff) >> 24);
    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::Float(float value)
{
    int32_t undefinedBehaviorValue = *(int32_t *)&value;
    U32(undefinedBehaviorValue);
    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::Vu(uint32_t value)
{
    do
    {
        uint8_t part = value & 0xff;
        value >>= 7;
        if (value != 0)
            part |= 0x80;
        U8(part);
    } while (value);

    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::Vu(ColorId value)
{
    Vu(static_cast<uint32_t>(value));

    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::Vi(int32_t value)
{
    Vu((0 - (value < 0 ? 1 : 0)) ^ (value << 1));

    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::Vi(TankId value)
{
    Vi((int32_t)value);

    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::Bytes(uint8_t *value, size_t size)
{
    for (size_t i = 0; i < size; i++)
        U8(value[i]);

    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::Radians(float value)
{
    Vi(value * 64);

    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::Degrees(float value)
{
    Radians(value * 3.1415927410125732); // 32 bit float rounded version of PI

    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::StringNT(std::string string)
{
    Bytes((uint8_t *)string.c_str(), string.size());
    U8(0);

    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::EntityId(entityId entity, int16_t hash)
{
    if (entity == -1 || hash == 0)
    {
        U8(0);
        return this;
    }
    Vu(hash);
    Vu(entity);

    return this;
}

diep::coder::writer::Writer *diep::coder::writer::Writer::EntityId(Entity *entity)
{
    if (entity != nullptr)
        EntityId(entity->id, entity->hash);
    else
        U8(0);

    return this;
}

diep::coder::writer::WriterOutput diep::coder::writer::Writer::Write() const
{
    uint8_t *output = OUTPUT_BUFFER;
    uint32_t size = at;

    return WriterOutput{size, output};
}
