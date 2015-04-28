
#include <math.h>

#include <glwidget.h>
#include <QString>
#include <qmath.h>


GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)

{
    setFocusPolicy( Qt::StrongFocus );
    esc = new Escena();

    xRot = 0;
    yRot = 0;
    zRot = 0;
    rot=false;
    alt=false;


    movX=0;
    movZ=0;
    mov = Translate(movX,0,movZ);
    a = 20.0;
    h = 20.0;
    p = 20.0;

    clearColor = Qt::black;
    qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    program = 0;
    moviment = false;
    cameraActual=true;

}


GLWidget::~GLWidget()
{
    makeCurrent();
    delete esc;
}


// Create a GLSL program object from vertex and fragment shader files
void
GLWidget::InitShader(const char* vShaderFile, const char* fShaderFile)
{           


    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    // Compilació del vertex shader
    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);

    program->bindAttributeLocation("vPosition", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("vColor", PROGRAM_COLOR_ATTRIBUTE);
    program->bindAttributeLocation("vCoordTexture", 2);
    // muntatge del shader en el pipeline gràfic per a ser usat
    program->link();

    // unió del shader al pipeline gràfic
    program->bind();
    program->setUniformValue("texture", 0);

}

void GLWidget::initShadersGPU()
{
// Carrega dels shaders i posa a punt per utilitzar els programes carregats a la GPU
   InitShader( "://vshader1.glsl", "://fshader1.glsl" );

}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const

{
    return QSize(400, 400);
}


static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}


void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot += (angle-xRot)/150;
//        xRot +=1;
        rot=true;
        update();
    }
}


void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot += (angle-yRot)/150;
//        yRot +=1;
        rot=true;
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot += (angle-zRot)/150;
//        zRot +=1;
        rot=true;
        update();
    }
}


void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    std::cout<<"Estic inicialitzant el shaders"<<std::ends;
    initShadersGPU();

    glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    newSalaBillar();
    //esc->CapsaMinCont3DEscena();
    esc->iniCamera(cameraActual,this->size().width(), this->size().height(),program);

}

void GLWidget::paintGL()
{
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   qNormalizeAngle(xRot);
   qNormalizeAngle(yRot);
   qNormalizeAngle(zRot);

   mat4 transform = ( RotateX( xRot / 16.0 ) *
                       RotateY( yRot / 16.0 ) *
                       RotateZ( zRot / 16.0 ) );


   // A modificar si cal girar tots els objectes
//   if (esc->taulaBillar!=NULL)
//       esc->taulaBillar->aplicaTGCentrat(transform);
//   if (esc->pla!=NULL)
//       esc->pla->aplicaTGCentrat(transform);
   if (esc->bola!=NULL){
//       esc->bola->aplicaTGCentrat(transform);
       bool trans=true;
       double x=esc->bola->capsa.pmin[0]-esc->bola->capsa.a;
       double y=esc->bola->capsa.pmin[1]-esc->bola->capsa.h;
       double z=esc->bola->capsa.pmin[2]-esc->bola->capsa.p;
       double radi=esc->bola->getRadi();
       double dist;

       for(int i=0;i<15;i++){
           double x1=esc->boles15->boles[i]->capsa.pmin[0]-esc->boles15->boles[i]->capsa.a;
           double y1=esc->boles15->boles[i]->capsa.pmin[1]-esc->boles15->boles[i]->capsa.h;
           double z1=esc->boles15->boles[i]->capsa.pmin[2]-esc->boles15->boles[i]->capsa.p;
           dist=qSqrt(qPow(x-x1,2)+qPow(y-y1,2)+qPow(z-z1,2));
           esc->boles15->boles[i]->capsa.pmin;
       }
       esc->bola->aplicaTGCentrat(mov);
   }
//   }
//   if (esc->boles15!=NULL)
//       esc->boles15->aplicaTGCentrat(transform);
   if(rot)
   {      
       esc->aplicaTGCentrat(transform);
   }
   rot=false;
   esc->draw();
   esc->actualizarCamara();
   esc->camera->toGPU(program);

}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#else
    glOrtho(-1.5, +1.5, -1.5, +1.5, 0.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}


void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
//        setXRotation(xRot + 1 * dy);
        if(lastPos.y()!=event->y() && lastPos.x()!=event->x()){
            if(abs(dx)<abs(dy)){
                // Se mueve en el eje y
                if(dy<0){
                    esc->camera->rotarY(false);
                }else{
                    esc->camera->rotarY(true);
                }
            }else{
                // Se mueve en el eje x
                if(dx<0){
                    esc->camera->rotarX(false);
                }else{
                    esc->camera->rotarX(true);
                }
            }
            update();
        }else if(lastPos.y()!=event->y()){
            if(dy<0){
                esc->camera->rotarY(false);
            }else{
                esc->camera->rotarY(true);
            }
            update();
        }else if(lastPos.x()!=event->x()){
            // Se mueve en el eje x
            if(dx<0){
                esc->camera->rotarX(false);
            }else{
                esc->camera->rotarX(true);
            }
            update();
        }
    }
    lastPos = event->pos();
}


