/**
 * Simple mandelbrot generator, useful to compare the speed of the ZZ9K (integrated ARM)
 * to that of the native 68k
 */ 
#include <math.h>

#include "mandel.h"

#ifndef ZZ9K_ARM_CODE
#include <libraries/Picasso96.h>
#endif

/**
 * Draws a simple Mandelbrot Set on the screen
 * Assumes a 24 format.
 * 
 * Based on the example from Rosetta Code: https://rosettacode.org/wiki/Mandelbrot_set#C
 * 
 * @param argc number of arguments passed
 * @param argv pointer to the array of arguments
 */
int mandel(uint32_t argc, uint32_t* argv) {

  if (argc < 4) {
    return 1;
  }
  /* screen ( integer) coordinate */
  int iX,iY;
  uint32_t* buffer = (uint32_t*)argv[0];
  const int iXmax = argv[1]; 
  const int iYmax = argv[2];
  const int colorFmt = argv[3];
  
  uint8_t cShifts[3];

  setColorShifts(colorFmt, cShifts);

  /* world ( double) coordinate = parameter plane*/
  double Cx,Cy;
  const double CxMin = -2.5;
  const double CxMax = 1.5;
  const double CyMin = -2.0;
  const double CyMax = 2.0;

  double PixelWidth = (CxMax - CxMin) / iXmax;
  double PixelHeight = (CyMax - CyMin) / iYmax;
  /* color component ( R or G or B) is coded from 0 to 255 */
  
  static unsigned char color[3];
  /* Z=Zx+Zy*i  ;   Z0 = 0 */
  double Zx, Zy;
  double Zx2, Zy2; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */

  int Iteration;
  const int IterationMax = 255;
  /* bail-out value , radius of circle ;  */
  const double EscapeRadius = 2;
  double ER2 = EscapeRadius * EscapeRadius;

  for (iY = 0; iY < iYmax; iY++) {
    Cy = CyMin + iY * PixelHeight;
    if (fabs(Cy) < PixelHeight / 2) Cy = 0.0; /* Main antenna */
    for(iX = 0; iX < iXmax; iX++) {
      Cx = CxMin + iX * PixelWidth;
      /* initial value of orbit = critical point Z= 0 */
      Zx = 0.0;
      Zy = 0.0;
      Zx2 = Zx*Zx;
      Zy2 = Zy*Zy;
      /* */
      for (Iteration = 0; Iteration < IterationMax && ((Zx2 + Zy2) < ER2); Iteration++)
      {
          Zy = 2 * Zx * Zy + Cy;
          Zx = Zx2 - Zy2 + Cx;
          Zx2 = Zx * Zx;
          Zy2 = Zy * Zy;
      }
      /* compute  pixel color (24 bit = 3 bytes) */
      if (Iteration == IterationMax)
      { /*  interior of Mandelbrot set = black */
          color[0] = 0;
          color[1] = 0;
          color[2] = 0;                           
      }
      else 
      { /* exterior of Mandelbrot set = black */
        color[0] = Iteration; /* Red*/
        color[1] = Iteration; /* Green */ 
        color[2] = Iteration; /* Blue */
      };

      *(buffer++) = (color[0] << cShifts[0]) | (color[1] << cShifts[1]) | (color[2] << cShifts[2]);
    }
  }
  return 0;
}

/**
 * Sets color shifts
 */
void setColorShifts(uint32_t colorFmt, uint8_t* cs) {

  switch (colorFmt) {
  
// Big-endian values!
#if PURE_68K == 1
    	case RGBFF_A8R8G8B8:		/* 4 Byte TrueColor ABGR (A unused alpha channel) */
        cs[0] = 16;
        cs[1] = 8;
        cs[2] = 0;
        break;
    	case RGBFF_A8B8G8R8:		/* 4 Byte TrueColor RGBA (A unused alpha channel) */
        cs[0] = 0;
        cs[1] = 8;
        cs[2] = 16;
        break;
    	case RGBFF_R8G8B8A8:		/* 4 Byte TrueColor BGRA (A unused alpha channel) */
        cs[0] = 24;
        cs[1] = 16;
        cs[2] = 8;
        break;
      default:
    	case RGBFF_B8G8R8A8:		/* 4 Byte TrueColor ARGB (A unused alpha channel) */
        cs[0] = 8;
        cs[1] = 16;
        cs[2] = 24;
        break;
#else // Little-endian for the ARM cpu.
    	case RGBFF_A8R8G8B8:		/* 4 Byte TrueColor ABGR (A unused alpha channel) */
        cs[0] = 8;
        cs[1] = 16;
        cs[2] = 24;
        break;
    	case RGBFF_A8B8G8R8:		/* 4 Byte TrueColor RGBA (A unused alpha channel) */
        cs[0] = 24;
        cs[1] = 16;
        cs[2] = 8;
        break;
    	case RGBFF_R8G8B8A8:		/* 4 Byte TrueColor BGRA (A unused alpha channel) */
        cs[0] = 0;
        cs[1] = 8;
        cs[2] = 16;
        break;
      default:
    	case RGBFF_B8G8R8A8:		/* 4 Byte TrueColor ARGB (A unused alpha channel) */
        cs[0] = 16;
        cs[1] = 8;
        cs[2] = 0;
        break;
#endif
  }
}