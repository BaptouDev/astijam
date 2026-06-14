#include <vector>
#include <raylib.h>
#include "vector2.h"

class PhysicsBody{
    public:
        Rectangle collision_rect;
        Vector2f position;
        Vector2f velocity;
        PhysicsBody(Vector2f position, Vector2f dimensions, Vector2f offset);
        void update_physics_col_list(std::vector<PhysicsBody> col_list,float dt);
    private:
        Vector2f last_pos;
        Vector2f offset;
        Rectangle base_rect;
};

