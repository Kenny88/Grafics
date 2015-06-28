#include "bola.h"
#include <qmath.h>
Bola::Bola():Objecte(10000) //inclous el numero de vertices
{
    num=0;
    GLfloat s = 1; //Tamany bola, com mes gran el valor, mes petita es
    int n = 4; //numero de divisions de la bola, com mes gran mes rodo, cal aumentar el numero de vertices si augmentes aixo
    xorig = 0;
    yorig = 0.4;
    zorig = 0;
    points = new point4[10000];
    colors = new color4[10000];
    drawMode = GL_TRIANGLES;
    polygonMode= GL_FILL;
    material = new Material();
    material->intensity.ambient = vec3(0.24725,	0.1995,	0.0745);
    material->intensity.diffuse = vec3(0.75164,	0.60648,	0.22648);
    material->intensity.specular = vec3(0.628281,	0.555802,	0.366065);
    material->intensity.shininess = 0.4*128;
    colorTemp=point4(1.0,1.0,1.0,1.0);
    point4 v[4] = {
        vec4( 0.0, 0.0, 1.0, s ),
        vec4( 0.0, 0.942809, -0.333333, s ),
        vec4( -0.816497, -0.471405, -0.333333, s ),
        vec4( 0.816497, -0.471405, -0.333333, s )
    };
    divide_triangle( v[0], v[1], v[2],n);
    divide_triangle( v[3], v[2], v[1],n);
    divide_triangle( v[0], v[3], v[1],n);
    divide_triangle( v[0], v[2], v[3],n);
//
    make();
    aplicaTG(Translate(xorig,yorig,zorig));
//    double escalaZ = 1.0 / 20.0;
//    mat4 m = Scale(escalaZ, escalaZ, escalaZ);
//    aplicaTG(m);

}

Bola::Bola(int color, GLfloat xOrg, GLfloat yOrg, GLfloat zOrg):Objecte(10000) //inclous el numero de vertices
{
    colorsB[0]=point4(1.0,1.0,1.0,1.0);colorsB[1]=point4(1.0,0.0,0.0,1.0);colorsB[2]=point4(1.0,1.0,0.0,1.0)
            ;colorsB[3]=point4(0.0,0.0,1.0,1.0);colorsB[4]=point4(0.0,1.0,1.0,1.0);colorsB[5]=point4(0.0,1.0,0.0,1.0)
            ;colorsB[6]=point4(0.5,0.5,0.5,1.0);colorsB[7]=point4(1.0,0.5,1.0,1.0);colorsB[8]=point4(0.5,0.0,1.0,1.0)
            ;colorsB[9]=point4(0.0,5.0,1.0,1.0);colorsB[10]=point4(0.0,0.0,0.5,1.0);colorsB[11]=point4(0.5,0.5,0.0,1.0)
            ;colorsB[12]=point4(0.0,0.5,0.5,1.0);colorsB[13]=point4(0.5,0.0,0.5,1.0);colorsB[14]=point4(0.25,0.25,0.4,1.0)
            ;colorsB[15]=point4(0.7,0.7,0.3,1.0);
    GLfloat s = 1; //Tamany bola, com mes gran el valor, mes petita es
//    path=QString("://resources/Bola")+QString::number(color)+QString(".jpg");
    path=QString("://resources/Bola")+QString::number(color)+QString(".jpg");
    int n = 4; //numero de divisions de la bola, com mes gran mes rodo, cal aumentar el numero de vertices si augmentes aixo
    num=color;
    xorig = xOrg;
    yorig = yOrg;
    zorig = zOrg;
    points = new point4[10000];
    colors = new color4[10000];
    drawMode = GL_TRIANGLES;
    polygonMode= GL_FILL;
    colorTemp=colorsB[0];
    material = new Material();
    material->intensity.ambient = vec3(0.24725,	0.1995,	0.0745);
    material->intensity.diffuse = vec3(0.75164,	0.60648,	0.22648);
    material->intensity.specular = vec3(0.628281,	0.555802,	0.366065);
    material->intensity.shininess = 0.4*128;
    point4 v[4] = {
        vec4( 0.0, 0.0, 1.0, s ),
        vec4( 0.0, 0.942809, -0.333333, s ),
        vec4( -0.816497, -0.471405, -0.333333, s ),
        vec4( 0.816497, -0.471405, -0.333333, s )
    };
    divide_triangle( v[0], v[1], v[2],n);
    divide_triangle( v[3], v[2], v[1],n);
    divide_triangle( v[0], v[3], v[1],n);
    divide_triangle( v[0], v[2], v[3],n);
    make();
    aplicaTG(Translate(xOrg,yOrg,zOrg));
//    make();

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

    vec3 normal = normalize( cross(b - a, c - b) );
    points[Index] = c;
    colors[Index]=colorTemp;
    setTexture(c);
    normals[Index]=normal;
    Index++;
    points[Index] = b;
    colors[Index]=colorTemp;
    setTexture(b);
    normals[Index]=normal;
    Index++;
    points[Index] = a;
    colors[Index]=colorTemp;
    setTexture(a);
    normals[Index]=normal;
    Index++;
}
void Bola::setTexture(const point4& a)
{
    GLfloat u = 0.5 + qAtan2(a[2], a[0])/ (2*M_PI);
    GLfloat v = 0.5 - qAsin(a[1])/M_PI;
    vertexsTextura[Index]=vec2(u,v);

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
//         v1 = normalize(a+b);
//         v2 = normalize(a+c);
//         v3 = normalize(b+c);
         divide_triangle(a ,v1, v2, n-1);
         divide_triangle(c ,v2, v3, n-1);
         divide_triangle(b ,v3, v1, n-1);
         divide_triangle(v1 ,v3, v2, n-1);
      }
      vertexs.push_back(c);
      vertexs.push_back(b);
      vertexs.push_back(a);
      Cara cara = Cara((vertexs.size()-3),(vertexs.size()-2),(vertexs.size()-1));
      cara.color = colorTemp;
      cares.push_back(cara);
//      triangle(a, b, c);
}

float Bola::getRadi()
{
    float max=-99999999,min=99999999;
    for(int i=0;i<Index;i++){
        if(points[i][0]<min)
            min=points[i][0];
        if(points[i][0]>max)
            max=points[i][0];
    }
    return (max-min)/2;
}

Bola::~Bola()
{

}

