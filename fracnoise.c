// ============ FRACNOISE.C ================

// ================= Include =================

#include "fracnoise.h"
#if BUILDMODE == 0
  #include "fracnoise-inline.c"
#endif

// -------------- PerlinNoise

// Declare the permutations for the Perlin noise
int PerlinNoisePermutation[256] = {
  151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,
  103,30,69,142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,
  26,197,62,94,252,219,203,117,35,11,32,57,177,33,88,237,149,56,87,
  174,20,125,136,171,168,68,175,74,165,71,134,139,48,27,166,77,
  146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,
  40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,
  18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,
  3,64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,
  207,206,59,227,47,16,58,17,182,189,28,42,223,183,170,213,119,248,
  152,2,44,154,163,70,221,153,101,155,167,43,172,9,129,22,39,253,19,
  98,108,110,79,113,224,232,178,185,112,104,218,246,97,228,251,34,
  242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,
  107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,
  127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,
  78,66,215,61,156,180
  };

// ================ Functions definition ====================

inline float fade(float t);
inline float lerp(float t, float a, float b);
inline float grad(int hash, float x, float y, float z);

// ================ Functions implementation ====================

// Return a new PerlinNoise
PerlinNoise* PerlinNoiseCreate(void) {
  // Allocate memory
  PerlinNoise *noise = PBErrMalloc(FracNoiseErr, 
    sizeof(PerlinNoise));
  // Initialize the permutations
  PerlinNoiseSetPermut(noise, PerlinNoisePermutation);
  // Return the new PerlinNoise
  return noise;
}

// Return a new static PerlinNoise
PerlinNoise PerlinNoiseCreateStatic(void) {
  // Declare the noise
  PerlinNoise noise;
  // Initialize the permutations
  PerlinNoiseSetPermut(&noise, PerlinNoisePermutation);
  // Return the noise
  return noise;
}

// Set the permutations of the PerlinNoise 'that' to 'permut'
// 'permut' is an array of 256 int
void PerlinNoiseSetPermut(PerlinNoise* that, int* permut) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (permut == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'permut' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Set the permutations
  for (int i = 256; i--;) 
    that->_p[256 + i] = that->_p[i] = permut[i]; 
}

// Free the memory used by the PerlinNoise 'that'
void PerlinNoiseFree(PerlinNoise** that) {
  // Check arguments
  if (that == NULL || *that == NULL)
    return;
  // Free memory
  free(*that);
  *that = NULL;
}

// Return the value of the PerlinNoise 'that' at position 'u'
// 'u' can be of dimension 1 to 3, 'u' values in R, the Perlin noise
// has interpolation on unit, so u in [0.0, 1.0] will be interpolated
// between 2 values, u in [0.0, 2.0] will be interpolated between
// 3 values, and the noise always equal 0.5 at unit values, so
// noise(0.0) == noise(1.0) == noise(2.0) == ... == 0.5
// Return a value in [0.0, 1.0]
float _PerlinNoiseGet(PerlinNoise* that, VecFloat* p) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (p == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'p' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (VecGetDim(p) > 3) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, "'p' 's dimension is invalid (%d<4)",
      VecGetDim(p));
    PBErrCatch(FracNoiseErr);
  }
#endif
  if (VecGetDim(p) == 1)
    return _PerlinNoiseGet1D(that, VecGet(p, 0));
  else if (VecGetDim(p) == 2)
    return _PerlinNoiseGet2D(that, (VecFloat2D*)p);
  else if (VecGetDim(p) == 3)
    return _PerlinNoiseGet3D(that, (VecFloat3D*)p);
  else if (VecGetDim(p) > 3) {
    VecFloat* p3 = VecGetNewDim(p, 3);
    float ret = _PerlinNoiseGet3D(that, (VecFloat3D*)p3);
    VecFree(&p3);
    return ret;
  } else
    return 0.0;
}

float _PerlinNoiseGet1D(PerlinNoise* that, float p) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  int pInt;
  float q = 0.0;
  float u = 0.0;
  // Get the Unit cube that contains the point
  pInt = (int)floor(p) & 255;
  // Get the relative coordinates of the point in the cube
  q = p - floor(p);
  // Fade input for smooth transition
  u = SmootherStep(q);
  // Hash coordinates of the segment extremities
  int A = that->_p[pInt]; 
  int AA = that->_p[A]; 
  int B = that->_p[pInt + 1]; 
  int BA = that->_p[B]; 
  // Blend the value of the 8 cube corners according to relative
  // position in the cube
  float res = lerp(u, grad(that->_p[AA], q, 0.0, 0.0), 
    grad(that->_p[BA], q - 1.0, 0.0, 0.0));
  // Return the result mapped to [0.0, 1.0]
  res = res * 0.5 + 0.5;
  return res;
}

