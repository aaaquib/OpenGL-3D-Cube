/**
Copyright 2007, All Rights Reserved: Zachary Wartell, University of North Carolina at Charlotte
\file Main.cpp
\author Zachary Wartell
\brief Main.cpp is a example of GLUT and OpenGL plus a few ITCS4120::OpenGLTrainer
calls to help setup for simply 2D drawing.

TO DO LIST:
\todo

BUG LIST:
\bug

FOOTNOTES:
- [F1] This is an example footnote.

REFERENCES:
- [R1] Donald Hearn and M. Pauline Baker.  Computer Graphics with OpenGL: Third Edition.
*/

/*******************************************************************************
    Includes	
*******************************************************************************/
#ifdef _WIN32
#include <windows.h>
#endif

#include <assert.h>
#include <time.h>
#include <iostream>

#include <GL/glew.h>   

#include <GL/glut.h>

#include <OpenGLTrainer/OpenGLTrainer.h>

#include <Cube.h>

using namespace std;

/*******************************************************************************
    File Scope Macros
*******************************************************************************/
/**
\brief enable debugging output to trace primary GLUT callbacks.
*/
//#define TRACE_CALLBACKS

/*******************************************************************************
    File Scope (static) Globals
*******************************************************************************/
//NONE

/*******************************************************************************
    File Scope (static) Functions - To be replaced by Student
*******************************************************************************/
/**
\brief All code in ZJW namespace should be completely replaced by the student to implement
their assignment.
*/
namespace ZJW
{

/**
\brief Print message for showing mouse position
*/
static void respondMouseMotion(int x, int y)
    {
    cout << "Mouse: " << x << " " << y << endl;   
    glutPostRedisplay();
    }

/**
\brief Set basic 3D view for a default fixed camera pose and frustum
*/
static void setupview(float eyeX,float eyeY,float eyeZ, float upX,float upY,float upZ)
    {
    /* Setup the view. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( /* field of view in degree */ 40.0,
	/* aspect ratio */ 1.0,
	/* Z near */ 10.0, /* Z far */ 50.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
	gluLookAt(eyeX, eyeY, eyeZ,  /* eye is at (0,0,5) */
	0.0, 0.0, 0.0,      /* center is at (0,0,0) */
	upX, upY, upZ);      /* up is in positive Y direction */
    
    }

static Cube cube;

// \brief draw some random stuff
static void draw_frame()
    {	
	cube.draw();
    }

} // namespace
/*******************************************************************************
    File Scope (static) Functions
*******************************************************************************/

float viewAngle[3] = {0,0,0};
const float angle = 3;
const float dist = 20;
float M_PI = (float)(4.0*atan(1.0));
float camX = 0;
float camY = 0;
float camZ = -20;
GLdouble upX=0,upY=1,upZ=0;
float orbitDegreesx=0,orbitDegreesy=90;

bool light0=true,light1=true,light2=true,light3=true;

void keys(unsigned char key,int x,int y)
{
	if(key=='a')
		orbitDegreesx -= angle;//viewAngle[0]-=angle;
	if(key=='d')
		orbitDegreesx += angle;//viewAngle[0]+=angle;
	if(key=='w')
		orbitDegreesy -= angle;//viewAngle[1]-=angle;
	if(key=='s')
		orbitDegreesy += angle;//viewAngle[1]+=angle;
	
	camX = dist * sinf(orbitDegreesy*(M_PI/180)) * sinf((orbitDegreesx)*(M_PI/180));
	camY = dist * cosf((orbitDegreesy)*(M_PI/180));
	camZ = -dist * sinf((orbitDegreesy)*(M_PI/180)) * cosf((orbitDegreesx)*(M_PI/180));

	GLfloat dt=1.0;
	GLfloat Xtemp = dist * sinf((orbitDegreesy - dt)*(M_PI/180)) * sinf((orbitDegreesx)*(M_PI/180));
	GLfloat Ytemp = dist * cosf((orbitDegreesy - dt)*(M_PI/180));
	GLfloat Ztemp = -dist * sinf((orbitDegreesy - dt)*(M_PI/180)) * cosf((orbitDegreesx)*(M_PI/180));

	upX = Xtemp-camX;
	upY = Ytemp-camY;
	upZ = Ztemp-camZ;

	if(key=='1')
	    {
	    if(light0==false)
		{
		glEnable(GL_LIGHT0);
		light0=true;
		}
	    else
		{
		glDisable(GL_LIGHT0);
		light0=false;
		}
	    }
	if(key=='2')
	    {
	    if(light1==false)
		{
		glEnable(GL_LIGHT1);
		light1=true;
		}
	    else
		{
		glDisable(GL_LIGHT1);
		light1=false;
		}
	    }
	if(key=='3')
	    {
	    if(light2==false)
		{
		glEnable(GL_LIGHT2);
		light2=true;
		}
	    else
		{
		glDisable(GL_LIGHT2);
		light2=false;
		}
	    }
	if(key=='4')
	    {
	    if(light3==false)
		{
		glEnable(GL_LIGHT3);
		light3=true;
		}
	    else
		{
		glDisable(GL_LIGHT3);
		light3=false;
		}
	    }
}

/**
\brief Simulate next time step in animation
*/
static void simulateNextTimeStep(void)
    {
    static clock_t lastTime = 0;

    /** update any animated objects' state */
    clock_t now;

    /* compute current time and time since last frame */
    now = clock ();

    if (lastTime)
	{// lastTime is initialize, so compute delta time
	float seconds=(float)(now - lastTime)/CLK_TCK;

	/* update all Animatible's data members based on time based since last frame */		
	ZJW::cube.animate(seconds);
	}

    /* record current time */
    lastTime=now;
    }

