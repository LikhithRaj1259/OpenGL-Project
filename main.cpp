#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
using namespace std;

void draw_axis()
{
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
    glEnd();
}

void make_cube()
{
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1); 
}

void drawCircle(float x, float y, float z,float r) {
        float i = 0.0f;
        
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(x, y, z); // Center
        for(i = 0.0f; i <= 360; i++)
                glVertex3f(r*cos(M_PI * i / 180.0) + x, r*sin(M_PI * i / 180.0) + y,z);
        glEnd();
}

void draw_ground()
{
    glColor3f(0.56,0.93,0.56);
    glBegin(GL_POLYGON);
    glVertex3f(-300,-0.1,-300);
    glVertex3f(-300,-0.1,300);
    glVertex3f(300,-0.1,300);
    glVertex3f(300,-0.1,-300);
    glEnd();
}

void make_window(float xe,float ye,float offset,float l,float b,float xc,float yc,float zc)
{
    l -= 0.5;
    glColor3f(0.6,0.6,0.6); 
    glPushMatrix();
    glTranslatef(xc,yc,zc);
    glTranslatef(xe,ye,offset);
    glScalef(l,b,0);
    make_cube();
    glPopMatrix();      

    drawCircle(xe+xc,ye+b/2+yc,offset+zc,b/2);
    drawCircle(xe+l+xc,ye+b/2+yc,offset+zc,b/2);
}

void make_door(float xe,float ye,float offset,float l,float b,float xc,float yc,float zc)
{
    glColor3f(0.6,0.6,0.6); 
    glPushMatrix();
    glTranslatef(xc,yc,zc);
    glTranslatef(xe,ye,offset);
    glScalef(l,b,0);
    make_cube();
    glPopMatrix();
}

void make_floor_window(float xe,float ye,float offset,float l,float b,float xc,float yc,float zc)
{
    glColor3f(0.6,0.6,0.6); 
    glPushMatrix();
    glTranslatef(xc,yc,zc);
    glTranslatef(xe,ye,offset);
    glScalef(l,b,0);
    make_cube();
    glPopMatrix();
}

void floor_0(int x,int y,int z)
{

    //concrete building.
    glColor3f(0.8,0.8, 0.8);
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(55,9,-18);
    make_cube();
    glPopMatrix(); 

    //openway 
    glColor3f(0.6,0.6,0.6); 
    glPushMatrix();
    glTranslatef(x,y,z);
    glTranslatef(16,0,0.1);
    glScalef(6,5,0);
    make_cube();
    glPopMatrix(); 

    //circle
    drawCircle(x+23.5,y+3.5,z+0.1,0.5);

    //windows column1 
    make_window(26,4,0.1,6,1,x,y,z);
    make_window(26,2,0.1,6,1,x,y,z); 

    //windows column2 
    make_window(35,4,0.1,3,1,x,y,z); 
    make_window(33,2,0.1,5,1,x,y,z); 

    //windows column3 
    make_window(39,1,0.1,3,1,x,y,z);

    //backside 
    make_door(6,0,-0.1,3,4,x,y,z-18);
    make_floor_window(11,1,-0.1,3,3,x,y,z-18); 
    make_door(17,0,-0.1,3,4,x,y,z-18);
    make_door(22,0,-0.1,1,3,x,y,z-18);

    //openway 
    glColor3f(0.6,0.6, 0.6);
    glPushMatrix();
    glTranslatef(x,y,z-18);
    glTranslatef(26,0,-0.1);
    glScalef(5,9,0);
    make_cube();
    glPopMatrix();

    make_door(32,0,-0.1,3,4,x,y,z-18);
    make_floor_window(37,1,-0.1,3,3,x,y,z-18); 
    make_floor_window(43,1,-0.1,3,3,x,y,z-18); 
    make_door(47,0,-0.1,3,4,x,y,z-18);
    // make_door(56,-0,0.1,3,4,x,y,z-18);
}

