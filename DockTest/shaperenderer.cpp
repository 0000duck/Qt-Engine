#include "shaperenderer.h"

#include<QJsonObject>


ShapeRenderer::ShapeRenderer(GameObject *myGO):Component(myGO, Type::COMP_MESH_RENDERER)
{
    fillColor = QColor(255,255,255);
    strokeColor= QColor(0,0,0);
    size = 1;
    thickness = 1;
}

void ShapeRenderer::Read(const QJsonObject &json)
{
    fillColor = QColor(json["fillColorR"].toInt(),
                       json["fillColorG"].toInt(),
                       json["fillColorB"].toInt());

    strokeColor= QColor(json["strokeColorR"].toInt(),
                        json["strokeColorG"].toInt(),
                        json["strokeColorB"].toInt());

    size =  json["size"].toInt();

    thickness =  json["thickness"].toInt();

    form = static_cast<ShapeForm>( json["shapeForm"].toInt());
    style = static_cast<StrokeStyle>( json["strokeStyle"].toInt());
}

void ShapeRenderer::Write(QJsonObject &json) const
{
    json["name"] = "Shape Renderer";

    json["fillColorR"] = fillColor.red();
    json["fillColorG"] = fillColor.green();
    json["fillColorB"] = fillColor.blue();

    json["strokeColorR"] = strokeColor.red();
    json["strokeColorG"] = strokeColor.green();
    json["strokeColorB"] = strokeColor.blue();

    json["size"] = size;

    json["thickness"] = thickness;

    json["shapeForm"] = form;
    json["strokeStyle"] = style;
}
