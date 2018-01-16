#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

float angle=0.0;

//DISABLED
GLfloat Light0Ambient[]={ 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat Light0Diffuse[]={ 0.3f, 1.0f, 0.3f, 1.0f };
GLfloat Light0Specular[]={ 255, 255, 255, 1.0f };

GLfloat LightAmbient[]={ 0, 0, 0, 1.0f };
GLfloat LightDiffuse[]={ 120, 125, 135, 1.0f };
GLfloat LightSpecular[]={ 255, 255, 255, 1.0f };

GLfloat LightPosition[]={ 5.0f, 0.0f, -7.0f, 1.0f };
GLfloat SpotDirection[]={-1.0f, 0.0f, -1.0f};
GLfloat SpotCutoff=5.0f;

GLfloat MaterialAmbient[] ={ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat MaterialDiffuse[] ={ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat MaterialShininess[] ={ 10.0 };
GLfloat MaterialSpecular[] ={ 1.0f, 1.0f, 1.0f, 1.0f };


void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, Light0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Diffuse);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0Specular);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, SpotDirection);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, SpotCutoff);
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);

   glEnable(GL_LIGHT1);

    glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, MaterialDiffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, MaterialShininess);
}

void DrawCube()
{
        glBegin(GL_POLYGON);
            glNormal3f(0.0f, 1.0f, 0.0f);   // top face
            glVertex3f(0.5f, 0.5f, 0.5f);
            glVertex3f(0.5f, 0.5f, -0.5f);
            glVertex3f(-0.5f, 0.5f, -0.5f);
            glVertex3f(-0.5f, 0.5f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);   // front face
            glVertex3f(0.5f, 0.5f, 0.5f);
            glVertex3f(-0.5f, 0.5f, 0.5f);
            glVertex3f(-0.5f, -0.5f, 0.5f);
            glVertex3f(0.5f, -0.5f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON);
            glNormal3f(1.0f, 0.0f, 0.0f);   // right face
            glVertex3f(0.5f, 0.5f, 0.5f);
            glVertex3f(0.5f, -0.5f, 0.5f);
            glVertex3f(0.5f, -0.5f, -0.5f);
            glVertex3f(0.5f, 0.5f, -0.5f);
        glEnd();
        glBegin(GL_POLYGON);
            glNormal3f(-1.0f, 0.0f, 0.0f);  // left face
            glVertex3f(-0.5f, 0.5f, 0.5f);
            glVertex3f(-0.5f, 0.5f, -0.5f);
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glVertex3f(-0.5f, -0.5f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON);
            glNormal3f(0.0f, -1.0f, 0.0f);  // bottom face
            glVertex3f(-0.5f, -0.5f, 0.5f);
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glVertex3f(0.5f, -0.5f, -0.5f);
            glVertex3f(0.5f, -0.5f, 0.5f);
        glEnd();
        glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, -1.0f);  // back face
            glVertex3f(0.5f, -0.5f, -0.5f);
            glVertex3f(-0.5f, -0.5f, -0.5f);
            glVertex3f(-0.5f, 0.5f, -0.5f);
            glVertex3f(0.5f, 0.5f, -0.5f);
        glEnd();
}

void display(int moment)
{
    moment == 0 ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
    moment == 0 ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,0,-10);
    glRotatef(angle,0.0,1.0,0.0);
    //body
    glPushMatrix();
 
    glRotatef(315,0,1,0);
    glTranslatef(0,0,0);
    glScalef(2,1,1);
    DrawCube();
    glPopMatrix();

    //leg1
    glPushMatrix();

    glRotatef(315,0,1,0);
    glTranslatef(0,-0.6,0.5);
    glScalef(3,0.15,0.15);
    DrawCube();
    glPopMatrix();

    //leg2
    glPushMatrix();

    glRotatef(315,0,1,0);
    glTranslatef(0,-0.6,-0.5);
    glScalef(3,0.15,0.15);
    DrawCube();
    glPopMatrix();

    //tail
    glPushMatrix();

    glRotatef(315,0,1,0);
    glTranslatef(-1.5,0,0);
    glScalef(2.5,0.3,0.3);
    DrawCube();
    glPopMatrix();

    //tailblade
    glPushMatrix();

    glRotatef(305,0,1,0);
    glTranslatef(-2.5,0,0.3);
    glScalef(0.2,1.1,0.05);
    DrawCube();
    glPopMatrix();


    //blade
    glPushMatrix();

    glTranslatef(0,0.55,0);
    glRotatef(70,0,1,0);
    glScalef(6,0.05,0.3);
    DrawCube();
    glPopMatrix();


    angle+=1;

}


int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int petla=1, moment=0;
//    Uint32 start;
    SDL_Event zdarzenie;
    init();
    while (petla==1)
    {
//        start=SDL_GetTicks();
        while (SDL_PollEvent(&zdarzenie))
        {
            switch(zdarzenie.type)
            {
                case SDL_QUIT:
                petla=0;
                break;
                case SDL_KEYDOWN:
                  switch (zdarzenie.key.keysym.sym) {
                    case SDLK_SPACE:// space key
                      moment++;
                      moment %= 2;
                      break;
                  }
                  break;
            }
        }
        display(moment);
        SDL_GL_SwapBuffers();
//        if (1000/30>(SDL_GetTicks()-start)) SDL_Delay(SDL_GetTicks()-start);
    }
    SDL_Quit();
    return 0;
}
