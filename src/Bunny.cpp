//============================================================================
// Name        : Bunny.cpp
// Author      : Zhikai
// Version     :
// Copyright   : (c) 2010 2015 Zhikai Wang/www.heteroclinic.net
// Description : The entry point of the project. There are a lot of comments I wrote five years ago,
// they will be cleaned later.
// Note: For all demo results, use 512x512.
//============================================================================

// TODO 20150322 Make sure Phong shading works (Demo 1)
// TODO 20150322 Create the visual C++ branch ?

//notes: we can render the value z(eyecoordinate) as a color element (frag.b=z) of a
// color texture, then use it to peel
// but the effect is not as good as depth buffer.

//Project Property -> Configuation Properties -> Linker -> Input -> Ignore Specific Library
//
//Ignore the LIBC.LIB
//
//I think it could fix your problems.

#define GLEW_STATIC
//#include "glew.h"
#include "textfile.h"
#include <stdio.h>
#include <stdlib.h>
//Include glew first
#include <GL/glew.h>
#include <GL/freeglut.h>
//#include <GL/glut.h>
//#include "glew.h"
//#include "wglew.h"

//#include <GL/wglew.h>
#include "model.h"

GLint width=512,height=512;// you must set them as 512 for best effects
//GLint width=800,height=800;// you must set them as 512 for best effects

GLhandleARB v,f,p;
GLhandleARB v2,f2,p2;
GLhandleARB v3,f3,p3;
GLhandleARB v4,f4,p4;
GLhandleARB v5,f5,p5;
GLhandleARB v6,f6,p6;

Model	bunny,horse,head,x_wing,lrzs15;
GLint loc1,loc2,loc3,loc4,loc5,loc6,loc7,loc8,loc9,loc10;
GLint mode;
GLfloat g_mCameraInverse[16],light_ProjectionMatrix[16],T[16],tmp[16],tmp2[16],tmp3[16],tmp4[16];
GLint	depthUnit;
GLuint img,depthImg,img3,img2,img4,img5,img6,img7,img8;
GLuint depth,depth2,depth3,depth4,depth5;
GLuint fbo,fbo2,fbo3,fbo4,fbo5;
//	GLuint width, height;
GLuint quadid;
GLenum buffers[] = {GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT};
GLint xRot=0;
GLint yRot=0;
GLint zRot=0;
GLfloat scale=1.0;

//GLfloat orthoganal_clip_size,orthoganal_clip_size2	;
// eyex ,eyey,eyez ;
//GLfloat lookatx,lookaty,lookatz;
//GLfloat NEAR_Z;
//GLfloat FAR_Z;


GLfloat	orthoganal_clip_size2 =5.0 ,orthoganal_clip_size	= 5.0;
GLfloat	eyex = 0 ,eyey= 0 ,eyez = 5.0;
GLfloat	lookatx =0,lookaty =0,lookatz=0;
GLfloat	NEAR_Z	=		3;
GLfloat	FAR_Z	=		30.0;
float zero[4];
float color[4] = {0.0f, 0.0f, 0.0f,0.2};
GLfloat frv4[4];


int maxPass = 2;
bool peelOnly = false;



const float mBias[] = {0.5, 0.0, 0.0, 0.0,
0.0, 0.5, 0.0, 0.0,
0.0, 0.0, 0.5, 0.0,
0.5, 0.5, 0.5, 1.0};
float g_mProjection[16] = {0};
float g_mModelView[16] = {0};
int depthTextureUnitID =0;
int colorTextureUnitID =3;
//uniform sampler2D colorTex;

GLfloat frontAlpha = 0.8,backAlpha = 0.6;

GLfloat back_brass_mat_shininess[] = { 8.8  };
GLfloat back_brass_mat_specular[] = { 0.49, 0.41, 0.31, 0.2};
GLfloat back_brass_mat_diffuse[] = {0.3, 0.27, 0.05,0.2};
GLfloat back_brass_mat_ambient[] = { 0.23, 0.12, 0.23, 0.2};
GLfloat back_brass_mat_emission[] = { 0.0, 0.0, 0.0, 0.2 };

GLfloat brass_mat_shininess[] = { 27.8 };
GLfloat brass_mat_specular[] = { 0.99, 0.91, 0.81, 0.8 };
GLfloat brass_mat_diffuse[] = { 0.7, 0.57, 0.11,0.8};
GLfloat brass_mat_ambient[] = { 0.33, 0.22, 0.33, 0.8 };
GLfloat brass_mat_emission[] = {0.0, 0.0,0.0, 0.8 };

GLfloat blue_shiny_mat_shininess[] = { 100.0 };
GLfloat blue_shiny_mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat blue_shiny_mat_diffuse[] = { 0.0, 0.0, 0.7,1.0};
GLfloat blue_shiny_mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat blue_shiny_mat_emission[] = { 0.0, 0.0,0.0, 1.0 };

GLfloat back_blue_shiny_mat_shininess[] = { 35.0 };
GLfloat back_blue_shiny_mat_specular[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat back_blue_shiny_mat_diffuse[] = { 0.0, 0.0, 0.2,1.0};
GLfloat back_blue_shiny_mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat back_blue_shiny_mat_emission[] = { 0.0, 0.0,0.0, 1.0 };

void setBlueShinyMaterial(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, blue_shiny_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue_shiny_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blue_shiny_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, blue_shiny_mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, blue_shiny_mat_emission);

	glMaterialfv(GL_BACK, GL_AMBIENT, back_blue_shiny_mat_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, back_blue_shiny_mat_diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, back_blue_shiny_mat_specular);
	glMaterialfv(GL_BACK, GL_SHININESS, back_blue_shiny_mat_shininess);
	glMaterialfv(GL_BACK, GL_EMISSION, back_blue_shiny_mat_emission);
}
void setRevBlueShinyMaterial(){
	glMaterialfv(GL_BACK, GL_AMBIENT, blue_shiny_mat_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, blue_shiny_mat_diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, blue_shiny_mat_specular);
	glMaterialfv(GL_BACK, GL_SHININESS, blue_shiny_mat_shininess);
	glMaterialfv(GL_BACK, GL_EMISSION, blue_shiny_mat_emission);

	glMaterialfv(GL_FRONT, GL_AMBIENT, back_blue_shiny_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, back_blue_shiny_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, back_blue_shiny_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, back_blue_shiny_mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, back_blue_shiny_mat_emission);
}
GLfloat red_shiny_mat_shininess[] = { 100.0 };
GLfloat red_shiny_mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat red_shiny_mat_diffuse[] = { 0.7, 0.0, 0.0,1.0};
GLfloat red_shiny_mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat red_shiny_mat_emission[] = { 0.0, 0.0,0.0, 1.0 };

