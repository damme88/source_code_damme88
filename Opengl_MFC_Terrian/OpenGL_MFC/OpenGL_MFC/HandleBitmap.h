#ifndef HANDLE_IMAGE_H_
#define HANDLE_IMAGE_H_

#include <iostream>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <Windows.h>
#include "Resource.h"

unsigned char* LoadBitmapFile(char * file_name, BITMAPINFOHEADER* bitmap_info_header) {
  FILE * file_ptr;
  BITMAPFILEHEADER bitmap_file_header;
  unsigned char *bitmap_image = NULL;
  int image_index = 0;
  unsigned char temp_rgb;

  file_ptr = fopen(file_name, "rb");
  if (file_ptr == NULL)
    return NULL;

  fread(&bitmap_file_header, sizeof(BITMAPFILEHEADER), 1, file_ptr);
  if (bitmap_file_header.bfType != BITMAP_ID) {
    fclose(file_ptr);
    return NULL;
  }
  // read the bitmap infomation header
  fread(bitmap_info_header, sizeof(BITMAPINFOHEADER), 1, file_ptr);
  // move file pointer to beginning of bitmap data
  fseek(file_ptr, bitmap_file_header.bfOffBits, SEEK_SET);
  
  // allocate enough memory for the bitmap image data
  bitmap_image = (unsigned char*)malloc(bitmap_info_header->biSizeImage);

  if (!bitmap_image) {
    free (bitmap_image);
    fclose  (file_ptr);
    return NULL;
  }

  // read in the bitmap image data
  fread(bitmap_image, 1, bitmap_info_header->biSizeImage, file_ptr);
  if (bitmap_image == NULL) {
    fclose(file_ptr);
    return NULL;
  }

  // Get color
  for (image_index = 0; image_index < bitmap_info_header->biSizeImage; image_index += 3) {
    temp_rgb = bitmap_image[image_index];
    bitmap_image[image_index] = bitmap_image[image_index + 2];
    bitmap_image[image_index + 2] = temp_rgb;
  }

  fclose(file_ptr);
  return bitmap_image;
}

#endif // HANDLE_IMAEE_