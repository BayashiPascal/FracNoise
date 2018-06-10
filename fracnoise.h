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
// _PerlinNoiseGet3D takes a third argument which is the squareness
// in [0.0,1.0]
// Return a value in [0.0, 1.0]
float _PerlinNoiseGet(const PerlinNoise* const that, 
  const VecFloat* const u, const float squareness);
float _PerlinNoiseGet1D(const PerlinNoise* const that, const float u, 
  const float squareness);
float _PerlinNoiseGet2D(const PerlinNoise* const that, 
  const VecFloat2D* const u, const float squareness);
float _PerlinNoiseGet3D(const PerlinNoise* const that, 
  const VecFloat3D* const u, const float squareness);

// Set the permutations of the PerlinNoise 'that' to 'permut'
// 'permut' is an array of 256 int
void PerlinNoiseSetPermut(PerlinNoise* const that, 
  const int* const permut);

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
  // Squareness
  float _square;
} PerlinNoisePod;

// ================ Functions declaration ====================

// Return a new PerlinNoisePod with dimension 'dim' and seed
// 'seed'
// If the seed is the vector null replace it by (1,1,1)
// Default values:
// bound = NULL, border = 0.1, scaleIn/Out = 1.0
// fractalLvl = 0, fractalCoeff = 0.1, smooth = 1.0
PerlinNoisePod* PerlinNoisePodCreate(const VecShort2D* const dim, 
  const VecFloat3D* const seed);

// Free memory used by the PerlinNoisePod 'that'
void PerlinNoisePodFree(PerlinNoisePod** that);

// Get the Perlin noise of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
const PerlinNoise* PerlinNoisePodNoise(const PerlinNoisePod* const that);

// Get the seed of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D* PerlinNoisePodSeed(const PerlinNoisePod* const that);

// Get the bound of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
Shapoid* PerlinNoisePodBound(const PerlinNoisePod* const that);

// Get the scale of inputs of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* PerlinNoisePodScaleIn(const PerlinNoisePod* const that);

// Get the scale of outputs of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* PerlinNoisePodScaleOut(const PerlinNoisePod* const that);

// Get the shift of outputs of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* PerlinNoisePodShiftOut(const PerlinNoisePod* const that);

// Get the fractal level of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
int PerlinNoisePodGetFractLvl(const PerlinNoisePod* const that);

// Get the fractal coefficient of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
float PerlinNoisePodGetFractCoeff(const PerlinNoisePod* const that);

// Get the border coefficient of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
float PerlinNoisePodGetBorder(const PerlinNoisePod* const that);

// Get the smoothness of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
float PerlinNoisePodGetSmooth(const PerlinNoisePod* const that);

// Get the squareness of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
float PerlinNoisePodGetSquare(const PerlinNoisePod* const that);

// Set the seed of the PerlinNoisePod 'that' to a copy of 'seed'
// If 'seed' is the vector null the seed is left unchanged 
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetSeed(PerlinNoisePod* const that, 
  const VecFloat3D* const seed);

// Set the bound of the PerlinNoisePod 'that' to 'bound'
// The Shapoid 'bound' must have same dimensions as the input dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetBound(PerlinNoisePod* const that, 
  Shapoid* const bound);

// Set the scale of inputs of the PerlinNoisePod 'that' to a 
// copy of 'scale'
// 'scale' must have same dimension as the input dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetScaleIn(PerlinNoisePod* const that, 
  const VecFloat* const scale);

// Set the scale of outputs of the PerlinNoisePod 'that' to a copy 
// of 'scale'
// 'scale' must have same dimension as the output dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetScaleOut(PerlinNoisePod* const that, 
  const VecFloat* const scale);

// Set the shift of outputs of the PerlinNoisePod 'that' to a copy 
// of 'shift'
// 'shift' must have same dimension as the output dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetShiftOut(PerlinNoisePod* const that, 
  const VecFloat* const shift);

