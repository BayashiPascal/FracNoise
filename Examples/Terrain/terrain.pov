#include "colors.inc"

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
}

light_source {
  <1.0, 2.0, 0.0>
  color rgb 1.0
  area_light <-0.1, 0, -0.1>, <0.1, 0, 0.1>, 3, 3
  adaptive 1
  jitter
}

background { color rgbft <1.0, 1.0, 1.0, 1.0, 1.0> }

intersection {
  height_field {
    tga 
    "HF.tga"
  }
  box {
    <0.0001,0.0001,0.0001>
    <0.9999,1.0,0.9999>
  }
  translate -0.5 * x
  scale <1.0, 0.25, 1.0>
  texture { _texNeutral }
}