float _PerlinNoiseGet2D(PerlinNoise* that, VecFloat2D* p) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (p == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'p' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (VecGetDim(p) != 2) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, "'p' 's dimension is invalid (%d==2)",
      VecGetDim(p));
    PBErrCatch(FracNoiseErr);
  }
#endif
  int pInt[2];
  VecFloat2D q = VecFloatCreateStatic2D();
  VecFloat2D u = VecFloatCreateStatic2D();
  for (int i = 2; i--;) {
    // Get the Unit cube that contains the point
    pInt[i] = (int)floor(VecGet(p, i)) & 255;
    // Get the relative coordinates of the point in the cube
    VecSet(&q, i, VecGet(p, i) - floor(VecGet(p, i)));
    // Fade input for smooth transition
    VecSet(&u, i, SmootherStep(VecGet(&q, i)));
  }
  // Hash coordinates of the 8 cube corners
  int A = that->_p[pInt[0]] + pInt[1]; 
  int AA = that->_p[A]; 
  int AB = that->_p[A + 1];
  int B = that->_p[pInt[0] + 1] + pInt[1]; 
  int BA = that->_p[B]; 
  int BB = that->_p[B + 1];
  // Blend the value of the 8 cube corners according to relative
  // position in the cube
  float res = 
    lerp(0.0, 
      lerp(VecGet(&u, 1), 
        lerp(VecGet(&u, 0), 
          grad(that->_p[AA], 
            VecGet(&q, 0), VecGet(&q, 1), 0.0), 
          grad(that->_p[BA], 
            VecGet(&q, 0) - 1.0, VecGet(&q, 1), 0.0)),
        lerp(VecGet(&u, 0), 
          grad(that->_p[AB], 
            VecGet(&q, 0), VecGet(&q, 1) - 1.0, 0.0),
          grad(that->_p[BB], 
            VecGet(&q, 0) - 1.0, VecGet(&q, 1) - 1.0, 0.0))),
      lerp(VecGet(&u, 1), 
        lerp(VecGet(&u, 0), 
          grad(that->_p[AA + 1], 
            VecGet(&q, 0), VecGet(&q, 1), -1.0),
          grad(that->_p[BA + 1], 
            VecGet(&q, 0) - 1.0, VecGet(&q, 1), -1.0)),
        lerp(VecGet(&u, 0), 
          grad(that->_p[AB + 1], 
            VecGet(&q, 0), VecGet(&q, 1) - 1.0, -1.0),
          grad(that->_p[BB + 1], 
            VecGet(&q, 0) - 1.0, VecGet(&q, 1) - 1.0, -1.0))));
  // Return the result mapped to [0.0, 1.0]
  res = res * 0.5 + 0.5;
  return res;
}

float _PerlinNoiseGet3D(PerlinNoise* that, VecFloat3D* p) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (p == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'p' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (VecGetDim(p) != 3) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, "'p' 's dimension is invalid (%d==3)",
      VecGetDim(p));
    PBErrCatch(FracNoiseErr);
  }
