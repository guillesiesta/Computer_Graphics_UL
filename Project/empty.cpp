#include<SDL/SDL.h>

#include<GL/gl.h>
#include<GL/glut.h> // includes GL/glu.h

#include<math.h>
#include<vector>
#include<iostream>

#define NOFILLED 1
#define FILLED 0

const unsigned npoints=100;

class Point3D{
  private:
    GLfloat coord[3];
  public:
    Point3D(){
      coord[0]=0;
      coord[1]=0;
      coord[2]=0;
    }
    Point3D(GLfloat x, GLfloat y, GLfloat z){
      coord[0]=x;
      coord[1]=y;
      coord[2]=z;
    }
    Point3D(const Point3D &p){
      coord[0]=p[0];
      coord[1]=p[1];
      coord[2]=p[2];
    }
    const GLfloat * toArray(){
      return coord;
    }
    GLfloat & operator[](const int index){ // write only
      return this->coord[index];
    }
    const GLfloat operator[](const int index) const{ // read only
      return this->coord[index];
    }
    Point3D operator+(const Point3D &p1) const{
      return Point3D(p1[0]+this->coord[0], p1[1]+this->coord[1], p1[2]+this->coord[2]);
    }
    bool operator==(const Point3D &p1) const{
      return coord[0]==p1[0] and coord[1]==p1[1] and coord[2]==p1[2];
    }
};

class Box{
  private:
    GLint type;
    GLfloat size;
    Point3D bottom_side[4];
    GLfloat vertices[24]; // 8*3 of vertex coords

    GLubyte indices_filled[24]={0, 1, 2, 3,   // bottom
                                4, 5, 6, 7,   // top
                                0, 1, 5, 4,   // front
                                3, 2, 6, 7,   // back
                                1, 2, 6, 5,   // right
                                0, 3, 7, 4};  // left
    GLubyte indices_nofilled[24]= { 0, 1,  1, 2,  2, 3,  3, 0, // top
                                    4, 5,  5, 6,  6, 7,  7, 4, // bottom
                                    0, 4,  1, 5,  2, 6,  3, 7};
    GLfloat colors[72] = {1,1,1,  1,1,0,  1,0,0,  1,0,1,              
                          1,1,1,  1,0,1,  0,0,1,  0,1,1,              
                          1,1,1,  0,1,1,  0,1,0,  1,1,0,              
                          1,1,0,  0,1,0,  0,0,0,  1,0,0,              
                          0,0,0,  0,0,1,  1,0,1,  1,0,0,              
                          0,0,1,  0,0,0,  0,1,0,  0,1,1};             
                         
  public:
    Box(Point3D init, GLfloat size){
      this->size = size;
      this->bottom_side[0] = init;
      this->bottom_side[1] = Point3D(init[0]+size, init[1], init[2]);
      this->bottom_side[2] = Point3D(init[0]+size, init[1], init[2]+size);
      this->bottom_side[3] = Point3D(init[0]     , init[1], init[2]+size);
      for(unsigned i=0, j=0; i<12; i+=3, j++){
        //bottom vertices
        vertices[i]    = bottom_side[j][0];
        vertices[i+1]  = bottom_side[j][1];
        vertices[i+2]  = bottom_side[j][2];
        //top vertices
        vertices[i+12] = bottom_side[j][0];
        vertices[i+13] = bottom_side[j][1] + size;
        vertices[i+14] = bottom_side[j][2];
      }
    }

    void show(unsigned &type){
      glEnableClientState(GL_VERTEX_ARRAY);  
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(3, GL_FLOAT, 0, colors);
      if(type == FILLED){
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices_filled);
      }else{
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, indices_nofilled);         
      }
      glDisableClientState(GL_COLOR_ARRAY);  
      glDisableClientState(GL_VERTEX_ARRAY);  
    }

    std::vector<Box> generate(){
      std::vector<Box> boxes;
      GLfloat newSize = size/3.0;
      for(unsigned i=0; i<3; i++){
        for(unsigned j=0; j<3; j++){
          for(unsigned k=0; k<3; k++){
            if( !(i==1 and j==1) and !(i==1 and k==1) and !(k==1 and j==1) ){
              boxes.push_back( 
                Box(Point3D(bottom_side[0][0]+newSize*i, 
                  bottom_side[0][1]+newSize*j, bottom_side[0][2]+newSize*k), newSize)
              );
            }
          }
        }
      }
      return boxes;
    }
};

