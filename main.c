#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "fracnoise.h"
#include "genbrush.h"

#define RANDOMSEED 0

void UnitTestPerlinNoise() {
  // Create a PerlinNoise
  PerlinNoise* noise = PerlinNoiseCreate();
  PerlinNoise noiseStatic = PerlinNoiseCreateStatic();
  // Create a GB to render the image
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 512); VecSet(&dim, 1, 512);
  GenBrush* gb = GBCreateImage(&dim);
  // Draw the Image
  VecShort2D pos = VecShortCreateStatic2D();
  VecFloat3D p = VecFloatCreateStatic3D();
  VecSet(&p, 2, 0.4);
  GBPixel pix = GBColorBlack;
  do {
    for (int i = 2; i--;)
      VecSet(&p, i, (float)VecGet(&pos, i) / 64.0);
    float pn = PerlinNoiseGet(noise, &p);
    float pnStatic = PerlinNoiseGet(&noiseStatic, &p);
    if (ISEQUALF(pn, pnStatic) == false) {
      FracNoiseErr->_type = PBErrTypeUnitTestFailed;
      sprintf(FracNoiseErr->_msg, "PerlinNoiseStatic NOK");
      PBErrCatch(FracNoiseErr);
    }
    unsigned char n = (unsigned char)floor(255.0 * pn);
    pix._rgba[GBPixelRed] = n;
    pix._rgba[GBPixelGreen] = n;
    pix._rgba[GBPixelBlue] = n;
    GBSetFinalPixel(gb, &pos, &pix);
  } while (VecStep(&pos, &dim));
  // Compare to reference
  GenBrush* gbRef = GBCreateFromFile("./UnitTestPerlinNoise3DRef.tga");
  if (gbRef == NULL) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, 
      "Couln't load UnitTestPerlinNoise3DRef.tga");
    PBErrCatch(FracNoiseErr);
  }
  if (GBIsSameAs(gb, gbRef) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoiseGet3D NOK");
    PBErrCatch(FracNoiseErr);
  }
  VecFloat2D p2 = VecFloatCreateStatic2D();
  do {
    for (int i = 2; i--;)
      VecSet(&p2, i, (float)VecGet(&pos, i) / 64.0);
    float pn = PerlinNoiseGet(noise, &p2);
    unsigned char n = (unsigned char)floor(255.0 * pn);
    pix._rgba[GBPixelRed] = n;
    pix._rgba[GBPixelGreen] = n;
    pix._rgba[GBPixelBlue] = n;
    GBSetFinalPixel(gb, &pos, &pix);
  } while (VecStep(&pos, &dim));
  // Compare to reference
  GBFree(&gbRef);
  gbRef = GBCreateFromFile("./UnitTestPerlinNoise2DRef.tga");
  if (gbRef == NULL) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, 
      "Couln't load UnitTestPerlinNoise2DRef.tga");
    PBErrCatch(FracNoiseErr);
  }
  if (GBIsSameAs(gb, gbRef) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoiseGet2D NOK");
    PBErrCatch(FracNoiseErr);
  }
  float p1 = 0.0;
  int i = 0;
  float check[64] = {
    0.500000,0.507794,0.515479,0.522958,0.530141,0.536949,0.543313,
    0.549172,0.554474,0.559176,0.563242,0.566646,0.569366,0.571388,
    0.572708,0.573324,0.573242,0.572474,0.571037,0.568952,0.566247,
    0.562952,0.559102,0.554736,0.549896,0.544627,0.538977,0.532996,
    0.526736,0.520251,0.513596,0.506826,0.500000,0.493174,0.486404,
    0.479749,0.473264,0.467004,0.461023,0.455373,0.450104,0.445264,
    0.440898,0.437048,0.433753,0.431048,0.428963,0.427526,0.426758,
    0.426676,0.427292,0.428612,0.430634,0.433354,0.436758,0.440824,
    0.445526,0.450828,0.456687,0.463051,0.469859,0.477042,0.484521,
    0.492206};
  do {
    float pn = PerlinNoiseGet(noise, p1);
    if (ISEQUALF(pn, check[i]) == false) {
      FracNoiseErr->_type = PBErrTypeUnitTestFailed;
      sprintf(FracNoiseErr->_msg, "PerlinNoiseGet1D NOK");
      PBErrCatch(FracNoiseErr);
    }
    p1 += 1.0 / 64.0;
    ++i;
  } while (p1 < 1.0);
  int permut[256] = {};
  for (int i = 256; i--;)
    permut[i] = i;
  PerlinNoiseSetPermut(noise, permut);
  for (int i = 256; i--;)
    if (noise->_p[i] != permut[i] ||
      noise->_p[256 + i] != permut[i]) {
      FracNoiseErr->_type = PBErrTypeUnitTestFailed;
      sprintf(FracNoiseErr->_msg, "PerlinNoiseSetPermut NOK");
      PBErrCatch(FracNoiseErr);
    }
  // Free memory
  GBFree(&gb);
  GBFree(&gbRef);
  PerlinNoiseFree(&noise);
  printf("UnitTestPerlinNoise OK\n");
}

