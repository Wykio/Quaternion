#version 120

// une 'varying' est une variable en ENTREE du fragment shader
// c'est la valeur finale interpolee par le rasterizer
varying vec4 v_Color;

uniform float u_Time;

void main(void)
{
	gl_FragColor = v_Color;
}