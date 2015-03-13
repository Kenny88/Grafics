#include "escena.h"

Escena::Escena()
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;

    taulaBillar = NULL;
    pla=NULL;
    bola=NULL;
}

Escena::~Escena()
{
    // Cal anar fent delete dels objectes que se'l hagi fet new
   delete this->taulaBillar;
   delete this->pla;
   delete this->bola;
}

void Escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<TaulaBillar*>(obj))
        this->taulaBillar = (TaulaBillar*)obj;
    if (dynamic_cast<Pla*>(obj))
        this->pla = (Pla*)obj;
    if (dynamic_cast<Bola*>(obj))
        this->bola = (Bola*)obj;
}


void Escena::CapsaMinCont3DEscena()
{
    // Metode a implementar
}

void Escena::aplicaTG(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTG(m);
    if (pla!=NULL)
        pla->aplicaTG(m);
    if (bola!=NULL)
        bola->aplicaTG(m);

}

void Escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTGCentrat(m);
    if (pla!=NULL)
        pla->aplicaTGCentrat(m);
    if (bola!=NULL)
        bola->aplicaTGCentrat(m);

}

void Escena::draw() {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->draw();
    if (pla!=NULL)
        pla->draw();
    if (bola!=NULL)
        bola->draw();

}