void UnitTestPerlinNoisePodCreateFree() {
  VecFloat3D seed = VecFloatCreateStatic3D();
  VecSet(&seed, 0, 1.0); VecSet(&seed, 1, 2.0); VecSet(&seed, 2, 3.0); 
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3); VecSet(&dim, 1, 2);
  PerlinNoisePod* pod = PerlinNoisePodCreate(&dim, &seed);
  if (pod->_bound != NULL || 
    ISEQUALF(pod->_border, 0.1) == false ||
    ISEQUALF(VecGet(pod->_scaleIn, 0), 1.0) == false ||
    ISEQUALF(VecGet(pod->_scaleIn, 1), 1.0) == false ||
    ISEQUALF(VecGet(pod->_scaleIn, 2), 1.0) == false ||
    VecGetDim(pod->_scaleOut) != 2 ||
    ISEQUALF(VecGet(pod->_scaleOut, 0), 1.0) == false ||
    ISEQUALF(VecGet(pod->_scaleOut, 1), 1.0) == false ||
    pod->_fractalLvl != 0 || 
    ISEQUALF(pod->_fractalCoeff, 0.1) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodCreate NOK");
    PBErrCatch(FracNoiseErr);
  }
  VecNormalise(&seed);
  if (VecIsEqual(&(pod->_seed), &seed) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodCreate NOK");
    PBErrCatch(FracNoiseErr);
  }
  PerlinNoisePodFree(&pod);
  if (pod != NULL) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodFree NOK");
    PBErrCatch(FracNoiseErr);
  }
  printf("UnitTestPerlinNoisePodCreateFree OK\n");
}

