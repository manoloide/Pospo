#version 150

uniform sampler2DRect tex0;
uniform float amount;
uniform float tone;
uniform float shadows;
uniform float highlights;
uniform sampler2DRect blur;

in vec2 texCoordVarying;
out vec4 outputColor;

void main() {

    vec4 ori = texture(tex0, texCoordVarying);
    vec3 tex = texture(blur, texCoordVarying).rgb;
    
    float tt = tone*0.5;
    vec3 colTone = vec3(1.0+tt*1.2, 1.0+tt*0.9, 1.0-tt);
    
    float luma = dot(tex, vec3(0.299, 0.587, 0.114));
    
    luma = smoothstep(0.0-shadows*0.6, 1.0-highlights*0.6, luma);
    
    vec3 col = ori.rgb+tex*colTone*amount*luma;
    
    outputColor = vec4(col, ori.a);
}
