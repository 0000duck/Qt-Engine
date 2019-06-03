#ifndef DEFERREDRENDER_H
#define DEFERREDRENDER_H

#include "render.h"
#include <QOpenGLTexture>
#include <QVector3D>
#include <qlist.h>
class DeferredRender : public Renderer
{
public:
    DeferredRender();
    ~DeferredRender() override;
    void InitProgram();
    void Resize(int width,int height);
    void DeleteBuffers();
    void Render(Camera* camera, Scene* scene) override;
    void RenderQuad();

public:

    int renderView = 0;
    int postProcessingEffect = 0;
    float lightIntensity = 1.0f;
    float blurIntensity = 2.0f;
    float glowIntensity = 0.8f;

    unsigned int gBuffer;

    unsigned int gPosition;
    unsigned int gNormal;
    unsigned int gColor;
    unsigned int gDepth;
    unsigned int gBlurVertical;
    unsigned int gBlurHorizontal;  
    unsigned int gDeferred;
    unsigned int gGlow;
    unsigned int gBrightness;
    unsigned int gBrightnessPlusBlurV;
    unsigned int gBrightnessPlusBlurH;
    unsigned int gBrightnessPlusGlow;

    unsigned int gFBOBrightnessPlusBlurV;
    unsigned int gFBOBrightnessPlusBlurH;
    unsigned int gFBOBrightnessPlusGlow;
    unsigned int gFBOBrightness;
    unsigned int gFBOBlurV;
    unsigned int gFBOBlurH;
    unsigned int gFBOGlow;
    unsigned int gFBODeferred;

    unsigned int attachments[3];

    unsigned int quadVAO = 0;
    unsigned int quadVBO;


private:
    QList<QVector3D> lightPos;
    QList<QVector3D> lightColor;

    int _width =0;
    int _height = 0;
};

#endif // DEFERREDRENDER_H
