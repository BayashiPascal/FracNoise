// ============ FRACNOISE.H ================

#ifndef FRACNOISE_H
#define FRACNOISE_H

// ================= Include =================

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "pbmath.h"
#include "gset.h"
#include "shapoid.h"

// -------------- PerlinNoise
// http://mrl.nyu.edu/~perlin/noise/

// ================= Data structure ===================

typedef struct PerlinNoise {
  // Parameters 
  int _p[512];
} PerlinNoise;

// ================ Functions declaration ====================

// Return a new PerlinNoise
PerlinNoise* PerlinNoiseCreate(void);

// Return a new static PerlinNoise
PerlinNoise PerlinNoiseCreateStatic(void);

// Free the memory used by the PerlinNoise 'that'
void PerlinNoiseFree(PerlinNoise** that);

// Return the value of the PerlinNoise 'that' at position 'u'
// 'u' can be of dimension 1 to 3, 'u' values in R, the Perlin noise
// has interpolation on unit, so u in [0.0, 1.0] will be interpolated
// between 2 values, u in [0.0, 2.0] will be interpolated between
// 3 values, and the noise always equal 0.5 at unit values, so
// noise(0.0) == noise(1.0) == noise(2.0) == ... == 0.5
// Return a value in [0.0, 1.0]
float _PerlinNoiseGet(PerlinNoise* noise, VecFloat* u);
float _PerlinNoiseGet1D(PerlinNoise* noise, float u);
float _PerlinNoiseGet2D(PerlinNoise* noise, VecFloat2D* u);
float _PerlinNoiseGet3D(PerlinNoise* noise, VecFloat3D* u);

// Set the permutations of the PerlinNoise 'that' to 'permut'
// 'permut' is an array of 256 int
void PerlinNoiseSetPermut(PerlinNoise* that, int* permut);

// -------------- PerlinNoisePod

typedef struct PerlinNoisePod {
  // Perlin noise
  PerlinNoise _noise;
  // Seed
  VecFloat3D _seed;
  // Boundary
  Shapoid* _bound;
  // Boundary border
  float _border;
  // Scale inputs
  VecFloat* _scaleIn;
  // Scale outputs
  VecFloat* _scaleOut;
  // Shift outputs
  VecFloat* _shiftOut;
  // Fractal level
  int _fractalLvl;
  // Fractal coefficient
  float _fractalCoeff;
  // Smoothness
  float _smooth;
} PerlinNoisePod;

// ================ Functions declaration ====================

// Return a new PerlinNoisePod with dimension 'dim' and seed
// 'seed'
// If the seed is the vector null replace it by (1,1,1)
// Default values:
// bound = NULL, border = 0.1, scaleIn/Out = 1.0
// fractalLvl = 0, fractalCoeff = 0.1, smooth = 1.0
PerlinNoisePod* PerlinNoisePodCreate(VecShort2D* dim, VecFloat3D* seed);

// Free memory used by the PerlinNoisePod 'that'
void PerlinNoisePodFree(PerlinNoisePod** that);

// Get the Perlin noise of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
PerlinNoise* PerlinNoisePodNoise(PerlinNoisePod* that);

// Get the seed of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D* PerlinNoisePodSeed(PerlinNoisePod* that);

// Get the bound of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
Shapoid* PerlinNoisePodBound(PerlinNoisePod* that);

// Get the scale of inputs of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* PerlinNoisePodScaleIn(PerlinNoisePod* that);

// Get the scale of outputs of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* PerlinNoisePodScaleOut(PerlinNoisePod* that);

// Get the shift of outputs of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* PerlinNoisePodShiftOut(PerlinNoisePod* that);

// Get the fractal level of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
int PerlinNoisePodGetFractLvl(PerlinNoisePod* that);

// Get the fractal coefficient of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
float PerlinNoisePodGetFractCoeff(PerlinNoisePod* that);

// Get the border coefficient of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
float PerlinNoisePodGetBorder(PerlinNoisePod* that);

// Get the smoothness of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
float PerlinNoisePodGetSmooth(PerlinNoisePod* that);

// Set the seed of the PerlinNoisePod 'that' to a copy of 'seed'
// If 'seed' is the vector null the seed is left unchanged 
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetSeed(PerlinNoisePod* that, VecFloat3D* seed);

// Set the bound of the PerlinNoisePod 'that' to 'bound'
// The Shapoid 'bound' must have same dimensions as the input dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetBound(PerlinNoisePod* that, Shapoid* bound);

// Set the scale of inputs of the PerlinNoisePod 'that' to a 
// copy of 'scale'
// 'scale' must have same dimension as the input dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetScaleIn(PerlinNoisePod* that, VecFloat* scale);

// Set the scale of outputs of the PerlinNoisePod 'that' to a copy 
// of 'scale'
// 'scale' must have same dimension as the output dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetScaleOut(PerlinNoisePod* that, VecFloat* scale);

// Set the shift of outputs of the PerlinNoisePod 'that' to a copy 
// of 'shift'
// 'shift' must have same dimension as the output dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetShiftOut(PerlinNoisePod* that, VecFloat* shift);

// Set the fractal level of the PerlinNoisePod 'that' to 'lvl'
// 'lvl' must be greater than or equal to 0
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetFractLvl(PerlinNoisePod* that, int lvl);

// Set the fractal coefficient of the PerlinNoisePod 'that' to 'coeff'
// 'coeff' must be greater than 0.0, if it's negative its absolute 
// value is used
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetFractCoeff(PerlinNoisePod* that, float coeff);

// Set the border coefficient of the PerlinNoisePod 'that' to 'border'
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetBorder(PerlinNoisePod* that, float border);

