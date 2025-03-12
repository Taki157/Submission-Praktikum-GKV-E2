#include <GL/glut.h>

// void gambarPersegi(float x, float y, float sisi) {
//     glBegin(GL_QUADS);
//         glVertex2f(x, y);
//         glVertex2f(x + sisi, y);
//         glVertex2f(x + sisi, y - sisi);
//         glVertex2f(x, y - sisi);
//     glEnd();
// }

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // float startX = -0.8f, startY = 0.8f;
    // float sisi = 0.3f;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glColor4f(0.64f, 0.85f, 0.89f, 0.1f);
    for (int i = 0; i < 10; i++) {
        // gambarPersegi()
        float shift = i * 0.1f;
        glRectf(-0.2f + shift, 0.2f - shift, 0.0f + shift, 0.0f - shift);
    }

    // for (int i = 0; i < 2; i++) { // Dua baris
    //     for (int j = 0; j < 2; j++) { // Dua kolom
    //         float x = startX + j * 0.4f;
    //         float y = startY - i * 0.4f;
            
    //         glColor3f((i + j) % 2, 1.0f - ((i + j) % 2), 0.0f); // Alternatif warna merah/hijau
    //         gambarPersegi(x, y, sisi);
    //     }
    // }

    glFlush();
}



int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800,800);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Kotak");
    glutDisplayFunc(display);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    
    return 0;
}