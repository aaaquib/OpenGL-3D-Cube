/**
\file Cube.cpp
\author Zachary Wartell \n \n
   Copyright 2006.  Zachary Wartell, University of North Carolina at \n
   Charlotte. All rights reserved.

\brief A brief comment describing the purpose of this file goes here.

More detailed comments go here.  

TO DO LIST:
- \\ todo Replace the '\\ ' with '\' to generate a real todo comment

BUG LIST:
- \\ bug Replace the '\\ ' with '\' to generate a real bug comment. 

FOOTNOTES:
- [_F1_] <blank example. replace _F1_ with F1,F2, etc. for actual footnote>

REFERENCES:
- \anchor DK90 Donald Knuth, Algorithms and Data Structures, 1990.

\internal
*/

/*******************************************************************************
    Includes	
*******************************************************************************/
#ifdef _WIN32
#include <windows.h>
#endif
#include <math.h>
#include <Cube.h>
 

using namespace ZJW;

/*******************************************************************************
    Private Macros 
*******************************************************************************/
/* NONE */
/*******************************************************************************
    Private Function Prototypes 
*******************************************************************************/
/* NONE */
/*******************************************************************************
    Private Data Types 
*******************************************************************************/
/* NONE */

/*******************************************************************************
    Private Global Declarations 
*******************************************************************************/
const GLint Cube::faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };

