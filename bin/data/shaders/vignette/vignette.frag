#version 150

uniform sampler2DRect tex0;
uniform float amount;
uniform float form;
uniform float size;
uniform float smoothed;
uniform vec2 center;
uniform vec2 resolution;

in vec2 texCoordVarying;
out vec4 outputColor;

void main() {

    vec4 color = texture(tex0, texCoordVarying);
    vec3 col = color.rgb;
    
    vec2 st = texCoordVarying/resolution;
    st -= vec2(0.5)+center;
    
    vec2 rect = vec2(st)*size*(1.0+form);
    
    float aspx = resolution.x/resolution.y;
    float aspy = resolution.y/resolution.x;
    
    if(resolution.x > resolution.y){
        rect.x *= aspx;
    }else {
        rect.y *= aspy;
    }
    
    float bx = form*aspx;
    float by = form*aspy;
    
    vec3 bor = vec3(1.0, 1.0, 0.0);
    if(abs(rect.x) < bx){
        rect.x = 0;
    }else {
        rect.x -= bx*sign(st.x);
    }
    if(abs(rect.y) < by){
        rect.y = 0;
    }else {
        rect.y -= by*sign(st.y);
    }
    
    
    float dis = distance(rect, vec2(0));
    dis = smoothstep(0.999-smoothed, 1.0+smoothed, dis);
    col = mix(col, vec3(trunc(1.0+amount)), dis*abs(amount));
    
    outputColor = vec4(col, color.a);
}
