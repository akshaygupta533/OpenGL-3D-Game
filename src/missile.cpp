#include "missile.h"
#include "main.h"

Missile::Missile(glm::vec3 plane_pos, glm::vec3 dir, double timer) {
    this->position = plane_pos;
    this->position.y-=1;
    this->rot_yaw = 0;
    this->rot_pitch = 0;
    this->rot_roll = 0;
    this->speed = 0.5;
    this->timer = timer;
    this->Iden = glm::mat4(1.0f);
    dir = -dir;
    glm::vec3 temp = dir;
    temp.x+=10;
    glm::vec3 n1 = glm::cross(dir,temp);
    glm::vec3 n2 = glm::cross(dir,n1);

    dir = glm::normalize(dir);
    n1 = glm::normalize(n1);
    n2 = glm::normalize(n2);

    this->Iden[0][0]=n1[0];
    this->Iden[0][1]=n1[1];
    this->Iden[0][2]=n1[2];

    this->Iden[1][0]=n2[0];
    this->Iden[1][1]=n2[1];
    this->Iden[1][2]=n2[2];

    this->Iden[2][0]=dir[0];
    this->Iden[2][1]=dir[1];
    this->Iden[2][2]=dir[2];

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[200*9];
    GLfloat vertex_buffer_data1[100*9];
    GLfloat vertex_buffer_data2[100*9];
    float angle=0;
    float rot_angle = 2*M_PI/100;

    for(int i=0;i<100;i++){
        vertex_buffer_data[18*i]=0.1*cos(angle);
        vertex_buffer_data[18*i+1]=0.1*sin(angle);
        vertex_buffer_data[18*i+2]=0.5;

        vertex_buffer_data[18*i+3]=0.1*cos(angle);
        vertex_buffer_data[18*i+4]=0.1*sin(angle);
        vertex_buffer_data[18*i+5]=2;

        vertex_buffer_data[18*i+6]=0.1*cos(angle+rot_angle);
        vertex_buffer_data[18*i+7]=0.1*sin(angle+rot_angle);
        vertex_buffer_data[18*i+8]=0.5;

        vertex_buffer_data[18*i+9]=0.1*cos(angle+rot_angle);
        vertex_buffer_data[18*i+10]=0.1*sin(angle+rot_angle);
        vertex_buffer_data[18*i+11]=0.5;

        vertex_buffer_data[18*i+12]=0.1*cos(angle+rot_angle);
        vertex_buffer_data[18*i+13]=0.1*sin(angle+rot_angle);
        vertex_buffer_data[18*i+14]=2;

        vertex_buffer_data[18*i+15]=0.1*cos(angle);
        vertex_buffer_data[18*i+16]=0.1*sin(angle);
        vertex_buffer_data[18*i+17]=2;

        angle+=rot_angle;

    }
    angle = 0;

    for(int i=0;i<100;i++){
        vertex_buffer_data1[9*i] = 0.1*cos(angle);
        vertex_buffer_data1[9*i+1] = 0.1*sin(angle);
        vertex_buffer_data1[9*i+2] = 0.5;

        vertex_buffer_data1[9*i+3] = 0.1*cos(angle+rot_angle);
        vertex_buffer_data1[9*i+4] = 0.1*sin(angle+rot_angle);
        vertex_buffer_data1[9*i+5] = 0.5;

        vertex_buffer_data1[9*i+6] = 0;
        vertex_buffer_data1[9*i+7] = 0;
        vertex_buffer_data1[9*i+8] = 0;
        
        angle+=rot_angle;
    }
    angle=0;
    for(int i=0;i<100;i++){
        vertex_buffer_data2[9*i] = 0.06*cos(angle);
        vertex_buffer_data2[9*i+1] = 0.06*sin(angle);
        vertex_buffer_data2[9*i+2] = 2;

        vertex_buffer_data2[9*i+3] = 0.06*cos(angle+rot_angle);
        vertex_buffer_data2[9*i+4] = 0.06*sin(angle+rot_angle);
        vertex_buffer_data2[9*i+5] = 2;

        vertex_buffer_data2[9*i+6] = 0;
        vertex_buffer_data2[9*i+7] = 0;
        vertex_buffer_data2[9*i+8] = 3;
        
        angle+=rot_angle;
    }


    this->object = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data2, COLOR_FIRE, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * this->Iden);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}


void Missile::tick() {
    // this->rotation += speed;
    this->position.x -= speed*this->Iden[2][0];
    this->position.y -= speed*this->Iden[2][1];
    this->position.z -= speed*this->Iden[2][2];
}

