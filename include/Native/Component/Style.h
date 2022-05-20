#pragma once

#include <Native/Component/types.h>

class Entity;

class StyleComponent
{
    struct
    {
        uint8_t styleFlags = 0;
        uint8_t color = 0;
        uint8_t borderThickness = 0;
        uint8_t opacity = 0;
        uint8_t zIndex = 0;
    } state;
    struct
    {
        float styleFlags = 1;
        ColorId color = ColorId::Border;
        int32_t borderThickness = 480;
        float opacity = 1;
        uint32_t zIndex = 0;
    } netProperties;

public:
    Entity *entity;

    static constexpr FieldGroupId id = FieldGroupId::style;
    std::vector<std::string> fields{"styleFlags", "color", "borderThickness", "opacity", "zIndex"};

    StyleComponent(Entity *entity);

    void Wipe();

    float StyleFlags();
    ColorId Color();
    int32_t BorderThickness();
    float Opacity();
    uint32_t ZIndex();

    void StyleFlags(float styleFlags);
    void Color(ColorId color);
    void BorderThickness(int32_t borderThickness);
    void Opacity(float opacity);
    void ZIndex(uint32_t zIndex);
};
