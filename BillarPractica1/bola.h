#ifndef BOLA_H
#define BOLA_H

#include <objecte.h>

class Bola : public Objecte
{
public:
    Bola();
    void triangle( const point4& a, const point4& b, const point4& c );
    ~Bola();
private:
    float radi;
    color4 colorTemp;
    point4 calculVectorUnitari(const point4& p);
    point4 sum(const point4& a, const point4& b);
    void divide_triangle(const point4& a, const point4& b, const point4& c, int n);
};

#endif // BOLA_H