GLfloat back_red_shiny_mat_shininess[] = { 35.0 };
GLfloat back_red_shiny_mat_specular[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat back_red_shiny_mat_diffuse[] = { 0.2, 0.0, 0.0,1.0};
GLfloat back_red_shiny_mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat back_red_shiny_mat_emission[] = { 0.0, 0.0,0.0, 1.0 };

void setRedShinyMaterial(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, red_shiny_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red_shiny_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, red_shiny_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, red_shiny_mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, red_shiny_mat_emission);

	glMaterialfv(GL_BACK, GL_AMBIENT, back_red_shiny_mat_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, back_red_shiny_mat_diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, back_red_shiny_mat_specular);
	glMaterialfv(GL_BACK, GL_SHININESS, back_red_shiny_mat_shininess);
	glMaterialfv(GL_BACK, GL_EMISSION, back_red_shiny_mat_emission);
}

GLfloat green_shiny_mat_shininess[] = { 100.0 };
GLfloat green_shiny_mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat green_shiny_mat_diffuse[] = { 0.0, 0.7, 0.0,1.0};
GLfloat green_shiny_mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat green_shiny_mat_emission[] = { 0.0, 0.0,0.0, 1.0 };

GLfloat back_green_shiny_mat_shininess[] = { 35.0 };
GLfloat back_green_shiny_mat_specular[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat back_green_shiny_mat_diffuse[] = { 0.0, 0.2, 0.0,1.0};
GLfloat back_green_shiny_mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat back_green_shiny_mat_emission[] = { 0.0, 0.0,0.0, 1.0 };

void setGreenShinyMaterial(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, green_shiny_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green_shiny_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, green_shiny_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, green_shiny_mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, green_shiny_mat_emission);

	glMaterialfv(GL_BACK, GL_AMBIENT, back_green_shiny_mat_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, back_green_shiny_mat_diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, back_green_shiny_mat_specular);
	glMaterialfv(GL_BACK, GL_SHININESS, back_green_shiny_mat_shininess);
	glMaterialfv(GL_BACK, GL_EMISSION, back_green_shiny_mat_emission);
}



GLfloat white_shiny_mat_shininess[] = { 100.0 };
GLfloat white_shiny_mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat white_shiny_mat_diffuse[] = { 1.0, 1.0, 1.0,1.0};
GLfloat white_shiny_mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat white_shiny_mat_emission[] = { 0.0, 0.0,0.0, 1.0 };

GLfloat back_white_shiny_mat_shininess[] = { 85.0 };
GLfloat back_white_shiny_mat_specular[] = { 0.85, 0.85, 0.85, 1.0 };
GLfloat back_white_shiny_mat_diffuse[] = { 0.85, 0.85, 0.85,1.0};
GLfloat back_white_shiny_mat_ambient[] = { 0.85, 0.85, 0.85, 1.0 };
GLfloat back_white_shiny_mat_emission[] = { 0.0, 0.0,0.0, 1.0 };

GLfloat red_plastic_mat_shininess[] = { 32.0 };
GLfloat red_plastic_mat_specular[] = { 0.0, 0.6, 0.6,0.3 };
GLfloat red_plastic_mat_diffuse[] = { 0.6, 0.0, 0.0,0.3};
GLfloat red_plastic_mat_ambient[] = { 0.3, 0.0, 0.0, 0.3 };
GLfloat red_plastic_mat_emission[] = {0.0, 0.0,0.0, 0.3 };

GLfloat back_red_plastic_mat_shininess[] = { 20.0 };
GLfloat back_red_plastic_mat_specular[] = { 0.0, 0.3, 0.3,0.3 };
GLfloat back_red_plastic_mat_diffuse[] = { 0.25, 0.0, 0.0,0.3};
GLfloat back_red_plastic_mat_ambient[] = { 0.1, 0.0, 0.0, 0.3 };
GLfloat back_red_plastic_mat_emission[] = {0.0, 0.0,0.0, 0.3 };


//void CreateRenderTexture(UINT textureArray[], int sizeX, int sizeY, int channels, int type, int textureID)
void CreateRenderTexture( GLuint textureArray[], int sizeX, int sizeY, int channels, int type, int textureID)
//CreateRenderTexture(g_Texture, SHADOW_WIDTH, SHADOW_HEIGHT, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, SHADOW_ID);
//UINT g_Texture[MAX_TEXTURES];
//#define MAX_TEXTURES 1000
//#define SHADOW_ID	0
{
	// Create a pointer to store the blank image data
	unsigned int *pTexture = NULL;

	// Store the current channels to be allocated by default
	int channelsTrue = channels;

	// If the channels are greater than 4 there must be a special flag like
	// GL_DEPTH_COMPONENT, so make sure we only allocate 1 bit per pixel.
	if(channels > 4)
		channelsTrue = 1;

	// Allocate and init memory for the image array and point to it from pTexture
	pTexture = new unsigned int [sizeX * sizeY * channelsTrue];
	memset(pTexture, 0, sizeX * sizeY * channelsTrue * sizeof(unsigned int));

	// Register the texture with OpenGL and bind it to the texture ID
	//GLAPI void GLAPIENTRY glGenTextures( GLsizei n, GLuint *textures );
	glGenTextures(1, &textureArray[textureID]);
	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	// Create the texture and store it on the video card
	glTexImage2D(GL_TEXTURE_2D, 0, channels, sizeX, sizeY, 0, type, GL_UNSIGNED_INT, pTexture);

	// Set the texture quality
	//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	//glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	// Since we stored the texture space with OpenGL, we can delete the image data
	if (NULL != pTexture )
		delete [] pTexture;
}


