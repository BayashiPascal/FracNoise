#include "colors.inc"

// unit is meter

#declare _texNeutral = texture {
  pigment { color rgb <0.75, 0.75, 0.75> }
  finish { ambient 0.1 diffuse 0.6 phong 0.0}
}

#declare _tex = texture {
  pigment { color White }
}

#declare RndSeed = seed(30);
#declare _posCamera = <0.0,1.0,2.0>;
#declare _lookAt = <0.0,0.0,0.5>;

camera {
  location    _posCamera
  look_at     _lookAt
  right x
  up y * 3/5
  /*focal_point _lookAt
  aperture 0.1
  blur_samples 50*/
}

light_source {
  <1.0, 1.0, 0.5>
  color rgb 1.0
  /*area_light <-0.1, 0, -0.1>, <0.1, 0, 0.1>, 3, 3
  adaptive 1
  jitter*/
}

background { color rgbft <1.0, 1.0, 1.0, 1.0, 1.0> }

//global_settings { ambient_light 0 radiosity {brightness 0.5}}


intersection {
  height_field {
    tga 
    //"UnitTestPerlinNoise.tga"
    "test.tga"
  }
  box {
    <0.0001,0.0001,0.0001>
    <0.9999,1.0,0.9999>
  }
  scale <1.0, 0.2, 1.0>
  translate -0.5 * x
  texture { _texNeutral }
}