void floor_2(int x,int y,int z)
{
    //concrete building 
    glColor3f(0.8,0.8, 0.8);
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(63,9,-18);
    make_cube();
    glPopMatrix(); 

    //openway
    glColor3f(0.6,0.6, 0.6);
    glPushMatrix();
    glTranslatef(x,y,z);
    glTranslatef(20.5,3,0.1);
    glScalef(4.5,3,0);
    make_cube();
    glPopMatrix(); 
    
    //windows column1 
    make_window(6,5,0.1,3,1,x,y,z);
    make_window(6,2,0.1,3,1,x,y,z);

    //windows column2 
    make_window(10,4,0.1,3,1,x,y,z);
    make_window(10,2,0.1,3,1,x,y,z);
    
    //windows column3
    make_window(14,5,0.1,3,1,x,y,z);
    make_window(14,2,0.1,5,1,x,y,z);

    //windows column4 
    make_window(26,5,0.1,6,1,x,y,z);
    make_window(26,3,0.1,2,1,x,y,z);
    make_window(29,2,0.1,3,1,x,y,z);

    //windows column5 
    make_window(32,5,0.1,3,1,x,y,z);
    make_window(32,2,0.1,3,1,x,y,z);

    //windows column6 
    make_window(36,4,0.1,3,1,x,y,z);
    make_window(36,2,0.1,3,1,x,y,z); 

    //small door 
    glColor3f(0.6,0.6, 0.6);
    glPushMatrix();
    glTranslatef(x,y,z);
    glTranslatef(40,3,0.1);
    glScalef(2,3,0);
    make_cube();
    glPopMatrix(); 

    //circle 
    drawCircle(x+43.5,y+3.5,z+0.1,0.5);

    //windows column7
    make_window(46,5,0.1,3,1,x,y,z); 
    make_window(46,2,0.1,3,1,x,y,z);

    //windows column8 
    make_window(49.5,5,0.1,3,1,x,y,z); 
    make_window(49.5,3,0.1,3,1,x,y,z); 

    //backside 
    y += 1;
    make_door(6,0,-0.1,3,4,x,y,z-18);
    make_floor_window(11,1,-0.1,3,3,x,y,z-18); 
    make_door(17,0,-0.1,3,4,x,y,z-18);
    make_door(22,0,-0.1,1,3,x,y,z-18);

    //openway 
    glColor3f(0.6,0.6, 0.6);
    glPushMatrix();
    glTranslatef(x,y-1,z-18);
    glTranslatef(26,0,-0.1);
    glScalef(5,9,0);
    make_cube();
    glPopMatrix();

    make_door(32,0,-0.1,3,4,x,y,z-18);
    make_floor_window(37,1,-0.1,3,3,x,y,z-18); 
    make_floor_window(43,1,-0.1,3,3,x,y,z-18); 
    make_door(47,0,-0.1,3,4,x,y,z-18);
    make_door(56,-0,0.1,3,4,x,y,z-18);

}

