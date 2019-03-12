#include "shaperenderer.h"

ShapeRenderer::ShapeRenderer(GameObject *myGO):Component(myGO, Type::COMP_MESH_RENDERER)
{
    fillColor = QColor(1,1,1);
    strokeColor= QColor(1,1,1);
    size = 1;
    tickness = 1;
}

void ShapeRenderer::Read(const QJsonObject &json)
{

}

void ShapeRenderer::Write(QJsonObject &json) const
{

}
