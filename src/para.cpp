#include "para.h"
#include "main.h"

Para::Para(glm::vec3 para_pos) {
    this->position = para_pos;
    this->rot_yaw = 0;
    this->rot_pitch = 0;
    this->rot_roll = 0;
    this->speed = 0.5;
    this->Iden = glm::mat4(1.0f);
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_datas[50][25*9];
    GLfloat vertex_buffer_data[]={
        0,0,0,
        cos(M_PI/4),sin(M_PI/4),-0.5,
        cos(M_PI/4),sin(M_PI/4),0.5,

        0,0,0,
        -cos(M_PI/4),sin(M_PI/4),-0.5,
        -cos(M_PI/4),sin(M_PI/4),0.5,
    };

    float angle=0;
    float rot_angle = 2*M_PI/100;

    for(int j=0;j<50;j++){

        for(int i=0;i<25;i++){

            vertex_buffer_datas[j][9*i] = 0;
            vertex_buffer_datas[j][9*i+1] = 0;
            vertex_buffer_datas[j][9*i+2] = 0;

            vertex_buffer_datas[j][9*i+3] = cos(angle+M_PI/4);
            vertex_buffer_datas[j][9*i+4] = sin(angle+M_PI/4);
            vertex_buffer_datas[j][9*i+5] = float(j-25)/50;

            vertex_buffer_datas[j][9*i+6] = cos(angle+M_PI/4+rot_angle);
            vertex_buffer_datas[j][9*i+7] = sin(angle+M_PI/4+rot_angle);
            vertex_buffer_datas[j][9*i+8] = float(j-25)/50;

            angle+=rot_angle;
        }
        angle = 0;
    }


    glPointSize(3);
    for(int i=0;i<50;i++)
        this->object[i] = create3DObject(GL_TRIANGLES, 25*3, vertex_buffer_datas[i], COLOR_RED, GL_POINT);
    
    glLineWidth(2);
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, COLOR_BLACK, GL_LINE);
}

void Para::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->Iden);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<50;i++)
        draw3DObject(this->object[i]);
    draw3DObject(this->object1);
}


void Para::tick() {
    // this->rotation += speed;
    this->position.y-=0.01;
}

