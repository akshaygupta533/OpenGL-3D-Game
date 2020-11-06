#include "main.h"
#include <string>

#ifndef BALL_H
#define BALL_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    float fuel;
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