class Ellipse{
  private:
    GLfloat smaxis; // semiminor axis
    GLfloat sMaxis; // semimajor axis
    Point3D center;
  public:
    Ellipse()
    {

    }
    Ellipse(Point3D center, GLfloat smaxis, GLfloat sMaxis){
      this->center = center;
      this->smaxis = smaxis;
      this->sMaxis = sMaxis;
    }
    void show(){
      GLfloat inc = 2*M_PI/npoints;
      glBegin(GL_LINE_STRIP);
      for(unsigned i=0; i<npoints; i++){
        glVertex3f(center[0]+sMaxis*cos(i*inc), center[1]+smaxis*sin(i*inc),center[2]);
        glVertex3f(center[0]+sMaxis*cos((i+1)*inc), center[1]+smaxis*sin((i+1)*inc),center[2]);
      }
      glEnd();
    }
};

class Ellipsoid{
  private:
    GLfloat sx_axis; // semi X axis
    GLfloat sy_axis; // semi Y axis
    GLfloat sz_axis; // semi Z axis
    Point3D center;
  public:
    Ellipsoid()
    {
    }
    Ellipsoid(Point3D center, GLfloat sx_axis, GLfloat sy_axis, GLfloat sz_axis){
      this->center = center;
      this->sx_axis = sx_axis;
      this->sy_axis = sy_axis;
      this->sz_axis = sz_axis;
    }
    void setCenter(Point3D new_center){
      this->center = new_center;
    }
    void show(){
      GLfloat j_step = M_PI/npoints;
      GLfloat i_step = 2*M_PI/npoints;
      for(unsigned i=0; i<npoints; i++){
        glBegin(GL_TRIANGLE_STRIP);
        for(unsigned j=0; j<npoints; j++){
          glVertex3f(center[0]+sx_axis*cos(i*i_step)*sin(j*j_step), 
                      center[1]+sy_axis*sin(i*i_step)*sin(j*j_step),
                      center[2]+sz_axis*cos(j*j_step));
          glVertex3f(center[0]+sx_axis*cos((i+1)*i_step)*sin(j*j_step), 
                      center[1]+sy_axis*sin((i+1)*i_step)*sin(j*j_step),
                      center[2]+sz_axis*cos(j*j_step));
        }
        glEnd();
      }
    }
};

class Orbit{
  private:
    // int obj_type;
    // GLfloat obj_size; 
    Ellipsoid obj;
    GLfloat smaxis;
    GLfloat sMaxis;
    Point3D center;
    Point3D current_pos;
    unsigned pos_index=0;
  public:
    Orbit(Point3D center, GLfloat smaxis, GLfloat sMaxis, Ellipsoid obj){
      this->smaxis = smaxis;
      this->sMaxis = sMaxis;
      this->center = center;
      this->current_pos = center;
      this->obj = obj;
    }
    Point3D getCurrentPos(){
      return this->current_pos;
    }
    void setCenter(Point3D new_center){
      this->center = new_center;
    }
    void show(){
      GLfloat step = 2*M_PI/npoints;
      pos_index++;
      if(center == current_pos){
        current_pos[0]=center[0]+sMaxis;
        current_pos[1]=center[1];
      }else{
        current_pos[0]=center[0]+sMaxis*cos(pos_index*step);
        current_pos[1]=center[1]+smaxis*sin(pos_index*step);
      }
      obj.setCenter(current_pos);
      obj.show();
      pos_index %= npoints;
    }
};

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

static int angle=0;
static GLdouble xW, yW, zW, c = sqrt(1/3*1/3*2)/2.0;