#endif
  int pInt[3];
  VecFloat3D q = VecFloatCreateStatic3D();
  VecFloat3D u = VecFloatCreateStatic3D();
  for (int i = 3; i--;) {
    // Get the Unit cube that contains the point
    pInt[i] = (int)floor(VecGet(p, i)) & 255;
    // Get the relative coordinates of the point in the cube
    VecSet(&q, i, VecGet(p, i) - floor(VecGet(p, i)));
    // Fade input for smooth transition
    VecSet(&u, i, SmootherStep(VecGet(&q, i)));
  }
  // Hash coordinates of the 8 cube corners
  int A = that->_p[pInt[0]] + pInt[1]; 
  int AA = that->_p[A] + pInt[2]; 
  int AB = that->_p[A + 1] + pInt[2];
  int B = that->_p[pInt[0] + 1] + pInt[1]; 
  int BA = that->_p[B] + pInt[2]; 
  int BB = that->_p[B + 1] + pInt[2];
  // Blend the value of the 8 cube corners according to relative
  // position in the cube
  float res = 
    lerp(VecGet(&u, 2), 
      lerp(VecGet(&u, 1), 
        lerp(VecGet(&u, 0), 
          grad(that->_p[AA], 
            VecGet(&q, 0), VecGet(&q, 1), VecGet(&q, 2)), 
          grad(that->_p[BA], 
            VecGet(&q, 0) - 1.0, VecGet(&q, 1), VecGet(&q, 2))),
        lerp(VecGet(&u, 0), 
          grad(that->_p[AB], 
            VecGet(&q, 0), VecGet(&q, 1) - 1.0, VecGet(&q, 2)),
          grad(that->_p[BB], 
            VecGet(&q, 0) - 1.0, VecGet(&q, 1) - 1.0, VecGet(&q, 2)))),
      lerp(VecGet(&u, 1), 
        lerp(VecGet(&u, 0), 
          grad(that->_p[AA + 1], 
            VecGet(&q, 0), VecGet(&q, 1), VecGet(&q, 2) - 1.0),
          grad(that->_p[BA + 1], 
            VecGet(&q, 0) - 1.0, VecGet(&q, 1), VecGet(&q, 2) - 1.0)),
        lerp(VecGet(&u, 0), 
          grad(that->_p[AB + 1], 
            VecGet(&q, 0), VecGet(&q, 1) - 1.0, VecGet(&q, 2) - 1.0),
          grad(that->_p[BB + 1], 
            VecGet(&q, 0) - 1.0, VecGet(&q, 1) - 1.0, 
            VecGet(&q, 2) - 1.0))));
  // Return the result mapped to [0.0, 1.0]
  res = res * 0.5 + 0.5;
  return res;
}

inline float fade(float t) { 
  float ret = t * t * t * (t * (t * 6.0 - 15.0) + 10.0); 
  return ret;
}

inline float lerp(float t, float a, float b) { 
  float ret = a + t * (b - a); 
  return ret;
}

float grad(int hash, float x, float y, float z) {
  int h = hash & 15;
  float u = h < 8 ? x : y;
  float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

// -------------- PerlinNoisePod

// ================ Functions implementation ====================

// Return a new PerlinNoisePod with output dimension 'dimOut' and seed
// 'seed'
// If the seed is the vector null replace it by (1,1,1)
// Default values:
// bound = NULL, border = 0.1, scaleIn/Out = 1.0
// fractalLvl = 0, fractalCoeff = 0.1, smooth = 1.0
PerlinNoisePod* PerlinNoisePodCreate(VecShort2D* dim, VecFloat3D* seed) {
#if BUILDMODE == 0
  if (VecGet(dim, 0) < 1 || VecGet(dim, 0) > 3 ||
    VecGet(dim, 1) < 1) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, "'dim' is invalid (0<%d<4,0<%d)",
      VecGet(dim, 0), VecGet(dim, 1));
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Declare the new PerlinNoisePod
  PerlinNoisePod* pod = PBErrMalloc(FracNoiseErr, 
    sizeof(PerlinNoisePod));
  // Set properties
  pod->_noise = PerlinNoiseCreateStatic();
  // If the seed is not given or is the vector null replace it by (1,1,1)
  if (seed == NULL || VecNorm(seed) < PBMATH_EPSILON) {
    pod->_seed = VecFloatCreateStatic3D();
    for (int i = 3; i--;)
      VecSet(&(pod->_seed), i, 1.0);
  // Else, copy the seed in argument
  } else {
    pod->_seed = *seed;
  }
  // Ensure the seed is normalized
  VecNormalise(&(pod->_seed));
  pod->_bound = NULL;
  pod->_border = 0.1;
  pod->_smooth = 1.0;
  pod->_scaleIn = VecFloatCreate(VecGet(dim, 0));
  for (int i = VecGet(dim, 0); i--;)
    VecSet(pod->_scaleIn, i, 1.0);
  pod->_scaleOut = VecFloatCreate(VecGet(dim, 1));
  for (int i = VecGet(dim, 1); i--;)
    VecSet(pod->_scaleOut, i, 1.0);
  pod->_shiftOut = VecFloatCreate(VecGet(dim, 1));
  pod->_fractalLvl = 0;
  pod->_fractalCoeff = 0.1;
  // Return the new pod
  return pod;
}

