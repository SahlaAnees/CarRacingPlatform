#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include <windows.h>
#include <GL/glut.h>
using namespace std;
#define pi 3.1415927


double camX = 10;
double camY = 50;
double camZ = 10;

double angle;
int frameNumber = 0;
int moveCar1 = 0;
int moveCar2 = 0;
int moveCar3 = 0;

double car = 0;
double leftRightMove = 0;
double sky = -1000;

void drawAxes() {
    glLineWidth(2);
    glBegin(GL_LINES);
    //X-Axis
    glColor3f(1, 0, 0);
    glVertex3f(-200, 0, 0);
    glVertex3f(200, 0, 0);

    //Y-Axis
    glColor3f(0, 1, 0);
    glVertex3f(0, 200, 0);
    glVertex3f(0, -200, 0);

    //Z-Axis
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -200);
    glVertex3f(0, 0, 200);
    glEnd();
}

void drawGrid(int gridSpan) {
    GLfloat step = 100;
    GLint line;

    glColor3f(0.2, 0.2, 0.2);
    glLineWidth(1);
    glBegin(GL_LINES);
    for (line = -gridSpan; line <= gridSpan; line += step) {
        glVertex3f(line, -gridSpan, -0.5);
        glVertex3f(line, gridSpan, -0.5);

        glVertex3f(-gridSpan, line, -0.5);
        glVertex3f(gridSpan, line, -0.5);
    }
    glEnd();
}

