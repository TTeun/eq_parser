#include "renderable.h"
#include "glwidget.h"

Renderable::Renderable(GLWidget *_ui)
  :
  ui(_ui),
  coords( make_unique<QVector<QVector2D>>() ),
  colours( make_unique<QVector<QVector3D>>() ),
  indices( make_unique<QVector<size_t>>() )
{
  qDebug() << "Renderable constructor";
}

void Renderable::registerRenderable()
{
  ui->glGenVertexArrays(1, &vao);
  ui->glBindVertexArray(vao);

  ui->glGenBuffers(1, &coordsBO);
  ui->glBindBuffer(GL_ARRAY_BUFFER, coordsBO);
  ui->glEnableVertexAttribArray(0);
  ui->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

  ui->glGenBuffers(1, &colourBO);
  ui->glBindBuffer(GL_ARRAY_BUFFER, colourBO);
  ui->glEnableVertexAttribArray(1);
  ui->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

  ui->glGenBuffers(1, &indicesBO);
  ui->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBO);

  ui->glBindVertexArray(0);
}

void Renderable::updateRenderable()
{
  ui->glBindBuffer(GL_ARRAY_BUFFER, coordsBO);
  ui->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * coords->size(), coords->data(), GL_DYNAMIC_DRAW);

  ui->glBindBuffer(GL_ARRAY_BUFFER, colourBO);
  ui->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D) * colours->size(), colours->data(), GL_DYNAMIC_DRAW);

  ui->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBO);
  ui->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices->size(), indices->data(), GL_DYNAMIC_DRAW);
}

Renderable::~Renderable()
{
}


