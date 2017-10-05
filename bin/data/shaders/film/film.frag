#version 150

uniform sampler2DRect tex0;
uniform vec3 color1;
uniform vec3 color2;
uniform vec3 color3;
uniform float faded;
uniform float strength;

in vec2 texCoordVarying;
out vec4 outputColor;

void main() {

    vec4 color = texture(tex0, texCoordVarying);
    vec3 col = color.rgb;
    float luma = dot(col, vec3(0.299, 0.587, 0.114));
    
    vec3 c1 = vec3(1.0)+(color1-0.5)*strength;
    vec3 c2 = vec3(1.0)+(color2-0.5)*strength;
    vec3 c3 = vec3(1.0)+(color3-0.5)*strength;
    vec3 film = vec3(luma);
    if(luma <= 0.5) {
        film = mix(c1, c2, luma*2.0);
    }else {
        film = mix(c2, c3, luma*2.0-1.0);
    }
    col = col*film;
    outputColor = vec4(col, color.a);
}
