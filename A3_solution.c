/* FILE: A3_solutions.c is where you will code your answers for Assignment 3.
 * 
 * Each of the functions below can be considered a start for you. They have 
 * the correct specification and are set up correctly with the header file to
 * be run by the tester programs.  
 *
 * You should leave all of the code as is, especially making sure not to change
 * any return types, function name, or argument lists, as this will break
 * the automated testing. 
 *
 * Your code should only go within the sections surrounded by
 * comments like "REPLACE EVERTHING FROM HERE... TO HERE.
 *
 * The assignment document and the header A3_solutions.h should help
 * to find out how to complete and test the functions. Good luck!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "A3_provided_functions.h"

unsigned char*
bmp_open( char* bmp_filename,        unsigned int *width, 
          unsigned int *height,      unsigned int *bits_per_pixel, 
          unsigned int *padding,     unsigned int *data_size, 
          unsigned int *data_offset                                  )
{
  unsigned char *img_data=NULL;
  // REPLACE EVERYTHING FROM HERE
  //printf( "UNIMPLEMENTED FUNCTION: bmp_open has not yet been coded. Please complete before submitting!\n");
  // Open a binary bmp file
  FILE *bmpFile = fopen(bmp_filename, "rb");
  if (bmpFile == NULL) {
    printf("Jeff's Error: I was unable to open the file %s\n", bmp_filename);
    return img_data;
  }
  
  // Read the b and m characters into chars
  char b, m;
  fread(&b, 1, 1, bmpFile);
  fread(&m, 1, 1, bmpFile);

  /*
  // Print the b and m to terminal
  printf("The first byte was: %c.\n", b);
  printf("The second byte was: %c.\n", m);
  */

  // Read the overall file size
  unsigned int overallFileSize;
  fread(&overallFileSize, 1, sizeof(unsigned int), bmpFile);
  *data_size = overallFileSize;
  // printf("The size is: %i.\n", *data_size);

  // Rewind file pointer to the beginning and read the entire contents.
  rewind(bmpFile);

  img_data = (unsigned char*)malloc(sizeof(unsigned char) * overallFileSize);
  if (fread(img_data, 1, overallFileSize, bmpFile) != overallFileSize) {
    printf("Jeff's Error: I was unable to read the requested %d bytes.\n", overallFileSize);
    return img_data;
  }

  // Read the width and height into unsigned int
  *width = *(unsigned int*)(img_data + 18);
  *height = *(unsigned int*)(img_data + 22);
  *bits_per_pixel = *(unsigned short*)(img_data + 28);
  *padding = ((*bits_per_pixel) * (*width) + 31) / 32 * 4;
  *padding -= (*bits_per_pixel) * (*width) / 8;
  *data_offset = *(unsigned int*)(img_data + 10);
  
  fclose(bmpFile);

  // TO HERE!  
  return img_data;  

}

void 
bmp_close( unsigned char **img_data )
{
  // REPLACE EVERYTHING FROM HERE
  // printf( "UNIMPLEMENTED FUNCTION: bmp_close has not yet been coded. Please complete before submitting!\n");
  if (*img_data != NULL) {
    free(*img_data);
    *img_data = NULL;
  }
  // TO HERE!  
}

unsigned char***  
bmp_scale( unsigned char*** pixel_array, unsigned char* header_data, unsigned int header_size,
           unsigned int* width, unsigned int* height, unsigned int num_colors,
           float scale )
{
  unsigned char*** new_pixel_array = NULL; 
  // REPLACE EVERYTHING FROM HERE
  // printf( "UNIMPLEMENTED FUNCTION: bmp_scale has not yet been coded. Please complete before submitting!\n");
  
  int scaledWidth = *width * scale;
  int scaledHeight = *height * scale;
  
  new_pixel_array = (unsigned char***)malloc(sizeof(unsigned char**) * scaledHeight);

  for (int row = 0; row < scaledHeight; row++) {
    new_pixel_array[row] = (unsigned char**)malloc(sizeof(unsigned char*) * scaledWidth);
    for (int col = 0; col < scaledWidth; col++) {
      new_pixel_array[row][col] = (unsigned char*)malloc(sizeof(unsigned char) * num_colors);
    }
  }

  for (int row = 0; row < scaledHeight; row++) {
    for (int col = 0; col < scaledWidth; col++) {
      for (int color = 0; color < num_colors; color++) {
        new_pixel_array[row][col][color] = pixel_array[(int)(row / scale)][(int)(col / scale)][color];
      }
    }
  }
  
  *width = scaledWidth;
  *height = scaledHeight;

/*
  for (int i = 2; i < 50; i += 4) {
    printf("%i\n", *(unsigned int*)(header_data + i));
  }
  */

  //printf("%i\n", *(unsigned short*)(header_data + 2));
  // printf("%i\n", *(unsigned int*)(header_data + 2));
  // printf("%i\n", header_size);
  // printf("%i\n", (*(unsigned int*)(header_data + 2) - header_size) * scale + header_size);
  *(unsigned int*)(header_data + 2) = scaledWidth * scaledHeight * num_colors + header_size;
  //printf("%i\n", *(unsigned short*)(header_data + 2));
  *(unsigned int*)(header_data + 18) = *width;
  *(unsigned int*)(header_data + 22) = *height;
  
  free(**pixel_array);
  **pixel_array = NULL;
  
  // TO HERE! 
  return new_pixel_array;
}         

