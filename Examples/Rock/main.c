#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "fracnoise.h"
#include "genbrush.h"

#define RANDOMSEED 30

typedef enum {
  rockA, rockB
} typeRock;

void MakeRock(typeRock type, int rndSeed, char* fileName, 
  VecFloat3D* radiusRock) {
  srandom(rndSeed);
  // Parameters
  float fractCoeff = 0.1;
  float smooth = 0.5;
  float scaleInXZ = 3.0;
  float scaleInY = 5.0;
  float scaleOut = 0.3;
  if (type == rockA) {
    fractCoeff = 0.05 + 0.15 * rnd();
    smooth = 0.1 + 1.9 * rnd();
    scaleInXZ = 1.0 + 4.0 * rnd();
    scaleInY = 1.0 + 4.0 * rnd();
    scaleOut = 0.1 + 0.2 * rnd();
  } else if (type == rockB) {
    fractCoeff = 0.1;
    smooth = 1.0;
    scaleInXZ = 2.0 * rnd();
    scaleInY = 2.0 * rnd();
    scaleOut = 0.1 + 0.2 * rnd();
  }
  // Create the FracNoise for the rock
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3); VecSet(&dim, 1, 3);
  VecFloat3D seed = VecFloatCreateStatic3D();
  for (int i = 3; i--;)
    VecSet(&seed, i, rnd());
  FracNoise* rock = FracNoiseCreate(&dim, &seed);
  PerlinNoisePod* pod = FracNoiseGetNoise(rock, 0);
  if (type == rockB)
    PerlinNoisePodSetSquare(pod, 0.8);
  VecFloat3D scaleIn = VecFloatCreateStatic3D();
  for (int i = 3; i--;)
    VecSet(&scaleIn, i, (i == 1 ? scaleInY : scaleInXZ));
  PerlinNoisePodSetScaleIn(pod, &scaleIn);
  VecFloat3D sOut = VecFloatCreateStatic3D();
  for (int i = 3; i--;)
    VecSet(&sOut, i, scaleOut);
  PerlinNoisePodSetScaleOut(pod, &sOut);
  for (int i = 3; i--;)
    VecSet(&sOut, i, -0.5 * scaleOut);
  PerlinNoisePodSetShiftOut(pod, &sOut);
  if (type != rockB)
    PerlinNoisePodSetFractLvl(pod, 1);
  PerlinNoisePodSetFractCoeff(pod, fractCoeff);
  PerlinNoisePodSetSmooth(pod, smooth);
  // Open the file to save the rock mesh
  FILE* fileRock = fopen(fileName, "w");
  // Print the head of the mesh
  fprintf(fileRock, "#declare rock = mesh {\n");
  // Loop on the polar coordinates
  float theta = 0.0;
  float phi = 0.0;
  float delta = PBMATH_TWOPI_DIV_360 * 1.0;
  VecFloat3D pos = VecFloatCreateStatic3D();
  float vtheta[4];
  float vphi[4];
  bool flagRow = true;
  for (phi = 0.0; phi < PBMATH_TWOPI; phi += delta) {
    for (theta = 0.0; theta < PBMATH_PI; theta += delta) {
      // Calculate the polar coordinates of vertices
      if (flagRow) {
        vtheta[0] = theta - delta * 0.5;
        vtheta[1] = theta;
        vtheta[2] = theta + delta * 0.5;
        vtheta[3] = theta + delta;
      } else {
        vtheta[0] = theta;
        vtheta[1] = theta - delta * 0.5;
        vtheta[2] = theta + delta;
        vtheta[3] = theta + delta * 0.5;
      }
      vphi[0] = phi + delta;
      vphi[1] = phi;
      vphi[2] = phi + delta;
      vphi[3] = phi;
      // Calculate the coordinates of vertices and write the 2 triangles
      fprintf(fileRock, "triangle {");
      for (int iv = 3; iv--;) {
        VecSet(&pos, 0, 
          VecGet(radiusRock, 0) * sin(vtheta[iv]) * cos(vphi[iv]));
        VecSet(&pos, 1, 
          VecGet(radiusRock, 1) * cos(vtheta[iv]));
        VecSet(&pos, 2, 
          VecGet(radiusRock, 2) * sin(vtheta[iv]) * sin(vphi[iv]));
        VecFloat* vert = FracNoiseGet(rock, &pos);
        VecOp(vert, 1.0, (VecFloat*)&pos, 1.0);
        VecFloatPrint(vert, fileRock, 5);
        if (iv != 0)
          fprintf(fileRock, ",");
        VecFree(&vert);
      }
      fprintf(fileRock, "}\n");
      fprintf(fileRock, "triangle {");
      for (int iv = 1; iv < 4; ++iv) {
        VecSet(&pos, 0, 
          VecGet(radiusRock, 0) * sin(vtheta[iv]) * cos(vphi[iv]));
        VecSet(&pos, 1, 
          VecGet(radiusRock, 1) * cos(vtheta[iv]));
        VecSet(&pos, 2, 
          VecGet(radiusRock, 2) * sin(vtheta[iv]) * sin(vphi[iv]));
        VecFloat* vert = FracNoiseGet(rock, &pos);
        VecOp(vert, 1.0, (VecFloat*)&pos, 1.0);
        VecFloatPrint(vert, fileRock, 5);
        if (iv != 3)
          fprintf(fileRock, ",");
        VecFree(&vert);
      }
      fprintf(fileRock, "}\n");
    }
    flagRow = (flagRow ? false : true);
  }
  // Print the tail of the mesh
  fprintf(fileRock, "};\n");
  fclose(fileRock);
}

int main(int argc, char** argv) {
  char* fileName = "./rock.inc";

  VecFloat3D radiusRock = VecFloatCreateStatic3D();
  VecSet(&radiusRock, 0, 1.0);
  VecSet(&radiusRock, 1, 0.5);
  VecSet(&radiusRock, 2, 1.0);
  //MakeRock(rockA, RANDOMSEED, fileName, &radiusRock);
  MakeRock(rockB, time(NULL), fileName, &radiusRock);
  system("make rock");
  //MakeRock(rockA, time(NULL), argv[1], &radiusRock);


  // Return success code
  return 0;
}

