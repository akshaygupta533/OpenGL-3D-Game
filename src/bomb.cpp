#include "bomb.h"
#include "main.h"

Bomb::Bomb(glm::vec3 plane_pos, glm::vec3 dir) {
    this->position = plane_pos;
    this->rot_yaw = 0;
    this->rot_pitch = 0;
    this->rot_roll = 0;
    this->speed = 0.08;
    this->Iden = glm::mat4(1.0f);
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_datas[100][100*9];

    float angle=0;
    float rot_angle = 2*M_PI/100;
    for(int i=0;i<100;i++){
        for(int j=0;j<100;j++){
            vertex_buffer_datas[i][9*j] = 0.2*cos(M_PI_2*float(i-50)/50)*cos(angle);
            vertex_buffer_datas[i][9*j+1] = float(i-50)/300;
            vertex_buffer_datas[i][9*j+2] = 0.2*cos(M_PI_2*float(i-50)/50)*sin(angle);

            vertex_buffer_datas[i][9*j+3] = 0.2*cos(M_PI_2*float(i-50)/50)*cos(angle+rot_angle);
            vertex_buffer_datas[i][9*j+4] = float(i-50)/300;
            vertex_buffer_datas[i][9*j+5] = 0.2*cos(M_PI_2*float(i-50)/50)*sin(angle+rot_angle);

            vertex_buffer_datas[i][9*j+6] = 0;
            vertex_buffer_datas[i][9*j+7] = float(i-50)/300;
            vertex_buffer_datas[i][9*j+8] = 0;

            angle+=rot_angle;
        }
        angle=0;
    }

    GLfloat vertex_buffer_data[1*9] = {
        -0.05,float(50)/300,0,
        0.05,float(50)/300,0,
        0,0.3,0,
    };

    for(int i=0;i<100;i++)
        this->object[i] = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_datas[i], COLOR_BLACK, GL_FILL);
    
    this->object1 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data, COLOR_FIRE, GL_FILL);
}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->Iden);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    for(int i=0;i<100;i++)
        draw3DObject(this->object[i]);

    draw3DObject(this->object1);
    
}


void Bomb::tick() {
    // this->rotation += speed;
    this->position.y -= speed;
}