int 
bmp_collage( char* background_image_filename,     char* foreground_image_filename, 
             char* output_collage_image_filename, int row_offset,                  
             int col_offset,                      float scale )
{
  // REPLACE EVERYTHING FROM HERE
  // printf( "UNIMPLEMENTED FUNCTION: bmp_collage has not yet been coded. Please complete before submitting!\n");

  // Open background image, get its header and pixel data, scale it
  unsigned char* b_header_data;
  unsigned int b_header_size, b_width, b_height, b_num_colors;
  unsigned char*** b_pixel_array = bmp_to_3D_array(
    background_image_filename, 
    &b_header_data, 
    &b_header_size, 
    &b_width, 
    &b_height, 
    &b_num_colors
  );

  if (b_pixel_array == NULL) {
    return -1;
  }

  // Open foreground image and get its header and pixel data
  unsigned char* f_header_data;
  unsigned int f_header_size, f_width, f_height, f_num_colors;
  unsigned char*** f_pixel_array = bmp_to_3D_array(
    foreground_image_filename, 
    &f_header_data,
    &f_header_size, 
    &f_width, 
    &f_height, 
    &f_num_colors
  );

  if (f_pixel_array == NULL) {
    return -1;
  }

  // Scale foreground image
  unsigned char*** scaled_f_pixel_array = bmp_scale(
    f_pixel_array,
    f_header_data,
    f_header_size,
    &f_width,
    &f_height,
    f_num_colors,
    scale
  );

  if (scaled_f_pixel_array == NULL) {
    return -1;
  }

  // Error cases
  // printf("background image bbp is %i.\n", *(unsigned short*)(b_header_data + 28));
  // printf("forground image bbp is %i.\n", *(unsigned short*)(f_header_data + 28));
  if (
    b_num_colors != 4
    || f_num_colors != 4
    || b_width < f_width
    || b_height < f_height
    || row_offset < 0
    || col_offset < 0
    || b_width < f_width + col_offset 
    || b_height < f_height + row_offset
  ) {
    printf("Jeff's Error: Either one of the images has a bbp that isn't 32, the scaled foreground image is larger, or the offset is negative or too large.\n");
    return -1;
  } else {
    // Put foreground image on background iamge
    for (int row = 0; row < f_height; row++) {
      for (int col = 0; col < f_width; col++) {
        for (int color = 0; color < f_num_colors; color++) {
          if (scaled_f_pixel_array[row][col][0] != 0) {
            b_pixel_array[row + row_offset][col + col_offset][color] = scaled_f_pixel_array[row][col][color];
          }
        }
      }
    }
    
    // Put collage into new file
    int row_size = ((32 * b_width + 31) / 32) * 4;
    int raw_pixel_size = b_header_size + b_height * row_size;
    unsigned char* raw_pixels = (unsigned char*)malloc( raw_pixel_size );
    
    for (int row = 0; row < b_height; row++) {
      for (int col = 0; col < b_width; col++) {
        for (int color = 0; color < b_num_colors; color++) {
          raw_pixels[row * row_size + col * b_num_colors + color] = b_pixel_array[b_height - row - 1][col][color];
        }
      }
    }
    
    FILE *out_fp = fopen(output_collage_image_filename, "wb");
    fwrite(b_header_data, 1, b_header_size, out_fp);
    fwrite(raw_pixels, 1, raw_pixel_size, out_fp);
    fclose(out_fp);
  }


  // TO HERE! 
  return 0;
}              

