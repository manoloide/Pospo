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
    
    vec2 rect = vec2(st)*size*10.0;
    
    
    float aspX = resolution.x/resolution.y;
    float aspY = resolution.y/resolution.x;
    float asp = max(aspX, aspY);
    
    float sx = 1.0*asp;
    float sy = 1.0*asp;
    
    if(resolution.x < resolution.y){
        rect.y *= asp;
        st.y *= asp;
        sx *= mix(1.0, aspX*0.5, form);
    }else {
        rect.y *= asp;
        st.y *= asp;
        sx *= mix(1.0, aspX*0.5, form);
    }
    
    float bx = sx*form;
    float by = sy*form;
    
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
    
     /*
    float print = smoothstep(sx, sx-0.001, abs(st.x))*smoothstep(sy, sy-0.001, abs(st.y));
    col = mix(col, bor, print);
     */
    /*
    float print2 = smoothstep(0.5, 0.0, abs(rect.x))*smoothstep(0.5, 0.0, abs(rect.y));
    col = mix(col, vec3(0.0, 1.0, 0.0), print2);
     */
    
    outputColor = vec4(col, color.a);
}
