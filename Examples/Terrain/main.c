#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "fracnoise.h"
#include "genbrush.h"

#define RANDOMSEED 1

int main() {
  srandom(RANDOMSEED);
  // HF dimension
  int HFDim = 512;
  // Create a FracNoise
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2); VecSet(&dim, 1, 1);
  VecFloat3D seed = VecFloatCreateStatic3D();
  for (int i = 3; i--;) 
    VecSet(&seed, i, rnd());
  FracNoise* terrain = FracNoiseCreate(&dim, &seed);
  // --- main ground
  PerlinNoisePod* ground = FracNoiseGetNoise(terrain, 0);
  // scaleIn
  VecFloat2D scaleIn = VecFloatCreateStatic2D();
  float sIn = 1.0 / (float)HFDim;
  for (int i = 2; i--;) 
    VecSet(&scaleIn, i, sIn);
  PerlinNoisePodSetScaleIn(ground, &scaleIn);
  // scaleOut
  float sOut = 200.0;
  VecFloat* scaleOut = VecFloatCreate(1);
  VecSet(scaleOut, 0, sOut);
  PerlinNoisePodSetScaleOut(ground, scaleOut);
  // fractal
  PerlinNoisePodSetFractLvl(ground, 2);
  PerlinNoisePodSetFractCoeff(ground, 0.3);
  // --- mountains
  PerlinNoisePod* mount = FracNoiseAddNoise(terrain, &seed);
  // scaleIn
  sIn = 5.0 / (float)HFDim;
  for (int i = 2; i--;) 
    VecSet(&scaleIn, i, sIn);
  PerlinNoisePodSetScaleIn(mount, &scaleIn);
  // scaleOut
  sOut = 500.0;
  VecSet(scaleOut, 0, sOut);
  PerlinNoisePodSetScaleOut(mount, scaleOut);
  // boundary
  Spheroid* boundMount = SpheroidCreate(2);
  PerlinNoisePodSetBound(mount, boundMount);
  VecFloat2D scaleBound = VecFloatCreateStatic2D();
  VecSet(&scaleBound, 0, 350.0); VecSet(&scaleBound, 1, 750.0);
  ShapoidScale(boundMount, (VecFloat*)&scaleBound);
  ShapoidRotCenter(boundMount, PBMATH_QUARTERPI * 0.5);
  VecFloat2D shiftBound = VecFloatCreateStatic2D();
  VecSet(&shiftBound, 0, 150.0); VecSet(&shiftBound, 1, 275.0);
  ShapoidTranslate(boundMount, &shiftBound);
  PerlinNoisePodSetBorder(mount, 1.0);
  // fractal
  PerlinNoisePodSetFractLvl(mount, 2);
  PerlinNoisePodSetFractCoeff(mount, 0.4);
  // Create a GB to render the height field
  VecSet(&dim, 0, HFDim); VecSet(&dim, 1, HFDim);
  GenBrush* gb = GBCreateImage(&dim);
  // Draw the image
  VecShort2D pos = VecShortCreateStatic2D();
  VecFloat2D p = VecFloatCreateStatic2D();
  GBPixel pix = GBColorBlack;
  // search the min and max values ot renormalize over the height field
  float min = 255.0;
  float max = 0.0;
  do {
    for (int i = 2; i--;)
      VecSet(&p, i, (float)VecGet(&pos, i));
    VecFloat* pn = FracNoiseGet(terrain, &p);
    if (VecGet(pn, 0) > max)
      max = VecGet(pn, 0);
    if (VecGet(pn, 0) < min)
      min = VecGet(pn, 0);
    VecFree(&pn);
  } while (VecStep(&pos, &dim));
  VecSetNull(&pos);
  do {
    for (int i = 2; i--;)
      VecSet(&p, i, (float)VecGet(&pos, i));
    VecFloat* pn = FracNoiseGet(terrain, &p);
    unsigned char rgb = (unsigned char)floor(255.0 * 
      (VecGet(pn, 0) - min) / (max - min));
    // Avoid hole in the height field due to water_level in POV
    if (rgb == 0) rgb = 1;
    pix._rgba[GBPixelRed] = rgb;
    pix._rgba[GBPixelGreen] = rgb;
    pix._rgba[GBPixelBlue] = rgb;
    GBSetFinalPixel(gb, &pos, &pix);
    VecFree(&pn);
  } while (VecStep(&pos, &dim));
  // Save the image
  GBSetFileName(gb, "./HF.tga");
  GBRender(gb);
  // Free memory
  GBFree(&gb);
  FracNoiseFree(&terrain);
  VecFree(&scaleOut);
  ShapoidFree(&boundMount);

  // Return success code
  return 0;
}

