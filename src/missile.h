#include "main.h"
#include <string>

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(glm::vec3 plane_pos, glm::vec3 dir, double timer);
    glm::vec3 position;
    float rotation;
    double timer;
    float rot_yaw;
    float rot_roll;
    float rot_pitch;
    void roll(float rot);
    void yaw (float rot);
    void pitch(float rot);
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    glm::mat4 Iden;
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // BALL_H
