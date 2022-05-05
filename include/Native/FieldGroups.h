#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <Const/Enums.h>

enum class FieldGroupId
{
    relations = 0,
    unused0,
    barrel,
    physics,
    health,
    unused1,
    unused2,
    arena,
    name,
    camera,
    position,
    style,
    unused3,
    score,
    team
};

using entityId = int16_t;

class FieldGroup
{
public:
    entityId entity;
    std::vector<std::string> fields;

    virtual std::vector<std::string> findUpdate();
    virtual void wipe();
};

class RelationsGroup : public FieldGroup
{
    struct
    {
        uint8_t parent = 0;
        uint8_t owner = 0;
        uint8_t team = 0;
    } state;

    struct
    {
        entityId parent = -1;
        entityId owner = -1;
        entityId team = -1;
    } values;

public:
    static constexpr FieldGroupId id = FieldGroupId::relations;
    std::vector<std::string> fields{"parent", "owner", "team"};

    RelationsGroup(entityId entity);

    virtual void wipe() override;

    entityId parent();
    entityId owner();
    entityId team();

    void parent(entityId parent);
    void owner(entityId parent);
    void team(entityId parent);
};
class BarrelGroup : public FieldGroup
{
private:
    struct
    {
        uint8_t shooting = 0;
        uint8_t reloadTime = 0;
        uint8_t trapezoidalDir = 0;
    } state;

    struct
    {
        uint32_t shooting = 0;
        float reloadTime = 15;
        float trapezoidalDir = 0;
    } values;

public:
    static constexpr FieldGroupId id = FieldGroupId::barrel;
    std::vector<std::string> fields{"shooting", "reloadTime", "trapezoidalDir"};

    BarrelGroup(entityId entity);

    virtual void wipe() override;

    uint32_t shooting();
    float reloadTime();
    float trapezoidalDir();

    void shooting(uint32_t shooting);
    void reloadTime(float reloadTime);
    void trapezoidalDir(float trapezoidalDir);
};
class PhysicsGroup : public FieldGroup
{
    struct
    {
        uint8_t objectFlags = 0;
        uint8_t sides = 0;
        uint8_t size = 0;
        uint8_t width = 0;
        uint8_t absorbtionFactor = 0;
        uint8_t pushFactor = 0;
    } state;
    struct
    {
        uint32_t objectFlags = 0;
        uint32_t sides = 0;
        float size = 0;
        float width = 0;
        float absorbtionFactor = 1;
        float pushFactor = 8;
    } values;

public:
    static constexpr FieldGroupId id = FieldGroupId::physics;
    std::vector<std::string> fields{"objectFlags", "sides", "size", "width", "absorbtionFactor", "pushFactor"};

    PhysicsGroup(entityId entity);

    virtual void wipe() override;

    uint32_t objectFlags();
    uint32_t sides();
    float size();
    float width();
    float absorbtionFactor();
    float pushFactor();

    void objectFlags(uint32_t objectFlags);
    void sides(uint32_t sides);
    void size(float size);
    void width(float width);
    void absorbtionFactor(float absorbtionFactor);
    void pushFactor(float pushFactor);
};
class HealthGroup : public FieldGroup
{
    struct
    {
        uint8_t healthbar = 0;
        uint8_t health = 0;
        uint8_t maxHealth = 0;
    } state;
    struct
    {
        uint32_t healthbar = 0;
        float health = 1;
        float maxHealth = 1;
    } values;

public:
    static constexpr FieldGroupId id = FieldGroupId::health;

    HealthGroup(entityId entity);

    virtual void wipe() override;

    uint32_t healthbar();
    float health();
    float maxHealth();

    void healthbar(uint32_t healthbar);
    void health(float health);
    void maxHealth(float maxHealth);
};
class UnusedGroup : public FieldGroup
{
    struct
    {
        uint8_t unknown = 0;
    } state;
    struct
    {
        uint8_t unknown = 0;
    } values;

public:
    static constexpr FieldGroupId id = FieldGroupId::unused0;
    std::vector<std::string> fields{"unknown"};

    UnusedGroup(entityId entity);

    virtual void wipe() override;

    uint8_t unknown();

    void unknown(uint8_t unknown);
};
template <typename T>
class ScoreboardTable
{
    uint8_t state[10];
    T values[10];

public:
    ScoreboardTable(T defaultValue, entityId arena);
};
class ArenaGroup : public FieldGroup
{
    struct
    {
        uint8_t GUI = 0;
        uint8_t leftX = 0;
        uint8_t topY = 0;
        uint8_t rightX = 0;
        uint8_t bottomY = 0;
        uint8_t scoreboardAmount = 0;
        uint8_t scoreboardNames = 0;
        uint8_t scoreboardScores = 0;
        uint8_t scoreboardColors = 0;
        uint8_t scoreboardSuffixes = 0;
        uint8_t scoreboardTanks = 0;
        uint8_t leaderX = 0;
        uint8_t leaderY = 0;
        uint8_t playersNedded = 0;
        uint8_t ticksUntilStart = 0;
    } state;
    struct Values
    {
        ArenaGroup *owner;

