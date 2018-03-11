#include "colors.inc"

#declare _posCamera = <2.0,2.0,2.0>;
#declare _lookAt = <0.0,0.0,0.0>;

camera {
  location    _posCamera
  look_at     _lookAt
  right x
  up y * 3/5
}

light_source {
  <1.0, 1.0, 0.5>
  color rgb 1.0
}

background { color rgb <0.0, 0.0, 0.0> }

#declare boxinterior = interior {
  media {
    intervals 300
    samples 1,20
    emission <1,1,1>
    absorption <0,0,0>
    scattering { 1,<0,0,0> }
    confidence 0.9999
    variance 1/1000
    density {
      density_file df3 "./UnitTestFracNoiseExport.df3" 
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
  translate <-0.5,-0.5,-0.5>
}

cylinder {
  <-10.0, 0.0, 0.0>, <10.0, 0.0, 0.0>, 0.005
  texture { pigment { color Red }}
}
cylinder {
  <0.0, -10.0, 0.0>, <0.0, 10.0, 0.0>, 0.005
  texture { pigment { color Green }}
}
cylinder {
  <0.0, 0.0, -10.0>, <0.0, 0.0, 10.0>, 0.005
  texture { pigment { color Blue }}
}
