#ifndef MATERIAL_H
#define MATERIAL_H

class QOpenGLTexture;
#include <QColor>
class Material
{
public:
    Material();
public:
    QOpenGLTexture *texture = nullptr;
    std::string textureName = "-";
    QColor fillColor;

};

#endif // MATERIAL_H