void display(std::vector<Orbit> & atom, Orbit & around, unsigned type)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // angle+=1;
    // glTranslatef( xW+c, yW+c, zW+c-1);
    // glRotatef( angle, 1, 1, 0);
    // glTranslatef( -1*(xW+c), -1*(yW+c), -1*(zW+c-1));
    // for(unsigned i=0; i<sponge.size(); i++){
    //   sponge[i].show(type);
    // }
    // angle++;
    // glTranslatef( xW, yW, -5);
    // glRotatef( angle, 1, 0, 0);
    // glTranslatef( -1*xW, -1*yW, 5);
    Ellipsoid(Point3D(xW,yW,-5), 0.5, 0.5, 0.5).show();
    float tam = 180/atom.size();
    for(unsigned i=0; i<atom.size(); i++){
      glPushMatrix();
      glTranslatef( xW, yW, -5);
      glRotatef( tam*i, 0, 0, 1);
      glTranslatef( -1*xW, -1*yW, 5);
      Ellipse(Point3D(xW,yW,-5), 1, 2).show();
      atom[i].show();
      if(i==0){
        around.setCenter(atom[i].getCurrentPos());
        Ellipse(atom[i].getCurrentPos(), 0.5, 1).show();
        around.show();
      }
      glPopMatrix(); 
    }
}

int main(int argc, char* args[])
{
    SDL_Event event;
    GLdouble modelview[16], projection[16];  
    GLint viewport[4];
    float h=600, w=800;
    unsigned mx, my, count, tam, type = 0, lvl=0;
    bool loop=true, click = false;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(w, h, 32, SDL_SWSURFACE|SDL_OPENGL);
    
    init();

    //get the projection matrix     
    glGetDoublev( GL_PROJECTION_MATRIX, projection);  
    //get the modelview matrix      
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview);  
    //get the viewport      
    glGetIntegerv( GL_VIEWPORT, viewport);
    //get the coordinates of the "center" of the screen
    gluUnProject(w/2, h/2, 0, modelview, projection, viewport, &xW, &yW, &zW);
    
    // std::vector<Box> sponge, next, aux;
    // sponge.push_back(Box(Point3D(xW, yW, zW-1), 1/3.0));
    
    std::vector<Orbit> orbits;
    Point3D center = Point3D(xW,yW,-5);
    Ellipsoid obj = Ellipsoid(center, 0.25, 0.25, 0.25);
    orbits.push_back(Orbit(center, 1, 2, obj));
    Orbit around = Orbit(orbits[0].getCurrentPos(), 0.5, 1, Ellipsoid(center, 0.1, 0.1, 0.1));
    while (loop)
    {
      while (SDL_PollEvent(&event))
      {
        switch(event.type)
        {
          case SDL_QUIT:
            loop=false;
            break;
          // case SDL_MOUSEBUTTONDOWN:
          //    orbits.push_back(Orbit(center, 1, 2, obj));
          //    break;
          // case SDL_MOUSEBUTTONUP:
          //   click = false;
          //   break;
          // case SDL_MOUSEMOTION:
          //   if( click ){
          //     mx=event.button.x;
          //     my=event.button.y;
          //     gluUnProject(mx, h-my, 0, modelview, projection, viewport, &xW, &yW, &zW);
          //   }
          //   break;
          case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
              case SDLK_KP_MINUS:
              case SDLK_MINUS:
                // lvl = lvl > 0 ? lvl-1 : lvl;
                if(orbits.size()>1)
                  orbits.pop_back();
                break;
              case SDLK_KP_PLUS:
              case SDLK_PLUS:
                // lvl++;
                orbits.push_back(Orbit(center, 1, 2, obj));
                break;
              // case SDLK_d:
              //   type++;
              //   type%=2;
              //   break;
            }
          //   break;
        }
      }
      // sponge.clear();
      // sponge.push_back(Box(Point3D(xW*2, yW*2, zW-1), 1/3.0));
      // for(unsigned k =0; k<lvl; k++){
      //   tam = sponge.size();
      //   aux.clear();
      //   for(unsigned i=0; i<tam; ++i){
      //     next = sponge[i].generate();
      //     count = next.size(); 
      //     for (unsigned j=0; j<count; ++j){
      //       aux.push_back(next[j]);
      //     }
      //   }
      //   sponge = aux;
      // }
      display(orbits, around, type);
      SDL_GL_SwapBuffers();
    }
    SDL_Quit();
    return 0;
}
