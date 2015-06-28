#include "llum.h"

Llum::Llum()
{
    posicioLlum=vec4(0,13,10,1);
    coefA=1.0;//coeficiente de atenuacion
    intensity1.ambient=vec4(1.0, 1.0, 1.0, 1.0);
    intensity1.diffuse=vec4(1.0, 1.0, 1.0, 1.0);
    intensity1.specular=vec4(0.5, 1.0, 1.0, 1.0);
    //posicioLlum=posicio;

    //difusa=dif;
    //coefA=coe;
}
Llum::Llum(vec4 posicio,vec3 dif,GLfloat coe)
{

    posicioLlum=posicio;
    difusa=dif;
    coefA=coe;
}

Llum::~Llum()
{

}

void Llum::toGPU(QGLShaderProgram *program){

    initializeGLFunctions();
    struct {
        GLuint posicio;
        GLuint a;
        GLuint ambient;
        GLuint diffuse;
        GLuint specular;

    } gl_IdLlum;
    // 2. obtencio dels identificadors de la GPU
    gl_IdLlum.posicio = program->uniformLocation("light.LightPosition");
    gl_IdLlum.a = program->uniformLocation("light.coef_a");
    gl_IdLlum.ambient = program->uniformLocation("light.ambient");
    gl_IdLlum.diffuse = program->uniformLocation("light.diffuse");
    gl_IdLlum.specular = program->uniformLocation("light.specular");

    // 3. Bind de les zones de memoria que corresponen
    glUniform4fv(gl_IdLlum.posicio, 1, posicioLlum); //posicioLlum és un vec4
    glUniform1f(gl_IdLlum.a, coefA); // coefA és un Glfloat
    glUniform4fv(gl_IdLlum.ambient, 1, intensity1.ambient); //posicioLlum és un vec4
    glUniform4fv(gl_IdLlum.diffuse, 1, intensity1.diffuse ); // difusa és un vec4
    glUniform4fv(gl_IdLlum.specular,1, intensity1.specular); // coefA és un vec4


}
