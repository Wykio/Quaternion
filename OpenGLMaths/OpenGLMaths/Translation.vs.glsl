#version 120

attribute vec3 a_Position;
attribute vec4 a_Color;
attribute vec2 a_Uv;

varying vec4 v_Color;
varying vec2 v_Uv;

uniform float u_Time;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 translationMatrix;

void main(void)
{
	v_Color = a_Color ;
	v_Uv = a_Uv;

	vec4 newPosition = projectionMatrix * viewMatrix * translationMatrix * vec4(a_Position, 1.0f);

	gl_Position = newPosition;
}