// Set the fractal level of the PerlinNoisePod 'that' to 'lvl'
// 'lvl' must be greater than or equal to 0
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetFractLvl(PerlinNoisePod* const that, const int lvl);

// Set the fractal coefficient of the PerlinNoisePod 'that' to 'coeff'
// 'coeff' must be greater than 0.0, if it's negative its absolute 
// value is used
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetFractCoeff(PerlinNoisePod* const that, 
  const float coeff);

// Set the border coefficient of the PerlinNoisePod 'that' to 'border'
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetBorder(PerlinNoisePod* const that, 
  const float border);

// Set the smoothness of the PerlinNoisePod 'that' to 'smooth'
// 'smooth' must be greater than 0.0
// Below 1.0 gives a bumpy aspect, above 1.0 gives a thorny aspect,
// 1.0 is the smoothest
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetSmooth(PerlinNoisePod* const that, 
  const float smooth);

// Set the squareness of the PerlinNoisePod 'that' to 'square'
// 'square' must be in [0.0, 1.0]
// 0.0 is the standard Perlin noise, 1.0 is the Perlin noise without
// the smoother function on input parameter
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetSquare(PerlinNoisePod* const that, 
  const float square);

// Get the insideness in boundary of the PerlinNoisePod 'that' at 
// position 'pos'
// If there is no bounday it's always 1.0
// If there is boundary, it's 0.0 outside of boundary and else it's
// the position depth in the Shapoid corrected with the border as follow:
// if depth > border the depth is set to 1.0, else the depth is
// SmootherStep from (0.0, border) to (0.0, 1.0)
// 'pos' 's dimension must be equal to the Shapoid's dimension
float PerlinNoisePodGetInsideness(PerlinNoisePod* const that, 
  const VecFloat* const pos);

// -------------- FracNoise

typedef struct FracNoise {
  // Dimensions (input, output)
  const VecShort2D _dim;
  // Set of PerlinNoisePod
  GSet _noises;
} FracNoise;

// ================ Functions declaration ====================

// Return a new FracNoise of dimensions 'dim' and 'seed'
// The number of input must be between 1 and 3
// The number of output can be any value greater or equal to 1
// If seed is null it is replaced by a default seed
// Return null if the number of dimensions are invalid
FracNoise* FracNoiseCreate(const VecShort2D* const dim, 
  const VecFloat3D* const seed);

// Free the memory used by the FracNoise 'that'
void FracNoiseFree(FracNoise** that);

// Get the dimensions of the noise 'that'
#if BUILDMODE != 0 
inline 
#endif 
const VecShort2D* FracNoiseDim(const FracNoise* const that);

// Get the pods of the noise 'that'
#if BUILDMODE != 0 
inline 
#endif 
const GSet* FracNoisePods(const FracNoise* const that);

// Get the 'iNoise'-th noise of the FracNoise 'that'
// Return null if 'iNoise' is invalid
#if BUILDMODE != 0 
inline 
#endif 
PerlinNoisePod* FracNoiseGetNoise(const FracNoise* const that, 
  const int iNoise);

// Add a new noise with seed 'seed' to the FracNoise 'that'
// If seed is null it is replaced by a default seed
// Return the new noise
#if BUILDMODE != 0 
inline 
#endif 
PerlinNoisePod* FracNoiseAddNoise(FracNoise* const that, 
  const VecFloat3D* const seed);

// Remove the PerlinNoisePod 'pod' from the FracNoise 'that'
#if BUILDMODE != 0 
inline 
#endif 
void FracNoiseRemoveNoise(FracNoise* const that, 
  const PerlinNoisePod* const pod);

// Get the noise value of the FracNoise 'that' at 'pos'
VecFloat* _FracNoiseGet(const FracNoise* const that, 
  const VecFloat* const pos);

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
bool FracNoiseExportDF3(const FracNoise* const that, 
  const VecFloat3D* const range, const VecShort3D* const nbSample, 
  const int res, const bool rescale, const char* const fileName);

