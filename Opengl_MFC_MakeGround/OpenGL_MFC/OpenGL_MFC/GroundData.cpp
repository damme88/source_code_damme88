

#include "stdafx.h"
#include "GroundData.h"

Ground3D::Ground3D() :
length_(0.0),
width_(0.0),
height_(0.0),
thickness_(0.0),
color_(0.0)
{
	;
}

Ground3D::Ground3D(double length, double width, double height, double thickness)
	: length_(length),
	  width_(width),
		height_(height),
		thickness_(thickness)
{
	;
}

Ground3D::~Ground3D()
{

}

BOOL Ground3D::MakeGround3D() 
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_);

	glColor3f(0.0f, 1.0f, 1.0f);
	DrawRectangleBox(length_, width_, thickness_);  // Bottom face

	glPushMatrix();  // left wall
	glTranslatef(0.0f, -1*(width_/2), (height_/2) - thickness_/2.0f);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	DrawRectangleBox(length_, height_, thickness_);
	glPopMatrix();

	glPushMatrix();    // right wall
	glTranslatef(0.0f, width_/2, (height_/2) - thickness_/2.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	DrawRectangleBox(length_, height_, thickness_);
	glPopMatrix();

	glPushMatrix();    // Back wall
	glTranslatef(-1*(length_/2), 0.0, (height_/2) - thickness_/2.0f);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	DrawRectangleBox(height_, width_ + thickness_, thickness_);
	glPopMatrix();

	glPushMatrix();    // Front wall
	glTranslatef((length_/2), 0.0, (height_/2) - thickness_/2.0f);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	DrawRectangleBox(height_, width_ + thickness_, thickness_);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	return true;
}

void Ground3D::DrawRectangleBox(float length, float width, float height, bool solid /*= true */) {
	float x = length / 2.0;
	float y = width / 2.0;
	float z = height / 2.0;
	if (!solid)
		glBegin(GL_LINE_LOOP);
	else {
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

		// bottom face
		glBegin(GL_QUADS);
		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-x, y, -z);   // 4
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-x, -y, -z);  // 3 
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x, -y, -z);  // 6
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x, y, -z);   // 5 
		glEnd();

		// right face
		glBegin(GL_QUADS);
		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-x, y, z);   //1
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x, y, z);  //  7
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x, y, -z);    // 5
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-x, y, -z);    // 4
		glEnd();

		// front face
		glBegin(GL_QUADS);
		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x, y, z);   //7
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x, -y, z);  //  8
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x, -y, -z);    // 6
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x, y, -z);     // 5
		glEnd();

		// right face
		glBegin(GL_QUADS);
		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x, -y, -z);    //6
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x, -y, z);      // 8
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-x, -y, z);    //2
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-x, -y, -z);  //  3
		glEnd();

		// top face
		glBegin(GL_QUADS);
		glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-x, -y, z);     //2
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x, -y, z);   //  8
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x, y, z);    //7
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-x, y, -z);     // 4
		glEnd();
	}
}
