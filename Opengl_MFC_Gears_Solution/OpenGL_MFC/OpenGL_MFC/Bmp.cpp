#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstring>    // use memcpy

#include "Bmp.h"

using std::ifstream;
using std::ofstream;
using std::ios;
using std::cout;
using std::endl;
using namespace Image; 

Bmp::Bmp() :
  width_(0),
  height_(0),
  bit_count_(0),
  data_size_(0),
  pdata_(NULL),
  pdata_rgb_(NULL),
  error_message_("no error")
{

}

Bmp::Bmp(const Bmp &rhs) {
  width_ = rhs.GetWidth();
  height_ = rhs.GetHeight();
  bit_count_ = rhs.GetBitCount();
  data_size_ = rhs.GetDataSize();
  error_message_ = rhs.GetError();
  if (rhs.GetData() != NULL) {
    pdata_ = new unsigned char [data_size_];
    memcpy(pdata_, rhs.GetData(), data_size_);  // copy data form rhs to pdata
  } else {
    pdata_ = NULL;
  }

  if (rhs.GetDataRGB() != NULL) {
    pdata_rgb_ = new unsigned char [data_size_];
    memcpy(pdata_rgb_, rhs.GetDataRGB(), data_size_);
  } else {
    pdata_rgb_ = NULL;
  }
}


Bmp::~Bmp() {
  if (pdata_ != NULL) {
    delete [] pdata_;
    pdata_= NULL;
  }
  if (pdata_rgb_ != NULL) {
    delete [] pdata_rgb_;
    pdata_rgb_ = NULL;
  }
}

// define operator = for 2 object of Bmp
Bmp& Bmp::operator= (const Bmp& rhs) {
  if (this == &rhs)  // avoid slef assignment a = a;
    return *this;
  // copy member variable;
  width_ = rhs.GetWidth();
  height_ = rhs.GetHeight();
  bit_count_ = rhs.GetBitCount();
  data_size_ = rhs.GetDataSize();
  error_message_ = rhs.GetError();

  if (rhs.GetData() != NULL) {
    pdata_ = new unsigned char [data_size_];
    memcpy(pdata_, rhs.GetData(), data_size_);
  } else {
    pdata_ = NULL;
  }

  if (rhs.GetDataRGB() != NULL) {
    pdata_rgb_ = new unsigned char [data_size_];
    memcpy(pdata_rgb_, rhs.GetDataRGB(), data_size_);
  } else {
    pdata_rgb_ = NULL;
  }
  return *this;
}

// define other member functions

void Bmp::Init() {
  width_ = 0;
  height_= 0;
  bit_count_ = 0;
  data_size_ = 0;
  error_message_ = ("no error");
  delete [] pdata_;
  pdata_ = NULL;
  delete []pdata_rgb_;
  pdata_rgb_ = NULL;
}

void Bmp::PrintSelf()const {
  cout <<"_______ Bmp_______\n"
       << "Width: "<< width_ << "pixels\n"
       << "Height: "<< height_<< "pixels\n"
       << "Bit count : " << bit_count_ << "bits\n"
       << "Data Size : "<< data_size_ << "bytes\n"
       << endl;
}


