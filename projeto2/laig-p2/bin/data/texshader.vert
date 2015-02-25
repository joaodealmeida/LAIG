uniform float time;
uniform float wind;


void main() {

	float PI= 3.14159265358979323846264338327950288;
	vec4 vertex;
	vertex = vec4(gl_Vertex); 

	vertex.y = sin(mod( 2*PI*(wind*time + vertex.x),2*PI));
	
			
	// Set the position of the current vertex 
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
	
	//Pass gl_TexCoord to FS so it can be interpolated
	gl_TexCoord[0] = gl_MultiTexCoord0;
	
}