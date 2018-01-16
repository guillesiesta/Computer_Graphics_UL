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

/*void drawCircle(float x, float y, float z)
{
    float c = 2 * M_PI / prec, r=1;

    for(int i=0; i<prec; i++)
    {
      glBegin(GL_LINES);
		  glVertex3f(x+r*cos(c*i),y+r*sin(c*i), z);
		  glVertex3f(x+r*cos(c*(i+1)),y+r*sin(c*(i+1)), z);
      glEnd();
    }
}*/

static float iniy;
static float inix;
static float iniz =-20;

const static float x = -1;
const static float y = -1;

void display(int angle)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1,0,0);

    
    glTranslatef(inix, iniy, 0);
    glRotatef(angle, 0, 0, 1);

    glBegin(GL_QUADS);
      glVertex3f(x, y, iniz);
      glVertex3f(2+x, y, iniz);
      glVertex3f(2+x, 2+y, iniz);
      glVertex3f(x, 2+y, iniz);
    glEnd();
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
      /*  if (keys[SDLK_LEFT]){
          angle += 5;
          angle %= 360;
        }
        if (keys[SDLK_RIGHT]){
          angle += 5;
          angle %= 360;
        }
        if (keys[SDLK_UP]){
          inix += push*cos(angle*M_PI/180);
          iniy += push*sin(angle*M_PI/180);
        }
        if (keys[SDLK_DOWN]){
          inix -= push*cos(angle*M_PI/180);
          iniy -= push*sin(angle*M_PI/180);
        }*/
        display(angle);
        SDL_GL_SwapBuffers();
//        if (1000/30>(SDL_GetTicks()-start)) SDL_Delay(SDL_GetTicks()-start);
    }
    SDL_Quit();
    return 0;
}
