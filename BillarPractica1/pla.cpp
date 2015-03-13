#include "pla.h"

Pla::Pla() : Objecte(6)
{
    sizeX = 1.0f;
    sizeZ = 1.0f;
    xorig = 0;
    yorig = -0.5;
    zorig = 0;
    drawMode = GL_TRIANGLES;
    polygonMode= GL_FILL;
    triangles();
}


Pla::Pla(GLfloat x0, GLfloat y0, GLfloat z0) : Objecte(NumVerticesF)
{
    sizeX = x0/2;
    sizeZ = z0/2;
    yorig = y0;
    xorig = 0;
    zorig = 0;
    drawMode = GL_TRIANGLES;
    polygonMode= GL_FILL;
    triangles();
}

void Pla::triangles()
{
    vertexs.push_back(point4( -sizeX, yorig, -sizeZ, 1.0 ));
    vertexs.push_back(point4( -sizeX, yorig, sizeZ, 1.0 ));
    vertexs.push_back(point4(  sizeX, yorig, sizeZ, 1.0 ));
    vertexs.push_back(point4(  sizeX, yorig, -sizeZ, 1.0 ));

    Cara c = Cara(0,1,2);
    c.color = point4(0.0,0.5,1.0,1.0);
    cares.push_back(c);
    c = Cara(0,2,3);
    c.color = point4(0.0,0.5,1.0,1.0);
    cares.push_back(c);
    c = Cara(2,1,0);
    c.color = point4(0.0,0.5,1.0,1.0);
    cares.push_back(c);
    c = Cara(3,2,0);
    c.color = point4(0.0,0.5,1.0,1.0);
    cares.push_back(c);
    Objecte::make();
    capsa = calculCapsa3D();
}

Pla::~Pla()
{

}

