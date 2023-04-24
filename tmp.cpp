#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

// Cloud position
float cloudX = 0.0f;
float cloudY = 0.0f;
float cloudZ = -10.0f;

int lighting = 0;
void setLighting()
{
    GLfloat lig_diff[] = {0.8, 0.8, 0.8, 1.0};

    vector<float> v;
    if(lighting == 1)
        v = {0.8, 0.8, 0.8, 1.0};
    else v = {0.2, 0.2, 0.2, 1.0};
    // GLfloat lig_amb[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat lig_amb[] = {v[0],v[1],v[2],v[3]};
    GLfloat mat_shininess[] = {50.0};
    GLfloat light_position[] = {0, 0, 100, 1};

    glClearColor(0.3,0.4,0.8,1);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_DIFFUSE, lig_diff);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    // glLightfv(GL_LIGHT1, GL_AMBIENT, lig_amb);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void setMyColor(vector<float> col)
{
    GLfloat color[] = {col[0],col[1],col[2]};
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
}

// Animation speed
float cloudSpeed = 0.25f;

float angle = 0, xx = 0,yy = -15, zz = -300;
void *font = GLUT_STROKE_MONO_ROMAN;

void building_name(string s, int x, int y, int z)
{

    glColor3f(1, 0, 0);

    float p = 0;
    for (float i = 0; i < s.size(); i++)
    {

        glPushMatrix();
        setMyColor({1, 0, 0});
        glTranslatef(x + 2.1f * i, y, z + 0.0);
        glScalef(0.04, 0.02, 1);
        glLineWidth(3);
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, s[i]);
        glPopMatrix();
    }
}

void draw_axis()
{
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100, 0);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100);
    glEnd();
}

void drawCircle(float x, float y, float z, float r)
{
    float i = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, z); // Center
    for (i = 0.0f; i <= 360; i++)
        glVertex3f(r * cos(M_PI * i / 180.0) + x, r * sin(M_PI * i / 180.0) + y, z);
    glEnd();
}

void draw_road()
{
    glColor3f(1, 0.9, 0.9);

    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(-10, 0.1, -300);
    glVertex3f(10, 0.1, -300);
    glVertex3f(10, 0.1, 300);
    glVertex3f(-10, 0.1, 300);
    glEnd();

    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(-300, 0.1, 50);
    glVertex3f(-300, 0.1, 30);
    glVertex3f(300, 0.1, 30);
    glVertex3f(300, 0.1, 50);
    glEnd();

    setMyColor({1, 0.9, 0.9});
    glBegin(GL_POLYGON);
    glVertex3f(-300, 0.1, -32);
    glVertex3f(300, 0.1, -32);
    glVertex3f(300, 0.1, -52);
    glVertex3f(-300, 0.1, -52);
    glEnd();
}

void make_tree(int x, int y, int z)
{

    // trunk
    glColor3f(0.67, 0.34, 0);
    glPushMatrix();
    setMyColor({0.67, 0.34, 0});
    glTranslatef(x, y, z);
    glScalef(6, 6, -6);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // middle part
    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x - 1, y + 6, z + 1);
    glScalef(8, 7, -8);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // spheres
    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x - 1, y + 6, z + 1);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 7, y + 6, z + 1);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x + 7, y + 6, z - 7);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x - 1, y + 6, z - 7);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    // 2nd line
    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x - 1, y + 8, z + 1);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 7, y + 8, z + 1);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x + 7, y + 8, z - 7);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x - 1, y + 8, z - 7);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    // 3rd line
    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x - 1, y + 11, z + 1);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
 ;
    glTranslatef(x + 7, y + 11, z + 1);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 7, y + 11, z - 7);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
 ;
    glTranslatef(x - 1, y + 11, z - 7);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    // middle line 1

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 3, y + 6, z + 1.5);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x + 7.5, y + 6, z - 3);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 3, y + 6, z - 7.5);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x - 1.5, y + 6, z - 3);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    // middle line  2

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 3, y + 8.5, z + 2);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x + 8, y + 8.5, z - 3);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 3, y + 8.5, z - 8);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x - 2, y + 8.5, z - 3);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    // middle line  3

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x + 3, y + 11.5, z + 1.5);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 7.5, y + 11.5, z - 3);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x + 3, y + 11.5, z - 7.5);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x - 1.5, y + 11.5, z - 3);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    // top corner
    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x + 4, y + 13, z - 4);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 2, y + 12.5, z - 3);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 5, y + 12.5, z - 3);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x + 2, y + 12.5, z - 4);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x + 5, y + 12.5, z - 4);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 2, y + 12.5, z - 2);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0, 0.8, 0);
    glPushMatrix();
    setMyColor({0, 0.8, 0});
    glTranslatef(x + 5, y + 12.5, z - 2);
    glScalef(2.5, 2.5, -2.5);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    glColor3f(0.1, 0.7, 0.1);
    glPushMatrix();
    setMyColor({0.1, 0.7, 0.1});
    glTranslatef(x + 2, y + 12.5, z - 1);
    glScalef(3, 3, 3);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();
}

