//version du shader
#version 120

//en entrée on reçoit d'abord des vertex attributs
//compilateur met automatiquement 1 pour la dernière valeur d'un vec4 et 0 pour les autres valeurs
attribute vec2 a_Position;
attribute vec4 a_Color;

//variables en sortie de shader
//transmise au rasterizer qui va interpoler la variable
varying vec4 v_Color;


void main (void)
{
	//il doit absolument renvoyer une valeur (sauf cas particulier)
	//renvoie une position en vec4 coordonnée normalisée
	v_Color = a_Color;
	float scale = 2;
	vec2 offset = vec2(-0.2, +0.4);
	gl_Position = vec4(a_Position, 0.0, 1.0);

	//la coordonnée w doit valoir 1 pour l'instant

}