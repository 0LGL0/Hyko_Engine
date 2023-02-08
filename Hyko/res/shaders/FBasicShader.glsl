#version 460 core

//uniform vec4 inColor;
layout(location = 0) out vec4 outColor;

in vec4 vColor;

void main(){
	outColor = vColor;
}