// Set the smoothness of the PerlinNoisePod 'that' to 'smooth'
// 'smooth' must be greater than 0.0
// Below 1.0 gives a bumpy aspect, above 1.0 gives a thorny aspect,
// 1.0 is the smoothest
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetSmooth(PerlinNoisePod* that, float smooth);

// Get the insideness in boundary of the PerlinNoisePod 'that' at 
// position 'pos'
// If there is no bounday it's always 1.0
// If there is boundary, it's 0.0 outside of boundary and else it's
// the position depth in the Shapoid corrected with the border as follow:
// if depth > border the depth is set to 1.0, else the depth is
// SmootherStep from (0.0, border) to (0.0, 1.0)
// 'pos' 's dimension must be equal to the Shapoid's dimension
float PerlinNoisePodGetInsideness(PerlinNoisePod* that, VecFloat* pos);

// -------------- FracNoise

typedef struct FracNoise {
  // Dimensions (input, output)
  VecShort2D _dim;
  // Set of PerlinNoisePod
  GSet _noises;
} FracNoise;

// ================ Functions declaration ====================

// Return a new FracNoise of dimensions 'dim' and 'seed'
// The number of input must be between 1 and 3
// The number of output can be any value greater or equal to 1
// If seed is null it is replaced by a default seed
// Return null if the number of dimensions are invalid
FracNoise* FracNoiseCreate(VecShort2D* dim, VecFloat3D* seed);

// Free the memory used by the FracNoise 'that'
void FracNoiseFree(FracNoise** that);

// Get the dimensions of the noise 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D* FracNoiseDim(FracNoise* that);

// Get the pods of the noise 'that'
#if BUILDMODE != 0 
inline 
#endif 
GSet* FracNoisePods(FracNoise* that);

// Get the 'iNoise'-th noise of the FracNoise 'that'
// Return null if 'iNoise' is invalid
#if BUILDMODE != 0 
inline 
#endif 
PerlinNoisePod* FracNoiseGetNoise(FracNoise* that, int iNoise);

// Add a new noise with seed 'seed' to the FracNoise 'that'
// If seed is null it is replaced by a default seed
// Return the new noise
#if BUILDMODE != 0 
inline 
#endif 
PerlinNoisePod* FracNoiseAddNoise(FracNoise* that, VecFloat3D* seed);

// Remove the PerlinNoisePod 'pod' from the FracNoise 'that'
#if BUILDMODE != 0 
inline 
#endif 
void FracNoiseRemoveNoise(FracNoise* that, PerlinNoisePod* pod);

// Get the noise value of the FracNoise 'that' at 'input'
VecFloat* _FracNoiseGet(FracNoise* that, VecFloat* input);

// Export the FracNoise 'that' to a POV-Ray .df3 file located at 
// 'filename'. The input range goes from 0.0 to 'range'. The number of 
// samples per axis is given by 'nbSample'. The resolution in bit is 
// given by 'res' (must be 8, 16 or 32).
// If 'rescale' equals true, the values are scaled to [0,1] else they
// are clipped
// The FracNoise's dimensions must be 3D->1D
// The output values are automatically scaled 
// If the arguments are invalid, the df3 file is not generated.
// Return true if the df3 has been succesfully created, false else.
bool FracNoiseExportDF3(FracNoise* that, VecFloat3D* range, 
  VecShort3D* nbSample, int res, bool rescale, char* fileName);

// ================ Polymorphism ====================
#define PerlinNoiseGet(Noise, U) _Generic(U, \
  VecFloat*: _PerlinNoiseGet, \
  float: _PerlinNoiseGet1D, \
  VecFloat2D*: _PerlinNoiseGet2D, \
  VecFloat3D*: _PerlinNoiseGet3D, \
  default:PBErrInvalidPolymorphism) (Noise, U)

#define PerlinNoisePodSetBound(Pod, Bound) _Generic(Bound, \
  Shapoid*: _PerlinNoisePodSetBound, \
  Facoid*: _PerlinNoisePodSetBound, \
  Pyramidoid*: _PerlinNoisePodSetBound, \
  Spheroid*: _PerlinNoisePodSetBound, \
  default:PBErrInvalidPolymorphism) (Pod, (Shapoid*)Bound)

#define PerlinNoisePodSetScaleIn(Pod, Scale) _Generic(Scale, \
  VecFloat*: _PerlinNoisePodSetScaleIn, \
  VecFloat2D*: _PerlinNoisePodSetScaleIn, \
  VecFloat3D*: _PerlinNoisePodSetScaleIn, \
  default:PBErrInvalidPolymorphism) (Pod, (VecFloat*)(Scale))
  
#define PerlinNoisePodSetScaleOut(Pod, Scale) _Generic(Scale, \
  VecFloat*: _PerlinNoisePodSetScaleOut, \
  VecFloat2D*: _PerlinNoisePodSetScaleOut, \
  VecFloat3D*: _PerlinNoisePodSetScaleOut, \
  default:PBErrInvalidPolymorphism) (Pod, (VecFloat*)(Scale))
  
#define PerlinNoisePodSetShiftOut(Pod, Shift) _Generic(Shift, \
  VecFloat*: _PerlinNoisePodSetShiftOut, \
  VecFloat2D*: _PerlinNoisePodSetShiftOut, \
  VecFloat3D*: _PerlinNoisePodSetShiftOut, \
  default:PBErrInvalidPolymorphism) (Pod, (VecFloat*)(Shift))
  
#define FracNoiseGet(Noise, U) _Generic(U, \
  VecFloat*: _FracNoiseGet, \
  VecFloat2D*: _FracNoiseGet, \
  VecFloat3D*: _FracNoiseGet, \
  default:PBErrInvalidPolymorphism) (Noise, (VecFloat*)(U))

// ================ Inliner ====================

#if BUILDMODE != 0
#include "fracnoise-inline.c"
#endif

#endif
