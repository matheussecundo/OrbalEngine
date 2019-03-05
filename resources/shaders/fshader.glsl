#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform float u_ambientLight_strength;
uniform vec3 u_lightPos;
uniform vec3 u_lightColor;

uniform sampler2D u_texture;

varying vec2 v_texcoord;
varying vec3 v_normal;
varying vec3 v_FragPos;

void main(){

    //ambient light
    vec3 ambientLight = u_ambientLight_strength * u_lightColor;

    //difuse light
    vec3 lightDir = normalize(u_lightPos - v_FragPos);
    float diff = max(dot(v_normal, lightDir), 0.0f);
    vec3 diffuseLight = diff * u_lightColor;

    vec4 objectColor = texture2D(u_texture, v_texcoord);
    //If have texture, light take effect, if not, pure normal of vertex color
    vec4 Color = (v_texcoord.xy != vec2(-1,-1)) ? vec4(ambientLight + diffuseLight, 1.0f) * objectColor : vec4(abs(v_normal), 1.0f);

    gl_FragColor = Color;
}