void StoreLightMatrices()
{
	// Reset our current light matrices
	memset(g_mModelView, 0, sizeof(float)*16);
	memset(g_mProjection, 0, sizeof(float)*16);

	// Let's push on a new matrix so we don't change the rest of the world
	glPushMatrix();

	// Push on a new matrix to keep our view changes isolated
	glPushMatrix();

	// Reset the current modelview matrix
	glLoadIdentity();

	// This is where we set the light's position and view.
	//gluLookAt(g_LightPosition[0],  g_LightPosition[1],  g_LightPosition[2],
	//		  g_LightView[0],	   g_LightView[1],	    g_LightView[2],		0, 1, 0);

	//gluLookAt(g_Camera.m_vPosition.x, g_Camera.m_vPosition.y, g_Camera.m_vPosition.z,
	//		  g_Camera.m_vView.x,	 g_Camera.m_vView.y,     g_Camera.m_vView.z,
	//		  g_Camera.m_vUpVector.x, g_Camera.m_vUpVector.y, g_Camera.m_vUpVector.z);
	gluLookAt(eyex,eyey, eyez, lookatx,lookaty,lookatz, 0,1,0);

	// Now that we have the light's view, let's save the current modelview matrix.
	glGetFloatv(GL_MODELVIEW_MATRIX, g_mModelView);

	// Now pop off the current light view's matrix
	glPopMatrix();

	// Reset the current matrix
	glLoadIdentity();

	// Set our FOV, aspect ratio, then near and far planes for the light's view
	//gluPerspective(60.0f, 1.0f, 0.5f, 25.0f);
	//gluPerspective(60.0f, 1.0f, 3.0f, 30.0f);

	//NEAR_Z	=		3;
	//FAR_Z	=		7.0;

	gluPerspective(90.0f, 1.0f, NEAR_Z,FAR_Z);
	//glOrtho(-5, 5, 		-5,  5,  2, 30);

	// Grab the current matrix that will be used for the light's projection matrix
	glGetFloatv(GL_MODELVIEW_MATRIX, g_mProjection);

	// Go back to the original matrix
	glPopMatrix();
}



void getInverseMatrix(float * m_fTransformMatrix  , float * mat )
{
	//static float mat[16] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	for ( int i = 0; i < 16; i++ ) mat[i] = (i % 5 ? 0.0f : 1.0f);
	mat[0] = m_fTransformMatrix[0];
	mat[1] = m_fTransformMatrix[4];
	mat[2] = m_fTransformMatrix[8];
	mat[4] = m_fTransformMatrix[1];
	mat[5] = m_fTransformMatrix[5];
	mat[6] = m_fTransformMatrix[9];
	mat[8] = m_fTransformMatrix[2];
	mat[9] = m_fTransformMatrix[6];
	mat[10] = m_fTransformMatrix[10];
	mat[12] = -m_fTransformMatrix[0] * m_fTransformMatrix[12] - m_fTransformMatrix[1] * m_fTransformMatrix[13] - m_fTransformMatrix[2] * m_fTransformMatrix[14];
	mat[13] = -m_fTransformMatrix[4] * m_fTransformMatrix[12] - m_fTransformMatrix[5] * m_fTransformMatrix[13] - m_fTransformMatrix[6] * m_fTransformMatrix[14];
	mat[14] = -m_fTransformMatrix[8] * m_fTransformMatrix[12] - m_fTransformMatrix[9] * m_fTransformMatrix[13] - m_fTransformMatrix[10] * m_fTransformMatrix[14];
}


void ShutDown()
{
	glDeleteFramebuffersEXT(1, &fbo);
	glDeleteFramebuffersEXT(1, &fbo2);
	glDeleteFramebuffersEXT(1, &fbo3);
	glDeleteFramebuffersEXT(1, &fbo4);
	glDeleteFramebuffersEXT(1, &fbo5);
//	glDeleteRenderbuffersEXT(1, &depthBuffer);
	glDeleteTextures(1,&img);
	glDeleteTextures(1,&img2);
	glDeleteTextures(1,&img3);
	glDeleteTextures(1,&img4);
	glDeleteTextures(1,&img5);
	glDeleteTextures(1,&depth);
	glDeleteTextures(1,&depth2);
	glDeleteTextures(1,&depth3);
	glDeleteTextures(1,&depth4);
	glDeleteTextures(1,&depth5);

}
void calllist(GLuint m_iID)
{
	glCallList(m_iID);
}

void newList( GLuint & m_iID)
{
	GLenum mode = GL_COMPILE;
	if ( glIsList(m_iID) == GL_FALSE ) m_iID = glGenLists(1);
	else glDeleteLists(m_iID, 0);

	glNewList(m_iID, mode);
}

void endList(void)
{
	glEndList();
}
void drawQuad(const float sz)
{
	const float texc = 1.0f;
	float data[][5] = {	{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }, { texc, 0.0f, sz, 0.0f, 0.0f }, { texc, texc, sz, sz, 0.0f }, { 0.0f, texc, 0.0f, sz, 0.0f } };
	glInterleavedArrays(GL_T2F_V3F, 0, data);
	glDrawArrays(GL_QUADS, 0, 4);
}


