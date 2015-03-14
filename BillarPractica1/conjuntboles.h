#ifndef CONJUNTBOLES_H
#define CONJUNTBOLES_H

#include <bola.h>

class ConjuntBoles
{
public:
    ConjuntBoles();
    ~ConjuntBoles();
    void aplicaTG(mat4 m);

    void aplicaTGCentrat(mat4 m);
    void reset();

    void draw();
    void CapsaMinCont3DEscena();
    Bola* boles[15];

};

#endif // CONJUNTBOLES_H
