#pragma once

#include "engine/core/event.h"

#include <queue>

class EventSystem
{
public:
    static EventSystem& instance()
    {
        static EventSystem s_instance;
        return s_instance;
    }

    ~EventSystem() = default;
    EventSystem(const EventSystem&) = delete;
    EventSystem& operator=(const EventSystem&) = delete;
    EventSystem(EventSystem&&) = delete;
    EventSystem& operator=(EventSystem&&) = delete;

    void push(const Event& event)
    {
        m_queue.push(event);
    }

    Event pop()
    {
        Event event = m_queue.front();
        m_queue.pop();
        return event;
    }

    bool hasEvents() const
    {
        return !m_queue.empty();
    }

    void clear()
    {
        while (!m_queue.empty()) m_queue.pop();
    }

private:
    EventSystem() = default;
    std::queue<Event> m_queue;
};