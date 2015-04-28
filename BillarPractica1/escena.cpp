#include "escena.h"

Escena::Escena()
{
    // Capsa minima contenidora provisional: S'ha de fer un recorregut dels objectes de l'escenes
    capsaMinima.pmin[0] = 0; capsaMinima.pmin[1] = 0; capsaMinima.pmin[2]=0;
    capsaMinima.a = 1; capsaMinima.h = 1; capsaMinima.p = 1;

    taulaBillar = NULL;
    pla=NULL;
    bola=NULL;
    boles15 = NULL;
    camera = new Camera();
}

Escena::~Escena()
{
    // Cal anar fent delete dels objectes que se'l hagi fet new
    delete this->taulaBillar;
    delete this->pla;
    delete this->bola;
    delete this->boles15;
    delete this->camera;
}
void Escena::iniCamera(bool camGeneral, int ampladaViewport, int alcadaViewport,QGLShaderProgram *program) {
    if (camGeneral){
        CapsaMinCont3DEscena();
        camera->ini(ampladaViewport,alcadaViewport,capsaMinima);
        camera->program=program;
        //camera->CalculWindow(capsaMinima);
        camera->CalculaMatriuModelView();
        camera->CalculaMatriuProjection();
        camera->piram.dant  = 0.1;
        camera->piram.dpost = 100.0;
    }
    //ini()
     //vs.obs = CalculObs (vs.vrp, piram.d, vs.angx, vs.angy);

}
void Escena::setAnglesCamera(bool camGeneral, float angX, float angY, float angZ){
    if (camGeneral){
       camera->vs.angx =angX;
       camera->vs.angy = angZ;
       camera->vs.angz = angZ;
       camera->CalculaMatriuModelView();
       camera->CalculaMatriuProjection();

    }

}
void Escena::setVRPCamera(bool camGeneral, point4 vrp){
    if (camGeneral){
        camera->vs.vrp= vrp;
        camera->CalculaMatriuModelView();
        camera->CalculaMatriuProjection();
    }
}

void Escena::setWindowCamera(bool camGeneral, bool retallat, Capsa2D window){
    if (camGeneral){
        //camera->CalculWindow(camera->wd);
        camera->setViewport(window.pmin[0],window.pmin[1],window.a,window.h);
        if(retallat)
            camera->CalculWindowAmbRetallat();
        camera->CalculaMatriuModelView();
        camera->CalculaMatriuProjection();

    }

}
void Escena::setDCamera(bool camGeneral, float d){
    if (camGeneral){

        camera->piram.d=d;
    }
}

void Escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<TaulaBillar*>(obj))
        this->taulaBillar = (TaulaBillar*)obj;
    if (dynamic_cast<Pla*>(obj))
        this->pla = (Pla*)obj;
    if (dynamic_cast<Bola*>(obj))
        this->bola = (Bola*)obj;

}

void Escena::addConjuntBoles(ConjuntBoles *obj)
{
    this->boles15 = (ConjuntBoles*)obj;
}


void Escena::CapsaMinCont3DEscena()
{
    // Metode a implementar
    point4 * total= new point4[bola->Index+boles15->Index+taulaBillar->Index];
    int index = 0;
    for(int i = 0; i<bola->Index;i++){
        total[index]=bola->points[i];
        index++;
    }
    for(int i = 0; i<taulaBillar->Index;i++){
        total[index]=taulaBillar->points[i];
        index++;
    }
    for(int j=0; j<15;j++){
        for(int i = 0; i<boles15->boles[j]->Index;i++){
            total[index]=boles15->boles[j]->points[i];
            index++;
        }
    }
    vec3    pmin, pmax;
    pmin=vec3(999999,999999,999999);
    pmax=vec3(-999999,-999999,-999999);

    for(int i =0;i<index;i++)
    {
        for(int j = 0;j<3;j++){
            if(total[i][j]<pmin[j])
                pmin[j]=total[i][j];
            if(total[i][j]>pmax[j])
                pmax[j]=total[i][j];
        }
    }

    capsaMinima.pmin=pmin;
    capsaMinima.a=pmax[0]-pmin[0];
    capsaMinima.h=pmax[1]-pmin[1];
    capsaMinima.p=pmax[2]-pmin[2];
}

void Escena::actualizarCamara()
{
    camera->CalculaMatriuModelView();
    camera->CalculaMatriuProjection();
}

void Escena::aplicaTG(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTG(m);
    if (pla!=NULL)
        pla->aplicaTG(m);
    if (bola!=NULL)
        bola->aplicaTG(m);
    if (boles15!=NULL)
        boles15->aplicaTG(m);

}

void Escena::aplicaTGCentrat(mat4 m) {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->aplicaTGCentrat(m);
    if (pla!=NULL)
        pla->aplicaTGCentrat(m);
    if (bola!=NULL)
        bola->aplicaTGCentrat(m);
    if (boles15!=NULL)
        boles15->aplicaTGCentrat(m);

}

void Escena::draw() {

    // Metode a modificar

    if (taulaBillar!=NULL)
        taulaBillar->draw();
    if (pla!=NULL)
        pla->draw();
    if (bola!=NULL)
        bola->draw();
    if (boles15!=NULL)
        boles15->draw();

}



