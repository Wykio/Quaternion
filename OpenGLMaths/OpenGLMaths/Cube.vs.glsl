#version 120

attribute vec3 a_Position;
attribute vec4 a_Color;

varying vec4 v_Color;

uniform float u_Time;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{
	v_Color = a_Color ;

	//vec4 newPosition = projectionMatrix * viewMatrix * modelMatrix * vec4(a_Position, 1.0f);
	vec4 newPosition = modelMatrix * vec4(a_Position, 1.0f);

	gl_Position = newPosition;
}