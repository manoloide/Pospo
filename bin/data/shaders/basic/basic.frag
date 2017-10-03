#version 150

uniform sampler2DRect tex0;
uniform float hue;
uniform float brightness;
uniform float contrast;
uniform float saturation;

in vec2 texCoordVarying;
out vec4 outputColor;

// https://thebookofshaders.com/06/
vec3 rgb2hsb( in vec3 c ){
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz),vec4(c.gb, K.xy),step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r),vec4(c.r, p.yzx),step(p.x, c.r));
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

//  Function from Iñigo Quiles
//  https://www.shadertoy.com/view/MsS3Wc
vec3 hsb2rgb( in vec3 c ){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),6.0)-3.0)-1.0, 0.0, 1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

//https://gist.github.com/jashmenn/5328940
vec3 ContrastSaturationBrightness(vec3 color, float brt, float sat, float con) {
    // Increase or decrease theese values to adjust r, g and b color channels seperately
    const float AvgLumR = 1.0;
    const float AvgLumG = 1.0;
    const float AvgLumB = 1.0;
    
    const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);
    
    vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);
    vec3 brtColor = color * brt;
    vec3 intensity = vec3(dot(brtColor, LumCoeff));
    vec3 satColor = mix(intensity, brtColor, sat);
    vec3 conColor = mix(AvgLumin, satColor, con);
    return conColor;
}

void main() {

    vec4 color = texture(tex0, texCoordVarying);
    vec3 hsb = rgb2hsb(color.rgb);
    hsb.x += hue;
    vec3 col = hsb2rgb(hsb);
    
    col = ContrastSaturationBrightness(col, brightness, saturation, contrast);
    
    outputColor = vec4(col, color.a);
}
