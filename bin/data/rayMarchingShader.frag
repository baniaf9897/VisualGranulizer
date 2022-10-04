// fragment shader

#version 150
in vec4 vertColor;
in vec2 texCoordVarying;

out vec4 outputColor;


uniform sampler2DRect texture;
uniform vec3 uCameraPosition;
uniform vec3 uCameraDir;
uniform float scale;

uniform vec2 screenSize;

float distance_from_sphere(in vec3 p, in vec3 c, float r)
{
    return length(p - c) - r;
}


float opSmoothUnion( float d1, float d2, float k ) {
    float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
    return mix( d2, d1, h ) - k*h*(1.0-h); 
    
 }

float map_the_world(in vec3 p)
{
    float sphere_0 = distance_from_sphere(p, vec3(-1.0,0.0,0.0),1); 
    float sphere_1 = distance_from_sphere(p, vec3(1.0,0.0,0.0),1); 
    

    return opSmoothUnion(sphere_0,sphere_1,0.7);
}

vec3 calculate_normal(in vec3 p)
{
    const vec3 small_step = vec3(0.001, 0.0, 0.0);

    float gradient_x = map_the_world(p + small_step.xyy) - map_the_world(p - small_step.xyy);
    float gradient_y = map_the_world(p + small_step.yxy) - map_the_world(p - small_step.yxy);
    float gradient_z = map_the_world(p + small_step.yyx) - map_the_world(p - small_step.yyx);

    vec3 normal = vec3(gradient_x, gradient_y, gradient_z);

    return normalize(normal);
}
vec3 ray_march(in vec3 ro, in vec3 rd)
{
    float total_distance_traveled = 0.0;
    const int NUMBER_OF_STEPS = 3200;
    const float MINIMUM_HIT_DISTANCE = 0.001;
    const float MAXIMUM_TRACE_DISTANCE = 10000.0;

    for (int i = 0; i < NUMBER_OF_STEPS; ++i)
    {
        vec3 current_position = ro + total_distance_traveled * rd;

        float distance_to_closest = map_the_world(current_position);

        if (distance_to_closest < MINIMUM_HIT_DISTANCE) 
        {
            vec3 normal = calculate_normal(current_position);
            vec3 light_position = vec3(2.0, -5.0, 3.0);
            vec3 direction_to_light = normalize(current_position - light_position);

            float diffuse_intensity = max(0.0, dot(normal, direction_to_light));

            return vec3(0.5, 0.7, 0.6) * diffuse_intensity;
        }

        if (total_distance_traveled > MAXIMUM_TRACE_DISTANCE)
        {
            return vec3(0.0);

            break;
        }
        total_distance_traveled += distance_to_closest;
    }
    return vec3(1.0);
}
void main()
{

    vec2 uv = (gl_FragCoord.xy / screenSize) * 2.0 - 1.0;


    vec3 ro = vec3(0,0,-5);;
    vec3 rd = vec3(uv,1);

    vec3 shaded_color = ray_march(ro, rd);

    outputColor = vec4(shaded_color, 1.0);
}

 