void UnitTestPerlinNoisePodSetGet() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2); VecSet(&dim, 1, 3);
  PerlinNoisePod* pod = PerlinNoisePodCreate(&dim, NULL);
  if (PerlinNoisePodNoise(pod) != &(pod->_noise)) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodNoise NOK");
    PBErrCatch(FracNoiseErr);
  }
  if (PerlinNoisePodSeed(pod) != &(pod->_seed)) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodSeed NOK");
    PBErrCatch(FracNoiseErr);
  }
  VecFloat3D seed = VecFloatCreateStatic3D();
  VecSet(&seed, 0, 1.0); VecSet(&seed, 1, 2.0); VecSet(&seed, 2, 3.0); 
  PerlinNoisePodSetSeed(pod, &seed);
  VecNormalise(&seed);
  if (VecIsEqual(PerlinNoisePodSeed(pod), &seed) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodSetSeed NOK");
    PBErrCatch(FracNoiseErr);
  }
  if (PerlinNoisePodBound(pod) != pod->_bound) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodBound NOK");
    PBErrCatch(FracNoiseErr);
  }
  Facoid* shap = FacoidCreate(2);
  PerlinNoisePodSetBound(pod, shap);
  if (ShapoidIsEqual(PerlinNoisePodBound(pod), shap) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodSetBound NOK");
    PBErrCatch(FracNoiseErr);
  }
  ShapoidFree(&shap);
  if (PerlinNoisePodScaleIn(pod) != pod->_scaleIn) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodScaleIn NOK");
    PBErrCatch(FracNoiseErr);
  }
  VecFloat2D in = VecFloatCreateStatic2D();
  VecSet(&in, 0, 2.0); VecSet(&in, 1, 3.0); 
  PerlinNoisePodSetScaleIn(pod, (VecFloat*)&in);
  if (VecIsEqual(PerlinNoisePodScaleIn(pod), &in) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodSetScaleIn NOK");
    PBErrCatch(FracNoiseErr);
  }
  if (PerlinNoisePodScaleOut(pod) != pod->_scaleOut) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodScaleOut NOK");
    PBErrCatch(FracNoiseErr);
  }
  VecFloat3D out = VecFloatCreateStatic3D();
  VecSet(&out, 0, 2.0); VecSet(&out, 1, 3.0); VecSet(&out, 2, 4.0);
  PerlinNoisePodSetScaleOut(pod, (VecFloat*)&out);
  if (VecIsEqual(PerlinNoisePodScaleOut(pod), &out) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodSetScaleOut NOK");
    PBErrCatch(FracNoiseErr);
  }
  if (PerlinNoisePodShiftOut(pod) != pod->_shiftOut) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodShiftOut NOK");
    PBErrCatch(FracNoiseErr);
  }
  VecFloat3D shift = VecFloatCreateStatic3D();
  VecSet(&shift, 0, 2.0); VecSet(&shift, 1, 3.0); VecSet(&shift, 2, 4.0);
  PerlinNoisePodSetShiftOut(pod, (VecFloat*)&shift);
  if (VecIsEqual(PerlinNoisePodShiftOut(pod), &shift) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodSetShiftOut NOK");
    PBErrCatch(FracNoiseErr);
  }
  if (PerlinNoisePodGetFractLvl(pod) != pod->_fractalLvl) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodGetFractLvl NOK");
    PBErrCatch(FracNoiseErr);
  }
  PerlinNoisePodSetFractLvl(pod, 2);
  if (PerlinNoisePodGetFractLvl(pod) != 2) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodSetFractLvl NOK");
    PBErrCatch(FracNoiseErr);
  }
  if (ISEQUALF(PerlinNoisePodGetFractCoeff(pod), pod->_fractalCoeff) == 
    false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodGetFractCoeff NOK");
    PBErrCatch(FracNoiseErr);
  }
  PerlinNoisePodSetFractCoeff(pod, 0.5);
  if (ISEQUALF(PerlinNoisePodGetFractCoeff(pod), 0.5) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodSetFractCoeff NOK");
    PBErrCatch(FracNoiseErr);
  }
  if (ISEQUALF(PerlinNoisePodGetBorder(pod), pod->_border) == 
    false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodGetBorder NOK");
    PBErrCatch(FracNoiseErr);
  }
  PerlinNoisePodSetBorder(pod, 0.25);
  if (ISEQUALF(PerlinNoisePodGetBorder(pod), 0.25) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodSetBorder NOK");
    PBErrCatch(FracNoiseErr);
  }
  if (ISEQUALF(PerlinNoisePodGetSmooth(pod), pod->_smooth) == 
    false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodGetSmooth NOK");
    PBErrCatch(FracNoiseErr);
  }
  PerlinNoisePodSetSmooth(pod, 0.25);
  if (ISEQUALF(PerlinNoisePodGetSmooth(pod), 0.25) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "PerlinNoisePodSetSmooth NOK");
    PBErrCatch(FracNoiseErr);
  }
  PerlinNoisePodFree(&pod);
  printf("UnitTestPerlinNoisePodSetGet OK\n");
}

void UnitTestPerlinNoisePodGetInsideness() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2); VecSet(&dim, 1, 3);
  PerlinNoisePod* pod = PerlinNoisePodCreate(&dim, NULL);
  Facoid* shap = FacoidCreate(2);
  PerlinNoisePodSetBound(pod, shap);
  PerlinNoisePodSetBorder(pod, 0.5);
  VecFloat2D pos = VecFloatCreateStatic2D();
  float check[25] = {
    0.000000,0.000000,0.000000,0.003368,0.113456,0.537834,0.955768,
    1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,1.000000,
    1.000000,1.000000,1.000000,1.000000,0.955768,0.537834,0.113456,
    0.003368,0.000000,0.000000,0.000000};
  for (int i = 0; i <= 24; ++i) {
    float x = -0.1 + 0.05 * (float)i;
    VecSet(&pos, 0, x); VecSet(&pos, 1, x);
    float in = PerlinNoisePodGetInsideness(pod, (VecFloat*)&pos);
    if (ISEQUALF(in, check[i]) == false) {
      FracNoiseErr->_type = PBErrTypeUnitTestFailed;
      sprintf(FracNoiseErr->_msg, "PerlinNoisePodGetInsideness NOK");
      PBErrCatch(FracNoiseErr);
    }
  }
  ShapoidFree(&shap);
  PerlinNoisePodFree(&pod);
  printf("UnitTestPerlinNoisePodGetInsideness OK\n");
}

