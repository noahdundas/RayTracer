light_ambient {
    rgb <1.0, 1.0, 1.0>
}

mesh {
    source { maps/bunny.pov flat direct }
    scale 50
    translate <0, 5, 0>
    
    finish { 
        ambient  0.2
        diffuse  0.9
        specular 0.8  phong_size 90 
        refraction 0.8 ior 1.33
    }
    
    pigment { color rgb <0.5, 0.5, 0.5> }
    
    normal { none }
    
    mask { none }
}

camera {
    screen_size 60
    density 1000
    depth 1
    location <0, 0, 80> 
    look_at <0,0,0>
    sky <0,1,0>
}

light_source {
    <-10, 30, 25>, rgb <1.0, 1.0, 1.0>
}