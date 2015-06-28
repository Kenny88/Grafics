#ifndef LLUM_H
#define LLUM_H

#include <Common.h>

#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <QGLFunctions>

typedef Common::vec4  color4;
typedef Common::vec4  point4;

typedef struct{
    float constant;
    float linear;
    float quadratic;
} Attenuation;

typedef struct{
    color4 ambient;
    color4 diffuse;
    color4 specular;
} Intensity;



class Llum: protected QGLFunctions
{
public:
    Llum();
    ~Llum();
    void toGPU(QGLShaderProgram *program);
    Llum(vec4 posicio,vec3 dif,GLfloat coe);
private:
    Intensity intensity1;
    point4 posicioLlum;
    vec3 difusa;
    GLfloat coefA;
};

#endif // LLUM_H
