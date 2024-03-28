#include <windows.h>
#include<bits/stdc++.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

static float shoulder = 0, elbow = 0, hand=0,rotateelbow=0,rotaterightshoulder=0,
           leftshoulder = 0, leftelbow = 0, lefthand=0,rotateleftelbow=0,rotateleftshoulder=0,
           body=0,head=0,translatebody=0,
           rightleg=0, rightknee=0,rightfoot=0,
           leftleg=0, leftknee=0,leftfoot=0,
           walk=0,height=100,rotaterobe=0,up=0,dist=0,flag1=0,rotatejump=0,
           translatetree1=0,translatetree2=0,translatetree3=0;
static int spin=0;
bool flag,flagrotate,flagwalk,playmove,flaglight;
void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   GLfloat mat_specular[] = { 1.0, 1.0, .8, 1.0 };
   GLfloat ambient[] = { 0.,.0,0., 1.0 };
   GLfloat lmodel_ambient[] = { 1., 1.,.8, 1.0 };
   glEnable(GL_COLOR_MATERIAL);
   glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   GLfloat diffuse[] = { .5, .5, .25, .8 };
   GLfloat position[] = { 3, 1.5, 0, 0.0 };
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
}
void movesun(void){
    spin=(spin+1)%90;
   glutPostRedisplay();
}
void walkbackward(void)
{
    if(body<180 &&!flagwalk)
    {
        body+=5;
        elbow-=2.5;
        leftelbow+=2.5;
    }
    else
    {
        flagwalk=1;
        if(!flagrotate)
        {
            leftknee-=3;
           rotaterightshoulder-=3;
            if(flag)
            {
                rightknee+=3;
                rotateleftshoulder+=3;
            }
            if(leftknee<-45)flagrotate=3;
        }
        else
        {
            if(leftknee<0 && !flag)
            {
                leftknee+=3;
                rotaterightshoulder+=3;
            }
            else
            {
                leftknee+=3;
                rotaterightshoulder+=3;
                flag=1;
                rightknee-=3;
                rotateleftshoulder-=3;
                if(leftknee>45)flagrotate=0;
            }
        }
        translatetree3+=0.05;
        if(translatetree3-5>5)translatetree3=-10;
        translatetree2+=0.05;
        if(translatetree2-2.5>5)translatetree2=-10;
        translatetree1+=0.05;
        if(translatetree1>5)translatetree1=-10;
    }
    glutPostRedisplay();
}
void jump()
{
    if(shoulder>-90)
    {
        shoulder-=5;
        leftshoulder+=5;
        glutPostRedisplay();
    }
    else
    {
        body+=1;
        rotaterobe+=360.0/(135.0/2.0);
        if(rotatejump<45 && flag1==1)
        {
            rotatejump+=2;
            dist-=0.024;
            glutPostRedisplay();
        }
        else
        {
            if(dist>0.0 )
            {
                flag1=2;
                up-=0.07;
                if(up<=0)
                {
                    rotaterobe=0;
                    dist=0;
                    up=0;
                    rotatejump=0;
                    flag1=1;
                    glutPostRedisplay();
                }

                else
                    glutPostRedisplay();
            }
            else
            {
                flag1=0;
                rotatejump-=2;
                dist+=0.024;
                up+=0.07;
                glutPostRedisplay();
            }
        }
    }
}
void initrotate()
{
    shoulder = 0;elbow = 0;hand=0;rotateelbow=0;rotaterightshoulder=0;
      leftshoulder = 0;leftelbow = 0;lefthand=0;rotateleftelbow=0;rotateleftshoulder=0;body=0;head=0;
      translatebody=0;rightleg=0;rightknee=0;rightfoot=0;leftleg=0;leftknee=0;leftfoot=0;walk=0;height=100;
      rotaterobe=0;up=0;dist=0;flag1=0;rotatejump=0;translatetree1=0;translatetree2=0;translatetree3=0;
      flag=0;flagrotate=0;flagwalk=0;
}
void display(void)
{
    GLfloat position[] = { 3,1.5,0,.0 };
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,1);
    double r=5.0/4.0;
    double pi=2*acos(0.0);
        //sky
    glPushMatrix();
        glTranslatef(0,0,-11);
        glColor3f(0.1,0.4,0.9);
        glScalef(100,100,0.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //SUN
    if(!flaglight)
    {
        glPushMatrix();
           glRotated ((GLdouble) -spin, (GLdouble) spin, 0.0, 0.0);
            glLightfv (GL_LIGHT0, GL_POSITION, position);
            glColor3f(1,1,0.7);
            glTranslatef(3.0,1.5,0);
            glScalef(.15,.15,0.15);
            glutSolidSphere(1.5,500,500);
        glPopMatrix();
    }

    //ground
    glPushMatrix();
        glColor3f(0,0.6,0);
        glTranslatef(-2.5,-0.9,0.0);
        glScalef(50,0.2,1000);
        glutSolidCube(1.0);
    glPopMatrix();

    //street
    glPushMatrix();
        glTranslatef(0.0,0,0);
        glScalef(0.7,1,1);
        glPushMatrix();
            glColor3f(0.2,0.2,0.2);
            glTranslatef(0.0,-0.8,0.0);
            glScalef(5,0.2,100);
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(1.5,-0.8,0.0);
            glColor3f(1,1,1);
            glScalef(0.1,0.3,100);
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1.5,-0.8,0.0);
            glColor3f(1,1,1);
            glScalef(0.1,0.3,100);
            glutSolidCube(1.0);
        glPopMatrix();

    glPopMatrix();
      //tree3left
    glPushMatrix();
        glTranslatef(0.0,0.0,translatetree3);
        glPushMatrix();
            glTranslatef(2.5,-0.6,-5);
            glScalef(0.25,2,0.025);
            glColor3f(0.4,0.2,0.1);
            glutSolidCube(0.5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,0.0,-5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,-0.1,-5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,0.1,-5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,0.2,-5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();
    glPopMatrix();

    //tree2left
    glPushMatrix();

        glTranslatef(0.0,0.0,translatetree2);
        glPushMatrix();
            glTranslatef(2.5,-0.6,-2.5);
            glScalef(0.25,2,0.025);
            glColor3f(0.4,0.2,0.1);
            glutSolidCube(0.5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,0.0,-2.5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,-0.1,-2.5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,0.1,-2.5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,0.2,-2.5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

    glPopMatrix();
    //tree1left
    glPushMatrix();

        glTranslatef(0.0,0.0,translatetree1);

        glPushMatrix();
            glTranslatef(2.5,-0.6,0.0);
            glScalef(0.25,2,0.025);
            glColor3f(0.4,0.2,0.1);
            glutSolidCube(0.5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,0.0,0.0);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,-0.1,0.0);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,0.1,0.0);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.5,0.2,0.0);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

    glPopMatrix();
     //tree3right
    glPushMatrix();

        glTranslatef(0.0,0.0,translatetree3);

        glPushMatrix();
            glTranslatef(-2.5,-0.6,-5);
            glScalef(0.25,2,0.025);
            glColor3f(0.4,0.2,0.1);
            glutSolidCube(0.5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,0.0,-5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,-0.1,-5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,0.1,-5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,0.2,-5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

    glPopMatrix();

    //tree2right
    glPushMatrix();

        glTranslatef(0.0,0.0,translatetree2);

        glPushMatrix();
            glTranslatef(-2.5,-0.6,-2.5);
            glScalef(0.25,2,0.025);
            glColor3f(0.4,0.2,0.1);
            glutSolidCube(0.5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,0.0,-2.5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,-0.1,-2.5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,0.1,-2.5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,0.2,-2.5);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

    glPopMatrix();
    //tree1right
    glPushMatrix();

        glTranslatef(0.0,0.0,translatetree1);

        glPushMatrix();
            glTranslatef(-2.5,-0.6,0.0);
            glScalef(0.25,2,0.025);
            glColor3f(0.4,0.2,0.1);
            glutSolidCube(0.5);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,0.0,0.0);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,-0.1,0.0);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,0.1,0.0);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2.5,0.2,0.0);
            glColor3f(0,0.8,0.4);
            glBegin(GL_TRIANGLES);
                glVertex3f(0.25,0.0,0.0);
                glVertex3f(-0.25,0.0,0.0);
                glVertex3f(0.0,0.25,0.0);
            glEnd();
        glPopMatrix();

    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,0.1,3.0);
        glScalef(0.3,0.3,0.3);

        glPushMatrix();
        glTranslatef(0,up,0);
            glPushMatrix();
                glScalef(.25,.25,.25);
                //body-------------------------------------
                glPushMatrix();
                    // glScalef(.25,.25,.25);
                    // glTranslatef (0, 0.0, walk);
                    glRotatef ((GLfloat) body, 0.0, 1.0, .0);
                    glTranslatef(0,4*dist,0);
                    glTranslatef((GLfloat)translatebody,0.0,0.0);
                    glPushMatrix();
                        glColor3f(.6, .6, 1.);
                        glScalef (4.0, 4, 1.0);
                        glutSolidCube (1.0);
                    glPopMatrix();
                    glTranslatef(0,0,0.6);
                    glPushMatrix();
                        glTranslatef(-0.,1.,0.);
                        glPushMatrix();
                            glScalef(0.5,0.5,0.);
                            glColor3f(1.,1.5,1.);
                            glutSolidSphere(0.5,480,460);
                        glPopMatrix();
                    glPopMatrix();

                    glPushMatrix();
                        glPushMatrix();
                            glScalef(0.5,0.5,0.);
                            glColor3f(1.,1.5,1.);
                            glutSolidSphere(0.5,480,460);
                        glPopMatrix();
                    glPopMatrix();

                    glPushMatrix();
                        glTranslatef(-0.,-1.,0.);
                        glPushMatrix();
                            glScalef(0.5,0.5,0.);
                            glColor3f(1.,1.5,1.);
                            glutSolidSphere(0.5,480,460);
                        glPopMatrix();
                    glPopMatrix();
                    glTranslatef(0,0,-0.5);
                    //glPopMatrix();

                    glPushMatrix();
                        //head----------------------------------------
                        // glRotatef(body,0.0,1.0,0.0);

                        //  glTranslatef (0, 0.0, walk);
                        glRotatef ((GLfloat) head, 0.0, 1.0, 0.0);
                        glTranslatef (-0, 3.3, 0.0);
                        glColor3f(.8, .8, 1.0);
                        glPushMatrix();
                            glScalef (2.0, 2, 1.0);
                            glutSolidCube(1.0);
                        glPopMatrix();

                        glColor3f(1,1,1);
                        glTranslatef(-0.4,0.5,0.6);
                        glPushMatrix();
                            glScalef(0.5,0.5,0.);
                            glutSolidSphere(0.5,480,460);
                        glPopMatrix();

                        glTranslatef(0.9,0.,0.);
                        //glRotatef(body,0.0,1.0,0.0);
                        glPushMatrix();
                            glScalef(0.5,0.5,0.);
                            glutSolidSphere(0.5,480,460);
                        glPopMatrix();

                        glTranslatef(-0.5,-1.,0.);
                        // glRotatef(body,0.0,1.0,0.0);
                        glPushMatrix();
                            glScalef(1.625,0.5,0.);
                            glutWireSphere(0.2,40,40);
                        glPopMatrix();

                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();

            //right arm-----------------------------------
            glPushMatrix();
                glScalef(.25,.25,.25);
                // glTranslatef (0, 0.0, walk);
                glRotatef ((GLfloat) body, 0.0, 1.0, 0.0);
                glTranslatef(0,dist*4,0);
                glTranslatef (2.5, 1.5, 0.0);

                glRotatef(rotaterightshoulder,1.0,0.0,0.0);
                glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
                glTranslatef (1.0, 0.0, 0.0);
                glPushMatrix();
                    glColor3f(1., 1.0, 1.0);
                    glScalef (2.0, .8, 1.0);
                    glutSolidCube (1.0);
                glPopMatrix();

                glTranslatef (1.0, 0.0, 0.0);
                glRotatef((GLfloat)rotateelbow,1.0,0.0,0.0);
                glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
                glTranslatef (1.0, 0.0, 0.0);
                glPushMatrix();
                    glColor3f(.8, .8, 1.0);
                    glScalef (2.0, .8, 1.0);
                    glutSolidCube (1.0);
                glPopMatrix();

                glTranslatef (.5, 0.0, 0.0);
                glRotatef ((GLfloat) hand, 0.0, 0.0, 1.0);
                glTranslatef (1.0, 0.0, 0.0);
                glPushMatrix();
                    glColor3f(1., 1.0, 1.0);
                    glScalef (1.0, 1.2, 1.0);
                    glutSolidCube (1.0);
                glPopMatrix();
            glPopMatrix();
            //left arm-----------------------------------
            glPushMatrix();

                glScalef(.25,.25,.25);
                glTranslatef (0, 0, 0.0);
                glRotatef ((GLfloat) body, 0.0, 1.0, 0.0);
                glTranslatef(0,4*dist,0);
                glTranslatef (-2.5, 1.5, 0.0);

                glRotatef(rotateleftshoulder,1.0,0.0,0.0);
                glRotatef ((GLfloat) leftshoulder, 0.0, 0.0, 1.0);
                glTranslatef (-1., 0.0, 0.0);
                glPushMatrix();
                    glColor3f(1., 1.0, 1.0);
                    glScalef (2.0, .8, 1.0);
                    glutSolidCube (1.0);
                glPopMatrix();

                glTranslatef (-1., 0.0, 0.0);
                glRotatef((GLfloat)rotateleftelbow,1.0,0.0,0.0);
                glRotatef ((GLfloat) leftelbow, 0.0, 0.0, 1.0);
                glTranslatef (-1., 0.0, 0.0);
                glPushMatrix();
                    glColor3f(.8, 0.8, 1.0);
                    glScalef (2.0, .8, 1.0);
                    glutSolidCube (1.0);
                glPopMatrix();

                glTranslatef (-.5, 0.0, 0.0);
                glRotatef ((GLfloat) lefthand, 0.0, 0.0, 1.0);
                glTranslatef (-1.0, 0.0, 0.0);
                glPushMatrix();
                    glColor3f(1., 1.0, 1.0);
                    glScalef (1.0, 1.2, 1.0);
                    glutSolidCube (1.0);
                glPopMatrix();
            glPopMatrix();

            //right leg-----------------------------------
            glPushMatrix();

                glScalef(.25,.25,.25);
            //  glTranslatef (-0, -.0, walk);
                glTranslatef (-0, 0.4, 0.0);
                glRotatef ((GLfloat) body, 0.0, 1.0, 0.0);
                glTranslatef(0,dist*4,0);
                glRotatef ((GLfloat) rightleg, 1.0, 0.0, 0.0);
                glTranslatef (1, -4, 0.0);
                glPushMatrix();
                    glTranslatef(0,1.5,0);
                    glRotatef(-rotatejump,1,0,0);
                    glTranslatef(0,-1.5,0);
                    glPushMatrix();
                        glScalef (1., 3, 1.0);
                        glutSolidCube(1.0);
                    glPopMatrix();
                glPopMatrix();

                glTranslatef(0,-dist*4,0);
                glRotatef ((GLfloat) rightknee, 1.0, 0.0, 0.0);
                glTranslatef (0.0, -3, 0.0);
                glPushMatrix();
                    glTranslatef(0,-1.5,0);
                    glRotatef(+rotatejump,1,0,0);
                    glTranslatef(0,+1.5,0);
                    glColor3f(.8, 0.8, 1.0);
                    glScalef (1.0, 3, 1.0);
                    glutSolidCube(1.0);
                glPopMatrix();

                glTranslatef (-1, -1.5, 0.0);
                glRotatef ((GLfloat) rightfoot, 0.0, 0.0, 1.0);
                glTranslatef (1.0, 0.0, 0.0);
                glPushMatrix();

                    glColor3f(1., 1.0, 1.0);
                    glScalef (1.5, 1., 1.5);
                    glutSolidCube (1.0);
                glPopMatrix();
            glPopMatrix();
            //left leg-----------------------------------
            glPushMatrix();

                glScalef(.25,.25,.25);
                // glTranslatef (-0, -.0, walk);
                glTranslatef (-0, 0.4, 0.0);
                glRotatef ((GLfloat) body, 0.0, 1.0, 0.0);
                glTranslatef(0,dist*4,0);
                glRotatef ((GLfloat) leftleg, 1.0, 0.0, .0);
                glTranslatef (-1., -4, 0.0);
                glPushMatrix();
                    glTranslatef(0,+1.5,0);
                    glRotatef(-rotatejump,1,0,0);
                    glTranslatef(0,-1.5,0);
                    glPushMatrix();
                        glColor3f(1., 1.0, 1.0);
                        glScalef (1.0, 3, 1.0);
                        glutSolidCube (1.0);
                    glPopMatrix();
                glPopMatrix();

                glTranslatef(0,-4*dist,0);
                glTranslatef (0, -1, 0.0);
                glTranslatef (0, 1, 0.0);
                glRotatef ((GLfloat) leftknee, 1.0, 0.0, .0);
                glTranslatef (0.0, -3, 0.0);
                glPushMatrix();
                    glTranslatef(0,-1.5,0);
                    glRotatef(+rotatejump,1,0,0);
                    glTranslatef(0,+1.5,0);
                    glColor3f(.8, 0.8, 1.0);
                    glScalef (1.0, 3, 1.0);
                    glutSolidCube (1.0);
                glPopMatrix();

                glTranslatef (-1, -1.5, 0.0);
                glRotatef ((GLfloat) leftfoot, 0.0, 0.0, 1.0);
                glTranslatef (1.0, 0.0, 0.0);
                glPushMatrix();

                    glColor3f(1., 1.0, 1.0);
                    glScalef (1.5, 1., 1.5);
                    glutSolidCube (1.0);
                glPopMatrix();

            glPopMatrix();
        glPopMatrix();

        //jump mashin
        glPushMatrix();
            glTranslatef(0,-0.4,0);
            glColor3f(0.6,0.6,1);
            glTranslatef(0,height,0);
            glPushMatrix();
                glTranslatef(0,(1.5/4.0)-(0.6/4.0),0);
                glRotatef((GLfloat)rotaterobe,1,0,0);
                glTranslatef(0,0,0);
                glBegin(GL_LINE_STRIP);
                for(int z=0;z<=180;z++)
                {
                    glVertex3f(r*2*cos(z*pi/180),r*1.5*sin(z*pi/180),0);
                }
                glEnd();
                glTranslatef(2.5,0,0);
                glutSolidCube(0.25);
                glTranslatef(-5,0,0);
                glutSolidCube(0.25);
            glPopMatrix();
            glPushMatrix();
                glPushMatrix();
                    glTranslatef(2*r+0.75/4,-0.5,0);
                    glScalef(1,12,1);
                    glutSolidCube(0.25);
                    glTranslatef(-4*r-1.5/4,0,0);
                    glutSolidCube(0.25);

                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}
