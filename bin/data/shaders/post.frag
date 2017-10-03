#version 150

// this is how we receive the texture
uniform sampler2DRect tex0;
uniform vec4 globalColor;
uniform float time;
in vec2 texCoordVarying;
out vec4 outputColor;

void main() {
    vec4 col = texture(tex0, texCoordVarying);
    col.r = abs((cos(time)*0.5+0.5)-col.r);
    col.g = col.g*cos(time*10);
    col.b = col.b*cos(time*2.7);
    outputColor = col;
}
