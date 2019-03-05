#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec2 v_texcoord;
varying vec3 v_normal;

void main(){

    vec4 color = (v_texcoord.xy != vec2(-1,-1)) ? texture2D(texture, v_texcoord) : vec4(abs(v_normal), 1.0f);
    gl_FragColor = color;
}

