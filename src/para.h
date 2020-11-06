#include "main.h"
#include <string>

#ifndef PARA_H
#define PARA_H


class Para {
public:
    Para() {}
    Para(glm::vec3 para_pos);
    glm::vec3 position;
    float rotation;
    float rot_yaw;
    float rot_roll;
    float rot_pitch;
    double timer;
    void roll(float rot);
    void yaw (float rot);
    void pitch(float rot);
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    glm::mat4 Iden;
private:
    VAO *object[50];
    VAO *object1;
};

#endif // BALL_H
