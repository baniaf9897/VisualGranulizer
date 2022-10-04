// fragment shader

#version 150
in vec4 vertColor;
in vec2 texCoordVarying;

out vec4 outputColor;


uniform sampler2DRect texture;


void main()
{
    // gl_FragCoord contains the window relative coordinate for the fragment.
    // we use gl_FragCoord.x position to control the red color value.
    // we use gl_FragCoord.y position to control the green color value.
    // please note that all r, g, b, a values are between 0 and 1.

    float windowWidth = 1024.0;
    float windowHeight = 768.0;

    float r = gl_FragCoord.x / windowWidth;
    float g = gl_FragCoord.y / windowHeight;
    float b = 1.0;
    float a = 1.0;
    outputColor = texture(texture, texCoordVarying);//vertColor;//vec4(1.0, 0.0, 0.0, a);
}