#version 120

attribute vec3 a_Position;
attribute vec4 a_Color;

varying vec4 v_Color;

uniform float u_Time;
uniform float u_Random;

uniform mat3 rotationMatrix;
uniform mat3 identityMatrix;

void main(void)
{
	v_Color = a_Color ;

	vec3 newPosition = rotationMatrix * identityMatrix * a_Position;

	gl_Position = vec4(newPosition, 1.0);
}