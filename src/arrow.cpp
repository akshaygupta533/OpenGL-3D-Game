#include"arrow.h"
#include "main.h"

Arrow::Arrow(glm::vec3 plane_pos, glm::vec3 check_pos) {
    this->position = glm::vec3(plane_pos.x, plane_pos.y + 1, plane_pos.z);
    this->rot_yaw = 0;
    this->rot_pitch = 0;
    this->rot_roll = 0;
    this->speed = 1;
    this->Iden = glm::mat4(1.0f);
    float norm = sqrt((plane_pos[0] - check_pos[0])*(plane_pos[0] - check_pos[0]) + (plane_pos[2] - check_pos[2])*(plane_pos[2] - check_pos[2]));
    this->Iden[0][2] = (check_pos[0] - plane_pos[0])/norm;
    this->Iden[1][2] = 0 ;
    this->Iden[2][2] = (check_pos[2] - plane_pos[2])/norm;

    this->Iden[0][0] = -(check_pos[2] - plane_pos[2])/norm;
    this->Iden[1][0] = 0;
    this->Iden[2][0] = (check_pos[0] - plane_pos[0])/norm;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[]={
        -0.5,0,0,
        0.5,0,0,
        0.5,0,1,

        0.5,0,1,
        -0.5,0,1,
        -0.5,0,0,

        -0.8,0,1,
        0.8,0,1,
        0,0,2.5,

    };

    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    
}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->Iden);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Arrow::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}