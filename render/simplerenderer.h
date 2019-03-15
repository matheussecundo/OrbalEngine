#include "entity.h"
#include <list>

class SimpleRenderer{

    std::list<Entity*> m_Entities;

    public:
        SimpleRenderer();
        ~SimpleRenderer();

        void submit(Entity* entity);
        void submit(const std::list<Entity*> &entities);
        void submit(const std::vector<Entity*> &entities);

        void flush();

};
