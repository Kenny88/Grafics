#include "material.h"

Material::Material()
{

}

void Material::toGPU(QGLShaderProgram *program)
{
    initializeGLFunctions();
    struct{
        GLuint ambient;
        GLuint diffuse;
        GLuint specular;
        GLuint shininess;
    } gl_Material;


    // obtenemos indices
    gl_Material.ambient     = program->uniformLocation("material.Ambient");
    gl_Material.diffuse     = program->uniformLocation("material.Diffuse");
    gl_Material.specular    = program->uniformLocation("material.Specular");
    gl_Material.shininess  = program->uniformLocation("material.Shininess");

    // cargamos variables del shader
    glUniform4fv(gl_Material.ambient, 1,  this->intensity.ambient);
    glUniform4fv(gl_Material.diffuse, 1,  this->intensity.diffuse);
    glUniform4fv(gl_Material.specular, 1, this->intensity.specular);
    glUniform1f (gl_Material.shininess,  this->intensity.shininess);
}

Material::~Material()
{

}

