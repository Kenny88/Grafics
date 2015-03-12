#ifndef PLA_H
#define PLA_H

#include <objecte.h>

class Pla : public Objecte
{   
public:
    Pla();
    Pla(GLfloat x0, GLfloat y0, GLfloat z0);
    void triangles();
    ~Pla();
private:
    static const int NumVerticesF = 4;
    float sizeX;
    float sizeZ;
};

#endif // PLA_H