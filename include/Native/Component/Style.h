#pragma once

#include <Native/Component/types.h>

class StyleComponent
{
    struct
    {
        uint8_t styleFlags;
        uint8_t color;
        uint8_t borderThickness;
        uint8_t opacity;
        uint8_t zIndex;
    } state;
    struct
    {
        float styleFlags = 1;
        Color color = Color::Border;
        int32_t borderThickness = 480;
        float opacity = 1;
        uint32_t zIndex = 0;
    } values;

public:
    entityId entity;

    static constexpr FieldGroupId id = FieldGroupId::style;
    std::vector<std::string> fields{"styleFlags", "color", "borderThickness", "opacity", "zIndex"};

    StyleComponent(entityId entity);

    void wipe();

    float styleFlags();
    Color color();
    int32_t borderThickness();
    float opacity();
    uint32_t zIndex();

    void styleFlags(float styleFlags);
    void color(Color color);
    void borderThickness(int32_t borderThickness);
    void opacity(float opacity);
    void zIndex(uint32_t zIndex);
};
