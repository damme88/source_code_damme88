
#ifndef GROUND_DATA_H_
#define GROUND_DATA_H_

class Ground3D 
{
public:
	Ground3D();
	~Ground3D();
	Ground3D(double length, double width, double height, double thickness);
	BOOL MakeGround3D();
	void SetLength(double l) {length_ = l;}
	double GetLength() const {return length_;}
	void SetWidth(double w) {width_ = w;}
	double GetWidh() const {return width_;}
	void SetHeight(double h) {height_ = h;}
	double GetHeight() const {return height_;}
	void SetThickness(double tk) {thickness_ = tk;}
	double GetThickness() const {return thickness_;}
	void SetColor(double color) {color_ = color;}
	double GetColor() const {return color_;}
	void SetTextureData(GLuint tt) {texture_ = tt;} 
protected:
	void DrawRectangleBox(float width, float height, float depth, bool  is_solid = true);
private:
	double length_;
	double width_;
	double height_;
	double thickness_;
	double color_;
	GLuint texture_;
};

#endif  // GROUND_DATA_H_