void UnitTestPerlinNoisePod() {
  UnitTestPerlinNoisePodCreateFree();
  UnitTestPerlinNoisePodSetGet();
  UnitTestPerlinNoisePodGetInsideness();
  
  printf("UnitTestPerlinNoisePod OK\n");
}

void UnitTestFracNoiseCreateFree() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2); VecSet(&dim, 1, 3);
  FracNoise* noise = FracNoiseCreate(&dim, NULL);
  if (VecIsEqual(&(noise->_dim), &dim) != true) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "FracNoiseCreate NOK");
    PBErrCatch(FracNoiseErr);
  }
  FracNoiseFree(&noise);
  if (noise != NULL) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "FracNoiseFree NOK");
    PBErrCatch(FracNoiseErr);
  }
  printf("UnitTestFracNoiseCreateFree OK\n");
}

void UnitTestFracNoiseSetGet() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2); VecSet(&dim, 1, 3);
  FracNoise* noise = FracNoiseCreate(&dim, NULL);
  if (VecIsEqual(FracNoiseDim(noise), &dim) != true) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "FracNoiseDim NOK");
    PBErrCatch(FracNoiseErr);
  }
  if (FracNoisePods(noise) != &(noise->_noises)) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "FracNoisePods NOK");
    PBErrCatch(FracNoiseErr);
  }
  if (FracNoiseGetNoise(noise, 0) != 
    (PerlinNoisePod*)(noise->_noises._head->_data)) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "FracNoiseGetNoise NOK");
    PBErrCatch(FracNoiseErr);
  }
  FracNoiseFree(&noise);
  printf("UnitTestFracNoiseSetGet OK\n");
}

void UnitTestFracNoiseAddRemoveNoise() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2); VecSet(&dim, 1, 3);
  FracNoise* noise = FracNoiseCreate(&dim, NULL);
  PerlinNoisePod* pod = FracNoiseAddNoise(noise, NULL);
  if (GSetNbElem(FracNoisePods(noise)) != 2 ||
    pod != FracNoiseGetNoise(noise, 1)) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "FracNoiseAddNoise NOK");
    PBErrCatch(FracNoiseErr);
  }
  FracNoiseRemoveNoise(noise, pod);
  if (GSetNbElem(FracNoisePods(noise)) != 1 ||
    pod == FracNoiseGetNoise(noise, 0)) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "FracNoiseRemoveNoise NOK");
    PBErrCatch(FracNoiseErr);
  }
  FracNoiseFree(&noise);
  printf("UnitTestFracNoiseAddRemoveNoise OK\n");
}

