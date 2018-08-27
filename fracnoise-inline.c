// ============ FRACNOISE-INLINE.C ================

// -------------- PerlinNoisePod

// ================ Functions implementation ====================

// Get the Perlin noise of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
const PerlinNoise* PerlinNoisePodNoise(const PerlinNoisePod* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return &(that->_noise);
}

// Get the seed of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
const VecFloat3D* PerlinNoisePodSeed(const PerlinNoisePod* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return (VecFloat3D*)&(that->_seed);
}

// Get the bound of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
Shapoid* PerlinNoisePodBound(const PerlinNoisePod* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return that->_bound;
}

// Get the scale of inputs of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
const VecFloat* PerlinNoisePodScaleIn(const PerlinNoisePod* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return that->_scaleIn;
}

// Get the scale of outputs of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
const VecFloat* PerlinNoisePodScaleOut(const PerlinNoisePod* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return that->_scaleOut;
}

// Get the shift of outputs of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* PerlinNoisePodShiftOut(const PerlinNoisePod* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return that->_shiftOut;
}

// Get the fractal level of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
int PerlinNoisePodGetFractLvl(const PerlinNoisePod* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return that->_fractalLvl;
}

// Get the fractal coefficient of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
float PerlinNoisePodGetFractCoeff(const PerlinNoisePod* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return that->_fractalCoeff;
}

// Get the border coefficient of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
float PerlinNoisePodGetBorder(const PerlinNoisePod* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return that->_border;
}

// Get the smoothness of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
float PerlinNoisePodGetSmooth(const PerlinNoisePod* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return that->_smooth;
}

// Get the squareness of the PerlinNoisePod 'that'
#if BUILDMODE != 0 
inline 
#endif 
float PerlinNoisePodGetSquare(const PerlinNoisePod* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return that->_square;
}

// Set the seed of the PerlinNoisePod 'that' to a copy of 'seed'
// If 'seed' is the vector null the seed is left unchanged 
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetSeed(PerlinNoisePod* const that, 
  const VecFloat3D* const seed) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (seed == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'seed' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Check if the seed is the vector null
  if (VecNorm(seed) < PBMATH_EPSILON)
    return;
  // Set the new seed
  that->_seed = *seed;
  // Make sure the seed is normalised
  VecNormalise(&(that->_seed));
}

// Set the bound of the PerlinNoisePod 'that' to 'bound'
// The Shapoid 'bound' must have same dimensions as the input dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetBound(PerlinNoisePod* const that, 
  Shapoid* const bound) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (bound == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'bound' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (ShapoidGetDim(bound) != VecGetDim(that->_scaleIn)) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, 
      "'bound' 's dimension is invalid (%d=%ld)",
      ShapoidGetDim(bound), VecGetDim(that->_scaleIn));
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Set the new bound
  that->_bound = bound;
}

// Set the scale of inputs of the PerlinNoisePod 'that' to a 
// copy of 'scale'
// 'scale' must have same dimension as the input dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetScaleIn(PerlinNoisePod* const that, 
  const VecFloat* const scale) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (scale == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'scale' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (VecGetDim(scale) != VecGetDim(that->_scaleIn)) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, 
      "'scale' 's dimension is invalid (%ld=%ld)",
      VecGetDim(scale), VecGetDim(that->_scaleIn));
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Set the new scale
  VecCopy(that->_scaleIn, scale);
}

// Set the scale of outputs of the PerlinNoisePod 'that' to a copy 
// of 'scale'
// 'scale' must have same dimension as the output dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetScaleOut(PerlinNoisePod* const that, const VecFloat* const scale) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (scale == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'scale' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (VecGetDim(scale) != VecGetDim(that->_scaleOut)) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, 
      "'scale' 's dimension is invalid (%ld=%ld)",
      VecGetDim(scale), VecGetDim(that->_scaleOut));
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Set the new scale
  VecCopy(that->_scaleOut, scale);
}

// Set the shift of outputs of the PerlinNoisePod 'that' to a copy 
// of 'shift'
// 'shift' must have same dimension as the output dimension
// of the PerlinNoisePod.
#if BUILDMODE != 0 
inline 
#endif 
void _PerlinNoisePodSetShiftOut(PerlinNoisePod* const that, 
  const VecFloat* const shift) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (shift == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'shift' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (VecGetDim(shift) != VecGetDim(that->_shiftOut)) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, 
      "'shift' 's dimension is invalid (%ld=%ld)",
      VecGetDim(shift), VecGetDim(that->_shiftOut));
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Set the new shift
  VecCopy(that->_shiftOut, shift);
}

