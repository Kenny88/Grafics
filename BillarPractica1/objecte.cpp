#include <objecte.h>
#include <readfile.h>
#include <qmath.h>

Objecte::Objecte(int npoints, QObject *parent) : numPoints(npoints) ,
    QObject(parent)
{
    initializeGLFunctions();
    points = new point4[npoints];
    //colors = new color4[npoints];
    normals = new vec4[npoints];
    vertexsTextura = new vec2[npoints];

}

Objecte::Objecte(int npoints, QString n) : numPoints(npoints)
{
    initializeGLFunctions();
    points = new point4[npoints];
//    colors = new color4[npoints];
    normals = new vec4[npoints];
    vertexsTextura = new vec2[npoints];
    std::cout<<"Estic en el constructor parametritzat del objecte\n";

    xRot = 0;
    yRot = 0;
    zRot = 0;


    Index = 0;

    readObj(n);

    make();

}


Objecte::~Objecte()
{
    delete points;
    delete colors;
    delete vertexsTextura;
}


Capsa3D Objecte::calculCapsa3D()
{

    // Metode a implementar: calcula la capsa mínima contenidora d'un objecte
    int i;
    //double xmin=999999, ymin=999999, zmin=999999, xmax=-999999, ymax=-999999, zmax=-999999;
    vec3    pmin, pmax;
    pmin=(999999,999999,999999);
    pmax=(-999999,-999999,-999999);

    for(int i =0;i<Index;i++)
    {
        for(int j = 0;j<3;j++){
            if(points[i][j]<pmin[j])
                pmin[j]=points[i][j];
            if(points[i][j]>pmax[j])
                pmax[j]=points[i][j];
        }
    }

    capsa.pmin=pmin;
    capsa.a=pmax[0]-pmin[0];
    capsa.h=pmax[1]-pmin[1];
    capsa.p=pmax[2]-pmin[2];
    return capsa;
}

void Objecte::aplicaTG(mat4 m)
{
    aplicaTGPoints(m);

    // Actualitzacio del vertex array per a preparar per pintar
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * Index,
                     &points[0] );

}

void Objecte::aplicaTGPoints(mat4 m)
{

    point4  *transformed_points = new point4[Index];

    for ( int i = 0; i < Index; ++i ) {
        transformed_points[i] = m * points[i];
    }

    transformed_points = &transformed_points[0];
    points = &points[0];

    for ( int i = 0; i < Index; ++i )
    {
        points[i] = transformed_points[i];
    }

    delete transformed_points;
}

void Objecte::aplicaTGCentrat(mat4 m)
{
    // Metode a implementar
    aplicaTGPoints(m);
    aplicaTG(m);
}

void Objecte::initTextura(int i)
 {
     qDebug() << "Initializing textures...";


     // Carregar la textura
     glActiveTexture(GL_TEXTURE0);
     texture = new QOpenGLTexture(QImage(path));
     texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
     texture->setMagnificationFilter(QOpenGLTexture::Linear);

     //texture->bind(0);

 }

void Objecte::toGPU(QGLShaderProgram *pr){

    program = pr;

    program->setUniformValue("texture", 0);

    std::cout<<"Passo les dades de l'objecte a la GPU\n";


    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(point4) * Index + sizeof(color4) * Index+sizeof(vec2)* Index,
                  NULL, GL_STATIC_DRAW );
    program->link();

    program->bind();
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_TEXTURE_2D);
}

// Pintat en la GPU.
void Objecte::draw()
{
    material->toGPU(program);

    // cal activar el buffer de l'objecte. Potser que ja n'hi hagi un altre actiu
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // per si han canviat les coordenades dels punts
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * Index, &points[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4) * Index, sizeof(normals) * Index, &normals[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)* Index +sizeof(color4) * Index,
                     sizeof(vec2)* Index, &vertexsTextura[0] );

    // Per a conservar el buffer
    int vertexLocation = program->attributeLocation("vPosition");
    int colorLocation = program->attributeLocation("vNormal");
    int coordTextureLocation = program->attributeLocation("vCoordTexture");

    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4);

    program->enableAttributeArray(colorLocation);
    program->setAttributeBuffer("vNormal", GL_FLOAT, sizeof(point4) * Index, 4);

    program->enableAttributeArray(coordTextureLocation);
    program->setAttributeBuffer("vCoordTexture", GL_FLOAT, sizeof(point4) * Index + sizeof(color4) * Index, 2);

