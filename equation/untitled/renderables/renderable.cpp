#include "renderable.h"
#include "glwidget.h"

Renderable::Renderable(GLWidget *_ui)
  :
  coords( make_unique<QVector<QVector2D>>() ),
  colours( make_unique<QVector<QVector3D>>() ),
  ui(_ui)
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

  ui->glBindVertexArray(0);
}

void Renderable::updateRenderable()
{
  assert(coords->size() > 0);

  ui->glBindBuffer(GL_ARRAY_BUFFER, coordsBO);
  ui->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * coords->size(), coords->data(), GL_STATIC_DRAW);

  ui->glBindBuffer(GL_ARRAY_BUFFER, colourBO);
  ui->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D) * colours->size(), colours->data(), GL_DYNAMIC_DRAW);
}

void Renderable::clear()
{
  coords->resize(0);
  colours->resize(0);
}

Renderable::~Renderable()
{
}