// Free memory used by the PerlinNoisePod 'that'
void PerlinNoisePodFree(PerlinNoisePod** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    // Nothing to do
    return;
  // Free memory
  VecFree(&((*that)->_scaleIn));
  VecFree(&((*that)->_scaleOut));
  VecFree(&((*that)->_shiftOut));
  free(*that);
  *that = NULL;
}

// Get the insideness in boundary of the PerlinNoisePod 'that' at 
// position 'pos'
// If there is no bounday it's always 1.0
// If there is boundary, it's 0.0 outside of boundary and else it's
// the position depth in the Shapoid corrected with the border as follow:
// if depth > border the depth is set to 1.0, else the depth is
// SmootherStep from (0.0, border) to (0.0, 1.0)
// 'pos' 's dimension must be equal to the Shapoid's dimension
float PerlinNoisePodGetInsideness(PerlinNoisePod* that, VecFloat* pos) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (pos == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'pos' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (that->_bound != NULL &&
    VecGetDim(pos) != ShapoidGetDim(that->_bound)) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, 
      "'pos' 's dimension is invalid (%d=%d)",
      VecGetDim(pos), ShapoidGetDim(that->_bound));
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Declare a variable to memorize the insideness in boundary
  float inside = 1.0;
  // If there is a boundary 
  if (PerlinNoisePodBound(that) != NULL) {
    // Get the insideness of the input
    inside = ShapoidGetPosDepth(PerlinNoisePodBound(that), pos);
    // If there is a border
    float border = PerlinNoisePodGetBorder(that);
    if (border > PBMATH_EPSILON) {
      // Correct insideness with border: inside the border apply a 
      // smootherstep transition and outside set to 1.0
      if (inside < border)
        inside = SmootherStep(inside / border);
      else
        inside = 1.0;
    }
  }
  // Return the insideness
  return inside;
}

// -------------- FracNoise

// ================ Functions implementation ====================

// Return a new FracNoise of dimensions 'dim' and seed 'seed'
// The number of input must be between 1 and 3
// The number of output can be any value greater or equal to 1
// If seed is null it is replaced by a default seed
// Return null if the number of dimensions are invalid
FracNoise* FracNoiseCreate(VecShort2D* dim, VecFloat3D* seed) {
#if BUILDMODE == 0
  if (dim == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'dim' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (VecGet(dim, 0) < 1 || VecGet(dim, 0) > 3 ||
    VecGet(dim, 1) < 1) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, "'dim' is invalid (0<%d<4,0<%d)",
      VecGet(dim, 0), VecGet(dim, 1));
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Check the dimensions
  if (VecGet(dim, 0) < 1 || VecGet(dim, 0) > 3 ||
    VecGet(dim, 1) < 1)
    return NULL;
  // Declare the new FracNoise
  FracNoise* noise = PBErrMalloc(FracNoiseErr, sizeof(FracNoise));
  // Set properties
  noise->_dim = VecShortCreateStatic2D();
  noise->_dim = *dim;
  noise->_noises = GSetCreateStatic();
  // Add a PerlinNoise
  PerlinNoisePod* pod = PerlinNoisePodCreate(dim, seed);
  GSetAppend(&(noise->_noises), pod);
  // Return the new FracNoise
  return noise;
}

// Free the memory used by the FracNoise 'that'
void FracNoiseFree(FracNoise** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    // Nothing to do
    return;
  // Free memory
  while (GSetNbElem(&((*that)->_noises)) > 0) {
    PerlinNoisePod* pod = GSetPop(&((*that)->_noises));
    PerlinNoisePodFree(&pod);
  }
  free(*that);
  *that = NULL;
}

