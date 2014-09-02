
#ifndef CUBE_OBJ_H_
#define CUBE_OBJ_H_
class CubeObj {
public:
	CubeObj();
	CubeObj(double edge, double xPos, double yPos, double zPos);
	~CubeObj();
	void SetEdge(double edge) {edge_ = edge;}
	void SetPos (double xPos, double yPos, double zPos);
	double GetXpos()const {return xPos_;}
	double GetYpos()const {return yPos_;}
	double GetZpos() const {return zPos_;}
	double GetEdge() const {return edge_;}
	void MakeCubeObj();
protected:
  double edge_;
	double xPos_;
	double yPos_;
	double zPos_;
};

#endif  // CUBE_OBJ_H_