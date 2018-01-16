#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<cmath>
#include<iostream>

using namespace std;

const static float prec = 1000.0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0, 1.0, 500.0); // last two parameters are zNear and zFar
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void drawCircle(float x, float y, float z)
{
    float c = 2 * M_PI / prec, r=1;

    for(int i=0; i<prec; i++)
    {
      glBegin(GL_LINES);
		  glVertex3f(x+r*cos(c*i),y+r*sin(c*i), z);
		  glVertex3f(x+r*cos(c*(i+1)),y+r*sin(c*(i+1)), z);
      glEnd();
    }
}

bool isInside(int square_down_left_x, int square_down_left_y, int mx, int my){
  //if( square_down_left_x <= mx && square_down_left_y <= my )
  cout << mx << " " <<  my << endl;
  return false;
}
void display(int mx, int my, bool choosen)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //glColor3f(x,y,z);
	  //drawCircle(0.0, 0.0, -8);
    float inix=-1, iniy=-1, iniz=-20;
    int square_down_left_x, square_down_left_y;
    glBegin(GL_QUADS);
    for(int j=0;j<3;j++){
      for(int i=0;i<3;i++){
        square_down_left_x = inix+i*3;
        square_down_left_y = iniy+j*3;
        if(choosen){
          if(isInside(square_down_left_x, square_down_left_y, mx,my))
            glColor3f(0,1,0); //green
        }else
          glColor3f(1,0,0); //red
        glVertex3f(inix+i*3, iniy+j*3, iniz);
        glVertex3f(2+inix+i*3, iniy+j*3, iniz);
        glVertex3f(2+inix+i*3, 2+iniy+j*3, iniz);
        glVertex3f(inix+i*3, 2+iniy+j*3, iniz);
      }
    }
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
    int mx=-1, my=-1;
    bool choosen;
    while (loop)
    {
//        start=SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            choosen = false;
            switch(event.type)
            {
                case SDL_QUIT:
                  loop=false;
                  break;
                case SDL_KEYDOWN:
                  switch (event.key.keysym.sym) {
                    case SDLK_SPACE:// space key
                      choosen = true;
                      break;
                  }
                  break;

                case SDL_MOUSEMOTION:
                    mx=event.button.x;
                    my=event.button.y;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button==SDL_BUTTON_LEFT)
                      choosen=true;
                    
                    break;
                            }
        }
        display(mx, my, choosen);
        SDL_GL_SwapBuffers();
//        if (1000/30>(SDL_GetTicks()-start)) SDL_Delay(SDL_GetTicks()-start);
    }
    SDL_Quit();
    return 0;
}
