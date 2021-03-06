#ifndef BOLA_H
#define BOLA_H

#include <objecte.h>

class Bola : public Objecte
{
public:
    Bola();
    Bola(int color, GLfloat xOrg, GLfloat yOrg, GLfloat zOrg);
    void triangle( const point4& a, const point4& b, const point4& c );
    ~Bola();
    float getRadi();
    void setTexture(const point4 &a);
private:

    float radi;
    color4 colorTemp;
    color4 colorsB[16];
    point4 calculVectorUnitari(const point4& p);
    point4 sum(const point4& a, const point4& b);
    void divide_triangle(const point4& a, const point4& b, const point4& c, int n);
};

#endif // BOLA_H
