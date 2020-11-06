#include "groundsky.h"
#include "main.h"

Groundsky::Groundsky(float x, float z) {
    this->position = glm::vec3(x, 0, z);
    this->rot_yaw = 0;
    this->rot_pitch = 0;
    this->rot_roll = 0;
    this->speed = 1;
    this->Iden = glm::mat4(1.0f);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[]={
        -1000.0,-10.0,1000.0,
        1000.0,-10.0,1000.0,
        -1000.0,-10.0,-1000.0,

        -1000.0,-10.0,-1000.0,
        1000.0,-10.0,-1000.0,
        1000.0,-10.0,1000.0,

    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_SEA, GL_FILL);
}

void Groundsky::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->Iden);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Groundsky::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

Ground::Ground(float x, float z) {
    this->position = glm::vec3(x, -10, z);
    this->rot_yaw = 0;
    this->rot_pitch = 0;
    this->rot_roll = 0;
    this->speed = 1;
    this->Iden = glm::mat4(1.0f);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[100*9];
    float angle = 0;
    float rot_angle = 2*M_PI/100;
    for(int i=0;i<100;i++){
        vertex_buffer_data[9*i+2] = 2*cos(angle);
        vertex_buffer_data[9*i] = 2*sin(angle);
        vertex_buffer_data[9*i+1] = 0;

        vertex_buffer_data[9*i+5] = 2*cos(angle+rot_angle);
        vertex_buffer_data[9*i+3] = 2*sin(angle+rot_angle);
        vertex_buffer_data[9*i+4] = 0;

        vertex_buffer_data[9*i+8] = 0;
        vertex_buffer_data[9*i+6] = 0;
        vertex_buffer_data[9*i+7] = 0.5;

        angle+=rot_angle;

    }
    this->object = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data, COLOR_GREEN, GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->Iden);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Ground::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}