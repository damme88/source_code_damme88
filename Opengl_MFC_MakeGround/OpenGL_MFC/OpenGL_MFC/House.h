#pragma once
class House
{
public:
	House(void);
	House(double lg, double wd, double hg);
	~House(void);
	double GetLength() const {return length_;}
	double GetWidth() const {return width_;}
	double GetHeigh() const {return height_;}
	void SetTexture(GLuint tx) {texture_ = tx;}
	void MakeHouse();
private:
	double length_;
	double width_;
	double height_;
	GLuint texture_;
};