void GLWidget::keyPressEvent(QKeyEvent *event)
{
    // Metode a implementar
    switch ( event->key() )
    {
    case Qt::Key_Up:
        movZ=0.03;
        break;
    case Qt::Key_Down:
        movZ=-0.03;
        break;
    case Qt::Key_Left:
        movX=-0.03;
        break;
    case Qt::Key_Right:
        movX=0.03;
        break;   
    case Qt::Key_Plus:
        esc->camera->zoom(true);
        break;
    case Qt::Key_Minus:
        esc->camera->zoom(false);
        break;
    case Qt::Key_Alt:
        alt=true;
        break;
    }
    if(alt)
    {
        esc->camera->pan(movX,movZ);
        mov=Translate(0,0,0);
    }
    else{
        mov=Translate(movX,0,movZ);
    }
    update();
}

void GLWidget::keyReleaseEvent(QKeyEvent *event)
{
    // Metode a implementar en el cas que es mogui la bola
    switch ( event->key() )
    {
    case Qt::Key_Up:
        movZ=0;
        break;
    case Qt::Key_Down:
        movZ=0;
        break;
    case Qt::Key_Left:
        movX=0;
        break;
    case Qt::Key_Right:
        movX=0;
        break;

    case Qt::Key_Alt:
        alt=false;
        break;
    }
    mov=Translate(movX,0,movZ);

}



void GLWidget::adaptaObjecteTamanyWidget(Objecte *obj)
{
        // Metode a implementar
//    double escalaZ = 1.0 / 20.0;
    double escalaZ = 1.0;
    if(dynamic_cast<Bola*>(obj))
    {
        escalaZ=escalaZ/2;
        mat4 m = Scale(escalaZ, escalaZ, escalaZ);
        obj->aplicaTG(m);
    }
    else{
        mat4 m = Scale(escalaZ, escalaZ, escalaZ);
        obj->aplicaTG(m);
    }

}

void GLWidget::newObjecte(Objecte * obj)
{
    adaptaObjecteTamanyWidget(obj);
    obj->initTextura(0);
    obj->toGPU(program);
    esc->addObjecte(obj);

    updateGL();
}
void GLWidget::newPlaBase()
{
    // Metode que crea un objecte PlaBase poligon amb el punt central al (0,0,0) i perpendicular a Y=0

    // Metode a implementar
    Pla* obj = new Pla();
    newObjecte(obj);
}

void GLWidget::newObj(QString fichero)
{
    // Metode que carrega un fitxer .obj llegit de disc
    TaulaBillar *obj;

    obj = new TaulaBillar(fichero);
    newObjecte(obj);
}

void GLWidget::newBola()
{
    Bola * obj=new Bola(0,0,22,-24);
//    Bola * obj=new Bola(1,0,0,0);
    newObjecte(obj);
    // Metode que crea la Bola blanca de joc
     // Metode a implementar
}
void GLWidget::newConjuntBoles()
{
    // Metode que crea les 15 Boles del billar america
    // Metode a implementar
    ConjuntBoles * obj=new ConjuntBoles();
    for(int i=0; i<15;i++)
    {
        adaptaObjecteTamanyWidget(obj->boles[i]);
        obj->boles[i]->initTextura(i);
        obj->boles[i]->toGPU(program);

    }
    float radi=obj->boles[0]->getRadi()*2, temp=0;
    int count=0;
    for(int j=0;j<5;j++)
    {
        for(int g=0;g<5-j;g++)
        {
            obj->boles[count]->aplicaTG(Translate(radi*(g+temp),0,-radi*j));
            count++;
        }
        temp+=0.5;
    }
    obj->CapsaMinCont3DEscena();
    esc->addConjuntBoles(obj);
    updateGL();
}
void GLWidget::newSalaBillar()
{
    // Metode que construeix tota la sala de billar: taula, 15 boles i bola blanca
    newConjuntBoles();
    TaulaBillar *obj2;

    obj2 = new TaulaBillar("../BillarPractica1/resources/taula.obj");
    newObjecte(obj2);

    //Pla* obj3 = new Pla();
    //newObjecte(obj3);
    newBola();
}

// Metode per iniciar la dinàmica del joc
void GLWidget::Play()
{

}
