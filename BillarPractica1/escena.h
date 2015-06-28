#ifndef ESCENA_H
#define ESCENA_H

#include <cmath>
#include <iostream>
#include <stdlib.h>

#include <list>
#include <vector>
#include <string>
#include <stdio.h>


#include <Common.h>
#include <objecte.h>

#include <taulabillar.h>
#include <pla.h>
#include <bola.h>
#include <conjuntboles.h>
#include <camera.h>
#include <llum.h>

using namespace std;

class Escena
{
public:
    Escena();
    ~Escena();

    void addObjecte(Objecte *obj);
    void addConjuntBoles(ConjuntBoles *obj);
    void aplicaTG(mat4 m);

    void iniCamera(bool camGeneral, int ampladaVewport, int alcadaViewport,QGLShaderProgram *program);
    void setAnglesCamera(bool camGeneral, float angX, float angY, float angZ);
    void setVRPCamera(bool camGeneral, point4 vrp);
    void setDCamera(bool camGeneral, float d);
    void setWindowCamera(bool camGeneral, bool retallat, Capsa2D window);
    void setAmbientToGPU(QGLShaderProgram *program);

    void aplicaTGCentrat(mat4 m);
    void reset();

    void draw();
    void CapsaMinCont3DEscena();

    void actualizarCamara();

    // Capsa contenedora de l'escena
    Capsa3D capsaMinima;

    // Objectes de l'escena: a modificar. Ara nomes té un objecte: la taula de billar.
    // Cal afegir la bola blanca o el pla base per testejar o les 15 boles
    TaulaBillar *taulaBillar;
    Pla *pla;
    Bola *bola;
    ConjuntBoles *boles15;
    Camera *camera;
    Camera *camera2;
    Llum *llum;
    vec4 posBola;
    void iniCameraPrespectiva(bool camGeneralBool, int ampladaViewport, int alcadaViewport, QGLShaderProgram *p);
    void actualitzarBola();
};

#endif // ESCENA_H
