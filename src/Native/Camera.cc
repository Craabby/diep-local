
#include <Native/Camera.h>
#include <Native/FieldGroups.h>

CameraEntity::CameraEntity(entityId arena)
    : camera(new CameraGroup(arena))
{
}
