#version 330 core
in vec3 normal ;
in vec3 fragmentPos ;
out vec4 fragmentColor;

uniform vec3 lightPos ;
uniform vec3 viewPos ;
uniform vec3 colorLight ;
uniform vec3 colorObject ;

struct Material {
    sampler2D diffuse ;
    sampler2D specular ;
//    vec3 specular ;
    float shininess ;
};

struct Light {
    vec3 position ;

    vec3 ambient ;
    vec3 diffuse ;
    vec3 specular ;
};

in vec2 fragTexture ;

uniform Material material ;
uniform Light light ;

void main() {
    float ambientStrength = 0.1 ;
    float reflectStrength = 0.1 ;

    //ambient
    vec3 ambient = light.ambient * texture( material.diffuse , fragTexture ).rgb ;

    //diffuse
    vec3 fragmentNormal = normalize( normal ) ;
    vec3 lightVec = normalize( light.position - fragmentPos ) ;
    float diff = max( dot(fragmentNormal,lightVec) , 0.0f ) ;
    vec3 diffuse = light.diffuse * diff * texture( material.diffuse , fragTexture ).rgb ;

    //specular
    vec3 viewNormal = normalize( viewPos - fragmentPos ) ;
    vec3 specularVec = normalize(reflect( -lightVec , fragmentNormal )) ;
    float spec = pow(max( dot(specularVec,viewNormal) , 0.0f ), material.shininess ) ;
    vec3 specular = light.specular * spec * texture( material.specular , fragTexture ).rgb ;

    vec3 color = ambient + diffuse + specular ;
//    vec3 color = specular ;
    fragmentColor = vec4( color , 1.0 )  ;
}