bool Bmp::Read(const char* file_name) {
  this->Init();
  if (!file_name) {  // check invalidation of file_name
    error_message_ == "file_name is not define";
    return false;
  }

  // open Bitmap file as binary mode
  ifstream in_file;
  in_file.open(file_name, ios::binary); 
  if (!in_file.good()) {
    error_message_  = "Failed to open a BMP file to read";
    return false;
  }

  // list variable for entires in header of bitmap 
  char id[2];
  int file_size   = 0;
  short reserved1 = 0;
  short reserved2 = 0;
  int data_offset = 0;
  int width       = 0;
  int height      = 0;
  short bit_count = 0;
  int compression = 0;
  int info_header_size = 0;
  short plane_count    = 0;
  int data_size_width_paddings = 0.0;
  
  in_file.read(id, 2);                        // get "BM" for id
  in_file.read((char*)&file_size, 4);         // should be same as file size
  in_file.read((char*)&reserved1, 2);         // must be 0
  in_file.read((char*)&reserved2, 2);         // must be 0
  in_file.read((char*)&data_offset, 4);
  in_file.read((char*)&info_header_size, 4);  // get size of header (must be 40)
  in_file.read((char*)&width, 4);
  in_file.read((char*)&height, 4);
  in_file.read((char*)&plane_count, 2);       // must be 1
  in_file.read((char*)&bit_count, 2);         // could be 1, 4, 8, 24, 32 bit
  in_file.read((char*)&compression, 4);       // 0 (uncompressed)
                                              // 1(8 bit RLE) 
                                              // 2(4 bit RLE)
                                              // 32 (RGB with mask)
  in_file.read((char*)&data_size_width_paddings, 4);

  // then get data header of BMP so implementing check them
  if (id[0] != 'B' || id[1] != 'M') {
    in_file.close();
    error_message_ = "magic id is invalid";
    return false;
  }

  if (bit_count < 8) {
    in_file.close();
    error_message_ = "unsupported format";
    return false;
  }

  if (compression > 1) {
    in_file.close();
    error_message_ = "Unsuppoted compression mode";
    return false;
  }

  // do not belive the file size in header, recalculate it
  in_file.seekg(0, ios::end);
  file_size = in_file.tellg();

  // compute the number of paddings
  // In BMP, each scanline must be divisible evenly by 4.
  // If not divisible by 4, then each line adds
  // extra paddings. So it can be divided evenly by 4.
  int paddings = (4 - ((width * bit_count / 8) % 4)) % 4;

  // compute data size without paddings
  int dataSize = width * height * bit_count / 8;
  data_size_width_paddings = file_size - data_offset; 

  // get data of bitmap 
  this->width_ = width;
  this->height_ = height;
  this->bit_count_ = bit_count;
  this->data_size_ = dataSize;

  pdata_ = new unsigned char [data_size_width_paddings];
  pdata_rgb_ = new unsigned char [dataSize];

  if(compression == 0) {
    in_file.seekg(data_offset, ios::beg); 
    in_file.read((char*)pdata_, data_size_width_paddings);
  } else if(compression == 1) {
    // get length of encoded data
    int size = file_size - data_offset;

    // allocate tmp array to store the encoded data
    unsigned char *encData = new unsigned char[size];

    // read data from file
    in_file.seekg(data_offset, ios::beg);
    in_file.read((char*)encData, size);

    // decode RLE into image data buffer
    DecodeRLE8(encData, pdata_);

    // deallocate encoded data buffer after decoding
    delete [] encData;
  }

  // close it after reading
  in_file.close();

  if(compression == 0 && paddings > 0) {
    int lineWidth = width * bit_count / 8;

    // copy line by line
    for(int i = 1; i < height; ++i)
    {
        memcpy(&pdata_[i*lineWidth], &pdata_[i*(lineWidth+paddings)], lineWidth);
    }
  }
  if(height > 0)
      FlipImage(pdata_, width, height, bit_count/8);
  memcpy(pdata_rgb_, pdata_, dataSize);    // copy data to dataRGB first
  if(bit_count == 24 || bit_count == 32)
      SwapRedBlue(pdata_rgb_, dataSize, bit_count/8);
  return true;
}

bool Bmp::Save(const char* fileName, int w, int h, int channelCount, const unsigned char* data)
{
  return true;
}

bool Bmp::DecodeRLE8(const unsigned char *encData, unsigned char *outData)
{
  return true;
}

void Bmp::FlipImage(unsigned char *data, int width, int height, int channelCount)
{
    if(!data) return;

    int lineSize = width * channelCount;
    unsigned char* tmp = new unsigned char [lineSize];
    int half = height / 2;

    int line1 = 0;                          // first line
    int line2 = (height - 1) * lineSize;    // last line

    // scan only half of height
    for(int i = 0; i < half; ++i)
    {
        // copy line by line
        memcpy(tmp, &data[line1], lineSize);
        memcpy(&data[line1], &data[line2], lineSize);
        memcpy(&data[line2], tmp, lineSize);

        // move to next line
        line1 += lineSize;
        line2 -= lineSize;
    }

    // deallocate temp arrays
    delete [] tmp;
}

void Bmp::SwapRedBlue(unsigned char *data, int dataSize, int channelCount)
{
    if(!data) return;
    if(channelCount < 3) return;            // must be 3 or 4
    if(dataSize % channelCount) return;     // must be divisible by the number of channels

    unsigned char tmp;
    int i;

    // swap the position of red and blue components
    for(i=0; i < dataSize; i+=channelCount)
    {
        tmp = data[i];
        data[i] = data[i+2];
        data[i+2] = tmp;
    }
}

int Bmp::GetColorCount(const unsigned char* data, int dataSize) {
  return 0;
}

void Bmp::BuildGrayScalePalette(unsigned char* palette, int paletteSize) {
}