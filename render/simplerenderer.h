#include "renderer.h"
#include <list>

class SimpleRenderer : protected Renderer{

    std::list<Entity*> m_Entities;

    public:
        SimpleRenderer();
        ~SimpleRenderer() override;

        void submit(Entity* entity) override;
        void flush() override;

};
