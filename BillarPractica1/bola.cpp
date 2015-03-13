#include "bola.h"

Bola::Bola():Objecte(10000)
{
    GLfloat s = 10;
    xorig = 0;
    yorig = 0;
    zorig = 0;
    points = new point4[10000];
    colors = new color4[10000];
    drawMode = GL_TRIANGLES;
    polygonMode= GL_FILL;
    colorTemp=point4(1.0,0.5,1.0,1.0);
    point4 v[4] = {
        vec4( 0.0, 0.0, 1.0, s ),
        vec4( 0.0, 0.942809, -0.333333, s ),
        vec4( -0.816497, -0.471405, -0.333333, s ),
        vec4( 0.816497, -0.471405, -0.333333, s )
    };
    divide_triangle( v[0], v[1], v[2],3);
    divide_triangle( v[3], v[2], v[1],3);
    divide_triangle( v[0], v[3], v[1],3);
    divide_triangle( v[0], v[2], v[3],3);

}

point4 Bola::calculVectorUnitari(const point4& p)
{
    point4 c;
       float d=0.0;
       for(int i=0; i<3; i++)
       {
          d+=p[i]*p[i];
       }
       d=sqrt(d);
       if(d > 0.0)
       {
          for(int i=0; i<3; i++)
          {
              c[i] = p[i]/d;
          }
       }
       c[3]=p[3];
       return c;
}

void Bola::triangle( const point4& a, const point4& b, const point4& c )
{
    points[Index] = c;
    colors[Index]=colorTemp;
    Index++;
    points[Index] = b;
    colors[Index]=colorTemp;
    Index++;
    points[Index] = a;
    colors[Index]=colorTemp;
    Index++;
}
point4 Bola::sum(const point4& a, const point4& b)
{
    point4 c;
    for(int i=0; i<3; i++)
    {
        c[i] = a[i] + b[i];
    }
    c[3]=a[3];
    return c;
}
void Bola::divide_triangle(const point4& a, const point4& b, const point4& c, int n)
{
     point4 v1, v2, v3;
     if(n>0)
     {
         v1 = calculVectorUnitari(sum(a,b));
         v2 = calculVectorUnitari(sum(a,c));
         v3 = calculVectorUnitari(sum(b,c));
         divide_triangle(a ,v1, v2, n-1);
         divide_triangle(c ,v2, v3, n-1);
         divide_triangle(b ,v3, v1, n-1);
         divide_triangle(v1 ,v3, v2, n-1);
      }
      triangle(a, b, c);
}
Bola::~Bola()
{

}

