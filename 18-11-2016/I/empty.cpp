#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<cmath>
#include<iostream>

const static float prec = 1000.0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
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


void display(int actual_i, int actual_j, int player, bool available[3][3][2])
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    float inix=-1, iniy=-1, iniz=-20;
    for(int j=0;j<3;j++){
      for(int i=0;i<3;i++){
        if(actual_i==i and actual_j==j){ // player position
          if(player==0)
            glColor3f(0,1,1); // first player is green
          else
            glColor3f(1,1,0); // second player is yellow
        }else{
          if(!available[i][j][0]) // this belongs to player 0
            glColor3f(0,0.85,1);
          if(!available[i][j][1]) // this belongs to player 1
            glColor3f(1,0.85,0);
          if(available[i][j][0] and available[i][j][1]) // this is free
            glColor3f(1,0,0);
        }
        glBegin(GL_QUADS);
          glVertex3f(inix+i*3, iniy+j*3, iniz);
          glVertex3f(2+inix+i*3, iniy+j*3, iniz);
          glVertex3f(2+inix+i*3, 2+iniy+j*3, iniz);
          glVertex3f(inix+i*3, 2+iniy+j*3, iniz);
        glEnd();
      }
    }

}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    bool loop=true;
//    Uint32 start;
    SDL_Event event;
    init();
    bool available[3][3][2];
    for(int i=0; i<3; i++){
      for(int j=0; j<3; j++){
        available[i][j][0]=true;
        available[i][j][1]=true;
      }
    }
    int actual_j=1, actual_i=1, player = 0;
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
                  switch (event.key.keysym.sym)
                  {
                    case SDLK_UP:// up arrow
                      if(actual_j<2)
                        actual_j++;
                      break;
                    case SDLK_DOWN:// down arrow
                      if(actual_j>0)
                        actual_j--;
                      break;
                    case SDLK_RIGHT:// right arrow
                      if(actual_i<2)
                        actual_i++;
                      break;
                    case SDLK_LEFT:// left arrow
                      if(actual_i>0)
                        actual_i--;
                      break;
                    case SDLK_SPACE:
                      if(available[actual_i][actual_j][0] and available[actual_i][actual_j][1]){
                        available[actual_i][actual_j][player]=false;
                        bool cont=true;
                        for(int i=0;i<3 && cont;i++){ // find first available
                          for(int j=0;j<3 && cont;j++){
                            if( available[i][j][0] and available[i][j][1]){ // move there
                              actual_i=i;
                              actual_j=j;
                              cont = false;
                            }
                          }
                        }
                        player ++; // next player
                        player %= 2;
                      }
                      break;
                  }
                  break;
            }
        }
        display(actual_i,actual_j, player, available);
        SDL_GL_SwapBuffers();
//        if (1000/30>(SDL_GetTicks()-start)) SDL_Delay(SDL_GetTicks()-start);
    }
    SDL_Quit();
    return 0;
}
