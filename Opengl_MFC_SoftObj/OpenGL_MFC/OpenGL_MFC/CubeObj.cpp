

#include "stdafx.h"
#include "CubeObj.h"

CubeObj::CubeObj() {
	edge_ = 0.0;
	xPos_ = 0.0;
	yPos_ = 0.0;
	zPos_ = 0.0;
}

CubeObj::CubeObj(double edge, double xPos, double yPos, double zPos) {
	xPos_ = xPos,
	yPos_ = yPos_,
	zPos_ = zPos,
	edge_ = edge;
}

CubeObj::~CubeObj() {

}

void CubeObj::SetPos(double xPos, double yPos, double zPos) {
	xPos_ = xPos;
	yPos_ = yPos;
	zPos_ = zPos;
}

void CubeObj::MakeCubeObj() {
	if (edge_ == 0)
	{
		AfxMessageBox(_T("Can not make cube with edge = 0.0"));
	}
	glPushMatrix();
	glTranslatef(xPos_, yPos_, zPos_);
	glutSolidCube(edge_);
	glPopMatrix();
}