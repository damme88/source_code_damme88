
#include "stdafx.h";
#include "Surface.h"


Surface::Surface() {
	length_ = 0.0;
	width_ = 0.0;
	height_ = 0.0;
	depth_ = 0.0;
}

Surface::Surface(double length, double width, double height, double depth) 
: length_(length),
  width_(width),
	height_(height),
	depth_(depth)
{
	;
}

Surface::~Surface() {
	;
}

void Surface::MakeSurface() {
	if (length_ == 0 && width_ == 0) {
		AfxMessageBox(_T("Can not make Surface. Length and with = 0"));
		return;
	}
	glColor3f(0.8f, 0.8f, 0.8f);
	DrawRectangleBox(length_, width_, depth_, 1);  // Bottom face

	glPushMatrix();  // left wall
	glTranslatef(0.0f, -1*(width_/2), (height_/2) - depth_/2.0f);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	DrawRectangleBox(length_, height_, depth_, 1);
	glPopMatrix();

	glPushMatrix();    // right wall
	glTranslatef(0.0f, width_/2, (height_/2) - depth_/2.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	DrawRectangleBox(length_, height_, depth_, 1);
	glPopMatrix();

	glPushMatrix();    // Back wall
	glTranslatef(-1*(length_/2), 0.0, (height_/2) - depth_/2.0f);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	DrawRectangleBox(height_, width_ + depth_, depth_, 1);
	glPopMatrix();


	glPushMatrix();    // Front wall
	glTranslatef((length_/2), 0.0, (height_/2) - depth_/2.0f);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	DrawRectangleBox(height_, width_ + depth_, depth_, 1);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void DrawRectangleBox(float width, float height, float depth, char solid) {
	char i, j = 0;
	float x = width / 2.0, y = height / 2.0, z = depth / 2.0;
	for (i = 0; i < 4; i++) {
		glRotatef(90.0, 0.0, 0.0, 1.0);
		if (j) {
			if (!solid)
				glBegin(GL_LINE_LOOP);
			else
				glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-x, y, z);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-x, -y, z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-x, -y, -z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-x, y, -z);
			glEnd();
			if (solid) {
				glBegin(GL_TRIANGLES);
				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(0.0, 0.0, z);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-x, y, z);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-x, -y, z);
				glNormal3f(0.0, 0.0, -1.0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(0.0, 0.0, -z);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-x, -y, -z);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-x, y, -z);
				glEnd();
			}
			j = 0;
		} else {
			if (!solid)
				glBegin(GL_LINE_LOOP);
			else
				glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-y, x, z);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-y, -x, z);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-y, -x, -z);
			glTexCoord2f(01.0f, 0.0f);
			glVertex3f(-y, x, -z);
			glEnd();
			if (solid) {
				glBegin(GL_TRIANGLES);
				glNormal3f(0.0, 0.0, 1.0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(0.0, 0.0, z);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-y, x, z);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-y, -x, z);
				glNormal3f(0.0, 0.0, -1.0);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(0.0, 0.0, -z);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-y, -x, -z);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-y, x, -z);
				glEnd();
			}
			j = 1;
		}
	}
}
