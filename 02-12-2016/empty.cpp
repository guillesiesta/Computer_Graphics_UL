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


void drawCircle(float x, float y, float z, float r)
{
    int prec = 100;
    float c = 2 * M_PI / prec;
    // glBegin(GL_LINES);
    for(int i=0; i<prec; i++)
    {

		  glVertex3f(x+r*cos(c*i),y+r*sin(c*i), z);
		  glVertex3f(x+r*cos(c*(i+1)),y+r*sin(c*(i+1)), z);

    }
    // glEnd();
}

inline float distance(float x0, float y0, float x1, float y1){
  return sqrt((x1-x0)*(x1-x0)+(y1-y0)*(y1-y0));
}

void drawSphere(float x, float y, float z)
{
    int prec = 100;
    float c = 2 * M_PI / prec,x0,neg_x0,x1,y0,neg_y0,y1,r=1;
    glBegin(GL_LINES);
    for(int i=0; i<prec; i++)
    {
      x0 = x+r*cos(c*i);
      y0 = y+r*sin(c*i);
      neg_x0 = x+r*cos((-1)*c*i);
      neg_y0 = y+r*sin((-1)*c*i);      
      x1 = x+r*cos(c*(i+1));
      y1 = y+r*sin(c*(i+1));
      drawCircle(z,y,x,distance(x0,y0,neg_x0,neg_y0));
      glVertex3f(x0,y0,z);
      glVertex3f(x1,y1,z);

    }
    glEnd();
}

static float iniy;
static float inix;
static float iniz =-20;

const static float x = -1;
const static float y = -1;

void display(int angle)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1,1,1);
    glRotatef(angle, 0, 1, 0);

    drawSphere(1,1,-10);
}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    bool loop=true;
//    Uint32 start;
    SDL_Event event;
    init();
    int angle=90;

    SDL_EnableKeyRepeat(10,0);
    Uint8 *keys = SDL_GetKeyState(NULL);
    while (loop)
    {
//        start=SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                  loop=false;
                  break;
                case SDL_KEYDOWN:
                  switch (event.key.keysym.sym) {
                    case SDLK_UP:// up arrow
                      inix += cos(angle*M_PI/180);
                      iniy += sin(angle*M_PI/180);
                      break;
                    case SDLK_DOWN:
                      inix -= cos(angle*M_PI/180);
                      iniy -= sin(angle*M_PI/180);
                      break;
                    case SDLK_RIGHT:// right arrow
                      angle += -5;
                      angle %= 360;
                      break;
                    case SDLK_LEFT:// left arrow
                      angle += 5;
                      angle %= 360;
                      break;
                  }
                  break;
            }
        }
        display(angle);
        SDL_GL_SwapBuffers();
//        if (1000/30>(SDL_GetTicks()-start)) SDL_Delay(SDL_GetTicks()-start);
    }
    SDL_Quit();
    return 0;
}
