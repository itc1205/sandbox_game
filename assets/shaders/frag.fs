#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.14159265359
#define blend 0.4

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

ivec3 sunColor = ivec3(202, 80, 17);
ivec3 cloudsColor = ivec3(244, 189, 82);
ivec3 skyColor = ivec3(99, 98, 141);


vec3 rgb(ivec3 color) {
    vec3 res_color = vec3(0.0); 
    res_color.r = float(color.r) / 255.0;
    res_color.g = float(color.g) / 255.0;
    res_color.b = float(color.b) / 255.0;
    return res_color;
}


float plot (vec2 st, float pct){
  return  smoothstep( pct-0.01, pct, st.y) -
          smoothstep( pct, pct+0.01, st.y);
}

float sky_func(vec2 st) {
    float x = st.x * 2.0 - 1.0 + 0.25;
    float y = pow(cos(PI * x / 2.0), 2.0);
    
    //y = plot(st, y);

    y = smoothstep(y+blend, 0.0, st.y);
    return y;
}

float upper_sky_func(vec2 st) {
    float x = st.x * 2.0 - 1.0 - 0.25;
    float y = pow(cos(PI * x / 2.0), 2.0);


    
    y = smoothstep(y+blend, 0.0, st.y);
    return y;
}

float sun_func(vec2 st) {
    float x = st.x * 2.0 - 1.0 + 0.25;
    float y = pow(cos(PI * x / 2.0), 2.0);

    y += min(pow(cos(PI * 0.25 / 2.0), 2.0), 0.3);

    y = smoothstep(y+blend, 0.0, st.y);
    return 1.0 - y;
}



void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(rgb(cloudsColor));
    //vec3 color = vec3(0.0);
    vec3 pct = vec3(st.x);

    color = mix(color, rgb(skyColor), sky_func(st));
    color = mix(color, rgb(sunColor), sun_func(st) / 2.0);

    gl_FragColor = vec4(color,1.0);
}
