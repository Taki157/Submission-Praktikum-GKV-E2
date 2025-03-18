#include <GL/glut.h>
#include <math.h>

const float pi = 3.14159265358979323846;
float carPosX = 0.0;
float carPosY = 0.0;
float carSpeed = 0.05;
float wheelAngle = 0.0;

// Fungsi untuk menggambar lingkaran (untuk roda)
void drawCircle(float x, float y, float radius) {
    int segments = 30;
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float theta = 2.0f * pi * i / segments;
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Fungsi untuk menggambar roda dengan jari-jari
void drawWheel(float x, float y, float radius) {
    // Roda - lingkaran hitam
    glColor3f(0.2, 0.2, 0.2);
    drawCircle(x, y, radius);
    
    // Velg - lingkaran abu-abu
    glColor3f(0.7, 0.7, 0.7);
    drawCircle(x, y, radius * 0.6);
    
    // Jari-jari roda
    glColor3f(0.2, 0.2, 0.2);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 5; i++) {
        float theta = wheelAngle + 2.0f * pi * i / 5;
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x, y);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Posisikan mobil
    glPushMatrix();
    glTranslatef(carPosX, carPosY, 0.0);
    
    // Badan mobil - persegi panjang
    glColor3f(0.3, 0.3, 0.3); // Abu-abu
    glBegin(GL_POLYGON);
    glVertex2f(-0.4, -0.1);
    glVertex2f(0.4, -0.1);
    glVertex2f(0.4, 0.07);
    glVertex2f(0.37, 0.1);
    glVertex2f(-0.4, 0.1);
    glEnd();
    
    // Kabin mobil - trapesium
    glColor3f(0.0, 0.0, 1.0); // Biru
    glBegin(GL_POLYGON);
    glVertex2f(-0.2, 0.1);
    glVertex2f(0.2, 0.1);
    glVertex2f(0.15, 0.25);
    glVertex2f(-0.15, 0.25);
    glEnd();
    
    // Kaca depan
    glColor3f(0.8, 0.8, 1.0); // Biru muda
    glBegin(GL_POLYGON);
    glVertex2f(0.15, 0.1);
    glVertex2f(0.2, 0.1);
    glVertex2f(0.15, 0.25);
    glEnd();
    
    // Kaca belakang
    glBegin(GL_POLYGON);
    glVertex2f(-0.15, 0.1);
    glVertex2f(-0.2, 0.1);
    glVertex2f(-0.15, 0.25);
    glEnd();
    
    // Lampu depan
    glColor3f(1.0, 1.0, 0.0); // Kuning
    glBegin(GL_POLYGON);
    glVertex2f(0.38, -0.05);
    glVertex2f(0.4, -0.05);
    glVertex2f(0.4, 0.05);
    glVertex2f(0.38, 0.05);
    glEnd();
    
    // Lampu belakang
    glColor3f(1.0, 0.0, 0.0); // Merah
    glBegin(GL_POLYGON);
    glVertex2f(-0.38, -0.05);
    glVertex2f(-0.4, -0.05);
    glVertex2f(-0.4, 0.05);
    glVertex2f(-0.38, 0.05);
    glEnd();
    
    // Roda
    drawWheel(-0.25, -0.1, 0.08);
    drawWheel(0.25, -0.1, 0.08);
    
    glPopMatrix();
    
    glutSwapBuffers();
}

void update(int value) {
    // Update posisi mobil
    carPosX += carSpeed;
    
    // Reset posisi jika keluar layar
    if (carPosX > 1.4) {
        carPosX = -1.4;
    } else if (carPosX < -1.4) {
        carPosX = 1.4;
    }
    
    // Update rotasi roda
    wheelAngle += carSpeed > 0 ? 0.1 : -0.1;
    if (carSpeed > 0) {
        wheelAngle += 0.1;
    } else if (carSpeed < 0) {
        wheelAngle -= 0.1;
    } else {
        wheelAngle = 0;
    }
    
    if (wheelAngle > 0) {
        wheelAngle -= 2 * pi;
    } else if (wheelAngle < 0) {
        wheelAngle += 2 * pi;
    } else {
        wheelAngle = 0;
    }
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Sekitar 60 FPS
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC key
            exit(0);
            break;
        case 'a': // Gerak ke kiri
            carSpeed = -0.05;
            break;
        case 'd': // Gerak ke kanan
            carSpeed = 0.05;
            break;
        case 's': // Berhenti
            carSpeed = 0.0;
            break;
    }
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Pertahankan aspek rasio
    if (width <= height) {
        glOrtho(-1.0, 1.0, -1.0 * (GLfloat)height / (GLfloat)width,
                1.0 * (GLfloat)height / (GLfloat)width, -1.0, 1.0);
    } else {
        glOrtho(-1.0 * (GLfloat)width / (GLfloat)height,
                1.0 * (GLfloat)width / (GLfloat)height, -1.0, 1.0, -1.0, 1.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mobil Gwejh");
    
    glClearColor(0.8, 0.8, 0.8, 1.0); // Warna background abu-abu muda
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(25, update, 0);
    
    glutMainLoop();
    return 0;
}