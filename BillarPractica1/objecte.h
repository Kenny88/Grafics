#ifndef OBJECTE_H
#define OBJECTE_H

#include <QObject>

#include <vector>
#include <QGLFunctions>
#include <Common.h>
#include <cara.h>
#include <material.h>

#include <QGLShaderProgram>
#include <QOpenGLTexture>

typedef Common::vec4  color4;
typedef Common::vec4  point4;


using namespace std;

class Objecte : public QObject, protected QGLFunctions
{
    Q_OBJECT
protected:
    int num;
    QString nom; // nom del fitxer on esta el cotxe
    vector<Cara> cares; // cares de l'objecte
    vector<point4> vertexs; // vertexs de l'objecte sense repetits

    // Sistema de coordenades d'un objecte: punt origen i eixos de rotació
    GLfloat xorig, yorig, zorig;
    float xRot;
    float yRot;
    float zRot;

    GLfloat tam; // Escala de l'objecte aplicada al fitxer d'entrada


    // Programa de shaders de la GPU
    QGLShaderProgram *program;
    GLuint buffer; // Buffer de comunicacio amb la GPU

    // Estructures de vertexs i colors per passar a la GPU
    int     numPoints;

    color4 *colors;
    vec2 *vertexsTextura;
     // index de control del numero de vertexs a posar a la GPU
    GLint drawMode;
    GLint polygonMode;
    QString path;
    QOpenGLTexture *texture;
    Material *material;

public:

  // Capsa mínima contenidora de l'objecte
    Capsa3D capsa;
    point4 *points;
    point4 *normals;
    int Index;
    //explicit Objecte(QObject *parent = 0);
    Objecte(const int npoints, QObject *parent = 0);
    Objecte(const int npoints, QString n);

    ~Objecte();

    // llegeix un model en format OBJ
    virtual void readObj(QString filename);

    // make(): omple l'estructura de points i colors de l'objecte, inicialitza NumVertices
    // Si l'objecte es construeix procedimentalment es sobrecarrega el make
    virtual void make();

    // Pas generic de vertexs i colors a la GPU
    void toGPU(QGLShaderProgram *p);
    // Pintat amb la GPU
    virtual void draw();

    // Calcula la capsa 3D contenidora de l'objecte
    Capsa3D calculCapsa3D();

    // Aplica una TG qualsevol a un objecte
    void aplicaTG(mat4 m);
    void aplicaTGPoints(mat4 m);
    // Aplica una TG centrada en el punt central de la capsa de l'objecte a un objecte
    void aplicaTGCentrat(mat4 m);

    void initTextura(int i);
    void setTexture(point4 a);
private:
    void construeix_cara ( char **words, int nwords, Objecte*objActual, int vindexUlt);

};



#endif // OBJECTE_H
