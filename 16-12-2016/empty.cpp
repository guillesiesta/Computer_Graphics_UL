#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<cmath>
#include<iostream>

using namespace std;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

static float iniy = -2;
static float inix = 0;
static float iniz = -10;

const static float x = -1;
const static float y = -1;
const static float alpha = 30;
const static float accel = 9.8*sin(alpha*M_PI/180);
const static float inctime = 0.01;
static float time1 = 0;
static float incspace;

inline float speed(float t){
  return accel*t;
}
inline float space(float t){
  return speed(t)*t + 0.5*accel*t*t;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1,1,1);
    int longitude = 5;
    glBegin(GL_TRIANGLES);
      glVertex3f(inix,iniy,iniz);
      glVertex3f(inix-longitude,iniy,iniz);
      glVertex3f(inix-longitude,tan(alpha*M_PI/180),iniz);
    glEnd();
    int x_q = inix-longitude;
    int y_q = tan(alpha*M_PI/180);

    glColor3f(1,1,0);
    if(time1>2){
      time1=0;
    }else{
        float dx = space(time1)*cos(alpha*M_PI/180);
        float dy = -1*space(time1)*sin(alpha*M_PI/180);

        glTranslatef(dx, dy, 0);
    }
    glRotatef(-30,0,0,1);
    glBegin(GL_QUADS);
      glVertex3f(x_q,y_q+1,iniz);
      glVertex3f(x_q+1,y_q+1,iniz);
      glVertex3f(x_q+1,y_q,iniz);
      glVertex3f(x_q,y_q,iniz);
    glEnd();

}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    bool loop=true;

    SDL_Event event;
    init();
    while (loop)
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                  loop=false;
                  break;
            }
        }
        time1 += inctime;
        display();
        SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
