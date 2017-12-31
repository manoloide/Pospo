#version 150

uniform sampler2DRect tex0;
uniform float blur;

in vec2 texCoordVarying;
out vec4 outputColor;

uniform vec2 direction;
uniform vec2 resolution;

vec4 blur13(sampler2DRect image, vec2 uv, vec2 resolution, vec2 direction) {
    vec4 color = vec4(0.0);
    vec2 off1 = vec2(1.411764705882353) * direction;
    vec2 off2 = vec2(3.2941176470588234) * direction;
    vec2 off3 = vec2(5.176470588235294) * direction;
    color += texture(image, texCoordVarying) * 0.1964825501511404;
    color += texture(image, texCoordVarying + (off1)) * 0.2969069646728344;
    color += texture(image, texCoordVarying - (off1)) * 0.2969069646728344;
    color += texture(image, texCoordVarying + (off2)) * 0.09447039785044732;
    color += texture(image, texCoordVarying - (off2)) * 0.09447039785044732;
    color += texture(image, texCoordVarying + (off3)) * 0.010381362401148057;
    color += texture(image, texCoordVarying - (off3)) * 0.010381362401148057;
    return color;
}

vec4 blur9(sampler2DRect image, vec2 uv, vec2 resolution, vec2 direction) {
    vec4 color = vec4(0.0);
    vec2 off1 = vec2(1.3846153846) * direction;
    vec2 off2 = vec2(3.2307692308) * direction;
    color += texture(image, texCoordVarying) * 0.2270270270;
    color += texture(image, texCoordVarying + (off1)) * 0.3162162162;
    color += texture(image, texCoordVarying - (off1)) * 0.3162162162;
    color += texture(image, texCoordVarying + (off2)) * 0.0702702703;
    color += texture(image, texCoordVarying - (off2)) * 0.0702702703;
    return color;
}

void main() {
    vec2 st = gl_FragCoord.xy/resolution;
    outputColor = blur13(tex0, st, resolution, direction);
}