void UnitTestFracNoiseGet() {
  // Create a FracNoise
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2); VecSet(&dim, 1, 3);
  FracNoise* noise = FracNoiseCreate(&dim, NULL);
  // Set properties of the FracNoise
  PerlinNoisePod* podA = FracNoiseGetNoise(noise, 0);
  VecFloat2D scaleIn = VecFloatCreateStatic2D();
  VecSet(&scaleIn, 0, 1.0); VecSet(&scaleIn, 1, 0.5);
  PerlinNoisePodSetScaleIn(podA, (VecFloat*)&scaleIn);
  VecFloat3D scaleOut = VecFloatCreateStatic3D();
  VecSet(&scaleOut, 0, 1.0); VecSet(&scaleOut, 1, 0.2); 
  VecSet(&scaleOut, 2, 1.0);
  PerlinNoisePodSetScaleOut(podA, (VecFloat*)&scaleOut);
  PerlinNoisePodSetFractLvl(podA, 1);
  VecFloat3D seed = VecFloatCreateStatic3D();
  VecSet(&seed, 0, -1.0); VecSet(&seed, 1, 0.5); 
  VecSet(&seed, 2, 1.0);
  PerlinNoisePod* podB = FracNoiseAddNoise(noise, &seed);
  VecSet(&scaleOut, 0, 0.0); VecSet(&scaleOut, 1, 0.7); 
  VecSet(&scaleOut, 2, 0.0);
  PerlinNoisePodSetScaleOut(podB, (VecFloat*)&scaleOut);
  VecFloat3D shiftOut = VecFloatCreateStatic3D();
  VecSet(&shiftOut, 0, 0.0); VecSet(&shiftOut, 1, 0.1); 
  VecSet(&shiftOut, 2, 0.0);
  Spheroid* bound = SpheroidCreate(2);
  ShapoidScale(bound, (float)(200.0 / 64.0)); 
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 250.0 / 64.0); VecSet(&v, 1, 250.0 / 64.0);
  ShapoidTranslate(bound, &v);
  PerlinNoisePodSetBound(podB, bound);
  PerlinNoisePodSetBorder(podB, 0.5);
  PerlinNoisePodSetSmooth(podA, 3.0);
  // Create a GB to render the image
  VecSet(&dim, 0, 512); VecSet(&dim, 1, 512);
  GenBrush* gb = GBCreateImage(&dim);
  // Draw the Image
  VecShort2D pos = VecShortCreateStatic2D();
  VecFloat2D p = VecFloatCreateStatic2D();
  GBPixel pix = GBColorBlack;
  do {
    for (int i = 2; i--;)
      VecSet(&p, i, (float)VecGet(&pos, i) / 64.0);
    VecFloat* pn = FracNoiseGet(noise, &p);
    pix._rgba[GBPixelRed] = (unsigned char)floor(255.0 * VecGet(pn, 0));
    pix._rgba[GBPixelGreen] = 
      (unsigned char)floor(255.0 * VecGet(pn, 1));
    pix._rgba[GBPixelBlue] = (unsigned char)floor(255.0 * VecGet(pn, 2));
    GBSetFinalPixel(gb, &pos, &pix);
    VecFree(&pn);
  } while (VecStep(&pos, &dim));
  // Compare to reference (two versions because changes in compilation
  // options trigger small variations when casting from float to int)
#if BUILDMODE == 0
  GenBrush* gbRef = GBCreateFromFile("./UnitTestFracNoiseGetRef0.tga");
#else
  GenBrush* gbRef = GBCreateFromFile("./UnitTestFracNoiseGetRef1.tga");
#endif
  if (gbRef == NULL) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, 
      "Couln't load UnitTestPerlinNoise3DRef.tga");
    PBErrCatch(FracNoiseErr);
  }
  if (GBIsSameAs(gb, gbRef) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "FracNoiseGet NOK");
    PBErrCatch(FracNoiseErr);
  }
  // Free memory
  ShapoidFree(&bound);
  GBFree(&gb);
  GBFree(&gbRef);
  FracNoiseFree(&noise);

  printf("UnitTestFracNoiseGet OK\n");
}

void UnitTestFracNoiseExport() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3); VecSet(&dim, 1, 1);
  FracNoise* noise = FracNoiseCreate(&dim, NULL);
  VecFloat3D range = VecFloatCreateStatic3D();
  VecSet(&range, 0, 10.0); VecSet(&range, 1, 10.0); 
  VecSet(&range, 2, 10.0); 
  VecShort3D nbSample = VecShortCreateStatic3D();
  VecSet(&nbSample, 0, 30); VecSet(&nbSample, 1, 30); 
  VecSet(&nbSample, 2, 30); 
  int res = 8;
  char* fileName = "./UnitTestFracNoiseExport.df3";
  if (FracNoiseExportDF3(noise, &range, &nbSample, res, true,
    fileName) == false) {
    FracNoiseErr->_type = PBErrTypeUnitTestFailed;
    sprintf(FracNoiseErr->_msg, "FracNoiseExportDF3 NOK");
    PBErrCatch(FracNoiseErr);
  }
  FracNoiseFree(&noise);
  printf("UnitTestFracNoiseExport OK\n");
}

void UnitTestFracNoise() {
  UnitTestFracNoiseCreateFree();
  UnitTestFracNoiseSetGet();
  UnitTestFracNoiseAddRemoveNoise();
  UnitTestFracNoiseGet();
  UnitTestFracNoiseExport();
  
  printf("UnitTestFracNoise OK\n");
}

void UnitTestAll() {
  UnitTestPerlinNoise();
  UnitTestPerlinNoisePod();
  UnitTestFracNoise();
  printf("UnitTestAll OK\n");
}

int main() {
  UnitTestAll();

  // Return success code
  return 0;
}

