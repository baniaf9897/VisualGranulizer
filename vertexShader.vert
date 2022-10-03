
// vertex shader

#version 150

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec4 color;
in vec2 texcoord;

out vec4 vertColor;
out vec2 texCoordVarying;

void main(){
    gl_Position = modelViewProjectionMatrix * position;
    //vertColor = color;
    texCoordVarying = texcoord;
    
    //billboard
    //vec4 view_pos = view * model * vec3(0,0,0);
    //float dist = -view_pos.z;
    //gl_Position = project * (view_pos + vec4(position.xy*dist,0,0));
}