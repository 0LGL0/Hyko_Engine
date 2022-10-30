#version 330 core

uniform vec4 inColor;
layout(location = 0) out vec4 outColor;

void main(){
	outColor = inColor;
}