// Get the noise value of the FracNoise 'that' at 'pos'
VecFloat* _FracNoiseGet(FracNoise* that, VecFloat* pos) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (pos == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'pos' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (VecGetDim(pos) != VecGet(&(that->_dim), 0)) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, 
      "'pos' 's dimension is invalid (%d==%d)",
      VecGetDim(pos), VecGet(&(that->_dim), 0));
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Create the result
  VecFloat* res = VecFloatCreate(VecGet(FracNoiseDim(that), 1));
  // Loop on noises
  GSetIterForward iter = 
    GSetIterForwardCreateStatic(FracNoisePods(that));
  do {
    // Get the current pod
    PerlinNoisePod* pod = GSetIterGet(&iter);
    // Get the insideness
    float inside = PerlinNoisePodGetInsideness(pod, pos);
    // If we are inside the boundary
    if (inside > PBMATH_EPSILON) {
      // Internally FracNoise always considers the input position as 3D,
      // declare a 3D version of it
      VecFloat3D* p = (VecFloat3D*)VecGetNewDim(pos, 3);
      // Scale the input
      for (int i = MIN(3, VecGetDim(pos)); i--;)
        VecSet(p, i, 
          VecGet(p, i) * VecGet(PerlinNoisePodScaleIn(pod), i));
      // Declare a variable to memorize the rotated version of the input
      VecFloat3D pRot = VecFloatCreateStatic3D();
      // Declare a variable to memorize the result for this pod
      VecFloat* resPod = VecFloatCreate(VecGet(FracNoiseDim(that), 1));
      // Declare a variable to memorize the current fractal coefficient
      float fractCoeff = 1.0;
      // Declare a variable to memorize the fractal coeff
      float fc = PerlinNoisePodGetFractCoeff(pod);
      // Get the angle for rotation of input vector over dimensions
      float theta = 
        PBMATH_TWOPI / (float)(VecGet(FracNoiseDim(that), 1) + 1);
      // Loop on fractal levels
      for (int iFract = PerlinNoisePodGetFractLvl(pod) + 1; iFract--;) {
        // If we are not at the first fractal level
        if (iFract != PerlinNoisePodGetFractLvl(pod))
          // Rescale to ensure the values stay in [0.0, 1.0] as addition
          // over fractal levels may bring the value outside this range
          VecScale(resPod, 1.0 / (1.0 + fractCoeff));
        // Loop on output dimension
        VecCopy(&pRot, p);
        for (int iDim = VecGet(FracNoiseDim(that), 1); iDim--;) {
          // Apply the seed
          VecRotAxis(&pRot, PerlinNoisePodSeed(pod), theta);
          // Get the Perlin noise value
          float val = _PerlinNoiseGet3D(PerlinNoisePodNoise(pod), &pRot);
          // Add the value for the current dimension at the current 
          // fractal level
          VecSet(resPod, iDim, VecGet(resPod, iDim) + val * fractCoeff);
        }
        // Update the fractal coefficient
        fractCoeff *= fc;
        // Update the input position at this level
        VecScale(p, 1.0 / fc);
      }
      // Apply the smoothness
      for (int i = VecGetDim(resPod); i--;)
        VecSet(resPod, i, 
          pow(VecGet(resPod, i), PerlinNoisePodGetSmooth(pod)));
      // Scale the output
      for (int i = VecGetDim(resPod); i--;)
        VecSet(resPod, i, 
          VecGet(resPod, i) * VecGet(PerlinNoisePodScaleOut(pod), i));
      // Shift the output
      VecOp(resPod, 1.0, PerlinNoisePodShiftOut(pod), 1.0);
      // Apply the insideness
      for (int i = VecGetDim(resPod); i--;)
        VecSet(resPod, i, VecGet(resPod, i) * inside);
      // Add the result for this pod
      VecOp(res, 1.0, resPod, 1.0);
      // Free memory
      VecFree(&resPod);
      VecFree((VecFloat**)&p);
    }
  } while (GSetIterStep(&iter));
  // Return the result
  return res;
}

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
  VecShort3D* nbSample, int res, bool rescale, char* fileName) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (range == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'range' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (nbSample == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'nbSample' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (fileName == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'fileName' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (VecGet(FracNoiseDim(that), 0) != 3) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, 
      "'that' 's input dimension is invalid (%d==3)",
      VecGet(FracNoiseDim(that), 0));
    PBErrCatch(FracNoiseErr);
  }
  if (VecGet(FracNoiseDim(that), 1) != 1) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, 
      "'that' 's output dimension is invalid (%d==1)",
      VecGet(FracNoiseDim(that), 1));
    PBErrCatch(FracNoiseErr);
  }
  if (VecGet(nbSample, 0) <= 0 ||
    VecGet(nbSample, 1) <= 0 ||
    VecGet(nbSample, 2) <= 0) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, 
      "'nbSample' is invalid (<%d,%d,%d> > <0,0,0>)",
      VecGet(nbSample, 0), VecGet(nbSample, 1), VecGet(nbSample, 2));
    PBErrCatch(FracNoiseErr);
  }
  if (res != 8 && res != 16 && res != 32) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, 
      "'res' is invalid (%d=={8,16,32})", res);
    PBErrCatch(FracNoiseErr);
  }
  if (GSetNbElem(&(that->_noises)) == 0) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, "'that' is empty");
    PBErrCatch(FracNoiseErr);
  }
  if (sizeof(unsigned char) != 1 ||
    sizeof(unsigned short) != 2 ||
    sizeof(unsigned int) != 4) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, 
      "types' size mismatched (%d==1,%d==2,%d==4)",
      sizeof(unsigned char),sizeof(unsigned short),
      sizeof(unsigned int));
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Check arguments
  if (VecGet(FracNoiseDim(that), 0) != 3 ||
    VecGet(FracNoiseDim(that), 1) != 1 ||
    VecGet(nbSample, 0) <= 0 ||
    VecGet(nbSample, 1) <= 0 ||
    VecGet(nbSample, 2) <= 0 ||
    (res != 8 && res != 16 && res != 32) ||
    GSetNbElem(&(that->_noises)) == 0)
    return false;
  // Get the min and max values of the noise for automatic rescaling
  float min = 0.0;
  float max = 1.0;
  if (rescale) {
    PerlinNoisePod* pod = FracNoiseGetNoise(that, 0);
    if (VecGet(PerlinNoisePodScaleOut(pod), 0) > 0.0) {
      min = VecGet(PerlinNoisePodShiftOut(pod), 0);
      max = min + VecGet(PerlinNoisePodScaleOut(pod), 0);
    } else {
      max = VecGet(PerlinNoisePodShiftOut(pod), 0);
      min = max + VecGet(PerlinNoisePodScaleOut(pod), 0);
    }
    for (int iNoise = 1; iNoise < GSetNbElem(&(that->_noises)); 
      ++iNoise) {
      pod = FracNoiseGetNoise(that, iNoise);
      float minP = 0.0;
      float maxP = 1.0;
      if (VecGet(PerlinNoisePodScaleOut(pod), 0) > 0.0) {
        minP = VecGet(PerlinNoisePodShiftOut(pod), 0);
        maxP = minP + VecGet(PerlinNoisePodScaleOut(pod), 0);
      } else {
        maxP = VecGet(PerlinNoisePodShiftOut(pod), 0);
        minP = maxP + VecGet(PerlinNoisePodScaleOut(pod), 0);
      }
      if (minP < 0.0)
        min += minP;
      if (maxP > 0.0)
        max += maxP;
    }
  }
  // Open the file
  FILE* file = fopen(fileName, "wb");
  // If we couldn't open the file
  if (file == NULL)
    // Stop here
    return false;
  // Write the header
  for (int i = 0; i < 3; ++i) {
    unsigned short v = VecGet(nbSample, i);
    // Big-endian !
    char* ptr = (char*)&v;
    for (int ip = sizeof(unsigned short); ip--;)
      fwrite(ptr + ip, 1, 1, file);
  }
  // Write the body
  // Loop on position
  VecShort3D pos = VecShortCreateStatic3D();
  do {
    // Get the equivalent input
    VecFloat3D u = VecFloatCreateStatic3D();
    for (int i = 3; i--;)
      VecSet(&u, i, 
        (float)VecGet(&pos, i) / (float)VecGet(nbSample, i) *
        VecGet(range, i));
    // Get the noise value
    VecFloat* out = FracNoiseGet(that, &u);
    float val = VecGet(out, 0);
    VecFree(&out);
    // Scale or clip the output value
    if (rescale)
      val = (val - min) / (max - min);
    if (val < 0.0)
      val = 0.0;
    else if (val > 1.0)
      val = 1.0;
    // Write the value according to resolution
    if (res == 8) {
      unsigned char vChar = (unsigned char)round(val * 255.0);
      fwrite(&vChar, sizeof(unsigned char), 1, file);
    } else if (res == 16) {
      unsigned short vShort = (unsigned short)round(val * 65535.0);
      // Big-endian !
      char* ptr = (char*)&vShort;
      for (int ip = sizeof(unsigned short); ip--;)
        fwrite(ptr + ip, 1, 1, file);
    } else if (res == 32) {
      unsigned int vInt = (unsigned int)round(val * 4294967296.0);
      // Big-endian !
      char* ptr = (char*)&vInt;
      for (int ip = sizeof(unsigned int); ip--;)
        fwrite(ptr + ip, 1, 1, file);
    }
  // The data in df3 are stored as z,y,x -> PStep
  } while (VecPStep(&pos, nbSample));
  // Close the file
  fclose(file);
  // Return the success code
  return true;
}

