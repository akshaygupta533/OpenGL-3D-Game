#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float z, double time) {
    this->position = glm::vec3(x, -10, z);
    this->rot_yaw = 0;
    this->rot_pitch = 0;
    this->rot_roll = 0;
    this->speed = 1;
    this->timer = time;
    this->Iden = glm::mat4(1.0f);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[200*9];
    float angle=0;
    float rot_angle = 2*M_PI/100;

    for(int i=0;i<100;i++){
        vertex_buffer_data[18*i+2]=0.2*cos(angle);
        vertex_buffer_data[18*i]=0.2*sin(angle);
        vertex_buffer_data[18*i+1]=0;

        vertex_buffer_data[18*i+5]=0.2*cos(angle);
        vertex_buffer_data[18*i+3]=0.2*sin(angle);
        vertex_buffer_data[18*i+4]=1;

        vertex_buffer_data[18*i+8]=0.2*cos(angle+rot_angle);
        vertex_buffer_data[18*i+6]=0.2*sin(angle+rot_angle);
        vertex_buffer_data[18*i+7]=0;

        vertex_buffer_data[18*i+11]=0.2*cos(angle+rot_angle);
        vertex_buffer_data[18*i+9]=0.2*sin(angle+rot_angle);
        vertex_buffer_data[18*i+10]=0;

        vertex_buffer_data[18*i+14]=0.2*cos(angle+rot_angle);
        vertex_buffer_data[18*i+12]=0.2*sin(angle+rot_angle);
        vertex_buffer_data[18*i+13]=1;

        vertex_buffer_data[18*i+17]=0.2*cos(angle);
        vertex_buffer_data[18*i+15]=0.2*sin(angle);
        vertex_buffer_data[18*i+16]=1;

        angle+=rot_angle;

    }
    this->object = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->Iden);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Cannon::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

