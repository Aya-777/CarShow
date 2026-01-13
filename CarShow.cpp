#include <GL/freeglut.h>
#include "Truck.h"

// Create a global instance of your Truck
Truck myTruck(Point(0,0,0));
// Function to initialize lighting and depth
void init() {
    glEnable(GL_DEPTH_TEST); // Ensures 3D objects overlap correctly
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Dark background for the expo

    // Basic Lighting setup to see the 3D shapes
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL); // Allows glColor3f to work with lights

    GLfloat lightPos[] = { 5.0f, 10.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

// The main drawing function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set the camera position
    // (Eye position, Look-at point, Up vector)
    gluLookAt(10.0, 5.0, 10.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    // Draw a simple floor grid
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5f);
    for (int i = -10; i <= 10; i++) {
        glVertex3f((float)i, 0, -10); glVertex3f((float)i, 0, 10);
        glVertex3f(-10, 0, (float)i); glVertex3f(10, 0, (float)i);
    }
    glEnd();

    // Call your Truck's draw method
    myTruck.draw();

    glutSwapBuffers();
}

// Function to handle logic updates (movement/rotation)
void idle() {
    myTruck.update();
    glutPostRedisplay(); // Redraw the screen as fast as possible
}

// Keyboard controls
void keyboard(unsigned char key, int x, int y) {
    // Press 'm' to toggle movement
    if (key == 'm' || key == 'M') {
        myTruck.isMovable = !myTruck.isMovable;
    }

    // Press 'a' or 'd' to steer the front wheels on Y-axis
    if (key == 'a' || key == 'A') {
        myTruck.steerAngle += 5.0f;
    }
    if (key == 'd' || key == 'D') {
        myTruck.steerAngle -= 5.0f;
    }

    // Press 'Esc' to exit
    if (key == 27) {
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Car Expo - 6 Wheeler Truck");

    init();

    // Setup projection (Perspective view)
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1200.0 / 800.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    // Register callbacks
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);

    glutMainLoop(); // Start the application
    return 0;
}