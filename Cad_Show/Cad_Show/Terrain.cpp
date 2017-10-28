
#include "stdafx.h"
#include "Terrain.h"

const float FALLOUT_RATIO = 0.5f;
Terrain::Terrain(int w2, int l2)
{
  width_ = w2;
  length_ = l2;
  height_ = new float*[length_];
  for(int i = 0; i < length_; i++) 
  {
    height_[i] = new float[width_];
  }

  v_normal_ = new Vector3d*[length_];
  for(int i = 0; i < length_; i++) 
  {
    v_normal_[i] = new Vector3d[width_];
  }
  is_compute_normal_ = false;
}

Terrain::~Terrain()
{
  for(int i = 0; i < length_; i++) {
    delete[] height_[i];
  }
  delete[] height_;

  for(int i = 0; i < length_; i++) {
    delete[] v_normal_[i];
  }
  delete[] v_normal_;
}

void Terrain::ComputeNormals()
{
  if (is_compute_normal_) {
    return;
  }

  //Compute the rough version of the normals
  Vector3d** normals2 = new Vector3d*[length_];
  for(int i = 0; i < length_; i++) {
    normals2[i] = new Vector3d[width_];
  }

  for(int z = 0; z < length_; z++) {
    for(int x = 0; x < width_; x++) {
      Vector3d sum(0.0f, 0.0f, 0.0f);

      Vector3d out;
      if (z > 0) {
        out = Vector3d(0.0f, height_[z - 1][x] - height_[z][x], -1.0f);
      }
      Vector3d in;
      if (z < length_ - 1) {
        in = Vector3d(0.0f, height_[z + 1][x] - height_[z][x], 1.0f);
      }
      Vector3d left;
      if (x > 0) {
        left = Vector3d(-1.0f, height_[z][x - 1] - height_[z][x], 0.0f);
      }
      Vector3d right;
      if (x < width_ - 1) {
        right = Vector3d(1.0f, height_[z][x + 1] - height_[z][x], 0.0f);
      }

      if (x > 0 && z > 0) {
        sum += out.cross(left).normalize();
      }
      if (x > 0 && z < length_ - 1) {
        sum += left.cross(in).normalize();
      }
      if (x < width_ - 1 && z < length_ - 1) {
        sum += in.cross(right).normalize();
      }
      if (x < width_ - 1 && z > 0) {
        sum += right.cross(out).normalize();
      }

      normals2[z][x] = sum;
    }
  }

  //Smooth out the normals
  const float FALLOUT_RATIO = 0.5f;
  for(int z = 0; z < length_; z++) {
    for(int x = 0; x < width_; x++) {
      Vector3d sum = normals2[z][x];

      if (x > 0) {
        sum += normals2[z][x - 1] * FALLOUT_RATIO;
      }
      if (x < width_ - 1) {
        sum += normals2[z][x + 1] * FALLOUT_RATIO;
      }
      if (z > 0) {
        sum += normals2[z - 1][x] * FALLOUT_RATIO;
      }
      if (z < length_ - 1) {
        sum += normals2[z + 1][x] * FALLOUT_RATIO;
      }

      if (sum.magnitude() == 0) {
        sum = Vector3d(0.0f, 1.0f, 0.0f);
      }
      v_normal_[z][x] = sum;
    }
  }

  for(int i = 0; i < length_; i++) {
    delete[] normals2[i];
  }
  delete[] normals2;

  is_compute_normal_ = true;
}

void Terrain::set_height(int x, int z, float y)
{
  height_[z][x] = y;
  is_compute_normal_ = false;
}

float Terrain::get_height(int x_post, int z_post)
{
  return height_[z_post][x_post];
}

Vector3d Terrain::get_normal(int x, int z)
{
  if (!is_compute_normal_) {
    ComputeNormals();
  }
  return v_normal_[z][x];
}

Terrain* LoadTerrain(const char* file_name, float height)
{
  Image* image = loadBMP(file_name);
  Terrain* t = new Terrain(image->width, image->height);
  for(int y = 0; y < image->height; y++) 
  {
    for(int x = 0; x < image->width; x++) 
    {
      int index = 3 * (y * image->width + x);
      unsigned char color = (unsigned char)image->pixels[index];
      float h = height * ((color / 255.0f) - 0.5f);
      t->set_height(x, y, h);
    }
  }

  delete image;
  t->ComputeNormals();
  return t;
}
