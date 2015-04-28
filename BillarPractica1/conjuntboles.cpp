#include "conjuntboles.h"

ConjuntBoles::ConjuntBoles()
{
    float d=1.9, xOrg=-3.8, yOrg=22,zOrg=24;
    //fila 1
    Index = 0;

    for(int i=0;i<15;i++)
    {
        boles[i]=new Bola(1+i,xOrg,yOrg,zOrg);
    }
//    boles[0]=new Bola(1,xOrg,yOrg,zOrg);
//    boles[1]=new Bola(2,xOrg+d,yOrg,zOrg);
//    boles[2]=new Bola(3,xOrg+d*2,yOrg,zOrg);
//    boles[3]=new Bola(4,xOrg+d*3,yOrg,zOrg);
//    boles[4]=new Bola(5,xOrg+d*4,yOrg,zOrg);
//    //fila 2
//    boles[5]=new Bola(6,xOrg+d/2,yOrg,zOrg-d);
//    boles[6]=new Bola(7,xOrg+3*d/2,yOrg,zOrg-d);
//    boles[7]=new Bola(8,xOrg+5*d/2,yOrg,zOrg-d);
//    boles[8]=new Bola(9,xOrg+7*d/2,yOrg,zOrg-d);
//    //flia 3
//    boles[9]=new Bola(10,xOrg+d,yOrg,zOrg-d*2);
//    boles[10]=new Bola(11,xOrg+d*2,yOrg,zOrg-d*2);
//    boles[11]=new Bola(12,xOrg+d*3,yOrg,zOrg-d*2);
//    //flia 4
//    boles[12]=new Bola(13,xOrg+3*d/2,yOrg,zOrg-d*3);
//    boles[13]=new Bola(14,xOrg+5*d/2,yOrg,zOrg-d*3);
//    //fila 5
//    boles[14]=new Bola(15,xOrg+d*2,yOrg,zOrg-d*4);
}

ConjuntBoles::~ConjuntBoles()
{
    for(int i=0; i<15;i++)
    {
        delete boles[i];
    }
    delete &boles;
}

void ConjuntBoles::aplicaTG(mat4 m)
{
    for(int i=0; i<15;i++)
    {
        boles[i]->aplicaTG(m);
    }

}

void ConjuntBoles::aplicaTGCentrat(mat4 m)
{
    for(int i=0; i<15;i++)
    {
        boles[i]->aplicaTGCentrat(m);
    }


}

void ConjuntBoles::draw()
{
    for(int i=0; i<15;i++)
    {
        boles[i]->draw();
    }
}

void ConjuntBoles::CapsaMinCont3DEscena()
{
    for(int i=0; i<15;i++)
    {
        Index+=boles[i]->Index;
    }

}
