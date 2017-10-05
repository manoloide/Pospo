#version 150

#define PI 3.14159265359

uniform sampler2DRect tex0;
uniform float barrel;
uniform float shift;
uniform float aberration;
uniform float defocus;
uniform vec2 resolution;

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


vec2 desform(vec2 st, float barrel) {
    float angle = atan(st.y, st.x);
    float radius = 1.0-length(st);
    radius = 1.0-pow(radius, 1.0/barrel);
    st.x = cos(angle)*radius;
    st.y = sin(angle)*radius;
    
    return st;
}

void main() {
    
    vec2 st = texCoordVarying/resolution;
    
    float bar = barrel;
    
    if(barrel < 1.0) {
        bar = 0.5+barrel*0.5;
    }
    
    vec2 aspect = vec2(1.0);
    if(resolution.x < resolution.y) {
        aspect.x = resolution.x/resolution.y;
    }
    else {
       aspect.y = resolution.y/resolution.x;
    }
    
    aspect *= 2.0;
    
    st -= 0.5;
    st *= aspect;
    vec2 st1 = desform(st*vec2(1.0-shift*0.018), bar);
    vec2 st2 = desform(st*vec2(1.0+shift*0.018), bar);
    st1 /= aspect*0.5;
    st1 += 0.5;
    st2 /= aspect*0.5;
    st2 += 0.5;

    vec3 col1 = rgb2hsb(texture(tex0, st1*resolution).rgb);
    vec3 col2 = rgb2hsb(texture(tex0, st2*resolution).rgb);
    
    col1.x += aberration;
    col2.x += aberration;
    col1 = hsb2rgb(col1);
    col2 = hsb2rgb(col2);
    
    vec3 color = rgb2hsb(vec3(col1.r, col2.g, col2.b));
    color.x -= aberration;
    
    
    outputColor = vec4(hsb2rgb(color), 1.0);
}
