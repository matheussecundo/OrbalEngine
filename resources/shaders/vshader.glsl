#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute vec3 a_normal;

varying vec2 v_texcoord;
varying vec3 v_normal;
varying vec3 v_FragPos;

void main(){
    // Calculate vertex position in screen space
    gl_Position = u_Projection * u_View * u_Model * a_position;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;

    v_FragPos = vec3(u_Model * a_position);
    v_normal = normalize(a_normal);
}
