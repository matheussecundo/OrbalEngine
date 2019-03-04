#include "renderer.h"
#include <list>

class SimpleRenderer : protected Renderer{

    Buffer arrayBuf;
    Buffer indexBuf;

    std::list<const Entity*> m_Entities;

    public:
        SimpleRenderer();
        ~SimpleRenderer() override;

        void submit(const Entity* entity) override;
        void flush() override;

};
