#version 330 core
out vec4 fragColor;

uniform vec3 colorLight ;

void main() {
    fragColor = vec4( colorLight , 1.0 )  ;
}