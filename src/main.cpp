#include "main.h"
#include "timer.h"
#include "plane.h"
#include "groundsky.h"
#include "ring.h"
#include "cannon.h"
#include "cannonball.h"
#include "bars.h"
#include "volcano.h"
#include "arrow.h"
#include "missile.h"
#include "para.h"
#include "bomb.h"
#include "fuelr.h"
using namespace std;

double score = 0;
int health = 100;
struct checkpoint{
    Ground island;
    vector<Cannon> can;
};

GLMatrices Matrices;
GLMatrices Matricesd;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Plane plane;
Groundsky grndsky;
vector<Ring> ring;
vector<Fuelr> fuelr;
Bars bars;
vector<Volcano> vol;
Arrow arrow;
vector<Missile> missile;
vector<checkpoint> checkpoints;
vector<Cannonball> cballs;
vector<Para> para;
vector<Bomb> bomb;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, mouse_x_rad = 0, mouse_y_rad = 0;
bool view_5 = false;
double ini_cur_x = 0, ini_cur_y = 0;
float camera_rotation_angle = 0;
int view = 1;

Timer t60(1.0 / 60);

void makecheckpoint(float x,float z){
    if(checkpoints.empty()){
        checkpoint ch;
        int temp = rand();
        ch.island = Ground( x + 100*cos(temp) , z + 100*sin(temp) );
        ch.can.push_back(Cannon(ch.island.position.x+1 , ch.island.position.z+1, glfwGetTime() ));
        ch.can.push_back(Cannon(ch.island.position.x+1 , ch.island.position.z-1, glfwGetTime()+2 ));
        ch.can.push_back(Cannon(ch.island.position.x-1 , ch.island.position.z+1, glfwGetTime()+4 ));
        ch.can.push_back(Cannon(ch.island.position.x-1 , ch.island.position.z-1, glfwGetTime()+6 ));

        temp = rand();
        vol.push_back(Volcano(ch.island.position.x+ 30*cos(temp), ch.island.position.z + 30*sin(temp) ));
        temp = rand();
        vol.push_back(Volcano(ch.island.position.x+ 30*cos(temp), ch.island.position.z + 30*sin(temp) ));
        temp = rand();
        vol.push_back(Volcano(ch.island.position.x+ 30*cos(temp), ch.island.position.z + 30*sin(temp) ));
        temp = rand();
        ring.push_back(Ring(ch.island.position.x+ 50*cos(temp),0,ch.island.position.z+ 50*sin(temp)));
        temp = rand();
        ring.push_back(Ring(ch.island.position.x+ 50*cos(temp),0,ch.island.position.z+ 50*sin(temp)));
        temp = rand();
        fuelr.push_back(Fuelr(ch.island.position.x+ 50*cos(temp),0,ch.island.position.z+ 50*sin(temp)));

        for(int i=0;i<10;i++)
        {   
            temp = rand(); 
            para.push_back(Para(ch.island.position+ glm::vec3(20*cos(temp),rand()%20,20*sin(temp))));
        }

        checkpoints.push_back(ch);
    }
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);


    makecheckpoint(plane.position.x,plane.position.z);

    glm::vec3 eye;
    glm::vec3 y_rot_vec;
    glm::vec4 eye1 = glm::vec4(plane.position.x+20*screen_zoom*plane.Iden[2][0]+4*screen_zoom*plane.Iden[1][0],plane.position.y+20*screen_zoom*plane.Iden[2][1]+4*screen_zoom*plane.Iden[1][1],plane.position.z+20*screen_zoom*plane.Iden[2][2]+4*screen_zoom*plane.Iden[1][2],1);;
    glm::vec4 eye2;
    glm::vec3 target;
    glm::vec3 up;
    glm::vec3 eyed = glm::vec3(0,0,0.1);
    glm::vec3 targetd = glm::vec3(0,0,0);
    glm::vec3 upd=glm::vec3(0,1,0);
    bars = Bars(plane.fuel,plane.position.y+10,plane.speed*100, -glm::vec3(plane.Iden[2]) );
    arrow = Arrow(plane.position,glm::vec3(checkpoints[0].island.position.x,0,checkpoints[0].island.position.z));
    if(view==1){
        view_5 = false;
        eye = glm::vec3(plane.position.x,plane.position.y,plane.position.z);
        target = glm::vec3(plane.position.x  - plane.Iden[2][0],plane.position.y - plane.Iden[2][1],plane.position.z - plane.Iden[2][2]);
        up = glm::vec3(plane.Iden[1][0],plane.Iden[1][1],plane.Iden[1][2]);
    }
    else if(view==2){
        view_5 = false;
        eye = glm::vec3(plane.position.x,50,plane.position.z);
        target = glm::vec3(plane.position.x,plane.position.y,plane.position.z);
        up = glm::vec3(-plane.Iden[2][0],-plane.Iden[2][1],-plane.Iden[2][2]);
    }
    else if(view==3){
        view_5 = false;
        eye = glm::vec3(checkpoints[0].island.position.x,10,checkpoints[0].island.position.z);
        target = glm::vec3(plane.position.x,plane.position.y,plane.position.z);
        up = glm::vec3(0,1,0);
    }

    else if(view==4){
        view_5 = false;
        eye = glm::vec3(plane.position.x+10*plane.Iden[2][0]+2*plane.Iden[1][0],plane.position.y+10*plane.Iden[2][1]+2*plane.Iden[1][1],plane.position.z+10*plane.Iden[2][2]+2*plane.Iden[1][2]);
        target = glm::vec3(plane.position.x - plane.Iden[2][0],plane.position.y  - plane.Iden[2][1] ,plane.position.z - plane.Iden[2][2]);
        up = glm::vec3(plane.Iden[1][0],plane.Iden[1][1],plane.Iden[1][2]);
    }
    else if(view==5){
        view_5 =true;
        target = glm::vec3(plane.position.x,plane.position.y ,plane.position.z );
        eye2 = glm::translate(target)*glm::rotate(-mouse_x_rad,glm::vec3(0,1,0))*glm::translate(-target)*eye1;
        eye = glm::vec3(eye2);
        y_rot_vec = glm::vec3( eye[2]-target[2],0,eye[0]-target[0]);
        eye = glm::vec3(glm::translate(target)*glm::rotate(-mouse_y_rad,glm::vec3(y_rot_vec[0],y_rot_vec[1],y_rot_vec[2]))*glm::translate(-target)*eye2);
        up = glm::vec3(0,1,0);
    }
    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    Matricesd.view = glm::lookAt( eyed, targetd, upd );
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VPd = Matricesd.projection * Matricesd.view;
    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    glm::mat4 MVPd;

    // Scene render

    for(int i=0;i<para.size();i++){
        para[i].draw(VP);
    }

    checkpoints[0].island.draw(VP);
    for(int i=0;i<checkpoints[0].can.size();i++){
        checkpoints[0].can[i].draw(VP);
    }
    for(int i=0;i<cballs.size();i++){
        cballs[i].draw(VP);
    }
    bars.draw(VPd);
    grndsky.draw(VP);
    for(int i=0;i<ring.size();i++)
        ring[i].draw(VP);
    for(int i=0;i<fuelr.size();i++)
        fuelr[i].draw(VP);
    for(int i=0;i<missile.size();i++)
        missile[i].draw(VP);

    for(int i=0;i<bomb.size();i++)
        bomb[i].draw(VP);

    for(int i=0;i<vol.size();i++)
        vol[i].draw(VP);

    plane.draw(VP);
    arrow.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int a  = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int q  = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int s = glfwGetKey(window, GLFW_KEY_S);
    int v1 = glfwGetKey(window, GLFW_KEY_1);
    int v2 = glfwGetKey(window, GLFW_KEY_2);
    int v3 = glfwGetKey(window, GLFW_KEY_3);
    int v4 = glfwGetKey(window, GLFW_KEY_4);
    int v5 = glfwGetKey(window, GLFW_KEY_5);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int fire = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1);
    int bomb_fire = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2);    
    int para_fire = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3);

    if (a) {
        plane.roll(2.0f);
    }
    else if (d) {
        plane.roll(-2.0f);
    }
    if (q) {
        plane.yaw(2.0f);
    }
    else if (e) {
        plane.yaw(-2.0f);
    }
    if (up) {
        plane.pitch(-2.0f);
    }
    else if (down) {
        plane.pitch(2.0f);
    }
    if(v1) {
        view = 1;
    }
    else if(v2) {
        view = 2;
    }
    else if(v3) {
        view = 3;
    }
    else if(v4) {
        view = 4;
    }
    else if(v5) {
        view = 5;
    }
    if (w && plane.speed<=1) {
        plane.speed+=0.001;
    }
    if (s && plane.speed>0.01) {
        plane.speed-=0.005;
    }
    if (!checkpoints[0].can.empty() && (missile.empty() || glfwGetTime()-missile.back().timer>3 ) ) {
        if(para_fire && !para.empty())
            missile.push_back(Missile(plane.position, para[0].position - plane.position, glfwGetTime() ));
        else if(fire)
        missile.push_back(Missile(plane.position, checkpoints[0].can[0].position - plane.position, glfwGetTime() ));
    }
    if(bomb_fire && bomb.empty()){
        bomb.push_back(Bomb(plane.position,glm::vec3(0,0,1)));
    }
}