void drawTexture(void)
{

	glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

			glPushAttrib(GL_VIEWPORT_BIT);
			glDisable(GL_LIGHTING);

			int sz = (height >> 2);
			glViewport(0, 0, width/4 , height/4);

			glActiveTexture(GL_TEXTURE0 );
			glDisable(GL_TEXTURE_1D);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_TEXTURE_3D);
			glEnable(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, img);
			glEnable(GL_TEXTURE_2D);
			calllist(quadid);
			glDisable(GL_TEXTURE_2D);


			glViewport(0, height/4, width/4 , height/4);
			glBindTexture(GL_TEXTURE_2D, img2);
			glEnable(GL_TEXTURE_2D);
			calllist(quadid);
			glDisable(GL_TEXTURE_2D);

			glViewport(0, 2*height/4, width/4 , height/4);
			glBindTexture(GL_TEXTURE_2D, img3);
			glEnable(GL_TEXTURE_2D);
			calllist(quadid);
			glDisable(GL_TEXTURE_2D);

			glViewport(0, 3*height/4, width/4 , height/4);
			glBindTexture(GL_TEXTURE_2D, img4);
			glEnable(GL_TEXTURE_2D);
			calllist(quadid);
			glDisable(GL_TEXTURE_2D);




			glViewport(3/4.0 *width ,0 , width/4 , height/4);
			glBindTexture(GL_TEXTURE_2D, depth);
			glEnable(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
			calllist(quadid);
			glDisable(GL_TEXTURE_2D);


			glViewport(3/4.0 *width ,height/4 , width/4 , height/4);
			glBindTexture(GL_TEXTURE_2D, depth2);
			glEnable(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
			calllist(quadid);
			glDisable(GL_TEXTURE_2D);

			glViewport(3/4.0 *width ,3*height/4 , width/4 , height/4);
			glBindTexture(GL_TEXTURE_2D, depth4);
			glEnable(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
			calllist(quadid);
			glDisable(GL_TEXTURE_2D);




			//glViewport(3/4.0 *width ,height/4 , width/4 , height/4);
			//glBindTexture(GL_TEXTURE_2D, img4);

			//glEnable(GL_TEXTURE_2D);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);

			//calllist(quadid);
			//glDisable(GL_TEXTURE_2D);

		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}


void initFBOnTEX()
{
	// Setup our FBO
	glGenFramebuffersEXT(1, &fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);

	// Now setup the first texture to render to
	CreateRenderTexture(&depth, width, height, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, depthTextureUnitID);

	glGenTextures(1, &img);
	glBindTexture(GL_TEXTURE_2D, img);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// And attach it to the FBO so we can render to it
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, img, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depth, 0);

	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		exit(1);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind the FBO for now

	// Setup our FBO 2
	glGenFramebuffersEXT(1, &fbo2);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo2);

	// Now setup the first texture to render to
	CreateRenderTexture(&depth2, width, height, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, depthTextureUnitID);
	glGenTextures(1, &img2);
	glBindTexture(GL_TEXTURE_2D, img2);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// And attach it to the FBO so we can render to it
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, img2, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depth2, 0);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		exit(1);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind the FBO for now

	// Setup our FBO 3
	glGenFramebuffersEXT(1, &fbo3);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo3);

	// Now setup the first texture to render to
	CreateRenderTexture(&depth3, width, height, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, depthTextureUnitID);
	glGenTextures(1, &img3);
	glBindTexture(GL_TEXTURE_2D, img3);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// And attach it to the FBO so we can render to it
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, img3, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depth3, 0);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		exit(1);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind the FBO for now


	// Setup our FBO 4
	glGenFramebuffersEXT(1, &fbo4);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo4);

	// Now setup the first texture to render to
	CreateRenderTexture(&depth4, width, height, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, depthTextureUnitID);
	glGenTextures(1, &img4);
	glBindTexture(GL_TEXTURE_2D, img4);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// And attach it to the FBO so we can render to it
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, img4, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depth4, 0);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		exit(1);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind the FBO for now

	// Setup our FBO 5
	glGenFramebuffersEXT(1, &fbo5);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo5);

	// Now setup the first texture to render to
	CreateRenderTexture(&depth5, width, height, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, depthTextureUnitID);
	glGenTextures(1, &img5);
	glBindTexture(GL_TEXTURE_2D, img5);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// And attach it to the FBO so we can render to it
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, img5, 0);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depth5, 0);

	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		exit(1);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind the FBO for now


}


void changeSize(int w, int h) {
	if ((w != width) || (h!= height)) {
		width = w, height = h;

		ShutDown();
		initFBOnTEX();
	}
//	glViewport(0, 0, w, h);				// whole window area
//
//	// set the projection transformation,
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	glOrtho(-orthoganal_clip_size, orthoganal_clip_size, 		-orthoganal_clip_size2,  orthoganal_clip_size2,  NEAR_Z, FAR_Z);
//	glMatrixMode(GL_MODELVIEW);
//
}
void setWhiteShinyMaterial(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, white_shiny_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white_shiny_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white_shiny_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, white_shiny_mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, white_shiny_mat_emission);

	glMaterialfv(GL_BACK, GL_AMBIENT, back_white_shiny_mat_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, back_white_shiny_mat_diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, back_white_shiny_mat_specular);
	glMaterialfv(GL_BACK, GL_SHININESS, back_white_shiny_mat_shininess);
	glMaterialfv(GL_BACK, GL_EMISSION, back_white_shiny_mat_emission);
}
void setRevWhiteShinyMaterial(){
	glMaterialfv(GL_BACK, GL_AMBIENT, white_shiny_mat_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, white_shiny_mat_diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, white_shiny_mat_specular);
	glMaterialfv(GL_BACK, GL_SHININESS, white_shiny_mat_shininess);
	glMaterialfv(GL_BACK, GL_EMISSION, white_shiny_mat_emission);

	glMaterialfv(GL_FRONT, GL_AMBIENT, back_white_shiny_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, back_white_shiny_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, back_white_shiny_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, back_white_shiny_mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, back_white_shiny_mat_emission);
}

