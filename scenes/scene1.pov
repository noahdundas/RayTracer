light_ambient {
    rgb <1.0, 1.0, 1.0>
}

mesh {
    source { maps/cat.pov flat direct }
    scale 20
    translate <0, 0, 0>
    
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

sphere {
    <-25, 25, -50>, 12

    pigment { color rgb <0.7, 0.7, 0.1> }
        
    finish { 
        ambient  0.2
        diffuse  0.9
        specular 0.8  phong_size 90 
        refraction 0.8 ior 1.33
    }
    
    normal { none }
    
    mask { none }
}

hyperboloid {
    <25, 25, -50>, 10, 10, 10, 10

    pigment { color rgb <0.9, 0.3, 0.9> }
        
    finish { 
        ambient  0.2
        diffuse  0.4
        specular 0.9  phong_size 130 
        refraction 0.8 ior 1.33
    }
}

cylinder {
    <-25, -25, -50>, 10, 20

    pigment { color rgb <0.3, 0.3, 0.9> }
        
    finish { 
        ambient  0.2
        diffuse  0.9
        specular 0.8  phong_size 90 
        refraction 0.8 ior 1.33
    }
}

cone {
    <25, -15, -50>, 15, 20, 15

    pigment { color rgb <0.1, 0.7, 0.1> }
        
    finish { 
        ambient  0.2
        diffuse  0.9
        specular 0.8  phong_size 90 
        refraction 0.8 ior 1.33
    }
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
    <-50, 50, 0>, rgb <1.0, 1.0, 1.0>
}