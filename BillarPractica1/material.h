#ifndef MATERIAL_H
#define MATERIAL_H
#include <stdio.h>
#include <Common.h>
#include <QGLShaderProgram>
#include <QGLFunctions>

typedef struct{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
} IntensityM;

class Material: protected QGLFunctions
{
public:
    Material();
    ~Material();
    IntensityM intensity;

    void toGPU(QGLShaderProgram *program);
};

#endif // MATERIAL_H