void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5);
    gluLookAt(0,0,0,0,0,-15,0,1,0);
}
void keyboard (unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':   /*  s key rotates at shoulder  */
       if(shoulder<90)shoulder+=5;
        glutPostRedisplay();
        break;
    case 'S':
        if(shoulder>-90)shoulder-=5;
        glutPostRedisplay();
        break;
    case 'e':  /*  e key rotates at elbow  */
        if(elbow+shoulder<150)elbow+=5;
        glutPostRedisplay();
        break;
    case 'E':
        if(elbow+shoulder>-150)elbow-=5;
        glutPostRedisplay();
        break;
    case 'd':   /*  d key rotates at leftshoulder  */
        if(leftshoulder>-90)leftshoulder-=5;
        glutPostRedisplay();
        break;
    case 'D':
        if(leftshoulder < 90)leftshoulder+=5;
        glutPostRedisplay();
        break;
    case 'r':  /*  r key rotates at leftelbow  */
        if(leftelbow+leftshoulder> -150)leftelbow-=5;
        glutPostRedisplay();
        break;
    case 'R':
        if(leftelbow+leftshoulder <150)leftelbow+=5;
        glutPostRedisplay();
        break;
    case 'f':   /*  f key rotates at leftleg  */
        if(leftleg - 5 > -30)
            leftleg += -5;
        glutPostRedisplay();
        break;
    case 'F':
        if(leftleg + 5 < 30)
            leftleg+= 5;
        glutPostRedisplay();
        break;
    case 't':  /*  t key rotates at leftknee  */
        if(leftknee> -30)
            leftknee+= -5;
        glutPostRedisplay();
        break;
    case 'T':
        if(leftknee < 30)
            leftknee+= 5;
        glutPostRedisplay();
        break;
    case 'g':  /*  g key rotates at rightleg  */
        if(rightleg > -30)
            rightleg+= -5;
        glutPostRedisplay();
        break;
    case 'G':
        if(rightleg< 30)
            rightleg+=5;
        glutPostRedisplay();
        break;
    case 'y':  /*  y key rotates at rightknee  */
        if(rightknee> -30)
            rightknee+=-5;
        glutPostRedisplay();
        break;
    case 'Y':
        if(rightknee< 30)
            rightknee+=5;
        glutPostRedisplay();
        break;
    case 'b':
        body+=5;
        glutPostRedisplay();
        break;
    case 'B':
        body-=5;
        glutPostRedisplay();
        break;
    case 'h':
        if(head<90)
            head = (head + 5);
        glutPostRedisplay();
        break;
    case 'H':
        if(head>-90)
            head-=5;
        glutPostRedisplay();
        break;
    case 'w':      /* w to walk backward*/
        glutIdleFunc(walkbackward);
        break;
    case 'l':
        glutIdleFunc(movesun);
    break;
    default:
        break;
    }
}
void menu(int val)
{
    if(val==1)
    {
        glutIdleFunc(NULL);
        initrotate();
        glutPostRedisplay();
    }
    if(val==2)
    {
        playmove=0;
        initrotate();
        glutIdleFunc(walkbackward);
    }
    else if(val==3)
    {
        playmove=1;
        initrotate();
        height=0;
        glutIdleFunc(jump);
    }
    else if(val==4)
    {
        glutIdleFunc(NULL);
    }
    else if(val==5)
    {
        if(playmove==0)
        {
            glutIdleFunc(walkbackward);
        }
        else
        {
            height=0;
            glutIdleFunc(jump);
        }
    }
    else if(val==6)
    {
        flaglight=0;
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glutPostRedisplay();
    }
    else
    {
        flaglight=1;
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glutPostRedisplay();
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("ROBOT");
    init ();
    glutCreateMenu(menu);
    glutAttachMenu(GLUT_LEFT_BUTTON);
    glutAddMenuEntry("Start",1);
    glutAddMenuEntry("Walk",2);
    glutAddMenuEntry("Robe Jumping",3);
    glutAddMenuEntry("Pause",4);
    glutAddMenuEntry("Resume",5);
    glutAddMenuEntry("Light",6);
    glutAddMenuEntry("NO Light",7);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
