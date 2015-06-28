#include "pla.h"

Pla::Pla() : Objecte(12)
{
    path=QString("://resources/Fabric_Green_L.jpg");
    sizeX = 20.0f;
    sizeZ = 20.0f;
    xorig = 0;
    yorig = 15.0;
    zorig = 0;
    drawMode = GL_TRIANGLES;
    polygonMode= GL_FILL;
    material = new Material();
    material->intensity.ambient = vec3(0.0f,0.15f,0.0f);
    material->intensity.diffuse = vec3(0.7f,0.9f,0.4f);
    material->intensity.specular = vec3(0.04f,0.7f,0.04f);
    material->intensity.shininess = 0.072158125f*64;
    triangles();
}


Pla::Pla(GLfloat x0, GLfloat y0, GLfloat z0) : Objecte(NumVerticesF)
{
    path=QString("://resources/Fabric_Green_L.jpg");
    sizeX = x0/2;
    sizeZ = z0/2;
    yorig = 0.0;
    xorig = 0;
    zorig = 0;
    drawMode = GL_TRIANGLES;
    polygonMode= GL_FILL;
    material = new Material();
    material->intensity.ambient = vec3(0.135,0.2225,0.1575);
    material->intensity.diffuse = vec3(0.54,0.89,0.63);
    material->intensity.specular = vec3(0.316228,0.316228,0.316228);
    material->intensity.shininess = 0.1*128;
    triangles();
}
void Pla::quad( int a, int b, int c, int d )
{
    color4 tempcolor=point4(0.5,0.5,0.5,1.0);
    vec4 normal2=normalize(cross(vertexs[c] - vertexs[a], vertexs[d] - vertexs[c]));
    normals[Index] = normalize( cross(vertexs[b] - vertexs[a], vertexs[c] - vertexs[b]) ); points[Index] = vertexs[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    normals[Index] = normalize( cross(vertexs[b] - vertexs[a], vertexs[c] - vertexs[b])  ); points[Index] = vertexs[b];
    vertexsTextura[Index] = vec2(1.0, 0.0); Index++;
    normals[Index] = normalize( cross(vertexs[b] - vertexs[a], vertexs[c] - vertexs[b])); points[Index] = vertexs[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    normals[Index] =normal2; points[Index] = vertexs[a];
    vertexsTextura[Index] = vec2(0.0, 0.0); Index++;
    normals[Index] = normal2; points[Index] = vertexs[c];
    vertexsTextura[Index] = vec2(1.0, 1.0); Index++;
    normals[Index] = normal2; points[Index] = vertexs[d];
    vertexsTextura[Index] = vec2(0.0, 1.0); Index++;
}

void Pla::triangles()
{
    Index=0;
    vertexs.push_back(point4( sizeX, yorig, -sizeZ, 1.0 ));
    vertexs.push_back(point4( sizeX, yorig, sizeZ, 1.0 ));
    vertexs.push_back(point4( -sizeX, yorig, sizeZ, 1.0 ));
    vertexs.push_back(point4( -sizeX, yorig, -sizeZ, 1.0 ));
    quad( 3,0,1,2 );
    //quad( 3, 2, 1, 0 );
//    color4 tempcolor=point4(0.5,0.5,0.5,1.0);
//    Cara c = Cara(0,1,2);
//    c.color = tempcolor;
//    cares.push_back(c);
//    c = Cara(0,2,3);
//    c.color = tempcolor;
//    cares.push_back(c);
//    c = Cara(2,1,0);
//    c.color = tempcolor;
//    cares.push_back(c);
//    c = Cara(3,2,0);
//    c.color = tempcolor;
//    cares.push_back(c);
//    Objecte::make();
//    capsa = calculCapsa3D();
}
point4 Pla::normal(point4 point)
{
    float size = sqrt(pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2));
    return vec4(point.x/size,point.y/size,point.z/size,1.0);
}

Pla::~Pla()
{

}