void setRedPlasticMaterial(){
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red_plastic_mat_ambient);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red_plastic_mat_diffuse);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, red_plastic_mat_specular);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, red_plastic_mat_shininess);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, red_plastic_mat_emission);
	glMaterialfv(GL_FRONT, GL_AMBIENT, red_plastic_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red_plastic_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, red_plastic_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, red_plastic_mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, red_plastic_mat_emission);

	glMaterialfv(GL_BACK, GL_AMBIENT, back_red_plastic_mat_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, back_red_plastic_mat_diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, back_red_plastic_mat_specular);
	glMaterialfv(GL_BACK, GL_SHININESS, back_red_plastic_mat_shininess);
	glMaterialfv(GL_BACK, GL_EMISSION, back_red_plastic_mat_emission);
}
void setBrassMaterial(){
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, brass_mat_ambient);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brass_mat_diffuse);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, brass_mat_specular);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, brass_mat_shininess);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, brass_mat_emission);
	glMaterialfv(GL_FRONT, GL_AMBIENT, brass_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, brass_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, brass_mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, brass_mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, brass_mat_emission);

	glMaterialfv(GL_BACK, GL_AMBIENT, back_brass_mat_ambient);
	glMaterialfv(GL_BACK, GL_DIFFUSE, back_brass_mat_diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, back_brass_mat_specular);
	glMaterialfv(GL_BACK, GL_SHININESS, back_brass_mat_shininess);
	glMaterialfv(GL_BACK, GL_EMISSION, back_brass_mat_emission);
}
void drawModels() {
////setBrassMaterial();
//	//setWhiteShinyMaterial();
//	setRedPlasticMaterial();
//lrzs15.drawNoTransformationSmoothShading();
	setGreenShinyMaterial();
//	//setBrassMaterial();
	//setWhiteShinyMaterial();
	bunny.drawNoTransformationSmoothShading();
//
//	//setRedPlasticMaterial();
//	setRedShinyMaterial();
//	glPushMatrix();
//	glTranslatef(0.0,0,-0.5);
//	glTranslatef(0.25,0,0);
//	glRotatef(60.0,0,1,0);
//	glRotatef(-90.0,1,0,0);
//	horse.drawNoTransformationSmoothShading();
//	glPopMatrix();
////x_wing
//	setBlueShinyMaterial();
////
////setRevWhiteShinyMaterial();
//////
////setRevBlueShinyMaterial();
//
	setRevBlueShinyMaterial();
	glPushMatrix();
	glTranslatef(5.0,0.0,-3.0);
	glRotatef(45,0,1,0);
	glRotatef(135,1,0,0);
	bunny.drawNoTransformationSmoothShading();
	glPopMatrix();
////		setWhiteShinyMaterial();
////		head.drawNoTransformationSmoothShading();

}
void setLight1() {
	color[0] = 0.0,color[1] = 0.0,color[2] = 0.00,color[3] = 1.0;
	glLightfv(GL_LIGHT1, GL_AMBIENT, color );
	color[0] = 1.0,color[1] = 1.0,color[2] = 1.00,color[3] = 1.0;
	glLightfv(GL_LIGHT1, GL_DIFFUSE,color);
	color[0] = 1.0,color[1] = 1.0,color[2] = 1.0,color[3] = 1.0;
	glLightfv(GL_LIGHT1, GL_SPECULAR, color );
}
void renderScene(void) {
	int noOfPass = 0;
//	float zero[4];
	zero[0]=0.0,zero[1]=0.0,zero[2]=10.0,zero[3]=1.0;
//	float color[4] = {0.0f, 0.0f, 0.0f,0.2};

	//initial pass 1, just render as an opaque scene
	setLight1();
	glEnable(GL_LIGHTING);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	StoreLightMatrices();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	//glDrawBuffers(2, buffers);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glViewport(0,0,width,height);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadMatrixf(g_mProjection);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(g_mModelView);
	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glPolygonOffset(8.0f, 4.0f);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPushMatrix();
	glScalef(scale,scale,scale);// This guarantees the lights distance to zero is also scaled.
	glLightfv(GL_LIGHT1, GL_POSITION, zero);
	glPopMatrix();
	glRotated(xRot , 1.0, 0.0, 0.0);
	glRotated(yRot , 0.0, 1.0, 0.0);
	glRotated(zRot , 0.0, 0.0, 1.0);
	glScalef(scale,scale,scale);
	//we can use zoomin/zoomout instead scaling
	glEnable(GL_DEPTH_TEST);
	glUseProgramObjectARB(p);
	drawModels();
	glUseProgramObjectARB(NULL);
	glDisable(GL_POLYGON_OFFSET_FILL);
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	noOfPass++;

	while (noOfPass<maxPass) {
		// pass 2, 1st peel
		setLight1();
		glEnable(GL_LIGHTING);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_NORMALIZE);
		StoreLightMatrices();

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo2);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0,0,width,height);
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glEnable(GL_LIGHTING);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadMatrixf(g_mProjection);

			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(g_mModelView);
			glPolygonOffset(8.0f, 4.0f);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPushMatrix();
				glScalef(scale,scale,scale);// This guarantees the lights distance to zero is also scaled.
				glLightfv(GL_LIGHT1, GL_POSITION, zero);
			glPopMatrix();

			glActiveTextureARB(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);
			if ( noOfPass >= 2)
				glBindTexture(GL_TEXTURE_2D, depth4);
			else
				glBindTexture(GL_TEXTURE_2D, depth);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

			glUseProgramObjectARB(p2);

			loc1 = glGetUniformLocationARB(p2,"shadowMap");
			glUniform1iARB(loc1,0);

			glPushMatrix();
				glLoadIdentity();
				gluLookAt(eyex,eyey, eyez, lookatx,lookaty,lookatz, 0,1,0);
				glGetFloatv(GL_MODELVIEW_MATRIX, tmp);
				getInverseMatrix( tmp,g_mCameraInverse) ;
			glPopMatrix();

			glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			glLoadMatrixf(mBias);			// The bias matrix to convert to a 0 to 1 ratio
			glMultMatrixf(g_mProjection);	// The light's projection matrix
			glMultMatrixf(g_mModelView);	// The light's modelview matrix
			glMultMatrixf(g_mCameraInverse);
			glMatrixMode(GL_MODELVIEW);

			glRotated(xRot , 1.0, 0.0, 0.0);
			glRotated(yRot , 0.0, 1.0, 0.0);
			glRotated(zRot , 0.0, 0.0, 1.0);
			glScalef(scale,scale,scale);
			drawModels();
			glUseProgramObjectARB(NULL);

			glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);

			glActiveTextureARB(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);

			glDisable(GL_POLYGON_OFFSET_FILL);
			//glViewport(0,0,width,height);
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

		// pass 3, 1st mix
		setLight1();
		glEnable(GL_LIGHTING);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_NORMALIZE);
		StoreLightMatrices();

		glViewport(0,0,width,height);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo3);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		//glClear(GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glLoadIdentity();

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
				glLoadIdentity();
				glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
				glDisable(GL_LIGHTING);

				//glActiveTexture(0 );
				glActiveTexture(GL_TEXTURE0 );
				glDisable(GL_TEXTURE_1D);
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_3D);
				if ( noOfPass >= 2)
					glBindTexture(GL_TEXTURE_2D, img5);
				else
					glBindTexture(GL_TEXTURE_2D, img);
				glEnable(GL_TEXTURE_2D);

				glActiveTexture(GL_TEXTURE1 );
				//glActiveTexture(1 );
				glDisable(GL_TEXTURE_1D);
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_3D);
				glBindTexture(GL_TEXTURE_2D, img2);
				glEnable(GL_TEXTURE_2D);

				glDisable(GL_DEPTH_TEST);

				glUseProgramObjectARB(p3);

				loc1 = glGetUniformLocationARB(p3,"tex1");
				glUniform1iARB(loc1,0);

				loc2 = glGetUniformLocationARB(p3,"tex2");
				glUniform1iARB(loc2,1);

				//	frontAlpha = 0.3,backAlpha = 0.7;
				loc3 = glGetUniformLocationARB(p3,"frontAlpha");
				glUniform1fARB(loc3,frontAlpha);

				loc4 = glGetUniformLocationARB(p3,"backAlpha");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc4,backAlpha);

				loc5 = glGetUniformLocationARB(p3,"left");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc5,0.0);
				loc6 = glGetUniformLocationARB(p3,"right");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc6,1.0);
				loc7 = glGetUniformLocationARB(p3,"bottom");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc7,0.0);
				loc8 = glGetUniformLocationARB(p3,"top");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc8,1.0);
				loc9 = glGetUniformLocationARB(p3,"near");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc9,-1.0);
				loc10 = glGetUniformLocationARB(p3,"far");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc10,1.0);


				glEnable(GL_TEXTURE_2D);
				calllist(quadid);
				//glBegin(GL_QUAD);
				//glVertex3f(
				//glEnd();


				glUseProgramObjectARB(NULL);

				glActiveTexture(GL_TEXTURE0 );
				glDisable(GL_TEXTURE_2D);

				glActiveTexture(GL_TEXTURE1 );
				glDisable(GL_TEXTURE_2D);

			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

		noOfPass++;
		if (noOfPass>= maxPass)
			break;




		//pass 4 peel 2
		setLight1();
		glEnable(GL_LIGHTING);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_NORMALIZE);
		StoreLightMatrices();

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo4);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glViewport(0,0,width,height);
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadMatrixf(g_mProjection);

			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(g_mModelView);
			glPolygonOffset(8.0f, 4.0f);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPushMatrix();
				glScalef(scale,scale,scale);// This guarantees the lights distance to zero is also scaled.
				glLightfv(GL_LIGHT1, GL_POSITION, zero);
			glPopMatrix();

			glActiveTextureARB(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, depth2);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

			glUseProgramObjectARB(p2);

			loc1 = glGetUniformLocationARB(p2,"shadowMap");
			glUniform1iARB(loc1,0);

			glPushMatrix();
				glLoadIdentity();
				gluLookAt(eyex,eyey, eyez, lookatx,lookaty,lookatz, 0,1,0);
				glGetFloatv(GL_MODELVIEW_MATRIX, tmp);
				getInverseMatrix( tmp,g_mCameraInverse) ;
			glPopMatrix();

			glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			glLoadMatrixf(mBias);			// The bias matrix to convert to a 0 to 1 ratio
			glMultMatrixf(g_mProjection);	// The light's projection matrix
			glMultMatrixf(g_mModelView);	// The light's modelview matrix
			glMultMatrixf(g_mCameraInverse);
			glMatrixMode(GL_MODELVIEW);

			glRotated(xRot , 1.0, 0.0, 0.0);
			glRotated(yRot , 0.0, 1.0, 0.0);
			glRotated(zRot , 0.0, 0.0, 1.0);
			glScalef(scale,scale,scale);
			drawModels();
			glUseProgramObjectARB(NULL);

			glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);

			glActiveTextureARB(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);

			glDisable(GL_POLYGON_OFFSET_FILL);
			//glViewport(0,0,width,height);
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

		//pass 5 blend 2
		setLight1();
		glEnable(GL_LIGHTING);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_NORMALIZE);
		StoreLightMatrices();

		glViewport(0,0,width,height);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo5);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		//glClear(GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glLoadIdentity();

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
				glLoadIdentity();
				glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
				glDisable(GL_LIGHTING);

				//glActiveTexture(0 );
				glActiveTexture(GL_TEXTURE0 );
				glDisable(GL_TEXTURE_1D);
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_3D);
				glBindTexture(GL_TEXTURE_2D, img3);
				glEnable(GL_TEXTURE_2D);

				glActiveTexture(GL_TEXTURE1 );
				//glActiveTexture(1 );
				glDisable(GL_TEXTURE_1D);
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_3D);
				glBindTexture(GL_TEXTURE_2D, img4);
				glEnable(GL_TEXTURE_2D);

				glDisable(GL_DEPTH_TEST);

				glUseProgramObjectARB(p3);

				loc1 = glGetUniformLocationARB(p3,"tex1");
				glUniform1iARB(loc1,0);

				loc2 = glGetUniformLocationARB(p3,"tex2");
				glUniform1iARB(loc2,1);

				//	frontAlpha = 0.3,backAlpha = 0.7;
				loc3 = glGetUniformLocationARB(p3,"frontAlpha");
				glUniform1fARB(loc3,frontAlpha);

				loc4 = glGetUniformLocationARB(p3,"backAlpha");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc4,backAlpha);

				loc5 = glGetUniformLocationARB(p3,"left");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc5,0.0);
				loc6 = glGetUniformLocationARB(p3,"right");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc6,1.0);
				loc7 = glGetUniformLocationARB(p3,"bottom");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc7,0.0);
				loc8 = glGetUniformLocationARB(p3,"top");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc8,1.0);
				loc9 = glGetUniformLocationARB(p3,"near");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc9,-1.0);
				loc10 = glGetUniformLocationARB(p3,"far");
				//glUniform1iARB(loc1,depthUnit);
				glUniform1fARB(loc10,1.0);


				glEnable(GL_TEXTURE_2D);
				calllist(quadid);

				glUseProgramObjectARB(NULL);

				glActiveTexture(GL_TEXTURE0 );
				glDisable(GL_TEXTURE_2D);

				glActiveTexture(GL_TEXTURE1 );
				glDisable(GL_TEXTURE_2D);

			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		noOfPass++;
		if (noOfPass>= maxPass)
			break;

	}//end of while




	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

			glPushAttrib(GL_VIEWPORT_BIT);
			glDisable(GL_LIGHTING);

			glViewport(0, 0, width , height);

			glActiveTexture(GL_TEXTURE0 );
			glDisable(GL_TEXTURE_1D);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_TEXTURE_3D);
			glEnable(GL_TEXTURE_2D);

			if (noOfPass <= 1)
				glBindTexture(GL_TEXTURE_2D, img);
			else {
				if (noOfPass % 2 ==0)
					glBindTexture(GL_TEXTURE_2D, img3);
				else
					glBindTexture(GL_TEXTURE_2D, img5);
			}
			glEnable(GL_TEXTURE_2D);
			calllist(quadid);
			glActiveTexture(GL_TEXTURE0 );
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glPopAttrib();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	//show the mini maps
	glDisable(GL_DEPTH_TEST);
	//drawTexture();
	glEnable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'p':
	case 'P':
		peelOnly = !peelOnly;
		break;

	case 'l':
	case 'L':
		if (maxPass <10)
			maxPass  += 1;
		//else
		//	return;
		break;
	case 'k':
	case 'K':
		if (maxPass >=2 )
			maxPass  -= 1;
		//else
		//	return;
		break;
	case 'e':
	case 'E':
		xRot  += 2;
		break;
	case 'd':
	case 'D':
		yRot  += 2;
		break;

	case 'C':
	case 'c':
		zRot  += 2;
		break;

	case 'r':
	case 'R':
		xRot  -= 2;
		break;
	case 'f':
	case 'F':
		yRot  -= 2;
		break;

	case 'V':
	case 'v':
		zRot  -= 2;
		break;
	case 's':
	case 'S':
		scale *= 1.1;
		break;
	case 'a':
	case 'A':
		scale /= 1.1;
		break;
	}

	if (key == 27)
		exit(0);
	renderScene();
}


