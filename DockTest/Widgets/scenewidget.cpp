#include "Widgets/scenewidget.h"
#include "Scene/scene.h"
#include "Scene/gameobject.h"
#include "Components/component.h"
#include "Components/transform.h"
#include <QPainter>

SceneWidget::SceneWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
}

bool SceneWidget::GetScene(Scene *scenePointer)
{
    if(scenePointer == nullptr)
        return false;

    scene = scenePointer;
    return true;
}

QSize SceneWidget::sizeHint() const
{
    return QSize(256, 256);
}

QSize SceneWidget::minimumSizeHint() const
{
    return QSize(64, 64);
}

void SceneWidget::SetPainter(QColor fillColor, QColor strokeColor, StrokeStyle strokeStyle, int lineSize,
                             QBrush& brush, QPen& pen, QPainter& painter, bool active)
{
    // Brush/Pen configuration
    if(!active)
    {
        fillColor.setAlphaF(0.5f);
        strokeColor.setAlphaF(0.5f);
    }

    brush.setColor(fillColor);
    pen.setWidth(lineSize);
    pen.setColor(strokeColor);

    if(strokeStyle == StrokeStyle::CONTINUOS)
        pen.setStyle(Qt::PenStyle::SolidLine);
    else if(strokeStyle == StrokeStyle::DISCONTINUOS)
        pen.setStyle(Qt::PenStyle::DashLine);

    painter.setBrush(brush);
    painter.setPen(pen);
}

void SceneWidget::DrawCircle(int posX, int posY, int radius, QPainter &painter)
{
    int r = radius;
    int w = r * 2;
    int h = r * 2;

    QRect circleRect(posX, posY, w, h);
    painter.drawEllipse(circleRect);
}

void SceneWidget::DrawSquare(int posX, int posY, int size, QPainter &painter)
{
    int s = size;
    int w = s * 2;
    int h = s * 2;

    QRect squareRect(posX, posY, w, h);
    painter.drawRect(squareRect);
}

void SceneWidget::DrawTriangle(int posX, int posY, int size, QPainter &painter)
{
    int s = size;
    int w = s * 2;
    int h = s * 2;

    QRect triangleRect(posX, posY, w, h);

    QPolygon triangle;
    triangle << triangleRect.bottomLeft() << triangleRect.bottomRight() << QPoint(triangleRect.left() + s, triangleRect.top());
    painter.drawPolygon(triangle);
}

void SceneWidget::paintEvent(QPaintEvent *event)
{
    QColor blue = QColor::fromRgb(127,190,220);
    QColor white = QColor::fromRgb(255,255,255);
    QColor black = QColor::fromRgb(0,0,0);

    // Prepare the painter for this widget
    QPainter painter(this);

    QBrush brush;
    QPen pen;

    // BACKGROUND -----------------------------

    // Brush/Pen configuration
    brush.setColor(blue);
    brush.setStyle(Qt::BrushStyle::SolidPattern);
    pen.setStyle(Qt::PenStyle::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);

    // Paint Background
    painter.drawRect(rect());

    // ----------------------------------------------

    if(scene == nullptr)
        return;

    foreach(GameObject* go, scene->gameObjects)
    {
        // Omit drawing for invisible objects
        if(!go->visible)
            continue;

        Transform* transform = go->GetTransform();
        ShapeRenderer* shape = (ShapeRenderer*)go->GetComponent(Type::COMP_MESH_RENDERER);

        ShapeForm form = shape->form;

        SetPainter(shape->fillColor, shape->strokeColor, shape->style, shape->thickness, brush, pen, painter, go->active);

        switch (form)
        {

        case ShapeForm::SQUARE:
        {
            DrawSquare(transform->position.x(), transform->position.y(), shape->size, painter);
            break;
        }

        case ShapeForm::CIRCLE:
        {
            DrawCircle(transform->position.x(), transform->position.y(), shape->size, painter);
            break;
        }

        case ShapeForm::TRIANGLE:
        {
            DrawTriangle(transform->position.x(), transform->position.y(), shape->size, painter);
            break;
        }

        default:
        {
            break;
        }

        }
    }
}
