#version 120

// une 'varying' est une variable en ENTREE du fragment shader
// c'est la valeur finale interpolee par le rasterizer
varying vec4 v_Color;
varying vec2 v_Uv;

uniform sampler2D u_Texture;
uniform float u_Time;

void main(void)
{
	vec4 texColor = texture2D(u_Texture, v_Uv);
	gl_FragColor = texColor;
}