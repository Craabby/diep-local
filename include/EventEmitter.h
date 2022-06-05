#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>
#include <vector>

enum class EventId : size_t
{
    packet,
    close,

    maxEventId
};

class EventEmitter
{
private:
    std::array<std::function<void(void *)>, (size_t)EventId::maxEventId> callbackList;

public:
    template <EventId id>
    void On(std::function<void(void *)> callback)
    {
        callbackList[static_cast<size_t>(id)] = callback;
    };
    template <EventId id>
    void Emit(void *argument = nullptr)
    {
        callbackList[static_cast<size_t>(id)](argument);
    };
};