void setShaders() {
	char *vs = NULL,*fs = NULL;
	char *vs2 = NULL,*fs2 = NULL;
	char *vs3 = NULL,*fs3 = NULL;
	//char *vs4 = NULL,*fs4 = NULL;
	//char *vs5 = NULL,*fs5 = NULL;
	//char *vs6 = NULL,*fs6 = NULL;

	v = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	f = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	vs = textFileRead("/home/zhikai/Desktop/Bunny/Shaders/phong.vert");
	fs = textFileRead("/home/zhikai/Desktop/Bunny/Shaders/phong.frag");

	v2 = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	f2 = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	vs2 = textFileRead("peel1.vert");
	fs2 = textFileRead("peel1.frag");

	v3 = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	f3 = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	vs3 = textFileRead("orthoblend.vert");
	fs3 = textFileRead("orthoblend.frag");

	//v4 = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	//f4 = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	//vs4 = textFileRead("phong3.vert");
	//fs4 = textFileRead("phong3.frag");

	//v5 = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	//f5 = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	//vs5 = textFileRead("blend.vert");
	//fs5 = textFileRead("blend.frag");

	//v6 = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	//f6 = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	//vs6 = textFileRead("textest.vert");
	//fs6 = textFileRead("textest.frag");

	const char * ff = fs;
	const char * vv = vs;

	const char * ff2 = fs2;
	const char * vv2 = vs2;

	const char * ff3 = fs3;
	const char * vv3 = vs3;

	//const char * ff4 = fs4;
	//const char * vv4 = vs4;

	//const char * ff5 = fs5;
	//const char * vv5 = vs5;

	//const char * ff6 = fs6;
	//const char * vv6 = vs6;

	glShaderSourceARB(v, 1, &vv,NULL);
	glShaderSourceARB(f, 1, &ff,NULL);

	glShaderSourceARB(v2, 1, &vv2,NULL);
	glShaderSourceARB(f2, 1, &ff2,NULL);
	glShaderSourceARB(v3, 1, &vv3,NULL);
	glShaderSourceARB(f3, 1, &ff3,NULL);
	//glShaderSourceARB(v4, 1, &vv4,NULL);
	//glShaderSourceARB(f4, 1, &ff4,NULL);
	//glShaderSourceARB(v5, 1, &vv5,NULL);
	//glShaderSourceARB(f5, 1, &ff5,NULL);
	//glShaderSourceARB(v6, 1, &vv6,NULL);
	//glShaderSourceARB(f6, 1, &ff6,NULL);

	free(vs);free(fs);
	free(vs2);free(fs2);
	free(vs3);free(fs3);
	//free(vs4);free(fs4);
	//free(vs5);free(fs5);
	//free(vs6);free(fs6);

	glCompileShaderARB(v);
	glCompileShaderARB(f);

	glCompileShaderARB(v2);
	glCompileShaderARB(f2);

	glCompileShaderARB(v3);
	glCompileShaderARB(f3);

	//glCompileShaderARB(v4);
	//glCompileShaderARB(f4);

	//glCompileShaderARB(v5);
	//glCompileShaderARB(f5);
	//glCompileShaderARB(v6);
	//glCompileShaderARB(f6);

	p = glCreateProgramObjectARB();
	glAttachObjectARB(p,f);
	glAttachObjectARB(p,v);
	p2 = glCreateProgramObjectARB();
	glAttachObjectARB(p2,f2);
	glAttachObjectARB(p2,v2);
	p3 = glCreateProgramObjectARB();
	glAttachObjectARB(p3,f3);
	glAttachObjectARB(p3,v3);
	//p4 = glCreateProgramObjectARB();
	//glAttachObjectARB(p4,f4);
	//glAttachObjectARB(p4,v4);
	//p5 = glCreateProgramObjectARB();
	//glAttachObjectARB(p5,f5);
	//glAttachObjectARB(p5,v5);
	//p6 = glCreateProgramObjectARB();
	//glAttachObjectARB(p6,f6);
	//glAttachObjectARB(p6,v6);

	glLinkProgramARB(p);
	glLinkProgramARB(p2);
	glLinkProgramARB(p3);
	//glLinkProgramARB(p4);
	//glLinkProgramARB(p5);
	//glLinkProgramARB(p6);
}

