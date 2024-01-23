light_ambient {
    rgb <1.0, 1.0, 1.0>
}

sphere {
    <0, 0, 0>, 20

    pigment { color rgb <0.1, 0.9, 0.1> }
        
    finish { 
        ambient  0.2
        diffuse  0.9
        specular 0.8  phong_size 90 
        refraction 0.8 ior 1.33
    }
    
    normal { none }
    
    mask { image_map { ppm maps/stripes.ppm } }
}

camera {
    screen_size 60
    density 300
    depth 1
    location <0, 0, 80> 
    look_at <0,0,0>
    sky <0,1,0>
}

light_source {
    <-50, 50, 50>, rgb <1.0, 1.0, 1.0>
}

light_source {
    <50, 25, -50>, rgb <1.0, 1.0, 1.0>
}