        uint32_t GUI = 2;
        float leftX = 0;
        float topY = 0;
        float rightX = 0;
        float bottomY = 0;
        uint8_t scoreboardAmount = 0;
        ScoreboardTable<std::string> scoreboardNames = ScoreboardTable<std::string>("", owner->entity);
        ScoreboardTable<uint32_t> scoreboardScores = ScoreboardTable<uint32_t>(0, owner->entity);
        ScoreboardTable<Color> scoreboardColors = ScoreboardTable<Color>(Color::ScoreboardBar, owner->entity);
        ScoreboardTable<std::string> scoreboardSuffixes = ScoreboardTable<std::string>("", owner->entity);
        ScoreboardTable<Tank> scoreboardTanks = ScoreboardTable<Tank>(Tank::Basic, owner->entity);
        float leaderX = 0;
        float leaderY = 0;
        uint32_t playersNeeded = 1;
        uint32_t ticksUntilStart = 250;

        Values(ArenaGroup *owner) : owner(owner) {}
    } values{this};

public:
    static constexpr FieldGroupId id = FieldGroupId::arena;
    std::vector<std::string> fields{"GUI", "leftX", "topY", "rightX", "bottomY", "scoreboardAmount", "scoreboardNames", "scoreboardScores", "scoreboardColors", "scoreboardSuffixes", "scoreboardTanks", "leaderX", "leaderY", "playersNeeded", "ticksUntilStart"};

    ArenaGroup(entityId entity);

    virtual void wipe() override;

    uint32_t GUI();
    float leftX();
    float topY();
    float rightX();
    float bottomY();
    uint8_t scoreboardAmount();
    ScoreboardTable<std::string> *scoreboardNames();
    ScoreboardTable<uint32_t> *scoreboardScores();
    ScoreboardTable<Color> *scoreboardColors();
    ScoreboardTable<std::string> *scoreboardSuffixes();
    ScoreboardTable<Tank> *scoreboardTanks();
    float leaderX();
    float leaderY();
    uint32_t playersNeeded();
    uint32_t ticksUntilStart();

    void GUI(uint32_t GUI);
    void leftX(float leftX);
    void topY(float topY);
    void rightX(float rightY);
    void bottomY(float bottomY);
    void scoreboardAmount(uint8_t scoreboardAmount);
    void scoreboardNames(ScoreboardTable<std::string> *scoreboardNames);
    void scoreboardScores(ScoreboardTable<uint32_t> *scoreboardScores);
    void scoreboardColors(ScoreboardTable<Color> *scoreboardColors);
    void scoreboardSuffixes(ScoreboardTable<std::string> *scoreboardSuffixes);
    void scoreboardTanks(ScoreboardTable<Tank> *scoreboardTanks);
    void leaderX(float leaderX);
    void leaderY(float leaderY);
    void playersNeeded(uint32_t playersNeeded);
    void ticksUntilStart(uint32_t ticksUntilStart);
};
class NameGroup : public FieldGroup
{
    struct
    {
        uint8_t nametag = 0;
        uint8_t name = 0;
    } state;
    struct
    {
        uint32_t nametag = 0;
        std::string name;
    } values;

public:
    static constexpr FieldGroupId id = FieldGroupId::name;
    std::vector<std::string> fields{"nametag", "name"};

    NameGroup(entityId entity);

    virtual void wipe() override;

    uint8_t nametag();
    std::string name();

    void nametag(uint8_t nametag);
    void name(std::string name);
};
template <typename T>
class CameraTable
{
    uint8_t state[8];
    T values[8];

public:
    CameraTable(T defaultValue, entityId owner);
};
class CameraGroup : public FieldGroup
{
    struct
    {
        uint8_t GUIunknown;
        uint8_t camera;
        uint8_t player;
        uint8_t FOV;
        uint8_t level;
        uint8_t tank;
        uint8_t levelbarProgress;
        uint8_t levelbarMax;
        uint8_t statsAvailable;
        uint8_t statNames;
        uint8_t statLevels;
        uint8_t statLimits;
        uint8_t cameraX;
        uint8_t cameraY;
        uint8_t scorebar;
        uint8_t respawnLevel;
        uint8_t killedBy;
        uint8_t spawnTick;
        uint8_t deathTick;
        uint8_t tankOverride;
        uint8_t movementSpeed;
    } state;
    struct Values
    {
        CameraGroup *owner;

