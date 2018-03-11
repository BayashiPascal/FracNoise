#include "colors.inc"

#declare _posCamera = <2.5,0.0,2.5>;
#declare _lookAt = <0.0,0.1,0.0>;

camera {
  location    _posCamera
  look_at     _lookAt
  right x
  up y * 3/5
}

light_source {
  <10.0, 10.0, 20.5>
  color rgb 1.0
}

background { color rgb <0.0, 0.0, 0.0> }

#declare boxinterior = interior {
  media {
    method 3
    samples 10,10
    emission <0.9, 0.9, 1> 
    //emission <1.25, 1.25, 1.25> // cumulusB
    absorption <1.0, 1.0, 1.0>*2 
    scattering {1, <1, 1, 1>*1 extinction 1.0 }
    density {
      density_file df3 "./cloud.df3" 
        interpolate 1
    }
  }
}

#declare boxtexture = texture {
  pigment {
    rgbf 1
  }
}

box {
  <0,0,0>, <1,1,1>
  texture { boxtexture }
  interior { boxinterior }
  hollow
  scale <2,1,2>
  translate <-0.5,-0.25,-0.5>
}

plane {
  y, -1.0
  pigment { color rgb 0.7 }
}

sphere {
  <0.0,0.0,0.0>, 1000.0
  pigment {color <0.8,0.8,1.0>}
  hollow
}
