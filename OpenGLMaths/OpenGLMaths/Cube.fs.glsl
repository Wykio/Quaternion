#version 120

// une 'varying' est une variable en ENTREE du fragment shader
// c'est la valeur finale interpolee par le rasterizer
varying vec4 v_Color;
varying vec2 v_Uv;
//varying vec2 u_UvParquet;

uniform sampler2D u_Texture;
//uniform sampler2D u_TextureParquet;
uniform float u_Time;

void main(void)
{
	vec4 texColor = texture2D(u_Texture, v_Uv);
	//vec4 texColor = texture2D(u_TextureParquet, v_UvParquet);
	gl_FragColor = texColor;
}