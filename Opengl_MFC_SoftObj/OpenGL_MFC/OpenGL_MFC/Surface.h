
#ifndef SURFACE_H_
#define SURFACE_H_

class Surface {
public:
	Surface();
	Surface(double length, double width, double height, double depth);
	~Surface();
	void SetLength(double length) {length_ = length;}
	void SetWidth(double width) {width_ = width;}
	void SetHegith(double height) {height_ = height;}
	void SetDepth(double depth) {depth_ = depth;}
	double GetLength() const {return length_;}
	double GetWidth() const {return width_;}
	double GetHeight() const {return height_;}
	double GetDepth() const {return depth_;}
	void MakeSurface();
protected:
	double length_;
	double width_;
	double height_;
	double depth_;
};

void DrawRectangleBox(float width, float height, float depth, char solid);
#endif  // SURFACE_H_