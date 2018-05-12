#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "fracnoise.h"
#include "genbrush.h"

#define RANDOMSEED 2

// I have no idea if the names match, you'd be warned !!
typedef enum {
  cumulusA, cumulusB, stratusA, stratusB, stratusC
} typeCloud;

void MakeCloud(typeCloud type, int rndSeed, char* fileName) {
  srandom(rndSeed);
  //srandom(time(NULL));
  // Set parameters according to type
  float smoothness = 1.0;
  float nbPodMin = 50.0;
  float nbPodMax = 100.0;
  float sizeCompMin = 0.1;
  float sizeCompMax = 0.3;
  float scaleInY = 1.0;
  float borderMin = 0.1;
  float borderMax = 0.5;
  if (type == cumulusA) {
    smoothness = 0.1;
    nbPodMin = 50.0;
    nbPodMax = 100.0;
    sizeCompMin = 0.1;
    sizeCompMax = 0.3;
    scaleInY = 1.0;
  } else if (type == cumulusB) {
    smoothness = 0.1;
    nbPodMin = 100.0;
    nbPodMax = 150.0;
    sizeCompMin = 0.1;
    sizeCompMax = 0.3;
    scaleInY = 1.0;
    borderMin = 0.0;
    borderMax = 0.0;
  } else if (type == stratusA) {
    smoothness = 1.0;
    nbPodMin = 100.0;
    nbPodMax = 200.0;
    sizeCompMin = 0.05;
    sizeCompMax = 0.15;
    scaleInY = 1.0;
  } else if (type == stratusB) {
    smoothness = 0.1;
    nbPodMin = 100.0;
    nbPodMax = 200.0;
    sizeCompMin = 0.05;
    sizeCompMax = 0.15;
    scaleInY = 1.0;
  } else if (type == stratusC) {
    smoothness = 1.0;
    nbPodMin = 20.0;
    nbPodMax = 50.0;
    sizeCompMin = 0.1;
    sizeCompMax = 0.8;
    scaleInY = 0.2;
  }
  // Create the noise
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3); VecSet(&dim, 1, 1);
  FracNoise* cloud = FracNoiseCreate(&dim, NULL);
  // Create the cloud components
  int nbPod = (int)floor(nbPodMin + rnd() * (nbPodMax- nbPodMin));
  VecFloat3D seed = VecFloatCreateStatic3D();
  Spheroid** bounds = malloc(nbPod * sizeof(Spheroid*));
  VecFloat3D scaleIn = VecFloatCreateStatic3D();
  VecFloat3D scaleBound = VecFloatCreateStatic3D();
  PerlinNoisePod* pod = NULL;
  for (int iPod = nbPod; iPod--;) {
    if (iPod == 0)
      pod = FracNoiseGetNoise(cloud, 0);
    else {
      for (int i = 3; i--;)
        VecSet(&seed, i, rnd());
      pod = FracNoiseAddNoise(cloud, &seed);
    }
    bounds[iPod] = SpheroidCreate(3);
    PerlinNoisePodSetBound(pod, bounds[iPod]);
    float border = borderMin + (borderMax - borderMin) * rnd();
    PerlinNoisePodSetBorder(pod, border);
    float s = sizeCompMin + (sizeCompMax - sizeCompMin) * rnd();
    for (int i = 3; i--;)
      VecSet(&scaleBound, i, s * (i == 1 ? scaleInY : 1.0));
    ShapoidScale(bounds[iPod], (VecFloat*)&scaleBound);
    for (int i = 3; i--;) {
      float x = s + (1.0 - 2.0 * s) * rnd();
      if (type != cumulusB && i == 1 && x < 0.5)
        x = 0.5 - pow(0.5 - x, 2.0);
      VecSet(ShapoidPos(bounds[iPod]), i, x);
    }
    float sIn = 20.0 + 40.0 * rnd();
    for (int i = 3; i--;)
      VecSet(&scaleIn, i, sIn);
    PerlinNoisePodSetScaleIn(pod, &scaleIn);
    PerlinNoisePodSetSmooth(pod, smoothness);
  }
  // Export to the df3 file
  VecFloat3D range = VecFloatCreateStatic3D();
  VecSet(&range, 0, 1.0); VecSet(&range, 1, 1.0); 
  VecSet(&range, 2, 1.0); 
  VecShort3D nbSample = VecShortCreateStatic3D();
  VecSet(&nbSample, 0, 50); VecSet(&nbSample, 1, 50); 
  VecSet(&nbSample, 2, 50); 
  int res = 16;
  if (FracNoiseExportDF3(cloud, &range, &nbSample, res, false,
    fileName) == false) {
    fprintf(stderr, "export to df3 failed\n");
  }
  // Free memory
  FracNoiseFree(&cloud);
  for (int iPod = nbPod; iPod--;)
    ShapoidFree(bounds + iPod);
  free(bounds);
  
}

int main(int argc, char** argv) {
  (void)argc;(void)argv;
  char* fileName = "./cloud.df3";
  MakeCloud(cumulusB, RANDOMSEED, fileName);
  int ret = system("make DF3");(void)ret;
  
  //MakeCloud((typeCloud)atoi(argv[1]), RANDOMSEED, argv[2]);


  // Return success code
  return 0;
}