//    program->bindAttributeLocation("vPosition", vertexLocation);
//    program->bindAttributeLocation("vColor", colorLocation);
    //program->bindAttributeLocation("vCoordTexture", coordTextureLocation);

    texture->bind(0);
    program->setUniformValue("texture", 0);
    glPolygonMode(GL_FRONT_AND_BACK,
                  polygonMode);
    glDrawArrays( drawMode, 0, Index );

    // Abans nomes es feia: glDrawArrays( GL_TRIANGLES, 0, NumVerticesP );
}

void Objecte::make()
{

//    static vec3  base_colors[] = {
//        vec3( 1.0, 0.0, 0.0 ),
//        vec3( 0.0, 1.0, 0.0 ),
//        vec3( 0.0, 0.0, 1.0 ),
//        vec3( 1.0, 1.0, 0.0 )
//    };
    // Recorregut de totes les cares per a posar-les en les estructures de la GPU
    // Cal recorrer l'estructura de l'objecte per a pintar les seves cares

    Index = 0;

    for(unsigned int i=0; i<cares.size(); i++)
    {
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++)
        {
            points[Index] = vertexs[cares[i].idxVertices[j]];
            colors[Index] = cares[i].color;
            setTexture(vertexs[cares[i].idxVertices[j]]);
            Index++;
        }
    }

    // S'ha de dimensionar uniformement l'objecte a la capsa de l'escena i s'ha posicionar en el lloc corresponent
}


// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
//

void Objecte::readObj(QString filename)
{

    FILE *fp = fopen(filename.toLocal8Bit(),"rb");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        while (true)
        {
            char *comment_ptr = ReadFile::fetch_line (fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp (first_word, "v"))
            {
                if (nwords < 4)
                {
                    fprintf (stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit (-1);
                }
                QString sx(ReadFile::words[1]);
                QString sy(ReadFile::words[2]);
                QString sz(ReadFile::words[3]);
                double x = sx.toDouble();
                double y = sy.toDouble();
                double z = sz.toDouble();

                if (nwords == 5)
                {
                    QString sw(ReadFile::words[4]);
                    double w = sw.toDouble();
                    x/=w;
                    y/=w;
                    z/=w;
                }
                // S'afegeix el vertex a l'objecte
                vertexs.push_back(point4(x, y, z, 1));

            }
            else if (!strcmp (first_word, "vn")) {
            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                // S'afegeix la cara a l'objecte
                // A modificar si es vol carregar mes de un objecte
                construeix_cara (&ReadFile::words[1], nwords-1, this, 0);
            }
            // added
            else if (!strcmp (first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            }
            else if (!strcmp (first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
            // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }
        }
    }

    capsa = calculCapsa3D();
}


void Objecte::construeix_cara ( char **words, int nwords, Objecte*objActual, int vindexUlt)
{
    Cara face;
    for (int i = 0; i < nwords; i++)
    {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0]>='0')&&(words[i][0]<='9'))
        {
            ReadFile::get_indices (words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

            /* store the vertex index */

            if (vindex > 0)       /* indices are from one, not zero */
                face.idxVertices.push_back(vindex - 1 - vindexUlt);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(objActual->vertexs.size() + vindex);
            else
            {
                fprintf (stderr, "Zero indices not allowed: '%s'\n", ReadFile::str_orig);
                exit (-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    objActual->cares.push_back(face);
}
void Objecte::setTexture( point4 a)
{
    GLfloat u = 0.5 + qAtan2(a[2], a[0])/ (2*M_PI);
    GLfloat v = 0.5 - qAsin(a[1])/M_PI;
    vertexsTextura[Index]=vec2(u,v);

}


