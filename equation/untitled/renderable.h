#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLFunctions_4_1_Core>
#include <memory>

// A general class used for all objects that will be displayed on screen

class GLWidget;

using namespace std;

class Renderable {

  public:
    Renderable(GLWidget *_ui);
    ~Renderable();

    unique_ptr<QVector <QVector2D>> coords;
    unique_ptr<QVector <QVector3D>> colours;
    unique_ptr<QVector<size_t>> indices;

    GLuint vao, coordsBO, colourBO, indicesBO;

    unsigned int maxInt = ((unsigned int) -1);

    void registerRenderable(); // Register the VAO etc.
    void updateRenderable();   // Send data to GPU

  private:
    GLWidget *ui;
};

#endif // RENDERABLE_H