void draw_ground()
{
    glColor3f(0.74, 0.62, 0.51);
    setMyColor({0.74, 0.62, 0.51});
    glBegin(GL_POLYGON);
    glVertex3f(-300, -0.1, -300);
    glVertex3f(-300, -0.1, 300);
    glVertex3f(300, -0.1, 300);
    glVertex3f(300, -0.1, -300);
    glEnd();

    // fencing
    glColor3f(0.67, 0.34, 0);
    glPushMatrix();
    setMyColor({0.67, 0.34, 0});
    glTranslatef(-300, 0, -300);
    glScalef(6, 20, 600);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.6, 0.3, 0);
    glPushMatrix();
    setMyColor({0.6, 0.3, 0});
    glTranslatef(-300, 0, -300);
    glScalef(600, 20, 6);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.67, 0.34, 0);
    glPushMatrix();
    setMyColor({0.67, 0.34, 0});
    glTranslatef(300, 0, -300);
    glScalef(6, 20, 600);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

void make_window(float xe, float ye, float offset, float l, float b, float xc, float yc, float zc)
{
    l -= 0.5;
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(xc, yc, zc);
    glTranslatef(xe, ye, offset);
    glScalef(l, b, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glNormal3f(0, 0, -offset);
    setMyColor({0.6, 0.6, 0.6});
    drawCircle(xe + xc, ye + b / 2 + yc, offset + zc, b / 2);
    glNormal3f(0, 0, -offset);
    setMyColor({0.6, 0.6, 0.6});
    drawCircle(xe + l + xc, ye + b / 2 + yc, offset + zc, b / 2);
}

void make_door(float xe, float ye, float offset, float l, float b, float xc, float yc, float zc)
{
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(xc, yc, zc);
    glTranslatef(xe, ye, offset);
    glScalef(l, b, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

void make_floor_window(float xe, float ye, float offset, float l, float b, float xc, float yc, float zc)
{
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(xc, yc, zc);
    glTranslatef(xe, ye, offset);
    glScalef(l, b, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

void floor_0(int x, int y, int z)
{

    // concrete building.
    glColor3f(0.8,0.8,0.8);
    glPushMatrix();
    setMyColor({0.8,0.8,0.8});
    glTranslatef(x, y, z);
    glScalef(55, 9, -18);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // openway
    glColor3f(0.6,0.6,0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(16, 0, 0.1);
    glScalef(6, 5, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // circle
    glNormal3f(0,0,1);
    setMyColor({0.6, 0.6, 0.6});
    drawCircle(x + 23.5, y + 3.5, z + 0.1, 0.5);

    // windows column1
    
    make_window(26, 4, 0.1, 6, 1, x, y, z);
    make_window(26, 2, 0.1, 6, 1, x, y, z);

    // windows column2
    make_window(35, 4, 0.1, 3, 1, x, y, z);
    make_window(33, 2, 0.1, 5, 1, x, y, z);

    // windows column3
    make_window(39, 1, 0.1, 3, 1, x, y, z);

    // backside
    make_door(6, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(11, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(17, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(22, 0, -0.1, 1, 3, x, y, z - 18);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z - 18);
    glTranslatef(26, 0, -0.1);
    glScalef(5, 9, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(32, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(37, 1, -0.1, 3, 3, x, y, z - 18);
    make_floor_window(43, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(47, 0, -0.1, 3, 4, x, y, z - 18);
    // make_door(56,-0,0.1,3,4,x,y,z-18);
}

void floor_2(int x, int y, int z)
{
    // concrete building
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    setMyColor({0.8, 0.8, 0.8});
    glTranslatef(x, y, z);
    glScalef(63, 9, -18);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // shaders
    // glColor3f(0.77, 0.77, 0.77);
    // glBegin(GL_POLYGON);
    // glVertex3f(x - 0.1, y + 0, z + 0);
    // glVertex3f(x - 0.1, y + 9, z + 0);
    // glVertex3f(x - 0.1, y + 9, z - 18);
    // glVertex3f(x - 0.1, y + 0, z - 18);
    // glEnd();

    // glColor3f(0.77, 0.77, 0.77);
    // glBegin(GL_POLYGON);
    // glVertex3f(x + 63.1, y + 0, z + 0);
    // glVertex3f(x + 63.1, y + 9, z + 0);
    // glVertex3f(x + 63.1, y + 9, z - 18);
    // glVertex3f(x + 63.1, y + 0, z - 18);
    // glEnd();

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(20.5, 3, 0.1);
    glScalef(4.5, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // windows column1
    make_window(6, 5, 0.1, 3, 1, x, y, z);
    make_window(6, 2, 0.1, 3, 1, x, y, z);

    // windows column2
    make_window(10, 4, 0.1, 3, 1, x, y, z);
    make_window(10, 2, 0.1, 3, 1, x, y, z);

    // windows column3
    make_window(14, 5, 0.1, 3, 1, x, y, z);
    make_window(14, 2, 0.1, 5, 1, x, y, z);

    // windows column4
    make_window(26, 5, 0.1, 6, 1, x, y, z);
    make_window(26, 3, 0.1, 2, 1, x, y, z);
    make_window(29, 2, 0.1, 3, 1, x, y, z);

    // windows column5
    make_window(32, 5, 0.1, 3, 1, x, y, z);
    make_window(32, 2, 0.1, 3, 1, x, y, z);

    // windows column6
    make_window(36, 4, 0.1, 3, 1, x, y, z);
    make_window(36, 2, 0.1, 3, 1, x, y, z);

    // small door
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(40, 3, 0.1);
    glScalef(2, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // circle
    drawCircle(x + 43.5, y + 3.5, z + 0.1, 0.5);

    // windows column7
    make_window(46, 5, 0.1, 3, 1, x, y, z);
    make_window(46, 2, 0.1, 3, 1, x, y, z);

    // windows column8
    make_window(49.5, 5, 0.1, 3, 1, x, y, z);
    make_window(49.5, 3, 0.1, 3, 1, x, y, z);

    // backside
    y += 1;
    make_door(6, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(11, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(17, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(22, 0, -0.1, 1, 3, x, y, z - 18);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y - 1, z - 18);
    glTranslatef(26, 0, -0.1);
    glScalef(5, 9, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(32, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(37, 1, -0.1, 3, 3, x, y, z - 18);
    make_floor_window(43, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(47, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(56, -0, 0.1, 3, 4, x, y, z - 18);
}

void floor_4(int x, int y, int z)
{
    // concrete building
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    setMyColor({0.8, 0.8, 0.8});
    glTranslatef(x, y, z);
    glScalef(63, 9, -18);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // shaders
    // glColor3f(0.77, 0.77, 0.77);
    // glBegin(GL_POLYGON);
    // glVertex3f(x - 0.1, y + 0, z + 0);
    // glVertex3f(x - 0.1, y + 9, z + 0);
    // glVertex3f(x - 0.1, y + 9, z - 18);
    // glVertex3f(x - 0.1, y + 0, z - 18);
    // glEnd();

    // glColor3f(0.77, 0.77, 0.77);
    // glBegin(GL_POLYGON);
    // glVertex3f(x + 63.1, y + 0, z + 0);
    // glVertex3f(x + 63.1, y + 9, z + 0);
    // glVertex3f(x + 63.1, y + 9, z - 18);
    // glVertex3f(x + 63.1, y + 0, z - 18);
    // glEnd();

    // circle
    glColor3f(0.6, 0.6, 0.6);
    drawCircle(x + 8.5, y + 6.5, z + 0.1, 0.5);

    // windows column1
    make_window(10, 6, 0.1, 3, 1, x, y, z);

    // windows column2
    make_window(13, 4, 0.1, 3, 1, x, y, z);
    make_window(13, 2, 0.1, 3, 1, x, y, z);

    // windows column3
    make_window(17, 4, 0.1, 3, 1, x, y, z);
    make_window(17, 2, 0.1, 3, 1, x, y, z);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(22, 4, 0.1);
    glScalef(5, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // circle
    drawCircle(x + 28.5, y + 5.5, z + 0.1, 0.5);

    // small door
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(32, 4, 0.1);
    glScalef(2, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // windows column4
    make_window(35, 6, 0.1, 3, 1, x, y, z);
    make_window(35, 4, 0.1, 3, 1, x, y, z);

    // windows column5
    make_window(39, 4, 0.1, 3, 1, x, y, z);
    make_window(39, 2, 0.1, 3, 1, x, y, z);

    // windows column6
    make_window(43, 6, 0.1, 6, 1, x, y, z);
    make_window(46, 4, 0.1, 3, 1, x, y, z);

    // small door
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(50, 4, 0.1);
    glScalef(2, 3, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // small circle
    drawCircle(x + 53.5, y + 5.5, z + 0.1, 0.5);

    // windows column7
    make_window(55, 4, 0.1, 3, 1, x, y, z);

    // backside
    y += 1;
    make_door(6, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(11, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(17, 0, -0.1, 3, 4, x, y, z - 18);
    make_door(22, 0, -0.1, 1, 3, x, y, z - 18);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y - 1, z - 18);
    glTranslatef(26, 0, -0.1);
    glScalef(5, 9, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(32, 0, -0.1, 3, 4, x, y, z - 18);
    make_floor_window(37, 1, -0.1, 3, 3, x, y, z - 18);
    make_floor_window(43, 1, -0.1, 3, 3, x, y, z - 18);
    make_door(47, 0, -0.1, 3, 4, x, y, z - 18);
    // make_door(56,-0,0.1,3,4,x,y,z-18);
}

void floor_in(int x, int y, int z)
{
    // concrete building.
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    setMyColor({0.7, 0.7, 0.7});
    glTranslatef(x, y, z);
    glScalef(66, 9, -18);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // shaders
    // glColor3f(0.72, 0.72, 0.72);
    // glBegin(GL_POLYGON);
    // glVertex3f(x - 0.1, y + 0, z + 0);
    // glVertex3f(x - 0.1, y + 9, z + 0);
    // glVertex3f(x - 0.1, y + 9, z - 18);
    // glVertex3f(x - 0.1, y + 0, z - 18);
    // glEnd();

    // glColor3f(0.72, 0.72, 0.72);
    // glBegin(GL_POLYGON);
    // glVertex3f(x + 66.1, y + 0, z + 0);
    // glVertex3f(x + 66.1, y + 9, z + 0);
    // glVertex3f(x + 66.1, y + 9, z - 18);
    // glVertex3f(x + 66.1, y + 0, z - 18);
    // glEnd();

    make_door(6, 0, 0.1, 3, 4, x, y, z);
    make_floor_window(11, 1, 0.1, 3, 3, x, y, z);
    make_door(17, 0, 0.1, 3, 4, x, y, z);
    make_door(22, 0, 0.1, 1, 3, x, y, z);

    // openway
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    setMyColor({0.6, 0.6, 0.6});
    glTranslatef(x, y, z);
    glTranslatef(26, 0, 0.1);
    glScalef(5, 9, 0);
    glTranslatef(0.5, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    make_door(32, 0, 0.1, 3, 4, x, y, z);
    make_floor_window(37, 1, 0.1, 3, 3, x, y, z);
    make_floor_window(43, 1, 0.1, 3, 3, x, y, z);
    make_door(47, 0, 0.1, 3, 4, x, y, z);
    make_door(56, 0, 0.1, 3, 4, x, y, z);
}

void cloud_formation(int x, int y, int z)
{
    float r = 3.0;
    y += 100.0;
    float cons = 100.0, red = 1.5;

    glColor3f(0.76, 0.76, 0.76);
    glPushMatrix();
    setMyColor({0.76, 0.76, 0.76});
    glTranslatef(x + 0, y + 0, z + 0);
    glScalef(5 * r, 3 * r, 5 * r);
    glutSolidSphere(1, 30, 30);
    ;
    glPopMatrix();

    int tx = x;
    {
        x -= (5 * r - 5 * r / cons);
        glColor3f(0.77, 0.77, 0.77);
        glPushMatrix();
        setMyColor({0.77, 0.77, 0.77});
        glTranslatef(x + 0, y + 0, z + 0);
        glScalef(5 * r / red, 3 * r / red, 5 * r / red);
        glutSolidSphere(1, 30, 30);
        ;
        glPopMatrix();

        x -= (5 * r / red - 5 * r / (red * cons));
        glColor3f(0.76, 0.76, 0.76);
        glPushMatrix();
        setMyColor({0.76, 0.76, 0.76});
        glTranslatef(x + 0, y + 0, z + 0);
        glScalef(5 * r / (red * red), 3 * r / (red * red), 5 * r / (red * red));
        glutSolidSphere(1, 30, 30);
        ;
        glPopMatrix();
    }

    {
        x = tx;
        x += (5 * r - 5 * r / cons);
        glColor3f(0.77, 0.77, 0.77);
        glPushMatrix();
        setMyColor({0.77, 0.77, 0.77});
        glTranslatef(x + 0, y + 0, z + 0);
        glScalef(5 * r / red, 3 * r / red, 5 * r / red);
        glutSolidSphere(1, 30, 30);
        ;
        glPopMatrix();

        x += (5 * r / red - 5 * r / (red * cons));
        glColor3f(0.76, 0.76, 0.76);
        glPushMatrix();
        setMyColor({0.76, 0.76, 0.76});
        glTranslatef(x + 0, y + 0, z + 0);
        glScalef(5 * r / (red * red), 3 * r / (red * red), 5 * r / (red * red));
        glutSolidSphere(1, 30, 30);
        glPopMatrix();
    }
}

void cloud()
{
    // Update cloud position
    cloudX += cloudSpeed;
    if (cloudX > 300.0f)
        cloudX = -300.0f;

    // Draw cloud (using spheres as particles)
    vector<vector<float>> arr{{0, 0, 0, 2}, {10, -30, -20, 3}, {10, -30, 40, 2.5}, {-30, -25, 20, 2}, {50, 10, 10, 1}, {-50, 10, 50, 1.34}, {-30, -40, 70, 2.4}, {-100, -15, 12, 2}, {150, 20, 32, 1.5}, {200, -35, 43, 2.8}, {-200, -25, -40, 2}, {-170, -45, -10, 1}, {-230, -45, -30, 2}, {-240, -15, -20, 1.6}, {240, 15, -40, 2.9}, {230, 45, -35, 2.1}, {-270, 45, -12, 0.7}, {-250, 65, -45, 1}, {-225, 35, -12, 1.6}, {-100, 65, -34, 2}, {-150, 55, -60, 2}, {-50, 57, -40, 1}, {25, 65, -15, 0.5}, {55, 67, -45, 2}, {100, 57, -35, 1.5}, {140, 64, 0, 1}, {180, 54, 0, 1.3}};

    for (int i = 0; i < arr.size(); i++)
    {
        vector<float> vec = arr[i];
        GLfloat green[] = {0,1,0};
        float mz = (i % 3 == 0) * 6 * i - (i % 3 == 1) * 5 * i;
        float cx = vec[0], cy = vec[1], cz = vec[2], ext = vec[3];
        for (int i = 0; i < 10; i++)
        {
            glPushMatrix();
            cloud_formation(cloudX + cx, cloudY + cy + 20, cloudZ + cz + mz);
            glTranslatef(cloudX + i * ext, cloudY, cloudZ);
            glPopMatrix();
        }
    }
}

void timer(int value)       
{
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // 60 FPS
}

void draw_pod(int x, int y, int z)
{
    floor_0(x + 6, y + 0, z + 0);
    floor_in(x + 1, y + 7, z - 4);
    floor_2(x + 3, y + 13, z + 0);
    floor_in(x - 1, y + 20, z - 4);
    floor_4(x + 0, y + 26, z + 0);
}

void draw_trees(int x,int y,int z)
{
    make_tree(10+x, 0+y, 26+z);
    make_tree(40+x, 0+y, 26+z);
    make_tree(80+x, 0+y, 26+z);
    make_tree(-20+x, 0+y, 26+z);
    make_tree(-50+x, 0+y, 26+z);
    make_tree(-80+x, 0+y, 26+z);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    building_name("Vanadium", 23 + 10, 35.5, 0);
    building_name("Titanium", 23 - 80, 35.5, 0);
    building_name("Indium", 23 + 10, 35.5, 0 - 68);
    building_name("Sodium", 23 - 80, 35.5, 0 - 68);
    draw_ground();
    draw_road();
    draw_pod(10, 0, 0);
    draw_pod(-80, 0, 0);
    draw_pod(10, 0, -68);
    draw_pod(-80, 0, -68);
    draw_trees(0,0,0);
    // draw_trees(0,0,-140);
    draw_trees(-150,0,-280);
    draw_trees(-150,0,-240);
    draw_trees(-150,0,-200);
    draw_trees(-150,0,-160);
    draw_trees(120,0,-280);
    draw_trees(120,0,-240);
    draw_trees(120,0,-200);
    draw_trees(120,0,-160);
    cloud();
    glFlush();
    glutSwapBuffers();
}

void init(void)
{
    glClearColor(0.5, 0.6, 0.9, 0.0);
   
    if(lighting)setLighting();
    else glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
}

float rad(float angle)
{
    return 3.14 * (angle / 180.0);
}

void keyboard(unsigned char key, int x, int y)
{
    // display_coordinates(xx,yy,zz);
    // cout<<xx<<" "<<"-15"<<" "<<zz<<" see \n";
    int rot = 0;
    switch (key)
    {
    case 'a':
    case 'A':
        xx += 5.0 * cos(rad(angle)), zz += 5.0 * sin(rad(angle));
        glTranslatef(5.0 * cos(rad(angle)), 0.0, 5.0 * sin(rad(angle)));
        break;
    case 'd':
    case 'D':
        xx += 5.0 * cos(rad(angle + 180)), zz += 5.0 * sin(rad(angle + 180));
        glTranslatef(5.0 * cos(rad(angle + 180)), 0.0, 5.0 * sin(rad(angle + 180)));
        break;
    case 'w':
    case 'W':
        xx += 5.0 * cos(rad(angle + 90)), zz += 5.0 * sin(rad(angle + 90));
        glTranslatef(5.0 * cos(rad(angle + 90)), 0.0, 5.0 * sin(rad(angle + 90)));
        break;
    case 's':
    case 'S':
        xx += 5.0 * cos(rad(angle - 90)), zz += 5.0 * sin(rad(angle - 90));
        glTranslatef(5.0 * cos(rad(angle - 90)), 0.0, 5.0 * sin(rad(angle - 90)));
        break;
    case 'q':
    case 'Q':
        rot = -1;
        break;
    case 'e':
    case 'E':
        rot = 1;
        break;
    case 't':
    case 'T':
        glTranslatef(0.0, 5.0, 0.0);
        break;
    case 'g':
    case 'G':
        glTranslatef(0.0, -5.0, 0.0);
        break;
    case 'l':
    case 'L':
        lighting = (lighting+1)%3; 
        init();
        break;
    }

    

    if (rot)
    {
        angle += rot * 2;
        glTranslatef(-xx, 0.0, -zz);
        glRotatef(rot * 2, 0.0, 1, 0);
        glTranslatef(xx, 0.0, zz);
        rot = 0;
    }
    glutPostRedisplay();
}

void resize(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, width / (height | 1), 1.0, 630.0);
    // glOrtho(-300,300,-50,200,-100,300);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, -15, -300);

    // display_coordinates();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1100, 1100);
    glutInitWindowPosition(100, 10);
    glutCreateWindow("3D model");
    init();
    glutTimerFunc(0, timer, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(resize);
    glutMainLoop();
    return 0;
}
