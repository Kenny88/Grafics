#include "pla.h"

Pla::Pla() : Objecte(12)
{
    path=QString("://resources/Fabric_Green_L.jpg");
    sizeX = 20.0f;
    sizeZ = 20.0f;
    xorig = 0;
    yorig = -6.0;
    zorig = 0;
    drawMode = GL_TRIANGLES;
    polygonMode= GL_FILL;
    triangles();
}


Pla::Pla(GLfloat x0, GLfloat y0, GLfloat z0) : Objecte(NumVerticesF)
{
    path=QString("://resources/Fabric_Green_L.jpg");
    sizeX = x0/2;
    sizeZ = z0/2;
    yorig = y0;
    xorig = 0;
    zorig = 0;
    drawMode = GL_TRIANGLES;
    polygonMode= GL_FILL;
    triangles();
}
void Pla::quad( int a, int b, int c, int d )
{
    color4 tempcolor=point4(0.5,0.5,0.5,1.0);
    colors[Index] = tempcolor; points[Index] = vertexs[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    colors[Index] = tempcolor; points[Index] = vertexs[b];
    vertexsTextura[Index] = vec2(1.0, 0.0); Index++;
    colors[Index] = tempcolor; points[Index] = vertexs[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    colors[Index] = tempcolor; points[Index] = vertexs[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    colors[Index] = tempcolor; points[Index] = vertexs[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    colors[Index] = tempcolor; points[Index] = vertexs[d];
    vertexsTextura[Index] = vec2(0.0, 1.0); Index++;
}

void Pla::triangles()
{
    Index=0;
    vertexs.push_back(point4( -sizeX, yorig, -sizeZ, 1.0 ));
    vertexs.push_back(point4( -sizeX, yorig, sizeZ, 1.0 ));
    vertexs.push_back(point4(  sizeX, yorig, sizeZ, 1.0 ));
    vertexs.push_back(point4(  sizeX, yorig, -sizeZ, 1.0 ));
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 0, 1 );
//    color4 tempcolor=point4(0.5,0.5,0.5,1.0);
//    Cara c = Cara(0,1,2);
//    c.color = tempcolor;
//    cares.push_back(c);
//    c = Cara(0,2,3);
//    c.color = tempcolor;
//    cares.push_back(c);
//    c = Cara(2,1,0);
//    c.color = tempcolor;
//    cares.push_back(c);
//    c = Cara(3,2,0);
//    c.color = tempcolor;
//    cares.push_back(c);
//    Objecte::make();
//    capsa = calculCapsa3D();
}

Pla::~Pla()
{

}