// ================ Polymorphism ====================
#define PerlinNoiseGet(Noise, U) _Generic(U, \
  VecFloat*: _PerlinNoiseGet, \
  const VecFloat*: _PerlinNoiseGet, \
  float: _PerlinNoiseGet1D, \
  const float: _PerlinNoiseGet1D, \
  VecFloat2D*: _PerlinNoiseGet2D, \
  const VecFloat2D*: _PerlinNoiseGet2D, \
  VecFloat3D*: _PerlinNoiseGet3D, \
  const VecFloat3D*: _PerlinNoiseGet3D, \
  default:PBErrInvalidPolymorphism) (Noise, U, 0.0)

#define PerlinNoisePodSetBound(Pod, Bound) _Generic(Bound, \
  Shapoid*: _PerlinNoisePodSetBound, \
  const Shapoid*: _PerlinNoisePodSetBound, \
  Facoid*: _PerlinNoisePodSetBound, \
  const Facoid*: _PerlinNoisePodSetBound, \
  Pyramidoid*: _PerlinNoisePodSetBound, \
  const Pyramidoid*: _PerlinNoisePodSetBound, \
  Spheroid*: _PerlinNoisePodSetBound, \
  const Spheroid*: _PerlinNoisePodSetBound, \
  default:PBErrInvalidPolymorphism) (Pod, (Shapoid*)Bound)

#define PerlinNoisePodSetScaleIn(Pod, Scale) _Generic(Scale, \
  VecFloat*: _PerlinNoisePodSetScaleIn, \
  const VecFloat*: _PerlinNoisePodSetScaleIn, \
  VecFloat2D*: _PerlinNoisePodSetScaleIn, \
  const VecFloat2D*: _PerlinNoisePodSetScaleIn, \
  VecFloat3D*: _PerlinNoisePodSetScaleIn, \
  const VecFloat3D*: _PerlinNoisePodSetScaleIn, \
  default:PBErrInvalidPolymorphism) (Pod, (const VecFloat*)(Scale))
  
#define PerlinNoisePodSetScaleOut(Pod, Scale) _Generic(Scale, \
  VecFloat*: _PerlinNoisePodSetScaleOut, \
  const VecFloat*: _PerlinNoisePodSetScaleOut, \
  VecFloat2D*: _PerlinNoisePodSetScaleOut, \
  const VecFloat2D*: _PerlinNoisePodSetScaleOut, \
  VecFloat3D*: _PerlinNoisePodSetScaleOut, \
  const VecFloat3D*: _PerlinNoisePodSetScaleOut, \
  default:PBErrInvalidPolymorphism) (Pod, (const VecFloat*)(Scale))
  
#define PerlinNoisePodSetShiftOut(Pod, Shift) _Generic(Shift, \
  VecFloat*: _PerlinNoisePodSetShiftOut, \
  const VecFloat*: _PerlinNoisePodSetShiftOut, \
  VecFloat2D*: _PerlinNoisePodSetShiftOut, \
  const VecFloat2D*: _PerlinNoisePodSetShiftOut, \
  VecFloat3D*: _PerlinNoisePodSetShiftOut, \
  const VecFloat3D*: _PerlinNoisePodSetShiftOut, \
  default:PBErrInvalidPolymorphism) (Pod, (const VecFloat*)(Shift))
  
#define FracNoiseGet(Noise, U) _Generic(U, \
  VecFloat*: _FracNoiseGet, \
  const VecFloat*: _FracNoiseGet, \
  VecFloat2D*: _FracNoiseGet, \
  const VecFloat2D*: _FracNoiseGet, \
  VecFloat3D*: _FracNoiseGet, \
  const VecFloat3D*: _FracNoiseGet, \
  default:PBErrInvalidPolymorphism) (Noise, (const VecFloat*)(U))

// ================ Inliner ====================

#if BUILDMODE != 0
#include "fracnoise-inline.c"
#endif

#endif