/**
\brief initialize some default OGL settings
*/
static
void initOpenGL (void)
    {
    const GLfloat light0_diffuse[] = {0.6, 0.7, 1.0, 1.0};
    const GLfloat light0_ambient[] = {0.3, 0.3, 0.3};  
    const GLfloat light0_specular[] = {1.0, 1.0, 1.0, 1.0}; 
    const GLfloat light0_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */

    const GLfloat light1_ambient[] = {0.2, 0.2, 0.2};  
    const GLfloat light1_diffuse[] = {0.7, 1.0, 0.6, 1.0};   
    const GLfloat light1_specular[] = {1.0, 1.0, 1.0, 1.0}; 
    const GLfloat light1_position[] = {-1.0, 1.0, 1.0, 0.0};  

    const GLfloat light2_diffuse[] = {1.0, 0.7, 0.6, 1.0}; 
    const GLfloat light2_ambient[] = {0.2, 0.2, 0.2};  
    const GLfloat light2_specular[] = {1.0, 1.0, 1.0, 1.0};   
    const GLfloat light2_position[] = {1.0, -1.0, 1.0, 0.0};  

    const GLfloat light3_diffuse[] = {1.0, 1.0, 1.0, 1.0};   
    const GLfloat light3_ambient[] = {0.1, 0.1, 0.1};  
    const GLfloat light3_specular[] = {1.0, 1.0, 1.0, 1.0};   
    const GLfloat light3_position[] = {-1.0, -1.0, 1.0, 0.0};  
    //set clear color to white
    glClearColor(0.0f,0.0f,0.0f,0.0f);     

    // Enable a single OpenGL light. 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glEnable(GL_LIGHT0);
     glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
    glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    glEnable(GL_LIGHT3);

    glEnable(GL_LIGHTING);

    // enable depth buffering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    
    }

/**
\brief 'motionFunc' is the GLUT motionFunc callback function
*/
static
void motionFunc 
	(
	int gx,  // 'glutX' - mouse X in GLUT coordinates
	int gy   // 'glutY' - mouse Y in GLUT coordinates
	)
    {
    /* convert from GLUT coordinate system to the 2D drawing coordinate system
       established by ITCS4120::OpenGLTrainer::matchWorldCoordinatesToPixelCoordinates 
     */
    const int WIDTH = glutGet(GLUT_WINDOW_WIDTH);
    const int HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);

    int sx,sy; // 'screenX', 'screenY'  mouse coordinate in our 2D screen coordinates
    sx = gx;
    sy = HEIGHT-gy;

    /* do something with mouse motion */
    ZJW::respondMouseMotion(sx,sy);
    }

/**
\brief 'display' is the GLUT display callback function (see [F2])

FOOTNOTES:
[F1] Note, OGL calls are only legal during execution of a GLUT display callback.  Below 
	is a standard method to make any OpenGL calls that we wish to make only the first
	time the GLUT display callback is executed.
[F2] DESIGN CHOICE: simulation of next time step is put in 'idle' callback and separated from
'display' callback.  This allows simulation to keep running even if the window is minimized
(in which case the display callback stops being called).  Other designs are of course possible.
To understand this design enable TRACE_CALLBACKS and toggle the window between it's minimized 
and non-minimized state and observe the console output. 
*/
static
void display(void)
    {      
    /**
	perform any 'one time' setup OGL calls (see [F1])
     **/
    static boolean doOnce=true;
    if (doOnce)
	{
	initOpenGL();
	doOnce = false;
	}

    /**
	setup frame
     **/   
    // clear screen
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // setup view
    ZJW::setupview(camX, camY, camZ,upX,upY,upZ);

    /**
	draw frame
     **/
    ZJW::draw_frame();
    
    /**
	end frame
     **/		
    ITCS4120::OpenGLTrainer::showFrameRate();
    GLenum e = glGetError();
    assert(e==GL_NO_ERROR);
    glutSwapBuffers();

   #ifdef TRACE_CALLBACKS
	cout << "display" << endl;
   #endif
    }

/**
\brief 'idle' is the GLUT idle callback function (see [F2])
*/
static
void idle(void)
    {	
    /** simulate next time step (in current approach simulation will keep running even if  
	    window is minimize)
	 **/
	simulateNextTimeStep();
	
    /** trigger display callback to redraw scene based on object's updated state (see [F2]) */
    glutPostRedisplay();

   #ifdef TRACE_CALLBACKS
	cout << "idle" << endl;
   #endif
    }

/**
\brief 'reshape' is the GLUT idle callback function
*/
static
void reshape(int width, int height)
    {    
    /* use the entire Window area for OpenGL drawing */
    glViewport( 0, 0,(GLsizei)width,(GLsizei)height);

    /* Setup the view. */
    ZJW::setupview(camX, camY, camZ,upX,upY,upZ);

    /** trigger display callback to redraw scene based on new window size */
    glutPostRedisplay();
    }

/**
\brief 'main' is the standard C/C++ main function where execution starts
*/
int main (int argc, char** argv)
    {       
    /* Initialize GLUT library */
    glutInit(&argc, argv);

    /* create window */    
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("Cube Skeleton I");
    
    /** init ITCS4120::OpenGLTrainer classes */
    ITCS4120::OpenGLTrainer::init(&argc,argv);    

    /* set glut callbacks */
    glutDisplayFunc (display);
    glutIdleFunc (idle);
    glutMotionFunc (motionFunc);     
    glutReshapeFunc (reshape);
    glutKeyboardFunc(keys);

    /* start GLUT main loop */
    glutMainLoop();
    return 0;
    }