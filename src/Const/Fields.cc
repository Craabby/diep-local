#include <Const/Fields.h>

std::array<FieldDefinition, static_cast<size_t>(FieldId::kMaxFieldId)> fieldList = {
    FieldDefinition{.component = FieldGroupId::position , .id = 1 , .encodingType = EncodingType::Vi      , .index = 0}, // y;
    FieldDefinition{.component = FieldGroupId::position , .id = 0 , .encodingType = EncodingType::Vi      , .index = 1}, // x;
    FieldDefinition{.component = FieldGroupId::position , .id = 2 , .encodingType = EncodingType::Radians , .index = 2}, // angle;
    FieldDefinition{.component = FieldGroupId::physics  , .id = 2 , .encodingType = EncodingType::Float   , .index = 3}, // size;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 2 , .encodingType = EncodingType::EntityId, .index = 4}, // player;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 0 , .encodingType = EncodingType::Vu      , .index = 5}, // GUI;
    FieldDefinition{.component = FieldGroupId::style    , .id = 1 , .encodingType = EncodingType::Vu      , .index = 6}, // color;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 8 , .encodingType = EncodingType::Vu      , .index = 7, .amount = 10}, // scoreboardColors;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 16, .encodingType = EncodingType::StringNT, .index = 8}, // killedBy;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 13, .encodingType = EncodingType::Vi      , .index = 9}, // playersNeeded;
    FieldDefinition{.component = FieldGroupId::physics  , .id = 1 , .encodingType = EncodingType::Vu      , .index = 10}, // sides;
    FieldDefinition{.component = FieldGroupId::team     , .id = 3 , .encodingType = EncodingType::Vu      , .index = 11}, // mothership;
    FieldDefinition{.component = FieldGroupId::health   , .id = 0 , .encodingType = EncodingType::Vu      , .index = 12}, // healthbar;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 10, .encodingType = EncodingType::Vi      , .index = 13, .amount = 10}, // scoreboardTanks;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 15, .encodingType = EncodingType::Vi      , .index = 14}, // respawnLevel;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 6 , .encodingType = EncodingType::Float   , .index = 15}, // levelbarProgress;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 17, .encodingType = EncodingType::Vi      , .index = 16}, // spawnTick;
    FieldDefinition{.component = FieldGroupId::physics  , .id = 4 , .encodingType = EncodingType::Float   , .index = 17}, // absorbtionFactor;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 11, .encodingType = EncodingType::Float   , .index = 18}, // leaderX;
    FieldDefinition{.component = FieldGroupId::health   , .id = 2 , .encodingType = EncodingType::Float   , .index = 19}, // maxHealth;
    FieldDefinition{.component = FieldGroupId::style    , .id = 0 , .encodingType = EncodingType::Vu      , .index = 20}, // styleFlags;
    FieldDefinition{.component = FieldGroupId::unused2  , .id = 0 , .encodingType = EncodingType::Vi      , .index = 21}, // unknown;
    FieldDefinition{.component = FieldGroupId::barrel   , .id = 3 , .encodingType = EncodingType::Float   , .index = 22}, // trapezoidalDir;
    FieldDefinition{.component = FieldGroupId::position , .id = 3 , .encodingType = EncodingType::Vu      , .index = 23}, // motion;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 6 , .encodingType = EncodingType::StringNT, .index = 24, .amount = 10}, // scoreboardNames;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 14, .encodingType = EncodingType::Float   , .index = 25}, // scorebar;
    FieldDefinition{.component = FieldGroupId::team     , .id = 2 , .encodingType = EncodingType::Float   , .index = 26}, // mothershipY;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 9 , .encodingType = EncodingType::StringNT, .index = 27, .amount = 10}, // scoreboardSuffixes;
    FieldDefinition{.component = FieldGroupId::name     , .id = 0 , .encodingType = EncodingType::Vu      , .index = 28}, // nametag;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 20, .encodingType = EncodingType::Float   , .index = 29}, // movementSpeed;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 12, .encodingType = EncodingType::Float   , .index = 30}, // leaderY;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 4 , .encodingType = EncodingType::Float   , .index = 31}, // bottomY;
    FieldDefinition{.component = FieldGroupId::relations, .id = 2 , .encodingType = EncodingType::EntityId, .index = 32}, // team;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 4 , .encodingType = EncodingType::Vi      , .index = 33}, // level;
    FieldDefinition{.component = FieldGroupId::team     , .id = 0 , .encodingType = EncodingType::Vu      , .index = 34}, // teamColor;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 3 , .encodingType = EncodingType::Float   , .index = 35}, // FOV;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 11, .encodingType = EncodingType::Vi      , .index = 36, .amount = 8}, // statLimits;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 1 , .encodingType = EncodingType::Float   , .index = 37}, // leftX;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 7 , .encodingType = EncodingType::Float   , .index = 38, .amount = 10}, // scoreboardScores;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 10, .encodingType = EncodingType::Vi      , .index = 39, .amount = 8}, // statLevels;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 19, .encodingType = EncodingType::StringNT, .index = 40}, // tankOverride;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 5 , .encodingType = EncodingType::Vi      , .index = 41}, // tank;
    FieldDefinition{.component = FieldGroupId::style    , .id = 2 , .encodingType = EncodingType::Vi      , .index = 42}, // borderThickness;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 18, .encodingType = EncodingType::Vi      , .index = 43}, // deathTick;
    FieldDefinition{.component = FieldGroupId::physics  , .id = 3 , .encodingType = EncodingType::Float   , .index = 44}, // width;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 8 , .encodingType = EncodingType::Vi      , .index = 45}, // statsAvailable;
    FieldDefinition{.component = FieldGroupId::barrel   , .id = 0 , .encodingType = EncodingType::Vu      , .index = 46}, // shooting;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 7 , .encodingType = EncodingType::Float   , .index = 47}, // levelbarMax;
    FieldDefinition{.component = FieldGroupId::name     , .id = 1 , .encodingType = EncodingType::StringNT, .index = 48}, // name;
    FieldDefinition{.component = FieldGroupId::relations, .id = 1 , .encodingType = EncodingType::EntityId, .index = 49}, // owner;
    FieldDefinition{.component = FieldGroupId::health   , .id = 1 , .encodingType = EncodingType::Float   , .index = 50}, // health;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 13, .encodingType = EncodingType::Float   , .index = 51}, // cameraY;
    FieldDefinition{.component = FieldGroupId::style    , .id = 3 , .encodingType = EncodingType::Float   , .index = 52}, // opacity;
    FieldDefinition{.component = FieldGroupId::barrel   , .id = 1 , .encodingType = EncodingType::Float   , .index = 53}, // reloadTime;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 9 , .encodingType = EncodingType::StringNT, .index = 54, .amount = 8}, // statNames;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 12, .encodingType = EncodingType::Float   , .index = 55}, // cameraX;
    FieldDefinition{.component = FieldGroupId::team     , .id = 1 , .encodingType = EncodingType::Float   , .index = 56}, // mothershipX;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 0 , .encodingType = EncodingType::Vu      , .index = 57}, // GUIunknown;
    FieldDefinition{.component = FieldGroupId::relations, .id = 0 , .encodingType = EncodingType::EntityId, .index = 58}, // parent;
    FieldDefinition{.component = FieldGroupId::style    , .id = 4 , .encodingType = EncodingType::Vu      , .index = 59}, // zIndex;
    FieldDefinition{.component = FieldGroupId::camera   , .id = 1 , .encodingType = EncodingType::Vu      , .index = 60}, // camera;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 3 , .encodingType = EncodingType::Float   , .index = 61}, // rightX;
    FieldDefinition{.component = FieldGroupId::physics  , .id = 5 , .encodingType = EncodingType::Float   , .index = 62}, // pushFactor;
    FieldDefinition{.component = FieldGroupId::physics  , .id = 0 , .encodingType = EncodingType::Vu      , .index = 63}, // objectFlags;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 5 , .encodingType = EncodingType::Vu      , .index = 64}, // scoreboardAmount;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 14, .encodingType = EncodingType::Float   , .index = 65}, // ticksUntilStart;
    FieldDefinition{.component = FieldGroupId::arena    , .id = 2 , .encodingType = EncodingType::Float   , .index = 66}, // topY;
    FieldDefinition{.component = FieldGroupId::score    , .id = 0 , .encodingType = EncodingType::Float   , .index = 67} // score;
};

std::array<FieldDefinition, static_cast<size_t>(FieldId::kMaxFieldId)> &GetFieldList()
{
    return fieldList;
}
