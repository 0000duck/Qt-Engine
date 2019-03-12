#ifndef SHAPERENDERER_H
#define SHAPERENDERER_H

#include "component.h"
#include <QColor>

class GameObject;

enum ShapeForm
{
    CIRCLE = 0,
    CUBE,
    TRIANGLE
};

enum StrokeStyle
{
    CONTINUOS = 0,
    DISCONTINUOS
};

class ShapeRenderer: public Component
{
public:
    ShapeRenderer(GameObject *myGO = nullptr);

    void Read(const QJsonObject &json) override;
    void Write(QJsonObject &json) const override;

public:
    ShapeForm form = ShapeForm::CIRCLE;
    StrokeStyle style = StrokeStyle::CONTINUOS;
    QColor fillColor;
    QColor strokeColor;
    int size;
    int thickness;
};

#endif // SHAPERENDERER_H