void initall() {

	setShaders();//OK

	bunny.OBJ_SIZE = 3.0;
	bunny.initFromFile("/home/zhikai/Desktop/Bunny/Models/bunny.gts");

	//x_wing.gts
	//bunny.initFromFile("x_wing.gts");
	bunny.calculateScale();
	bunny.offSet();
	bunny.calculateTrianglesNormals();


//	bunny.OBJ_SIZE = 3.0;
//	bunny.initFromFile("bunny.gts");
//	bunny.calculateScale();
//	bunny.offSet();
//	bunny.calculateTrianglesNormals();
//
//
//	horse.OBJ_SIZE = 4.5;
//	horse.initFromFile("horse.gts");
//	horse.calculateScale();
//	horse.offSet();
//	horse.calculateTrianglesNormals();
////x_wing.gts
//
//	x_wing.OBJ_SIZE = 12.0;
//	x_wing.initFromFile("x_wing.gts");
//	x_wing.calculateScale();
//	x_wing.offSet();
//	x_wing.calculateTrianglesNormals();
//
//
//
//	lrzs15.OBJ_SIZE = 3.0;
//	lrzs15.initFromFile("lrzs15.gts");
//	lrzs15.calculateScale();
//	lrzs15.offSet();
//	lrzs15.calculateTrianglesNormals();
//
//
//	head.OBJ_SIZE = 5.0;
//	head.initFromFile("head.gts");
//	head.calculateScale();
//	head.offSet();
//	head.calculateTrianglesNormals();
//
//	//bun2ny.OBJ_SIZE = 2.5;
//	//bun2ny.initFromFile("bunny.gts");
//	//bun2ny.calculateTrianglesNormals();
//
//	//orthoganal_clip_size2 = orthoganal_clip_size	= 5.0;
//	//eyex = 0 ,eyey= 0 ,eyez = 4.0;
//	//lookatx =0,lookaty =0,lookatz=0;
//	//NEAR_Z	=		3;
//	//FAR_Z	=		6.0;

	glClearColor (1.0, 1.0, 1.0, 0.0);

	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);

	//width = 512;
	//height = 512;



	initFBOnTEX();
	depthUnit  = 0;
	//GLuint quadid;
	newList(quadid);
	drawQuad(1.0f);
	endList();
}
void idleFunc() {
	zRot +=2.0;
	renderScene();
}
int main(int argc, char **argv) {
	/*
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("MM 2004-05");

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0,1.0,1.0,1.0);
	//glEnable(GL_CULL_FACE);

	glewInit();
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
	printf("Ready for GLSL\n");
	else {
	printf("No GLSL support\n");
	exit(1);
	}
	//glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
	printf("Ready for OpenGL 2.0\n");
	else {
	printf("OpenGL 2.0 not supported\n");
	exit(1);
	}
	setShaders();

	glutMainLoop();

	// just for compatibiliy purposes
	return 0;
	*/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(width,height); //OK
	glutCreateWindow("Bunny without QT");

	glutDisplayFunc(renderScene);//OK
	//glutIdleFunc(renderScene);
	//glutIdleFunc(idleFunc);
	glutReshapeFunc(changeSize);//OK
	glutKeyboardFunc(processNormalKeys);

	glewInit();
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		printf("Ready for GLSL\n");
	else {
		printf("No GLSL support\n");
		exit(1);
	}
	//glewInit();
	if (glewIsSupported("GL_VERSION_2_0"))
		printf("Ready for OpenGL 2.0\n");
	else {
		printf("OpenGL 2.0 not supported\n");
		exit(1);
	}
	//setShaders();

	initall();// OK



	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0,1.0,1.0,0.0);
	//glEnable(GL_CULL_FACE);

	//changeSize(width, height);

	glutMainLoop();

	// just for compatibiliy purposes
	return 0;
}

