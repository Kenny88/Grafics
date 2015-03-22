#include "taulabillar.h"

TaulaBillar::TaulaBillar(QString n) : Objecte(NumVerticesF)
{
    path=QString("://resources/Fabric_Green_L.jpg");
    drawMode=GL_TRIANGLES;
    polygonMode=GL_FILL;
    nom = n;
    Index = 0;
    tam = 1;

    xorig = 0;
    yorig = 0;
    zorig = 0;

    xRot = 0;
    yRot = 0;
    zRot = 0;

    readObj(n);

    Objecte::make();
    capsa = calculCapsa3D();

    // Codi adhoc per a la taula carregada de fitxer taula.obj. Cal modificar-lo per a que sigui general

    double escalaZ = 20*(2.0 / 8.63);
    mat4 m = Scale(escalaZ, escalaZ, escalaZ)*Translate(-2.55, +3.8, -0.74);
    aplicaTG(m);

    for(int i=0;i<Index;i++)
    {
        colors[i]=point4(0.0,0.2,0.0,1);
    }
    capsa = calculCapsa3D();
}

TaulaBillar::~TaulaBillar()
{

}

