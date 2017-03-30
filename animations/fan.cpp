#include <GL/glut.h>
#include <math.h>
#include "iostream"
using namespace std;

struct rot_state {
    bool rotating;    // animation/movement happening
    float x,y,z;      // current rotation values
    int current_axis; // 0 for x, 1 for y, 2 for z
} app_state;

void init(void){
    // Setting up initial app state
    app_state.rotating = false;
    app_state.x = app_state.y = app_state.z = 0.0f;
    app_state.current_axis = 0;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
}

void action(void)
{
    // Animate the rotation
    float increment = 1.0f;
    switch (app_state.current_axis)
    {
    case 0:
        app_state.x += increment;
        break;
    case 1:
        app_state.y += increment;
        break;
    case 2:
        app_state.z += increment;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Apply the rotations
    glRotatef(app_state.x, 1, 0, 0);
    glRotatef(app_state.y, 0, 1, 0);
    glRotatef(app_state.z, 0, 0, 1);

    glBegin(GL_LINE_LOOP);
    glColor3f(1.00, 0.00, 0.00);
    glVertex3f(0.00, 0.00, 0.00);
    glVertex3f(0.00, 0.00, -1.00);
    glVertex3f(0.50, 0.00, -1.00);
    glVertex3f(0.75, 0.0, -0.75);
    glVertex3f(0.25, 0.25, -1.0);
    glVertex3f(0.50, 0.50, -0.50);

    glColor3f(0.00, 1.00, 0.00);
    glVertex3f(0.00, 0.00, 0.00);
    glVertex3f(0.00, 0.00, 1.00);
    glVertex3f(0.50, 0.00, 1.00);
    glVertex3f(0.75, 0.0, 0.75);
    glVertex3f(0.25, 0.25, 1.0);
    glVertex3f(0.50, 0.50, 0.50);
    glEnd();

    glPopMatrix();
    glutSwapBuffers();
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 0.5, 15.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.5, 1.5, 1.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

//keyboard event handler
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'x':
        app_state.current_axis = 0;
        break;
    case 'y':
        app_state.current_axis = 1;
        break;
    // case 'z':
    //     app_state.current_axis = 2;
    //     break;
    case 'r':
        app_state.rotating ^= 1;
        glutIdleFunc(app_state.rotating ? action : NULL);
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotating Fan");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(action);
    glutMainLoop();
    return 0;
}
