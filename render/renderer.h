#pragma once

#include "entity.h"

class Renderer{

    protected:
        Renderer() {}
        virtual ~Renderer() {}

    public:

        virtual void begin() {}
        virtual void submit(Entity* entity) = 0;
        virtual void end() {}
        virtual void flush() = 0;
};
