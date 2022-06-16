#include <Native/Component/Physics.h>

#include <Game.h>
#include <Native/Entity.h>

PhysicsComponent::PhysicsComponent(Entity *entity)
    : entity(entity)
{
}

void PhysicsComponent::Tick(uint32_t tick)
{
    PositionComponent &position = entity->gameServer->entities.registry.get<PositionComponent>(entity->entity);
    std::vector<entityId> possibleCollisions = entity->gameServer->entities.collisionManager.Retrieve(
        (int32_t)position.position.X(),
        (int32_t)position.position.Y(),
        (int32_t)Size(),
        (int32_t)Size());

    for (entityId id : possibleCollisions)
    {
        if (entity->id == id)
            continue;

        Entity *entity = this->entity->gameServer->entities.inner[id];
        if (!entity->gameServer->entities.registry.all_of<PhysicsComponent>(entity->entity))
            continue;

        PositionComponent &otherPosition = entity->gameServer->entities.registry.get<PositionComponent>(entity->entity);
        PhysicsComponent &otherPhysics = entity->gameServer->entities.registry.get<PhysicsComponent>(entity->entity);

        Vector<float> delta = *otherPosition.position.Clone().Subtract(position.position);

        if (delta.Distance() < Size() + otherPhysics.Size())
            OnCollision(otherPhysics);
    }
}

void PhysicsComponent::OnCollision(PhysicsComponent &other)
{
    // https://www.youtube.com/watch?v=LPzyNOHY3A4&ab_channel=javidx9 amazing video
    PhysicsComponent &pA = *this;
    PhysicsComponent &pB = other;
    PositionComponent &posA = entity->gameServer->entities.registry.get<PositionComponent>(entity->entity);
    PositionComponent &posB = entity->gameServer->entities.registry.get<PositionComponent>(pB.entity->entity);

    Vector<float> delta = *posB.position.Clone().Subtract(posA.position);
    Vector<float> unitDelta = *delta.Clone().Distance(1);
    float distance = delta.Distance();
    float collisionRadius = Size() + other.Size();

    // static collision
    float overlap = 0.5 * (distance - Size() - other.Size());

    posA.position.X(posA.position.X() - (overlap * unitDelta.X()));
    posA.position.Y(posA.position.Y() - (overlap * unitDelta.Y()));

    posB.position.X(posB.position.X() + (overlap * unitDelta.X()));
    posB.position.Y(posB.position.Y() + (overlap * unitDelta.Y()));

    // the dynamic collisions
    float tangentX = -unitDelta.Y();
    float tangentY = unitDelta.X();

    float dotProductTangentA = posA.velocity.X() * tangentX + posA.velocity.Y() * tangentY;
    float dotProductTangentB = posB.velocity.X() * tangentX + posB.velocity.Y() * tangentY;

    float dotProductNormalA = posA.velocity.X() * unitDelta.X() + posA.velocity.Y() * unitDelta.Y();
    float dotProductNormalB = posB.velocity.X() * unitDelta.X() + posB.velocity.Y() * unitDelta.Y();

    float momentumA = (dotProductNormalA * (pA.Mass() - pB.Mass()) + 2 * pB.Mass() * dotProductNormalB) / (pA.Mass() + pB.Mass());
    float momentumB = (dotProductNormalB * (pB.Mass() - pA.Mass()) + 2 * pA.Mass() * dotProductNormalA) / (pB.Mass() + pA.Mass());

    posA.velocity.X(tangentX * dotProductTangentA + unitDelta.X() * momentumA);
    posA.velocity.Y(tangentY * dotProductTangentA + unitDelta.Y() * momentumA);
    posB.velocity.X(tangentX * dotProductTangentB + unitDelta.X() * momentumB);
    posB.velocity.Y(tangentY * dotProductTangentB + unitDelta.Y() * momentumB);
}

void PhysicsComponent::Wipe()
{
    state.objectFlags = 0;
    state.sides = 0;
    state.size = 0;
    state.width = 0;
    state.absorbtionFactor = 0;
    state.pushFactor = 0;
}

float PhysicsComponent::Mass()
{
    return m_Mass;
}

void PhysicsComponent::Size(float x)
{
    if (Size() == x)
        return;

    m_Mass = 3.1415926535 * x * x;

    state.size |= 1;
    entity->state |= 1;
    netProperties.size = x;
}

void PhysicsComponent::Sides(uint32_t x)
{
    if (Sides() == x)
        return;

    state.sides |= 1;
    entity->state |= 1;
    netProperties.sides = x;
}

std::vector<FieldId> PhysicsComponent::FindUpdates()
{
    std::vector<FieldId> found;

    if (state.objectFlags != 0)
        found.push_back(FieldId::ObjectFlags);
    if (state.sides != 0)
        found.push_back(FieldId::Sides);
    if (state.size != 0)
        found.push_back(FieldId::Size);
    if (state.width != 0)
        found.push_back(FieldId::Width);
    if (state.absorbtionFactor != 0)
        found.push_back(FieldId::AbsorbtionFactor);
    if (state.pushFactor != 0)
        found.push_back(FieldId::PushFactor);

    return found;
}

uint32_t PhysicsComponent::ObjectFlags()
{
    return netProperties.objectFlags;
}

uint32_t PhysicsComponent::Sides()
{
    return netProperties.sides;
}

float PhysicsComponent::Size()
{
    return netProperties.size;
}

float PhysicsComponent::Width()
{
    return netProperties.width;
}

float PhysicsComponent::AbsorbtionFactor()
{
    return netProperties.absorbtionFactor;
}

float PhysicsComponent::PushFactor()
{
    return netProperties.pushFactor;
}
