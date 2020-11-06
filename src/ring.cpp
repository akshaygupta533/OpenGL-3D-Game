#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y, float z) {
    this->position = glm::vec3(x, 0, z);
    float angle = 0;
    float rot_angle = 2*M_PI/100;
    

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[200*9];
    for(int i=0;i<100;i++){
        vertex_buffer_data[18*i] = 2*cos(angle);
        vertex_buffer_data[18*i+1] = 2*sin(angle);
        vertex_buffer_data[18*i+2] = 0;

        vertex_buffer_data[18*i+3] = 2.2*cos(angle);
        vertex_buffer_data[18*i+4] = 2.2*sin(angle);
        vertex_buffer_data[18*i+5] = 0;

        vertex_buffer_data[18*i+6] = 2.2*cos(angle+rot_angle);
        vertex_buffer_data[18*i+7] = 2.2*sin(angle+rot_angle);
        vertex_buffer_data[18*i+8] = 0;

        vertex_buffer_data[18*i+9] = 2.2*cos(angle+rot_angle);
        vertex_buffer_data[18*i+10] = 2.2*sin(angle+rot_angle);
        vertex_buffer_data[18*i+11] = 0;

        vertex_buffer_data[18*i+12] = 2*cos(angle+rot_angle);
        vertex_buffer_data[18*i+13] = 2*sin(angle+rot_angle);
        vertex_buffer_data[18*i+14] = 0;

        vertex_buffer_data[18*i+15] = 2*cos(angle);
        vertex_buffer_data[18*i+16] = 2*sin(angle);
        vertex_buffer_data[18*i+17] = 0;

        angle+=rot_angle;
    }

    this->object = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->Iden);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Ring::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

