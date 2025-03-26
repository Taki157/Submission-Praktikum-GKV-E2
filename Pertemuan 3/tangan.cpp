#include <GL/glut.h>
#include <cmath>

// Variabel global untuk kontrol sendi
static int shoulder = 0, elbow = 0;
static int fingerRotation[5][3][2] = {{{0}}}; // [jari][sendi][sumbu Y/Z]

// Fungsi pembatas nilai untuk gerakan sendi yang realistis
int clamp(int value, int min, int max) {
    return (value < min) ? min : (value > max) ? max : value;
}

// Batasi rotasi sesuai kisaran gerak anatomi
void clampFingerRotation(int* yRotation, int* zRotation, int fingerIndex, int jointIndex) {
    // Batasan rotasi berbeda untuk setiap jari dan sendi
    int maxY = (fingerIndex == 0) ? 100 : 90;  // Ibu jari berbeda
    int maxZ = 45;  // Rotasi samping maksimal

    *yRotation = clamp(*yRotation, -maxY, maxY);
    *zRotation = clamp(*zRotation, -maxZ, maxZ);
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

// Fungsi untuk menggambar segmen jari dengan panjang dan lebar variabel
void drawFingerSegment(float length, float width) {
    glPushMatrix();
    glTranslatef(length / 2.0, 0.0, 0.0);
    glScalef(length, width, width);
    glutWireCube(1.0);
    glPopMatrix();
}

// Fungsi menggambar jari dengan panjang segmen yang berbeda
void drawFinger(int fingerIndex) {
    // Definisi panjang segmen untuk setiap jari
    float segmentLengths[5][3] = {
        {0.4, 0.3, 0.2},    // Ibu jari
        {0.5, 0.4, 0.3},    // Telunjuk
        {0.55, 0.45, 0.35}, // Jari tengah
        {0.5, 0.4, 0.3},    // Jari manis
        {0.45, 0.35, 0.25}  // Jari kelingking
    };

    glPushMatrix();
    
    // Sendi pertama - rotasi kompleks
    glRotatef(fingerRotation[fingerIndex][0][0], 0, 1, 0);  // Rotasi Y
    glRotatef(fingerRotation[fingerIndex][0][1], 0, 0, 1);  // Rotasi Z
    drawFingerSegment(segmentLengths[fingerIndex][0], 0.1);
    
    glTranslatef(segmentLengths[fingerIndex][0], 0, 0);
    
    // Sendi kedua
    glRotatef(fingerRotation[fingerIndex][1][0], 0, 1, 0);
    glRotatef(fingerRotation[fingerIndex][1][1], 0, 0, 1);
    drawFingerSegment(segmentLengths[fingerIndex][1], 0.09);
    
    glTranslatef(segmentLengths[fingerIndex][1], 0, 0);
    
    // Sendi ketiga
    glRotatef(fingerRotation[fingerIndex][2][0], 0, 1, 0);
    glRotatef(fingerRotation[fingerIndex][2][1], 0, 0, 1);
    drawFingerSegment(segmentLengths[fingerIndex][2], 0.08);
    
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    
    // Lengan atas
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Lengan bawah
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
    
    // Pergelangan tangan
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 0.5, 1.0);
    glutWireCube(1.0);
    
    // Tangan dan Jari
    // Posisi dan rotasi jari disesuaikan
    float fingerPositions[5][3] = {
        {0.3, 0.2, -0.3},   // Ibu jari
        {0.3, 0.1, 0.3},    // Telunjuk
        {0.3, 0, 0.5},      // Jari tengah
        {0.3, -0.1, 0.3},   // Jari manis
        {0.3, -0.2, -0.1}   // Jari kelingking
    };

    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(fingerPositions[i][0], fingerPositions[i][1], fingerPositions[i][2]);
        if (i == 0) glRotatef(-45, 0, 1, 0);  // Posisi khusus ibu jari
        
        glRotatef(fingerRotation[i][0][0], 0, 1, 0);
        glRotatef(fingerRotation[i][0][1], 0, 0, 1);
        drawFinger(i);
        glPopMatrix();
    }
    
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Kontrol lengan
        case 'k': shoulder = clamp(shoulder + 5, 0, 180); break;
        case 'K': shoulder = clamp(shoulder - 5, 0, 180); break;
        case 'l': elbow = clamp(elbow + 5, 0, 150); break;
        case 'L': elbow = clamp(elbow - 5, 0, 150); break;
        
        // Kontrol jari dengan rotasi Y dan Z
        // Jari 1 (telunjuk)
        case '1': fingerRotation[1][0][0] += 5; break; // Rotasi Y
        case '!': fingerRotation[1][0][0] -= 5; break;
        case '2': fingerRotation[1][0][1] += 5; break; // Rotasi Z
        case '@': fingerRotation[1][0][1] -= 5; break;
        
        // Jari 2 (jari tengah)
        case '3': fingerRotation[2][0][0] += 5; break;
        case '#': fingerRotation[2][0][0] -= 5; break;
        case '4': fingerRotation[2][0][1] += 5; break;
        case '$': fingerRotation[2][0][1] -= 5; break;
        
        // Jari 3 (jari manis)
        case '5': fingerRotation[3][0][0] += 5; break;
        case '%': fingerRotation[3][0][0] -= 5; break;
        case '6': fingerRotation[3][0][1] += 5; break;
        case '^': fingerRotation[3][0][1] -= 5; break;
        
        // Jari 4 (kelingking)
        case '7': fingerRotation[4][0][0] += 5; break;
        case '&': fingerRotation[4][0][0] -= 5; break;
        case '8': fingerRotation[4][0][1] += 5; break;
        case '*': fingerRotation[4][0][1] -= 5; break;
        
        // Ibu jari
        case '9': fingerRotation[0][0][0] += 5; break;
        case '(': fingerRotation[0][0][0] -= 5; break;
        case '0': fingerRotation[0][0][1] += 5; break;
        case ')': fingerRotation[0][0][1] -= 5; break;
        
        case 27: exit(0); break;
        default: break;
    }
    
    // Validasi rotasi
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            clampFingerRotation(&fingerRotation[i][j][0], &fingerRotation[i][j][1], i, j);
        }
    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}