void tick_elements() {

    score+=0.01;

    if(health<=0){
        cout<<"Zero Health";
        quit(window);
    }

    if(plane.fuel<=0)
    {
        cout<<"Ran out of fuel";
        quit(window);
    }

    for(int i=0;i<bomb.size();i++){
        if(bomb[i].position.y<-10){
            bomb.erase(bomb.begin()+i);
        }
    }


    for(int i=0;i<missile.size();i++){
        missile[i].tick();
    }

    if(checkpoints[0].can.empty()){
        checkpoints.clear();
    }

    for(int i=0;i<para.size();i++){
        para[i].tick();
    }

    for(int i=0;i<para.size();i++){
        if(para[i].position.y<=-11)
            para.erase(para.begin()+i);
    }

    for(int i=0;i<checkpoints[0].can.size();i++)
    {
        if(glfwGetTime() - checkpoints[0].can[i].timer>5){
            checkpoints[0].can[i].timer = glfwGetTime();
            cballs.push_back(Cannonball(checkpoints[0].can[i].position.x,checkpoints[0].can[i].position.z,plane.position - checkpoints[0].can[i].position ));   
        }
    }

    for(int i = 0; i < cballs.size(); i++)
    {   
        cballs[i].tick();
    }
    for(int i=0;i<bomb.size();i++)
        bomb[i].tick();

    /* Detect Collisions */
    for(int i=0;i<cballs.size();i++){
        if(detect_collision_1(cballs[i],plane)){
            cballs.erase(cballs.begin()+i);
            health-=5;
        }
    }

    for(int i=0;i<ring.size();i++){
        if(detect_collision_4(ring[i],plane)){
            score+=10;
            ring.erase(ring.begin()+i);
        }
    }

    for(int i=0;i<fuelr.size();i++){
        if(detect_collision_6(fuelr[i],plane)){
            plane.fuel=90;
            fuelr.erase(fuelr.begin()+i);
        }
    }

    for(int i=0;i<para.size();i++){
        for(int j=0;j<missile.size();j++){
            if(detect_collision_5(missile[j],para[i])){
                para.erase(para.begin()+i);
                score+=10;
                missile.erase(missile.begin()+j);
            }
        }
    }

    for(int i=0;i<vol.size();i++){
        if(detect_collision_3(vol[i],plane))
        {   cout<<"Too close to volcano"; 
            quit(window);
        }
    }

    for(int i=0;i<cballs.size();i++){
        if(cballs[i].position.y>=100)
            cballs.erase(cballs.begin()+i);
    }

     if(plane.position.y<=-10){
        cout<<"Crashed into the sea"<<endl;
        quit(window);
    }

    for(int i=0;i<checkpoints[0].can.size();i++){
        for(int j=0;j<missile.size();j++){
            if(detect_collision(checkpoints[0].can[i],missile[j])){
                checkpoints[0].can.erase(checkpoints[0].can.begin()+i);
                missile.erase(missile.begin()+j);
                score+=10;
            }
        }

        for(int j=0;j<bomb.size();j++){
            if(detect_collision_2(bomb[j],checkpoints[0].can[i]))
            {
                checkpoints[0].can.erase(checkpoints[0].can.begin()+i);
                bomb.erase(bomb.begin()+j);
                score+=10;
            }
        }
    }
    

    plane.tick();
    grndsky = Groundsky(plane.position.x,plane.position.z);
    ostringstream str1;
    str1<<"Score: "<<int(score)<<" Health: "<<health;
    glfwSetWindowTitle(window, str1.str().c_str() );
    //camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    plane = Plane(0, 0, 0);
    grndsky = Groundsky(0,0);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(Cannon c, Missile m) {
    if( sqrt(pow(c.position.x-m.position.x,2) + pow(c.position.y-m.position.y,2) + pow(c.position.z-m.position.z,2))<1.5 ){
        return true;
    }
    else
        return false;
    
}

bool detect_collision_1(Cannonball cball, Plane p){
    glm::mat4 translate = glm::translate(-plane.position);
    glm::mat4 rotate = glm::mat4(1.0f);
    rotate[0][0] = p.Iden[0][0];
    rotate[1][0] = p.Iden[0][1];
    rotate[2][0] = p.Iden[0][2];

    rotate[0][1] = p.Iden[1][0];
    rotate[1][1] = p.Iden[1][1];
    rotate[2][1] = p.Iden[1][2];

    rotate[0][2] = p.Iden[2][0];
    rotate[1][2] = p.Iden[2][1];
    rotate[2][2] = p.Iden[2][2];

    glm::vec4 temp = glm::vec4(cball.position.x,cball.position.y,cball.position.z,1);
    glm::vec3 temp1 = glm::vec3( rotate*translate*temp );
    if(temp1.z<=4 && temp1.z>=0 && temp1.x*temp1.x + temp1.y*temp1.y<=0.5*0.5)
        return true;
    else
        return false;
}

bool detect_collision_2(Bomb bmb, Cannon c){
    if( glm::distance(bmb.position, c.position)<2 )
        return true;
    else
        return false;
}

bool detect_collision_3(Volcano vol, Plane p){
    if(p.position.y<=0 &&  glm::distance( glm::vec2(p.position.x,p.position.z), glm::vec2(vol.position.x,vol.position.z))<=3 )
        return true;
    else 
        return false;
}

bool detect_collision_4(Ring r, Plane p){
    if( abs(p.position.z-r.position.z)<0.5 && glm::distance( glm::vec2(r.position.x,r.position.y), glm::vec2(p.position.x,p.position.y) )<=2.1)
        return true;
    else
    return false;
}

bool detect_collision_5(Missile m, Para p){
    if(m.position.y<=p.position.y+1 && m.position.y>=p.position.y && glm::distance(glm::vec2(m.position.x,m.position.z), glm::vec2(p.position.x,p.position.z))<1.5)
        return true;
    else 
        return false;
}

bool detect_collision_6(Fuelr r, Plane p){
    if( abs(p.position.z-r.position.z)<0.5 && glm::distance( glm::vec2(r.position.x,r.position.y), glm::vec2(p.position.x,p.position.y) )<=2.1)
        return true;
    else
    return false;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(45.0f, 1.0f, 1.0f, 1000.0f);
    Matricesd.projection = glm::ortho(left,right,bottom,top);
}
