#include "plane.h"
#include "main.h"

Plane::Plane(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rot_yaw = 0;
    this->rot_pitch = 0;
    this->rot_roll = 0;
    this->speed = 0.1;
    this->Iden = glm::mat4(1.0f);
    this->fuel = 90;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[100*9];

    float angle = 0;
    float rot_angle = 2*M_PI/100;

    for(int i=0;i<100;i++){
        vertex_buffer_data[9*i]=0.0;
        vertex_buffer_data[9*i+1]=-0.2;
        vertex_buffer_data[9*i+2]=0.0;

        vertex_buffer_data[9*i+3]=0.5*cos(angle);
        vertex_buffer_data[9*i+4]=0.5*sin(angle);
        vertex_buffer_data[9*i+5]=0.3;

        vertex_buffer_data[9*i+6]=0.5*cos(angle+rot_angle);
        vertex_buffer_data[9*i+7]=0.5*sin(angle+rot_angle);
        vertex_buffer_data[9*i+8]=0.3;
    
        angle+=rot_angle;

    }
    GLfloat vertex_buffer_data1[200*9];
    angle=0;

    for(int i=0;i<100;i++){
        vertex_buffer_data1[18*i]=0.5*cos(angle);
        vertex_buffer_data1[18*i+1]=0.5*sin(angle);
        vertex_buffer_data1[18*i+2]=0.3;

        vertex_buffer_data1[18*i+3]=0.5*cos(angle);
        vertex_buffer_data1[18*i+4]=0.5*sin(angle);
        vertex_buffer_data1[18*i+5]=4;

        vertex_buffer_data1[18*i+6]=0.5*cos(angle+rot_angle);
        vertex_buffer_data1[18*i+7]=0.5*sin(angle+rot_angle);
        vertex_buffer_data1[18*i+8]=0.3;

        vertex_buffer_data1[18*i+9]=0.5*cos(angle+rot_angle);
        vertex_buffer_data1[18*i+10]=0.5*sin(angle+rot_angle);
        vertex_buffer_data1[18*i+11]=0.3;

        vertex_buffer_data1[18*i+12]=0.5*cos(angle+rot_angle);
        vertex_buffer_data1[18*i+13]=0.5*sin(angle+rot_angle);
        vertex_buffer_data1[18*i+14]=4;

        vertex_buffer_data1[18*i+15]=0.5*cos(angle);
        vertex_buffer_data1[18*i+16]=0.5*sin(angle);
        vertex_buffer_data1[18*i+17]=4;

        angle+=rot_angle;

    }

    GLfloat vertex_buffer_data2[]={
        0.5, 0, 1.5,
        0.5, 0, 3,
        3, 0, 3,

        -0.5, 0, 1.5,
        -0.5, 0, 3,
        -3, 0, 3,

        0.05,0.5,2.8,
        0,0.5,4,
        0,1.5,4,

        0,0.2,0.1,
        -0.25,0.1,0.1,
        0.25,0.1,0.1,


    };
    GLfloat vertex_buffer_data3[100*9];
    angle=0;

    for(int i=0;i<100;i++){
        vertex_buffer_data3[9*i]=0.0;
        vertex_buffer_data3[9*i+1]=0.0;
        vertex_buffer_data3[9*i+2]=4.9;

        vertex_buffer_data3[9*i+3]=0.45*cos(angle);
        vertex_buffer_data3[9*i+4]=0.45*sin(angle);
        vertex_buffer_data3[9*i+5]=4;

        vertex_buffer_data3[9*i+6]=0.45*cos(angle+rot_angle);
        vertex_buffer_data3[9*i+7]=0.45*sin(angle+rot_angle);
        vertex_buffer_data3[9*i+8]=4;
    
        angle+=rot_angle;

    }
    

    this->object = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data, COLOR_WHITE, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 200*3, vertex_buffer_data1, COLOR_WHITE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_BLACK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 100*3, vertex_buffer_data3, COLOR_FIRE, GL_FILL);
}


void Plane::roll(float rot){
    glm::mat4 rot_mat = glm::rotate(rot/180, glm::vec3(this->Iden[2][0],this->Iden[2][1],this->Iden[2][2]) );
    this->Iden = rot_mat * this->Iden ;
}

void Plane::yaw(float rot){
    glm::mat4 rot_mat = glm::rotate(rot/180, glm::vec3(this->Iden[1][0],this->Iden[1][1],this->Iden[1][2]) );
    this->Iden = rot_mat * this->Iden ;
}

void Plane::pitch(float rot){
    glm::mat4 rot_mat = glm::rotate(rot/180, glm::vec3(this->Iden[0][0],this->Iden[0][1],this->Iden[0][2]) );
    this->Iden = rot_mat * this->Iden ;
}

void Plane::draw(glm::mat4 VP) {
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
    draw3DObject(this->object3);
}

void Plane::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plane::tick() {
    this->position.x += -this->Iden[2][0]*speed;
    if(this->position.y<90)
        this->position.y += -this->Iden[2][1]*speed;
    this->position.z += -this->Iden[2][2]*speed;

    this->fuel-= speed/10;
}

