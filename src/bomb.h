#include "main.h"
#include <string>

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(glm::vec3 plane_pos, glm::vec3 dir);
    glm::vec3 position;
    float rotation;
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
    VAO *object[100];
    VAO *object1;
    
};

#endif // BALL_H
