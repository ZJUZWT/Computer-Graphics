#version 330 core
out vec4 fragColor;

in vec3 vertexColor;
in vec2 vertexTexture ;

uniform sampler2D texture1 ;
uniform sampler2D texture2 ;

void main() {
    fragColor = mix( texture( texture1 , vertexTexture ) , texture( texture2 , vertexTexture ) , 0.2 )  ;
//    fragColor = texture( texture2 , vertexTexture )  ;
}