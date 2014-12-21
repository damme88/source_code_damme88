#include "StdAfx.h"
#include "House.h"


House::House(void)
{
	length_ = 0.0;
	width_ = 0.0;
	height_ = 0.0;
}

House::House(double lg, double wd, double hg) 
{
	length_ = lg;
	width_ = wd;
	height_ = hg;
}

House::~House(void)
{
}

void House::MakeHouse() 
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_);

	float x = length_/2.0;
	float y = width_/2.0;
	float z = height_/2.0;
	// back face
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);  
	glVertex3f(-x, y, z);    // 1
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, -y, z);    // 2
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-x, -y, -z);   // 3
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-x, y, -z);    // 4
	glEnd();

	//// bottom face
	//glBegin(GL_QUADS);
	//glNormal3f(-1.0, 0.0, 0.0);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-x, y, -z);   // 4
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(-x, -y, -z);  // 3 
	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(x, -y, -z);  // 6
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(x, y, -z);   // 5 
	//glEnd();

	// right face
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, y, z);   //1
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y, z);  //  8
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y, -z);    // 5
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-x, y, -z);    // 4
	glEnd();

	// front face
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y, z);   //8
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, -y, z);  //  7
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, -y, -z);    // 6
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, -z);     // 5
	glEnd();

	// left face
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, -y, -z);    //6
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, -y, z);      // 7
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-x, -y, z);    //2
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-x, -y, -z);  //  3
	glEnd();

	//top face
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	//glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, -y, z);     //2
	//glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, -y, z);			 //7
	//glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y, z);			 //8
	//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-x, y, z);    //1
	glEnd();

	glDisable(GL_TEXTURE_2D);
}