/*
Compilation and Installation Instructions for OpenGL

A. Your account on the Windows PCs in the Software Engineering Lab:
When you first log in, you may encounter several pop-up dialog windows giving error/warning messages. Ignore them by pressing "OK" or "Yes". You should be able to log in successfully. After the first time, you should be able to log in normally. Once you log on, look at the H: drive for your home directory. Note that you have a write permission only to your home directory .

B. Compilation Steps for Visual C++ (VC++) 2008 (similarly for other versions):

Start VC++ from the start menu.
File -> New a project with template Win32 Console Application (note: not Win32 Project), give a project name. In the next pop-up window, click Application Settings. In the yet next pop-up window, choose Empty project (so that the two items chosen are Console application and Empty project), and click Finish. A new folder with the project name is created (if you want to use an existing folder which contains all source (.c or .cpp) files, in the first pop-up window give this folder name as the "Name" and its parent folder location as the "Location").
If you want to open an existing project, instead of New use Open -> Project/Solution.
Move all source (.c or .cpp) files, header (.h) files, and input data files to the project folder (either the new folder created in Step 2 or the existing folder mentioned at the end of Step 2).
In the left sub-window of VC++, right click Source Files and select Add -> Existing Item to include the source (.c or .cpp) files, one by one, into the project as source files. Similarly include the .h files (if any) as Header Files. (For shader files *.glsl, you can include them as Resource Files in the same way.)
Sometimes it is necessary to declare the dependencies for the libraries used:
a. Click on Project -> [project name] Properties.
b. In the left window, click Configuration Properties to expand it. On the very top left, the Configuration drop-down, select All Configurations.
c. Below Configuration Properties, select Linker -> Input.
d. In the right window, click Additional Dependencies to activate this field. Type in
"glew32.lib glut32.lib opengl32.lib glu32.lib". Then click OK.

Typically these *.lib files can be automatically found except for "glew32.lib". Thus, for OpenGL projects that use GLEW (such as those involving GLSL) you only need to specify "glew32.lib" here; for other OpenGL projects you don't need to specify anything (except when the needed *.lib files cannot be automatically found during linking).

To compile, click on Build -> Build [project name] (or Rebuild [project name]).
To run, click on Debug -> Start Without Debugging (or Ctrl+F5).

Note: All VC++ programs using OpenGL functions must start with #include <windows.h> followed by #include <GL/glut.h> in the source code. If you use GLEW functions, put #include <GL/glew.h> before #include <GL/glut.h>. Also, if you need to include "stdlib.h", put #include <stdlib.h> before #include <GL/glut.h>. In summary, put them in this order: #include <windows.h> then #include <stdlib.h> then #include <GL/glew.h> then #include <GL/glut.h>.
C. Installation on your own PC by yourself:
You need to have the VC++ software installed (there is a free download version, VC++ 2008 Express Edition, available at this site ). You may also need to install the Microsoft Windows SDK package (e.g., Windows SDK for Windows Server 2008 and .NET Framework 3.5, freely available at this site ). You need to get the GLUT package (available from the course web site "http://cis.poly.edu/cs653/glut-3.7.6-bin.zip" ) and the GLEW package (available from the course web site "http://cis.poly.edu/cs653/glew-1.5.1-win32.zip" ). After unzipping the GLUT and GLEW packages, put the following files to the specified folders as below:

1. glut.h, glew.h, wglew.h: to the "include/gl" folder of either VC++ or SDK (e.g., "C:\Program Files\Microsoft SDKs\Windows\v6.1\Include\gl", or "C:\Program Files\Microsoft Visual Studio 8\VC\include\gl\"), where the OpenGL header files "gl.h" and "glu.h" should already be there.

2. glut32.lib, glew32.lib: to the "Lib" folder of either VC++ or SDK (e.g., "C:\Program Files\Microsoft SDKs\Windows\v6.1\Lib" or "C:\Program Files\Microsoft Visual Studio 8\VC\lib"), where the OpenGL library files "opengl32.lib" and "glu32.lib" should already be there.

3. glut32.dll, glew32.dll: to the systems folder (e.g., "C:\Windows\System32" for a 32-bit OS, or "C:\Windows\SysWOW64" for a 64-bit OS), where the OpenGL .DLL files "opengl32.dll" and "glu32.dll" should already be there.
*/


/*
#include <iostream>
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
*/
