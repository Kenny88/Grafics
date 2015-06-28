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
    llum=new Llum();
    camera = new Camera();
    camera2 = new Camera();
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
void Escena::setAmbientToGPU(QGLShaderProgram *program){
    llum->toGPU(program);
}

void Escena::iniCamera(bool camGeneral, int ampladaViewport, int alcadaViewport,QGLShaderProgram *program) {
    CapsaMinCont3DEscena();
    camera->ini(ampladaViewport,alcadaViewport,capsaMinima);
    camera->program=program;
    //camera->CalculWindow(capsaMinima);
    camera->CalculaMatriuModelView();
    camera->CalculaMatriuProjection();
    camera->piram.dant  = 0.1;
    camera->piram.dpost = 100.0;
    //ini()
     //vs.obs = CalculObs (vs.vrp, piram.d, vs.angx, vs.angy);

}
void Escena::iniCameraPrespectiva(bool camGeneralBool, int ampladaViewport, int alcadaViewport, QGLShaderProgram *p){
    CapsaMinCont3DEscena();
    camera2->program=p;
    actualitzarBola();
    camera2->ini(ampladaViewport, alcadaViewport, capsaMinima);  // vs.vup
    Capsa2D capsa;
    capsa.a = capsaMinima.a;
    capsa.h = capsaMinima.h;
    capsa.pmin.x = capsaMinima.pmin.x;
    capsa.pmin.y = capsaMinima.pmin.y;
    camera2->capsaMinima=bola->calculCapsa3D();
    camera2->piram.proj  = PERSPECTIVA;
    camera2->piram.dant  = 1;
    camera2->piram.dpost = 100.0;// piram.d
    setDCamera(true, 1.2);
    setAnglesCamera(true, -195, 0, 0);              // vs.angx, vs.angy, vs.angz
    setVRPCamera(true, posBola);             // vs.vrp
    camera2->CalculWindow(bola->calculCapsa3D());
    setWindowCamera(true, true, capsa);

    camera2->vs.vup = camera2->CalculVup(camera2->vs.angx,camera2->vs.angy,camera2->vs.angz);
    camera2->vs.obs = camera2->CalculObs(posBola, camera2->piram.d, camera2->vs.angx, camera2->vs.angy);
        // wd

    actualizarCamara();
    //actualitzaCameraFirstPerson(true);

}

void Escena::setAnglesCamera(bool camGeneral, float angX, float angY, float angZ){
    if (camGeneral){
       camera2->vs.angx =angX;
       camera2->vs.angy = angY;
       camera2->vs.angz = angZ;


    }

}
void Escena::setVRPCamera(bool camGeneral, point4 vrp){
    if (camGeneral){
        camera2->vs.vrp= vrp;

    }
}

void Escena::setWindowCamera(bool camGeneral, bool retallat, Capsa2D window){
    if (camGeneral){
        //camera->CalculWindow(camera->wd);
        //camera2->wd=window;
        if(retallat){
            camera2->CalculAngleOberturaHoritzontal();
            camera2->CalculAngleOberturaVertical();
            camera2->CalculWindowAmbRetallat();
        }


    }

}
void Escena::setDCamera(bool camGeneral, float d){
    if (camGeneral){

        camera2->piram.d=d;
    }
}

void Escena::addObjecte(Objecte *obj) {
    if (dynamic_cast<TaulaBillar*>(obj))
        this->taulaBillar = (TaulaBillar*)obj;
    if (dynamic_cast<Pla*>(obj))
        this->pla = (Pla*)obj;
    if (dynamic_cast<Bola*>(obj)){

        this->bola = (Bola*)obj;
        actualitzarBola();
    }

}
void Escena::actualitzarBola(){
    posBola.x=this->bola->calculCapsa3D().pmin[0]+this->bola->calculCapsa3D().a/2;
    posBola.y=this->bola->calculCapsa3D().pmin[1]+this->bola->calculCapsa3D().h/2;
    posBola.z=this->bola->calculCapsa3D().pmin[2]+this->bola->calculCapsa3D().p/2;
    posBola.w=1;
}

void Escena::addConjuntBoles(ConjuntBoles *obj)
{
    this->boles15 = (ConjuntBoles*)obj;
}


void Escena::CapsaMinCont3DEscena()
{
    // Metode a implementar
    point4 * total= new point4[bola->Index+boles15->Index+pla->Index];
    int index = 0;
    for(int i = 0; i<bola->Index;i++){
        total[index]=bola->points[i];
        index++;
    }
    for(int i = 0; i<pla->Index;i++){
        total[index]=pla->points[i];
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
//    camera2->CalculaMatriuModelView();
//    camera2->CalculaMatriuProjection();
    actualitzarBola();
    camera2->vs.vrp=posBola;
    camera2->CalculAngleOberturaHoritzontal();
    camera2->CalculAngleOberturaVertical();
    camera2->CalculaMatriuModelView();
    camera2->CalculWindow(bola->capsa);
    camera2->CalculWindowAmbRetallat();
    camera2->CalculaMatriuProjection();
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



