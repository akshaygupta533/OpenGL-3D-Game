#include "bars.h"
#include "main.h"

Bars::Bars(float fuel, float altitude, float speed, glm::vec3 plane_z) {
    this->position = glm::vec3(-2,-3,0);
    this->rot_yaw = 0;
    this->rot_pitch = 0;
    this->rot_roll = 0;
    this->speed = 0.2;
    this->Iden = glm::mat4(1.0f);
    plane_z[1] = 0;
    plane_z = glm::normalize(plane_z);
    float compass_angle = acos(plane_z[2]);
    if(plane_z[0]>0)
        compass_angle = -compass_angle;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[400*9];
    GLfloat vertex_buffer_data1[80*9];
    GLfloat vertex_buffer_data2[]={
        -0.05*cos(-2*M_PI*altitude/100),-0.05*sin(-2*M_PI*altitude/100),0,
        +0.05*cos(-2*M_PI*altitude/100),+0.05*sin(-2*M_PI*altitude/100),0,
        0.25*sin(-2*M_PI*altitude/100),-0.25*cos(-2*M_PI*altitude/100),0,

        -0.05*cos(-2*M_PI*speed/100)+0.6,-0.05*sin(-2*M_PI*speed/100),0,
        +0.05*cos(-2*M_PI*speed/100)+0.6,+0.05*sin(-2*M_PI*speed/100),0,
        0.25*sin(-2*M_PI*speed/100)+0.6,-0.25*cos(-2*M_PI*speed/100),0,

        -0.05*cos(-2*M_PI*fuel/100)-0.6,-0.05*sin(-2*M_PI*fuel/100),0,
        +0.05*cos(-2*M_PI*fuel/100)-0.6,+0.05*sin(-2*M_PI*fuel/100),0,
        0.25*sin(-2*M_PI*fuel/100)-0.6,-0.25*cos(-2*M_PI*fuel/100),0,

        -0.05*cos(compass_angle)+4,-0.05*sin(compass_angle),0,
        +0.05*cos(compass_angle)+4,+0.05*sin(compass_angle),0,
        0.25*sin(compass_angle)+4,-0.25*cos(compass_angle),0,

    };
    GLfloat vertex_buffer_data3[]={
        -0.05*cos(compass_angle)+4,-0.05*sin(compass_angle),0,
        +0.05*cos(compass_angle)+4,+0.05*sin(compass_angle),0,
        -0.25*sin(compass_angle)+4,0.25*cos(compass_angle),0,
    };

    float angle = 0;
    float rot_angle = 2*M_PI/100;

    for(int i=0;i<100;i++){
        vertex_buffer_data[9*i]=0.3*cos(angle);
        vertex_buffer_data[9*i+1]=0.3*sin(angle);
        vertex_buffer_data[9*i+2]=0.0;

        vertex_buffer_data[9*i+3]=0;
        vertex_buffer_data[9*i+4]=0;
        vertex_buffer_data[9*i+5]=0;

        vertex_buffer_data[9*i+6]=0.3*cos(angle+rot_angle);
        vertex_buffer_data[9*i+7]=0.3*sin(angle+rot_angle);
        vertex_buffer_data[9*i+8]=0.0;
    
        angle+=rot_angle;
    }
    angle=0;
    for(int i=100;i<200;i++){
        vertex_buffer_data[9*i]=0.3*cos(angle)+0.6;
        vertex_buffer_data[9*i+1]=0.3*sin(angle);
        vertex_buffer_data[9*i+2]=0.0;

        vertex_buffer_data[9*i+3]=0+0.6;
        vertex_buffer_data[9*i+4]=0;
        vertex_buffer_data[9*i+5]=0;

        vertex_buffer_data[9*i+6]=0.3*cos(angle+rot_angle)+0.6;
        vertex_buffer_data[9*i+7]=0.3*sin(angle+rot_angle);
        vertex_buffer_data[9*i+8]=0.0;
    
        angle+=rot_angle;
    }
    angle=0;
    for(int i=200;i<300;i++){
        vertex_buffer_data[9*i]=0.3*cos(angle)-0.6;
        vertex_buffer_data[9*i+1]=0.3*sin(angle);
        vertex_buffer_data[9*i+2]=0.0;

        vertex_buffer_data[9*i+3]=0-0.6;
        vertex_buffer_data[9*i+4]=0;
        vertex_buffer_data[9*i+5]=0;

        vertex_buffer_data[9*i+6]=0.3*cos(angle+rot_angle)-0.6;
        vertex_buffer_data[9*i+7]=0.3*sin(angle+rot_angle);
        vertex_buffer_data[9*i+8]=0.0;
    
        angle+=rot_angle;
    }

        for(int i=300;i<400;i++){
        vertex_buffer_data[9*i]=0.3*cos(angle)+4;
        vertex_buffer_data[9*i+1]=0.3*sin(angle);
        vertex_buffer_data[9*i+2]=0.0;

        vertex_buffer_data[9*i+3]=0+4;
        vertex_buffer_data[9*i+4]=0;
        vertex_buffer_data[9*i+5]=0;

        vertex_buffer_data[9*i+6]=0.3*cos(angle+rot_angle)+4;
        vertex_buffer_data[9*i+7]=0.3*sin(angle+rot_angle);
        vertex_buffer_data[9*i+8]=0.0;
    
        angle+=rot_angle;
    }

    angle = 0;
    rot_angle = 2*M_PI/20;
    for(int i=0;i<20;i++){
        vertex_buffer_data1[9*i] = 0.25*cos(angle);
        vertex_buffer_data1[9*i+1] = 0.25*sin(angle);
        vertex_buffer_data1[9*i+2] = 0;

        vertex_buffer_data1[9*i+3] = 0.29*cos(angle);
        vertex_buffer_data1[9*i+4] = 0.29*sin(angle);
        vertex_buffer_data1[9*i+5] = 0;

        vertex_buffer_data1[9*i+6] = 0.29*cos(angle+rot_angle/5);
        vertex_buffer_data1[9*i+7] = 0.29*sin(angle+rot_angle/5);
        vertex_buffer_data1[9*i+8] = 0;

        angle+=rot_angle;
    }
    angle=0;
    for(int i=20;i<40;i++){
        vertex_buffer_data1[9*i] = 0.25*cos(angle)+0.6;
        vertex_buffer_data1[9*i+1] = 0.25*sin(angle);
        vertex_buffer_data1[9*i+2] = 0;

        vertex_buffer_data1[9*i+3] = 0.29*cos(angle)+0.6;
        vertex_buffer_data1[9*i+4] = 0.29*sin(angle);
        vertex_buffer_data1[9*i+5] = 0;

        vertex_buffer_data1[9*i+6] = 0.29*cos(angle+rot_angle/5)+0.6;
        vertex_buffer_data1[9*i+7] = 0.29*sin(angle+rot_angle/5);
        vertex_buffer_data1[9*i+8] = 0;

        angle+=rot_angle;
    }

    angle=0;
    for(int i=40;i<60;i++){
        vertex_buffer_data1[9*i] = 0.25*cos(angle)-0.6;
        vertex_buffer_data1[9*i+1] = 0.25*sin(angle);
        vertex_buffer_data1[9*i+2] = 0;

        vertex_buffer_data1[9*i+3] = 0.29*cos(angle)-0.6;
        vertex_buffer_data1[9*i+4] = 0.29*sin(angle);
        vertex_buffer_data1[9*i+5] = 0;

        vertex_buffer_data1[9*i+6] = 0.29*cos(angle+rot_angle/5)-0.6;
        vertex_buffer_data1[9*i+7] = 0.29*sin(angle+rot_angle/5);
        vertex_buffer_data1[9*i+8] = 0;

        angle+=rot_angle;
    }

    for(int i=60;i<80;i++){
        vertex_buffer_data1[9*i] = 0.25*cos(angle)+4;
        vertex_buffer_data1[9*i+1] = 0.25*sin(angle);
        vertex_buffer_data1[9*i+2] = 0;

        vertex_buffer_data1[9*i+3] = 0.29*cos(angle)+4;
        vertex_buffer_data1[9*i+4] = 0.29*sin(angle);
        vertex_buffer_data1[9*i+5] = 0;

        vertex_buffer_data1[9*i+6] = 0.29*cos(angle+rot_angle/5)+4;
        vertex_buffer_data1[9*i+7] = 0.29*sin(angle+rot_angle/5);
        vertex_buffer_data1[9*i+8] = 0;

        angle+=rot_angle;
    }

    this->object = create3DObject(GL_TRIANGLES, 400*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 80*3, vertex_buffer_data1, COLOR_WHITE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data3, COLOR_GREY, GL_FILL);
}

void Bars::draw(glm::mat4 VP) {
    Matricesd.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matricesd.model *= (translate * this->Iden);
    glm::mat4 MVPd = VP * Matricesd.model;
    glUniformMatrix4fv(Matricesd.MatrixID, 1, GL_FALSE, &MVPd[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}


void Bars::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    this->position.y += speed;
}