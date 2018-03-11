#include "colors.inc"
#include "rock.inc"

#declare _texNeutral = texture {
  pigment { color rgb <0.75, 0.75, 0.75> }
  finish { ambient 0.1 diffuse 0.6 phong 0.0}
}

#declare _posCamera = <3.0,0.0,3.0>;
#declare _lookAt = <0.0,0.0,0.0>;

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

background { color rgb <1.0, 1.0, 1.0> }

object {
  rock
  texture {_texNeutral}
}