const GLfloat Cube::n[6][3] = {  /* Normals for the 6 faces of a cube. */
	  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
	  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
GLfloat Cube::v[8][3];

GLfloat Cube::color[4][3] = { { 0.8,0.3,0.2},{ 0.0,0.7,0.0},{0.1f, 0.5f, 0.8f},{ 0.7,0.7,0.0} };

GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[4][4] = { { 0.3, 1, 0.1, 1.0 }, { 0.2, 0.77, 0.05, 1.0 }, { 0.1, 0.44, 0.01, 1.0 }, { 0.0, 0.0, 0.0, 1.0 } };
GLfloat mat_diffuse[4][4] = { { 0.3, 1, 0.1, 1.0 }, { 0.2, 0.77, 0.05, 1.0 }, { 0.1, 0.44, 0.01, 1.0 }, { 0.0, 0.0, 0.0, 1.0 } };

GLfloat mat_ambient_color[16][4]  =   { { 1.0, 0.0, 0.0, 1.0 }, { 0.8, 0.0, 0.0, 1.0 }, { 0.46, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, 
					{ 0.0, 1.0, 0.0, 1.0 }, { 0.0, 0.8, 0.0, 1.0 }, { 0.0, 0.46, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, 
					{ 0.0, 0.0, 1.0, 1.0 }, { 0.0, 0.0, 0.8, 1.0 }, { 0.0, 0.0, 0.46, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, 
					{ 1.0, 1.0, 0.0, 1.0 }, { 0.8, 0.8, 0.0, 1.0 }, { 0.46, 0.46, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 } };

GLfloat mat_diffuse_color[16][4] = {  { 1.0, 0.0, 0.0, 1.0 }, { 0.8, 0.0, 0.0, 1.0 }, { 0.44, 0.0, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, 
				{ 0.0, 1.0, 0.0, 1.0 }, { 0.0, 0.8, 0.0, 1.0 }, { 0.0, 0.44, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, 
				{ 0.0, 0.0, 1.0, 1.0 }, { 0.0, 0.0, 0.8, 1.0 }, { 0.0, 0.0, 0.44, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }, 
				{ 1.0, 1.0, 0.0, 1.0 }, { 0.8, 0.8, 0.0, 1.0 }, { 0.44, 0.44, 0.0, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }  };


GLfloat mat_specular[4][4] = {{ 1.0, 0.7, 1.0, 1.0 }, { 0.6, 0.3, 0.6, 1.0 }, { 0.3, 0.1, 0.3, 1.0 }, { 0.0, 0.0, 0.0, 1.0 }};

GLfloat mat_shininess[4][1] = { {3.0}, {15.0}, {50.0}, {128.0} };

GLfloat mat_emission[4][4] = { {0.8, 0.6, 0.4, 0.0}, {0.7, 0.4, 0.2, 0.0}, {0.5, 0.2, 0.1, 0.0}, {0.0, 0.0, 0.0, 0.0} };

GLfloat var_emission[4] = {0.6, 0.2, 0.3, 1.0 } ;

GLuint DLid;

bool Cube::init=false;

/*******************************************************************************
    Internal Global Declarations 
*******************************************************************************/
/* NONE */
/*******************************************************************************
    Exported Global Declarations 
*******************************************************************************/
/* NONE */


/*******************************************************************************
    Exported Functions & Exported Class Member Functions 
*******************************************************************************/
/**
\brief Construct this cube
**/
Cube::Cube()
{
	
	if (!init)
		initVertices();
	spin = 0;
	velocity = 45;

}

/**
\brief update cube pose
*/
void Cube::animate(float deltaT)
	{
	/*spin += velocity * deltaT;
	spin = fmod(spin,361);*/
	for(int i=0;i<3;i++)
	    {
		if(var_emission[i]>=1)
		    var_emission[i] -= 1; 
		var_emission[i] += deltaT;
	    }
	}

GLuint Cube::createDL(int r, int subdivisions) 
    {
	GLUquadricObj *sphere=NULL;
	sphere = gluNewQuadric();
    	GLuint sphereDL;
	sphereDL = glGenLists(1);
	glNewList(sphereDL,GL_COMPILE);
	//glutSolidSphere (r, subdivisions, subdivisions);
	//gluSphere(sphere, 1.0, 50, 50);
	renderCube(1,30);
	glEndList();
	GLenum e = glGetError();
	gluDeleteQuadric(sphere);
	return (sphereDL);
    }
/**
\brief draw cube
*/
void Cube::draw()
{	
	renderCube(1,50);
	//glCallList(DLid);
	GLenum e = glGetError();
}


void Cube::renderCube(float radius,int subdivisions)

{
int i=0,j=0;
GLUquadricObj *sphere=NULL;
  sphere = gluNewQuadric();
  gluQuadricNormals(sphere, GLU_SMOOTH);
//the same quadric can be re-used for drawing many spheres

    glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
    glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);

    //FRONT FACE
    for(float y=-3;y<=3;y+=2)
	{
	for(float x=-3;x<=3;x+=2)
	    {
	    glPushMatrix();
	    glTranslatef( x,y,-4 );

	    glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
	    glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
	    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_color[j]);

	    gluSphere(sphere, radius, subdivisions, subdivisions);
	    //glutSolidSphere (1.0, subdivisions, subdivisions);
	    //glCallList(DLid);
	    glPopMatrix();
	    
	    j++;
	    }
	}
   
    glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
    glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);
    i=0;j=0;
     //RIGHT FACE
    for(float y=-3;y<=3;y+=2)
	{
	for(float z=3;z>=-3;z-=2)
	    {
	    glPushMatrix();
	    glTranslatef( -4,y,z );
	 glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
	    glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);
	    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_color[j]);

	    gluSphere(sphere,radius, subdivisions, subdivisions);
	    //glutSolidSphere (1.0, subdivisions, subdivisions);
	    //glCallList(DLid);
	    glPopMatrix();
	    j++;
	    }
	}

    glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
    glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);
    i=0,j=0;
    //BACK FACE
    for(float y=-3;y<=3;y+=2)
	{
	int j=0;
	for(float x=3;x>=-3;x-=2)
	    {
	    glPushMatrix();

	    glTranslatef( x,y,4 );
	    glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
	    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient[i]);
	    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse[j]);
	    
	    gluSphere(sphere,radius, subdivisions, subdivisions);
	    //glutSolidSphere (1.0, subdivisions, subdivisions);
	    //glCallList(DLid);
	    glPopMatrix();
	    j++;
	    }
	i++;
	}

    glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
    glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);
    i=0,j=0;
    //BOTTOM FACE
    for(float z=-3;z<=3;z+=2)
	{
	int j=0;
	for(float x=3;x>=-3;x-=2)
	    {
	    glPushMatrix();

	    glTranslatef( x,-4,z );
	    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_color[5]);
	    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_color[9]);
	    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular[j]);
	    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess[i]);
	    
	    gluSphere(sphere,radius, subdivisions, subdivisions);
	    //glutSolidSphere (1.0, subdivisions, subdivisions);
	    //glCallList(DLid);
	    glPopMatrix();
	    j++;
	    }
	i++;
	}

    glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
    glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);
    i=0,j=0;
    //LEFT FACE
    for(float y=-3;y<=3;y+=2)
	{
	for(float z=3;z>=-3;z-=2)
	    {
	    glPushMatrix();
	    glTranslatef( 4,y,z );
	 if(y==-3)
		{
		glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_color[1]);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_color[0]);
		glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[i]);
		
		gluSphere(sphere,radius, subdivisions, subdivisions);
		//glutSolidSphere (1.0, subdivisions, subdivisions);

		}
	    else if(y==-1)
		{
		glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_color[9]);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_color[8]);
		glMaterialfv(GL_FRONT, GL_EMISSION, var_emission);
		gluSphere(sphere,radius, subdivisions, subdivisions);
		}
	    else if(y==1)
		{
		glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_color[13]);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_color[12]);
		glMaterialfv(GL_FRONT, GL_EMISSION, var_emission);

		gluSphere(sphere,radius, subdivisions, subdivisions);
		//glutSolidSphere (1.0, subdivisions, subdivisions);
		}
	    else if(y==3)
		{
		glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_color[5]);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_color[4]);
		glMaterialfv(GL_FRONT, GL_EMISSION, var_emission);

		gluSphere(sphere,radius, subdivisions, subdivisions);
		//glutSolidSphere (1.0, subdivisions, subdivisions);
		}
	    
	    glPopMatrix();
	    j++;
	    }
	i++;
	}

    glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
    glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    i=0,j=0;
    //TOP FACE
    for(float z=-3;z<=3;z+=2)
	{
	for(float x=3;x>=-3;x-=2)
	    {
	    glPushMatrix();
	    glTranslatef( x,4,z );
	 if(z==-3)
		{
		glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_color[3]);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_color[0]);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular[2]);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess[0]);

		gluSphere(sphere,radius, subdivisions, subdivisions);
		//glutSolidSphere (1.0, subdivisions, subdivisions);
		}
	    else if(z==-1)
		{
		glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_color[7]);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_color[9]);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[2]);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular[1]);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess[1]);

		gluSphere(sphere,radius, subdivisions, subdivisions);
		//glutSolidSphere (1.0, subdivisions, subdivisions);
		}
	    else if(z==1)
		{
		glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_color[14]);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_color[4]);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[2]);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular[1]);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess[2]);

		gluSphere(sphere,radius, subdivisions, subdivisions);
		//glutSolidSphere (1.0, subdivisions, subdivisions);
		}
	    else if(z==3)
		{
		glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_color[j]);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_color[j]);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[1]);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular[0]);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess[3]);

		gluSphere(sphere,radius, subdivisions, subdivisions);
		//glutSolidSphere (1.0, subdivisions, subdivisions);
		}
	    glPopMatrix();
	    j++;
	    }
	i++;
	}
    glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv(GL_FRONT,GL_SPECULAR,no_mat);
    glMaterialfv(GL_FRONT,GL_AMBIENT,no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    gluDeleteQuadric(sphere);
    GLenum e = glGetError();
}

/*******************************************************************************
    Internal Functions & Internal Class Member Functions 
*******************************************************************************/
/* NONE */
/*******************************************************************************
    Private Functions & Private Class Member Functions 
*******************************************************************************/
/*
\brief Init static member vertex data
*/
void Cube::initVertices()
{
	
	//GLuint DLid;
	DLid = createDL(1,25);
	init = true;
	GLenum e = glGetError();
	
}
/* NONE */
