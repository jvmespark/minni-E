#include "renderer.h"

void draw_triangle() {
    glBegin(GL_POLYGON);

    glColor3f(1, 1, 1); 

    glVertex3f(-0.6, -0.75, 0.5);
    glVertex3f(0.6, -0.75, 0);
    glVertex3f(0, 0.75, 0);

    glEnd();
    // Flush drawing command buffer to make drawing happen as soon as possible.
    glFlush();
}

void draw_ground() {
    glBegin(GL_QUADS);
    glColor3f(0,0,0);

    //ground plane at y = 0, spanning 100x100x100
    glVertex3f(-100, 0, 100);
    glVertex3f(100, 0,100);
    glVertex3f(-100, 0,-100);
    glVertex3f(100, 0,-100);

    glEnd();
    glFlush();
}

void render(Window window) {
    //Shader shader("shader_sources/vertexShader.vert", "shader_sources/fragShader.frag");
    //shader.use();

    glViewport(0, 0, window.width(), window.height());
    glClearColor(0.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    draw_triangle();
    draw_ground();

    SDL_GL_SwapWindow(window.program());
}