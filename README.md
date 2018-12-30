# FracNoise
FracNoise is a C library providing structures and functions to generate noise based on the Perlin noise.

The library provides the structure PerlinNoise and its functions to generate noise as described by Prof. Ken Perlin.

It also provides the structure FracNoise and its functions, which extends the PerlinNoise. A FracNoise is made of a composition of one or several PerlinNoise. Each of the composed PerlinNoise can be individually controled over its input/output values scale and shift; be attached to a boundary (Shapoid) outside of which the PerlinNoise is inactive, and inside of which it becomes smoothly active across a border width defined by the user; support a recursive definition with user defined depth and strength; have a 'smooth' parameter to set the aspect (round or spiky) of the PerlinNoise; have a user defined seed; return output as a vector of any dimension; take input as a vector of 1, 2 or 3 dimensions, however the limit of 3 can somehow be extended up to 6 by using the 3 components of the seed as input values too.

The FracNoise structure also provides an export function toward ".df3" density file to be used in computer graphics software like POV-Ray.

Examples of how to use the FracNoise to generate terrains, rocks and clouds are provided.

## How to install this repository
1) Create a directory which will contains this repository and all the repositories it is depending on. Lets call it "Repos"
2) Download the master branch of this repository into "Repos". Unzip it if necessary.
3) The folder's name for the repository should be followed by "-master", rename the folder by removing "-master".
4) cd to the repository's folder
5) If wget is not installed: ```sudo apt-get update && sudo apt-get install wget``` on Ubuntu 16.04, or ```brew install wget``` on Mac OSx
6) If gawk is not installed: ```sudo apt-get update && sudo apt-get install gawk```  on Ubuntu 16.04, ```brew install gawk``` on Mac OSx
7) If this repository is the first one you are installing in "Repos", run the command ```make -k pbmake_wget```
8) Run the command ```make``` to compile the repository. 
9) Eventually, run the command ```main``` to run the unit tests and check everything is ok.
10) Refer to the documentation to learn how to use this repository.

The dependancies to other repositories should be resolved automatically and needed repositories should be installed in the "Repos" folder. However this process is not completely functional and some repositories may need to be installed manually. In this case, you will see a message from the compiler saying it cannot find some headers. Then install the missing repository with the following command, e.g. if "pbmath.h" is missing: ```make pbmath_wget```. The repositories should compile fine on Ubuntu 16.04. On Mac OSx, there is currently a problem with the linker.
If you need assistance feel free to contact me with my gmail address: at bayashipascal.
