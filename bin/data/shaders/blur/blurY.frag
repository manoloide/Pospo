#version 150

uniform sampler2DRect tex0;
uniform float blur;

in vec2 texCoordVarying;
out vec4 outputColor;

void main() {

    vec4 color = vec4(0.0);
	
    color += 1.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * 7.0));
    color += 2.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * 6.0));
    color += 3.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * 5.0));
    color += 4.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * 4.0));
	color += 5.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * 3.0));
	color += 6.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * 2.0));
    color += 7.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * 1.0));
    
    color += 8.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * 0.0));
    
	color += 7.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * -1.0));
	color += 6.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * -2.0));
    color += 5.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * -3.0));
    color += 4.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * -4.0));
    color += 3.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * -5.0));
    color += 2.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * -6.0));
    color += 1.0 * texture(tex0, texCoordVarying + vec2(0.0, blur * -7.0));

    color /= 64.0;
    
    outputColor = color;
}
