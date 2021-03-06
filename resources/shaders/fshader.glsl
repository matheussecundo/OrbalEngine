#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//light variables
uniform float u_ambientLight_strength;
uniform float u_specularLight_strength;
uniform vec3 u_lightPos;
uniform vec3 u_lightColor;
uniform vec3 u_viewPos;

uniform sampler2D u_texture;

varying vec2 v_texcoord;
varying vec3 v_normal;
varying vec3 v_FragPos;


void main(){

    //ambient light
    vec3 ambientLight = u_ambientLight_strength * u_lightColor;

    //difuse light
    vec3 lightDir = normalize(u_lightPos - v_FragPos);
    float diff = max(dot(v_normal, lightDir), 0.0);
    vec3 diffuseLight = diff * u_lightColor;

    //specular light
    vec3 viewDir = normalize(u_viewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, v_normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = u_specularLight_strength * spec * u_lightColor;

    vec4 objectColor = texture2D(u_texture, v_texcoord);

    //If have texture, light take effect, if not, pure normal of vertex color
    vec4 Color = (v_texcoord.xy != vec2(-1,-1)) ? vec4(ambientLight + diffuseLight + specular, 1.0) * objectColor : vec4(ambientLight + diffuseLight + specular, 1.0) * vec4(0.5,0.5,0.5,1.0);

    gl_FragColor = Color;
}

