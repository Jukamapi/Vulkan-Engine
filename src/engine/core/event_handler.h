#pragma once

#include "engine/core/event.h"

class Context;

class EventHandler
{
public:
    EventHandler(Context& context);
    void handle(const Event& event);

private:
    Context* m_context;

    void onWindowResize(uint32_t width, uint32_t height);
    void onMouseMove(int32_t x, int32_t y);

};