        int16_t GUIunknown = 2;
        uint32_t camera = 1;
        entityId player = -1;
        float FOV = 0.35;
        int32_t level = 1;
        Tank tank = Tank::Basic;
        float levelbarProgress = 0;
        float levelbarMax = 0;
        int32_t statsAvailable = 0;
        CameraTable<std::string> statNames = CameraTable<std::string>("", owner->entity);
        CameraTable<uint32_t> statLevels = CameraTable<uint32_t>(0, owner->entity);
        CameraTable<uint32_t> statLimits = CameraTable<uint32_t>(7, owner->entity);
        float cameraX = 0;
        float cameraY = 0;
        float scorebar = 0;
        int32_t respawnLevel = 0;
        std::string killedBy = "";
        uint32_t spawnTick = 0;
        uint32_t deathTick = -1;
        std::string tankOverride = "";
        float movementSpeed = 0;

        Values(CameraGroup *owner) : owner(owner) {}
    } values{this};

public:
    static constexpr FieldGroupId id = FieldGroupId::camera;
    std::vector<std::string> fields{"GUIunknown", "camera", "player", "FOV", "level", "tank", "levelbarProgress", "levelbarMax", "statsAvailable", "statNames", "statLevels", "statLimits", "cameraX", "cameraY", "scorebar", "respawnLevel", "killedBy", "spawnTick", "deathTick", "tankOverride", "movementSpeed"};

    CameraGroup(entityId entity);

    virtual void wipe() override;

    int16_t GUIunknown();
    uint32_t camera();
    entityId player();
    float FOV();
    int32_t level();
    Tank tank();
    float levelbarProgress();
    float levelbarMax();
    int32_t statsAvailable();
    CameraTable<std::string> *statNames();
    CameraTable<uint32_t> *statLevels();
    CameraTable<uint32_t> *statLimits();
    float cameraX();
    float cameraY();
    float scorebar();
    int32_t respawnLevel();
    std::string killedBy();
    uint32_t spawnTick();
    uint32_t deathTick();
    std::string tankOverride();
    float movementSpeed();

    void GUIunknown(int16_t guiUnknown);
    void camera(uint32_t camera);
    void player(entityId player);
    void FOV(float FOV);
    void level(int32_t level);
    void tank(Tank tank);
    void levelbarProgress(float levelbarProgress);
    void levelbarMax(float levelbarMax);
    void statsAvailable(int32_t statsAvailable);
    void statNames(CameraTable<std::string> *statNames);
    void statLevels(CameraTable<uint32_t> *statLevels);
    void statLimits(CameraTable<uint32_t> *statLimits);
    void cameraX(float cameraX);
    void cameraY(float cameraY);
    void scorebar(float scorebar);
    void respawnLevel(int32_t respawnLevel);
    void killedBy(std::string killedBy);
    void spawnTick(uint32_t spawnTick);
    void deathTick(uint32_t deathTick);
    void tankOverride(std::string tankOverride);
    void movementSpeed(float movementSpeed);
};
class PositionGroup : public FieldGroup
{
    struct
    {
        uint8_t x;
        uint8_t y;
        uint8_t angle;
        uint8_t motion;
    } state;
    struct
    {
        int32_t x;
        int32_t y;
        uint32_t angle;
        uint32_t motion;
    } values;

public:
    static constexpr FieldGroupId id = FieldGroupId::position;
    std::vector<std::string> fields{"x", "y", "angle", "motion"};

    PositionGroup(entityId entity);

    virtual void wipe() override;

    int32_t x();
    int32_t y();
    uint32_t angle();
    uint32_t motion();

    void x(int32_t x);
    void y(int32_t y);
    void angle(uint32_t angle);
    void motion(uint32_t motion);
};
class StyleGroup : public FieldGroup
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
    static constexpr FieldGroupId id = FieldGroupId::style;
    std::vector<std::string> fields{"styleFlags", "color", "borderThickness", "opacity", "zIndex"};

    StyleGroup(entityId entity);

    virtual void wipe() override;

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
class ScoreGroup : public FieldGroup
{
    struct
    {
        uint8_t score = 0;
    } state;
    struct
    {
        float score = 0;
    } values;

public:
    static constexpr FieldGroupId id = FieldGroupId::score;
    std::vector<std::string> fields{"score"};

    ScoreGroup(entityId entity);

    virtual void wipe() override;

    float score();
    void score(float score);
};
class TeamGroup : public FieldGroup
{
    struct
    {
        uint8_t teamColor;
        uint8_t mothershipX;
        uint8_t mothershipY;
        uint8_t mothership;
    } state;
    struct
    {
        Color teamColor;
        float mothershipX;
        float mothershipY;
        uint32_t mothership;
    } values;

public:
    static constexpr FieldGroupId id = FieldGroupId::team;
    std::vector<std::string> fields{"teamColor", "mothershipX", "mothershipY", "mothership"};

    TeamGroup();

    virtual void wipe() override;
};