// Set the fractal level of the PerlinNoisePod 'that' to 'lvl'
// 'lvl' must be greater than or equal to 0
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetFractLvl(PerlinNoisePod* const that, const int lvl) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (lvl < 0) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, "'lvl' is invalid (%d>=0)", lvl);
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Set the new level
  that->_fractalLvl = lvl;
}

// Set the fractal coefficient of the PerlinNoisePod 'that' to 'coeff'
// 'coeff' must be greater than 0.0, if it's negative its absolute 
// value is used
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetFractCoeff(PerlinNoisePod* const that, 
  const float coeff) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (fabs(coeff) < PBMATH_EPSILON) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, "'coeff' is equal to 0.0");
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Set the new coefficient
  that->_fractalCoeff = fabs(coeff);
}

// Set the fractal coefficient of the PerlinNoisePod 'that' to 'border'
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetBorder(PerlinNoisePod* const that, 
  const float border) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Set the new coefficient
  that->_border = border;
}

// Set the smoothness of the PerlinNoisePod 'that' to 'smooth'
// 'smooth' must be greater than 0.0
// Below 1.0 gives a bumpy aspect, above 1.0 gives a spiky aspect,
// 1.0 is the smoothest
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetSmooth(PerlinNoisePod* const that, 
  const float smooth) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (smooth < PBMATH_EPSILON) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, "'smooth' is invalid (%f>0)", smooth);
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Set the new coefficient
  that->_smooth = smooth;
}

// Set the squareness of the PerlinNoisePod 'that' to 'square'
// 'square' must be in [0.0, 1.0]
// 0.0 is the standard Perlin noise, 1.0 is the Perlin noise without
// the smoother function on input parameter
#if BUILDMODE != 0 
inline 
#endif 
void PerlinNoisePodSetSquare(PerlinNoisePod* const that, 
  const float square) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
  if (square < 0.0 || square > 1.0) {
    FracNoiseErr->_type = PBErrTypeInvalidArg;
    sprintf(FracNoiseErr->_msg, "'square' is invalid (0<=%f<1)", square);
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Set the new coefficient
  that->_square = square;
}

// -------------- FracNoise

// ================ Functions implementation ====================

// Get the dimensions of the noise 'that'
#if BUILDMODE != 0 
inline 
#endif 
const VecShort2D* FracNoiseDim(const FracNoise* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return &(that->_dim);
}

// Get the pods of the noise 'that'
#if BUILDMODE != 0 
inline 
#endif 
const GSet* FracNoisePods(const FracNoise* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  return &(that->_noises);
}


// Get the 'iNoise'-th noise of the FracNoise 'that'
// Return null if 'iNoise' is invalid
#if BUILDMODE != 0 
inline 
#endif 
PerlinNoisePod* FracNoisePod(const FracNoise* const that, 
  const int iNoise) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  if (iNoise < 0 || iNoise >= GSetNbElem(&(that->_noises)))
    return NULL;
  return (PerlinNoisePod*)GSetGet(&(that->_noises), iNoise);
}

// Add a new noise with seed 'seed' to the FracNoise 'that'
// If seed is null it is replaced by a default seed
// Return the new noise
#if BUILDMODE != 0 
inline 
#endif 
PerlinNoisePod* FracNoiseAddNoise(FracNoise* const that, 
  const VecFloat3D* const seed) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Create a new pod
  PerlinNoisePod* pod = PerlinNoisePodCreate(FracNoiseDim(that), seed);
  // Add the pod to the set of noises
  GSetAppend(&(that->_noises), pod);
  // Return the new pod
  return pod;
}

// Remove the PerlinNoisePod 'pod' from the FracNoise 'that'
#if BUILDMODE != 0 
inline 
#endif 
void FracNoiseRemoveNoise(FracNoise* const that, 
  const PerlinNoisePod* const pod) {
#if BUILDMODE == 0
  if (that == NULL) {
    FracNoiseErr->_type = PBErrTypeNullPointer;
    sprintf(FracNoiseErr->_msg, "'that' is null");
    PBErrCatch(FracNoiseErr);
  }
#endif
  // Loop on the set of noises
  GSetIterForward iter = GSetIterForwardCreateStatic(&(that->_noises));
  bool flag = true;
  do {
    // Get the current pod
    PerlinNoisePod* p = GSetIterGet(&iter);
    // If it's the searched pod
    if (p == pod) {
      // Remove from the set
      GSetIterRemoveElem(&iter);
      // Free memory
      PerlinNoisePodFree(&p);
      // End the loop on the set
      flag = false;
    }
  } while (flag && GSetIterStep(&iter));
}


