# FracNoise
FracNoise is a C library providing structures and functions to generate noise based on the Perlin noise.

The library provides the structure PerlinNoise and its functions to generate noise as described by Prof. Ken Perlin.

It also provides the structure FracNoise and its functions, which extends the PerlinNoise. A FracNoise is made of a composition of one or several PerlinNoise. Each of the composed PerlinNoise can be individually controled over its input/output values scale and shift; be attached to a boundary (Shapoid) outside of which the PerlinNoise is inactive, and inside of which it becomes smoothly active across a border width defined by the user; support a recursive definition with user defined depth and strength; have a 'smooth' parameter to set the aspect (round or spiky) of the PerlinNoise; have a user defined seed; return output as a vector of any dimension; take input as a vector of 1, 2 or 3 dimensions, however the limit of 3 can somehow be extended up to 6 by using the 3 components of the seed as input values too.

The FracNoise structure also provides an export function toward ".df3" density file to be used in computer graphics software like POV-Ray.
