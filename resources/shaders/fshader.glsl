#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec2 v_texcoord;
varying vec3 v_normal;

void main(){

    gl_FragColor = vec4(abs(v_normal), 1.0f);//texture2D(texture, v_texcoord);
}

