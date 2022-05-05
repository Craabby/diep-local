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
    std::unordered_map<EventId, std::vector<void (*)(void *)>> callbackList;

public:
    template <EventId id>
    void on(void (*callback)(void *))
    {
        callbackList[id].push_back(callback);
    };
    template <EventId id>
    void emit(void *argument = nullptr)
    {
        for (void (*callback)(void *) : callbackList[id])
        {
            callback(argument);
        }
    };
};
