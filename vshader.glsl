#version 150

in  vec3 vPosition;
in  vec4 vColor;
out vec4 color;
uniform vec3 translateForAnimate;
uniform vec3 theta;
uniform vec3 scale;

void main() 
{

	vec3 angle = radians(theta);
	vec3 angleCos = cos(angle);
	vec3 angleSin = sin(angle);
	
	
	mat4 rotateZ = mat4( angleCos.z, angleSin.z, 0.0, 0.0,
		    -angleSin.z,  angleCos.z, 0.0, 0.0,
		    0.0,  0.0, 1.0, 0.0,
		    0.0,  0.0, 0.0, 1.0 );
	
	mat4 rotateX = mat4( 1.0, 0.0, 0.0, 0.0,
		    0.0,  angleCos.x, angleSin.x, 0.0,
		    0.0,  -angleSin.x, angleCos.x, 0.0,
		    0.0,  0.0, 0.0, 1.0 );
			
	mat4 translateForAnimateMat = mat4(1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		translateForAnimate.x,translateForAnimate.y,translateForAnimate.z,1.0);
		
	mat4 scaleMat = mat4(scale.x,0.0,0.0,0.0,
					0.0,scale.y,0.0,0.0,
					0.0,0.0,scale.z,0.0,
					0.0,0.0,0.0,1.0);
  gl_Position = translateForAnimateMat*rotateZ*rotateX*scaleMat*vec4(vPosition,1.0);
  color = vColor;
}