void drawDisk(double radius) {
    int d;
    glBegin(GL_POLYGON);
    for (d = 0; d < 32; d++) {
        double angle = 2 * pi / 32 * d;
        glVertex2d(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

void drawRectangle(float w, float h) {
    glRectf(-w / 2, -h / 2, w / 2, h / 2);
}

void drawCylinder(float radius, float height) {
    float radius1 = radius;
    float radius2 = radius;
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, radius1, radius2, height, 100, 100);
    drawDisk(radius1);
    glTranslatef(0, 0, height);
    drawDisk(radius2);
}

void drawRoad() {
    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

    glBegin(GL_POLYGON);

    glVertex3f(100, 0, -30);
    glVertex3f(-100, 0, -30);

    glVertex3f(-100, -5000, -30);
    glVertex3f(100, -5000, -30);

    glEnd();

    glPopMatrix();
}

void drawRoadMiddle() {

    glPushMatrix();
    glColor3f(1, 1, 1);

    glTranslatef(0, 0, 3);

    glBegin(GL_POLYGON);

    glVertex3f(-2, 0, -30);
    glVertex3f(2, 0, -30);

    glVertex3f(-2, -5000, -30);
    glVertex3f(2, -5000, -30);

    glEnd();

    glPopMatrix();
}


void drawMainCar() {
    glPushMatrix();
    cout << car << endl;

    glTranslatef(leftRightMove, car, 0);
    glRotatef(90, 0, 0, 1);

    //lower part
    glPushMatrix();
    glColor3f(1, .8, 3);
    glScalef(2, 1, .4);
    glutSolidCube(10);
    glPopMatrix();

    //upper part
    glPushMatrix();
    glTranslatef(0, 0, 3);
    glColor3f(.8, .8, .8);
    glScalef(1, 1, .6);
    glutSolidCube(10);
    glPopMatrix();

    //front left wheel
    glPushMatrix();
    glTranslatef(4, 5, -2);
    glColor3f(1, .3, 8);
    glScalef(2, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    glPushMatrix();
    //front right wheel
    glTranslatef(-4, 5, -2);
    glColor3f(1, 0, 1);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    //back left wheel
    glPushMatrix();
    glTranslatef(4, -5, -2);
    glColor3f(1, .6, 8);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    //back right wheel
    glPushMatrix();
    glTranslatef(-4, -5, -2);
    glColor3f(1, .3, 8);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    glPopMatrix();
}

//red car
void drawCar1() {
    glTranslatef(0, moveCar1, 0);
    glRotatef(90, 0, 0, 1);

    //lower part
    glPushMatrix();
    glColor3f(1, 0, 0);
    glScalef(3, 1, 0.4);
    glutSolidCube(10);
    glPopMatrix();

    //upper part
    glPushMatrix();
    glTranslatef(0.5, 0.1, 2.5);
    glColor3f(.67, .67, .67);
    glScalef(1.5, 0.9, 0.3);
    glutSolidCube(10);
    glPopMatrix();

    //front left wheel
    glPushMatrix();
    glTranslatef(4, 5, -2);
    glColor3f(0, 0, 0);
    glScalef(2, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    glPushMatrix();
    //front right wheel
    glTranslatef(-4, 5, -2);
    glColor3f(0, 0, 0);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    //back left wheel
    glPushMatrix();
    glTranslatef(4, -5, -2);
    glColor3f(0, 0, 0);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    //back right wheel
    glPushMatrix();
    glTranslatef(-4, -5, -2);
    glColor3f(0, 0, 0);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();
}


//blue car
void drawCar2() {
    glTranslatef(0, moveCar2, 0);
    glRotatef(90, 0, 0, 1);

    //lower part
    glPushMatrix();
    glColor3f(0, 0, 1);
    glScalef(3, 1, 0.4);
    glutSolidCube(10);
    glPopMatrix();

    //upper part
    glPushMatrix();
    glTranslatef(0.5, 0.1, 2.5);
    glColor3f(.6, .6, .6);
    glScalef(1.5, 0.9, 0.5);
    glutSolidCube(10);
    glPopMatrix();

    //front left wheel
    glPushMatrix();
    glTranslatef(4, 5, -2);
    glColor3f(0, 0, 0);
    glScalef(2, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    glPushMatrix();
    //front right wheel
    glTranslatef(-4, 5, -2);
    glColor3f(0, 0, 0);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    //back left wheel
    glPushMatrix();
    glTranslatef(4, -5, -2);
    glColor3f(0, 0, 0);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    //back right wheel
    glPushMatrix();
    glTranslatef(-4, -5, -2);
    glColor3f(0, 0, 0);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();
}


//magenta car
void drawCar3() {
    glTranslatef(0, moveCar3, 0);
    glRotatef(90, 0, 0, 1);

    //lower part
    glPushMatrix();
    glColor3f(1, 0, 1);
    glScalef(3, 1, 0.4);
    glutSolidCube(10);
    glPopMatrix();

    //upper part
    glPushMatrix();
    glTranslatef(0.5, 0.1, 2.5);
    glColor3f(1, 1, 1);
    glScalef(1.5, 0.9, 0.5);
    glutSolidCube(10);
    glPopMatrix();

    //front left wheel
    glPushMatrix();
    glTranslatef(4, 5, -2);
    glColor3f(0, 0, 0);
    glScalef(2, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    glPushMatrix();
    //front right wheel
    glTranslatef(-4, 5, -2);
    glColor3f(0, 0, 0);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    //back left wheel
    glPushMatrix();
    glTranslatef(4, -5, -2);
    glColor3f(0, 0, 0);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();

    //back right wheel
    glPushMatrix();
    glTranslatef(-4, -5, -2);
    glColor3f(0, 0, 0);
    glScalef(1, .7, 1);
    glutSolidSphere(2, 100, 100);
    glPopMatrix();
}

void drawBackground() {
    glPushMatrix();
    glTranslatef(0, sky, 480);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.3, 0.95, .95);
    //glScalef(0.8, 1, 0.8);
    //glutSolidCube(1000);
    drawRectangle(8000, 1000);
    glPopMatrix();
}

void drawHill() {
    //left hills
    glPushMatrix();
    glTranslatef(500, sky + 10, -20);
    glRotatef(90, 0, 0, 1);
    glColor3f(0.0, 0.9, 0.2);
    glutSolidCone(250, 500, 15, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(800, sky + 10, -20);
    glRotatef(90, 0, 0, 1);
    glColor3f(0, 0.9, 0.2);
    glutSolidCone(250, 500, 15, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1000, sky + 10, -20);
    glRotatef(90, 0, 0, 1);
    glColor3f(0, 0.9, 0.2);
    glutSolidCone(280, 400, 15, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1400, sky + 10, -20);
    glRotatef(90, 0, 0, 1);
    glColor3f(0, 0.9, 0.2);
    glutSolidCone(250, 500, 15, 20);
    glPopMatrix();

    //right hills
    glPushMatrix();
    glTranslatef(-500, sky + 30, -20);
    glRotatef(90, 0, 0, 1);
    glColor3f(0, 0.9, 0.5);
    glutSolidCone(250, 400, 15, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-700, sky + 30, -20);
    glRotatef(90, 0, 0, 1);
    glColor3f(0, 0.9, 0.5);
    glutSolidCone(250, 400, 15, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1200, sky + 30, -20);
    glRotatef(90, 0, 0, 1);
    glColor3f(0, 0.9, 0.5);
    glutSolidCone(280, 350, 15, 20);
    glPopMatrix();
}

void drawSun() {
    glPushMatrix();
    int i;
    glColor3f(0.8, 0.8, 0);
    glTranslatef(-250, sky + 50, 600);
    glRotatef(90, 1, 0, 0);
    for (i = 0; i < 13; i++) { // Draw 13 rays, with different rotations.
        glRotatef(360 / 13, 0, 0, 1); // Note that the rotations accumulate!
        glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(120, 0);
        glEnd();
    }
    drawDisk(60);
    glPopMatrix();
}

void drawBigTree() {
    glPushMatrix();
    glColor3f(0.9, 0.4, 0);
    glTranslatef(0, 0, -50);
    drawCylinder(7, 100);
    glPopMatrix();

    /* glPushMatrix();
     glColor3f(0, 1, 0);
     glTranslatef(0, 0, 70);
     glScalef(35, 35, 35);
     glutSolidIcosahedron();
     glPopMatrix();*/

    glPushMatrix();
    glRotatef(200, 0, 0, 1);

    glPushMatrix();
    glColor3f(1, 0.6, 0);
    glTranslatef(0, 0, 50);
    glRotatef(50, -1, 0, 0);
    drawCylinder(2.5, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(0, 20, 80);
    glRotatef(50, -1, 0, 0);
    glScalef(45, 45, 45);
    glutSolidIcosahedron();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glRotatef(60, 0, 0, 1);

    glPushMatrix();
    glColor3f(1, 0.6, 0);
    glTranslatef(0, 0, 30);
    glRotatef(55, -1, 0, 0);
    drawCylinder(2.5, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(0, 20, 60);
    glRotatef(45, -1, 0, 0);
    glScalef(30, 30, 30);
    glutSolidIcosahedron();
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glColor3f(1, 0.6, 0);
    glTranslatef(0, 0, -5);
    glRotatef(45, -1, 0, 0);
    drawCylinder(2.5, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(0, 20, 15);
    glRotatef(45, -1, 0, 0);
    glScalef(15, 15, 15);
    glutSolidIcosahedron();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0.6, 0);
    glTranslatef(0, 0, -15);
    glRotatef(45, 1, 0, 0);
    drawCylinder(2.5, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(0, -20, 10);
    glRotatef(45, 1, 0, 0);
    glScalef(12, 12, 12);
    glutSolidIcosahedron();
    glPopMatrix();

}

void drawRock() {
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(5, 55, 0);
    glutSolidSphere(20, 5, 50);
    glPopMatrix();
}

void drawSmallConeTree() {
    glPushMatrix();
    glColor3f(0, 1, 0);
    glutSolidCone(20, 30, 20, 20);

    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 0.3);
    glScalef(0.01, 0.4, 5);
    glutSolidSphere(7, 10, 10);

    glPopMatrix();
}

void drawSmallSphereTree() {
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.3);
    glScalef(0.01, 0.4, 5);
    glutSolidSphere(7, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 0, 1);
    glColor3f(0, 0.5, 0.3);
    glutSolidSphere(10, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5, 0, 1);
    glColor3f(0, 0.5, 0.3);
    glutSolidSphere(10, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 20);
    glColor3f(0, 0.5, 0.2);
    glutSolidSphere(15, 10, 10);
    glPopMatrix();
}

void drawLightTower() {
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0, 0, -50);
    drawCylinder(4, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0, 0, 80);
    glRotatef(90, 0, 1, 0);
    drawCylinder(1.5, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(20, 0, 72);
    glutSolidCone(10, 10, 50, 5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(20, 0, 72);
    glutSolidSphere(5, 50, 50);
    glPopMatrix();
}

void drawHouse() {
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glColor3f(0.85, 0.85, 0.9);
    glRotatef(90, 1, 0, 0);
    glutSolidCube(50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 22);
    glColor3f(1, 0.6, 0);
    //glRotatef(90,1,0,0);
    glutSolidCone(40, 30, 30, 40);
    glPopMatrix();
}

void drawHouse2() {
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glColor3f(0.6, 0.6, 0.6);
    glRotatef(90, 1, 0, 0);
    glutSolidCube(70);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 70);
    glColor3f(0.88, 0.88, 0.88);
    glRotatef(90, 1, 0, 0);
    glutSolidCube(70);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 100);
    glColor3f(0.7, 0.7, 0.7);
    glRotatef(90, 1, 0, 0);
    glScalef(1, 0.05, 1);
    glutSolidCube(75);
    glPopMatrix();
}

void drawWindmill() {
    int i;
    glColor3f(0.9, 0.9, 0.9);
    glPushMatrix();
    drawCylinder(10, 250);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 230);
    glRotatef(90, 0, 1, 0);
    glutSolidCone(10, 50, 50, 800);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(20, 0, 230);
    glRotated(frameNumber * (180.0 / 46), 1, 0, 0);
    glColor3f(0.6f, 0.6f, 0.8f);
    for (i = 0; i < 3; i++) {
        glRotated(120, 1, 0, 0);  // Note: These rotations accumulate.
        //glutSolidOctahedron();
        glutSolidCone(10, 150, 50, 100);
    }
    glPopMatrix();

}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glClearColor(0.345, 0.4, 0, 0);	//green floor 

    glPushMatrix();
    gluLookAt(0 + camX, 0 + camY, 10 + camZ, 0, -30000, 0, 0, 0, 1);


    GLfloat white[4] = { 1.0f,1.0f, 1.0f, 1.0f };
    GLfloat yellow[4] = { 0.8f,0.8f, 0.0f, 1.0f };

    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);

    glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glMaterialf(GL_FRONT, GL_SHININESS, 25);

    GLfloat position[] = { -0.5, -1.0, 2.0,  1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, position);


    //drawAxes();
    //drawGrid(1000);

    //glColor3f(1,0,0);
    car -= 0.5;
    camY -= 0.5;
    sky -= 0.5;


    if (abs(car) <= 4000)
    {

        //********Right side of the road - start
        for (int i = 1, j = 0; i <= 25; i++, j += 200) {

            if (i == 1) {
                glPushMatrix();
                glTranslatef(-120, -j, 0);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }

            else if (i > 1 && i <= 4) {
                glPushMatrix();
                glTranslatef(-120, -j, 20);
                drawBigTree();         //----Big tree
                glPopMatrix();
            }

            else if (i == 5) {
                glPushMatrix();
                glTranslatef(-120, -j, 0);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }

            else if (i > 5 && i <= 8) {
                glPushMatrix();
                glTranslatef(-150, -j, 0);
                drawHouse2();         //----2 floor house
                glPopMatrix();
            }

            else if (i == 9) {
                glPushMatrix();
                glTranslatef(-120, -j, 0);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }

            else if (i > 9 && i <= 12) {
                glPushMatrix();
                glTranslatef(-120, -j, 20);
                drawBigTree();         //----Big tree
                glPopMatrix();
            }

            else if (i == 13) {
                glPushMatrix();
                glTranslatef(-120, -j, 0);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }

            else if (i > 13 && i <= 16) {
                glPushMatrix();
                glTranslatef(-120, -j, 0);
                drawHouse();         //----House
                glPopMatrix();
            }

            else if (i == 17) {
                glPushMatrix();
                glTranslatef(-120, -j, 0);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }

            else if (i > 17 && i <= 20) {
                glPushMatrix();
                glTranslatef(-120, -j, 20);
                drawBigTree();         //----Big tree
                glPopMatrix();
            }

            else if (i == 21) {
                glPushMatrix();
                glTranslatef(-120, -j, 0);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }

            else {
                glPushMatrix();
                glTranslatef(-120, -j, 0);
                drawHouse();         //----House
                glPopMatrix();
            }
        }


        //********Left side of the road - start
        for (int i = 1, j = 0; i <= 25; i++, j += 200) {
            if (i <= 2) {
                glPushMatrix();
                glTranslatef(150, -j, 0);
                drawHouse2();         //----2 floor house
                glPopMatrix();
            }

            else if (i == 3) {
                glPushMatrix();
                glTranslatef(120, -j, 0);
                glRotatef(180, 0, 0, 1);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }

            else if (i > 3 && i <= 6) {
                glPushMatrix();
                glTranslatef(120, -j, 0);
                drawHouse();         //----1 floor house
                glPopMatrix();

            }

            else if (i == 7) {
                glPushMatrix();
                glTranslatef(120, -j, 0);
                glRotatef(180, 0, 0, 1);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }

            else if (i > 7 && i <= 10) {
                glPushMatrix();
                glTranslatef(120, -j, 0);
                drawSmallSphereTree();         //----Sphere tree - small
                glPopMatrix();
            }

            else if (i == 11) {
                glPushMatrix();
                glTranslatef(120, -j, 0);
                glRotatef(180, 0, 0, 1);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }

            else if (i > 11 && i <= 14) {
                glPushMatrix();
                glColor3f(.345, .78, 0);
                glTranslatef(130, -j + 20, -40);
                drawRock();         //----Rock
                glPopMatrix();

                glPushMatrix();
                glTranslatef(300, -j, -50);
                glRotatef(90, 0, 0, 1);
                drawWindmill();     //----wind mill
                glPopMatrix();
            }

            else if (i == 15) {
                glPushMatrix();
                glTranslatef(120, -j, 0);
                glRotatef(180, 0, 0, 1);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }

            else if (i > 15 && i <= 18) {
                glPushMatrix();
                glTranslatef(120, -j, 0);
                drawSmallConeTree();         //----Cone tree - small
                glPopMatrix();

            }

            else if (i == 19) {
                glPushMatrix();
                glTranslatef(120, -j, 0);
                glRotatef(180, 0, 0, 1);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }

            else if (i > 19 && i <= 22) {
                glPushMatrix();
                glTranslatef(150, -j, 0);
                drawHouse2();         //----2 floor house
                glPopMatrix();
            }

            else if (i == 23) {
                glPushMatrix();
                glTranslatef(120, -j, 0);
                glRotatef(180, 0, 0, 1);
                drawLightTower();         //---Light tower
                glPopMatrix();
            }
            else {
                glPushMatrix();
                glTranslatef(120, -j, 0);
                drawSmallConeTree();         //----Cone tree - small
                glPopMatrix();
            }
        }

        drawRoad();
        drawRoadMiddle();
    }


    else if (abs(car) <= 4500)
    {
        cout << "problem\n";;

        //********Right side until road end
        for (int i = 0, j = 0; i <= 15; i++, j += 200) {


            glPushMatrix();
            glTranslatef(-120, -j, 0);
            drawHouse();         //----House
            glPopMatrix();

        }

        //********Left side until road end
        for (int i = 0, j = 0; i <= 15; i++, j += 200) {
            glPushMatrix();
            glTranslatef(120, -j, 0);
            drawSmallConeTree();         //----Cone tree - small
            glPopMatrix();
        }
        drawRoad();
        drawRoadMiddle();
    }


    else {
        //right side after road end
        for (int i = 0, j = 4700; i <= 10; i++, j += 100) {
            glPushMatrix();
            glTranslatef(-120, -j, 0);
            drawBigTree();         //----Big tree
            glPopMatrix();
        }

        //left side after road end
        for (int i = 0, j = 4700; i <= 10; i++, j += 100) {
            glPushMatrix();
            glTranslatef(120, -j, 0);
            drawBigTree();         //----Big tree
            glPopMatrix();

        }

        // drawRoad();
         //drawRoadMiddle();

    }
    drawMainCar();         //----car

    glPushMatrix();
    glTranslatef(-20, 0, 0);
    drawCar1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25, 0, 0);
    drawCar2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-5, 0, 0);
    drawCar3();
    glPopMatrix();

    glPushMatrix();
    drawBackground();     //----sky
    glPopMatrix();

    glPushMatrix();
    drawSun();
    glPopMatrix();

    glPushMatrix();
    drawHill();
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}


void animate() {
    angle += 0.05;

    glutPostRedisplay();
}
void init() {
    glClearColor(0.345, 0.4, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);

   
}


void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        car -= 10;
        camY -= 10;
        sky -= 10;
        if (camY == -10000) {
            camY = 50; car = 0;
        }
    }

    if (key == GLUT_KEY_DOWN) {
        car += 5;
        camY += 5;
        sky += 5;
    }

    if (key == GLUT_KEY_LEFT) {
        if (leftRightMove == 30) {
            leftRightMove = 0;
            //return;
        }

        else {
            leftRightMove += 1.5;
        }
    }

    if (key == GLUT_KEY_RIGHT) {
        if (leftRightMove == -30) {
            leftRightMove = 0;             //----get back to starting point when try to esc from the road 
            //return;
        }

        else {
            leftRightMove -= 1.5;
        }
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'Z')	camZ += 0.8;
    if (key == 'z')	camZ -= 0.8;

    if (key == 'X')	camX += 0.8;
    if (key == 'x')	camX -= 0.8;

    if (key == 'w')	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == 'o')	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (key == '1')	glEnable(GL_LIGHT0);
    if (key == '!')	glDisable(GL_LIGHT0);

    glutPostRedisplay();
}


void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    GLfloat aspect = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, aspect, 1, 2000.0);
}

void doFrame(int v) {
    frameNumber++;
    glutPostRedisplay();
    glutTimerFunc(100, doFrame, 0);
}

//move red car
void move1(int v) {
    moveCar1 -= 5;
    glutPostRedisplay();
    glutTimerFunc(50, move1, 0);
}

//move blue car
void move2(int v) {
    moveCar2 -= 10;
    glutPostRedisplay();
    glutTimerFunc(10, move2, 0);
}

//move magenta car
void move3(int v) {
    moveCar3 -= 8;
    glutPostRedisplay();
    glutTimerFunc(30, move3, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1200, 900);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("CS308 Final Project");

    init();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutReshapeFunc(reshape);

    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(100, doFrame, 0);
    glutTimerFunc(50, move1, 0);
    glutTimerFunc(10, move2, 0);
    glutTimerFunc(30, move3, 0);

    glutMainLoop();
    return 0;
}