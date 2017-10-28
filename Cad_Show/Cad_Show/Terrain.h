
#ifndef TERRAIN_H_
#define TERRAIN_H_
#include "Vector3d.h"
#include "ImageProcess.h"

class  Terrain
{
private:
  int width_;
  int length_;
  float** height_;
  Vector3d** v_normal_;
  bool is_compute_normal_;

public:
  Terrain(int w2, int l2);
  ~Terrain();
  int get_width() const {return width_;}
  int get_length() const {return length_;}
  void set_height(int x, int z, float y);
  float get_height(int x_post, int z_post);
  void ComputeNormals();
  Vector3d get_normal(int x, int z);
};

Terrain* LoadTerrain(const char* file_name, float height);
#endif