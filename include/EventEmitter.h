#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>
#include <vector>

enum class EventId
{
    packet,
    close,
};

class EventEmitter
{
private:
    std::unordered_map<EventId, std::function<void(void *)>> callbackList;

public:
    template <EventId id>
    void On(std::function<void(void *)> callback)
    {
        callbackList[id] = callback;
    };
    template <EventId id>
    void Emit(void *argument = nullptr)
    {
        callbackList.at(id)(argument);
    };
};