void floor_4(int x,int y,int z)
{
    //concrete building 
    glColor3f(0.8,0.8, 0.8);
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(63,9,-18);
    make_cube();
    glPopMatrix(); 

    //circle 
    glColor3f(0.6,0.6,0.6); 
    drawCircle(x+8.5,y+6.5,z+0.1,0.5); 

    //windows column1 
    make_window(10,6,0.1,3,1,x,y,z); 

    //windows column2
    make_window(13,4,0.1,3,1,x,y,z); 
    make_window(13,2,0.1,3,1,x,y,z); 

    //windows column3
    make_window(17,4,0.1,3,1,x,y,z); 
    make_window(17,2,0.1,3,1,x,y,z); 

    //openway
    glColor3f(0.6,0.6, 0.6);
    glPushMatrix();
    glTranslatef(x,y,z);
    glTranslatef(22,4,0.1);
    glScalef(5,3,0);
    make_cube();
    glPopMatrix(); 

    //circle 
    drawCircle(x+28.5,y+5.5,z+0.1,0.5); 

    //small door 
    glColor3f(0.6,0.6, 0.6);
    glPushMatrix();
    glTranslatef(x,y,z);
    glTranslatef(32,4,0.1);
    glScalef(2,3,0);
    make_cube();
    glPopMatrix();

    //windows column4 
    make_window(35,6,0.1,3,1,x,y,z);
    make_window(35,4,0.1,3,1,x,y,z);

    //windows column5
    make_window(39,4,0.1,3,1,x,y,z);
    make_window(39,2,0.1,3,1,x,y,z); 

    //windows column6
    make_window(43,6,0.1,6,1,x,y,z);
    make_window(46,4,0.1,3,1,x,y,z);

    //small door 
    glColor3f(0.6,0.6, 0.6);
    glPushMatrix();
    glTranslatef(x,y,z);
    glTranslatef(50,4,0.1);
    glScalef(2,3,0);
    make_cube();
    glPopMatrix();

    //small circle 
    drawCircle(x+53.5,y+5.5,z+0.1,0.5); 

    //windows column7
    make_window(55,4,0.1,3,1,x,y,z);

    //backside
    y += 1;
    make_door(6,0,-0.1,3,4,x,y,z-18);
    make_floor_window(11,1,-0.1,3,3,x,y,z-18); 
    make_door(17,0,-0.1,3,4,x,y,z-18);
    make_door(22,0,-0.1,1,3,x,y,z-18);

    //openway 
    glColor3f(0.6,0.6, 0.6);
    glPushMatrix();
    glTranslatef(x,y-1,z-18);
    glTranslatef(26,0,-0.1);
    glScalef(5,9,0);
    make_cube();
    glPopMatrix();

    make_door(32,0,-0.1,3,4,x,y,z-18);
    make_floor_window(37,1,-0.1,3,3,x,y,z-18); 
    make_floor_window(43,1,-0.1,3,3,x,y,z-18); 
    make_door(47,0,-0.1,3,4,x,y,z-18);
    // make_door(56,-0,0.1,3,4,x,y,z-18);
}

void floor_in(int x,int y,int z)
{
     //concrete building.
    glColor3f(0.7,0.7, 0.8);
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(66,9,-18);
    make_cube();
    glPopMatrix(); 

    make_door(6,0,0.1,3,4,x,y,z);
    make_floor_window(11,1,0.1,3,3,x,y,z); 
    make_door(17,0,0.1,3,4,x,y,z);
    make_door(22,0,0.1,1,3,x,y,z);

    //openway 
    glColor3f(0.6,0.6, 0.6);
    glPushMatrix();
    glTranslatef(x,y,z);
    glTranslatef(26,0,0.1);
    glScalef(5,9,0);
    make_cube();
    glPopMatrix();

    make_door(32,0,0.1,3,4,x,y,z);
    make_floor_window(37,1,0.1,3,3,x,y,z); 
    make_floor_window(43,1,0.1,3,3,x,y,z); 
    make_door(47,0,0.1,3,4,x,y,z);
    make_door(56,0,0.1,3,4,x,y,z);

}

void draw_pod(int x,int y,int z)
{
    floor_0(x+6,y+0,z+0);
    floor_in(x+1,y+7,z-4);
    floor_2(x+3,y+13,z+0);
    floor_in(x-1,y+20,z-4);
    floor_4(x+0,y+26,z+0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_axis();
    draw_ground();
    draw_pod(0,0,0);
    draw_pod(-80,0,0);
    draw_pod(0,0,-68);
    draw_pod(-80,0,-68);
    glFlush();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(1, 1, 1, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
    case 'A':
        glTranslatef(5.0, 0.0, 0.0);
        break;
    case 'd':
    case 'D':
        glTranslatef(-5.0, 0.0, 0.0);
        break;
    case 'w':
    case 'W':
        glTranslatef(0.0, 0.0, 5.0);
        break;
    case 's':
    case 'S':
        glTranslatef(0.0, 0.0, -5.0);
        break;
    case 'q':
    case 'Q':
        glRotatef(-2, 1.0, 0.0, 0.0);

    case 'e':
    case 'E':
        glRotatef(2, 0.0, 1.0, 0.0);
    }
    display();
}

void resize(int width, int height)
{
    if (height == 0)
        height = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(80.0, width / height, 1.0, 600.0);

    glTranslatef(0.0, -15.0, -320.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1100, 1100);
    glutInitWindowPosition(100, 10);
    glutCreateWindow("3D map");
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(resize);

    glutMainLoop();
    return 0; 
}