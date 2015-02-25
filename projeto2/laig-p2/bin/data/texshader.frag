uniform sampler2D img;

void main(void)
{
	vec4 color;
	color = texture2D(img, gl_TexCoord[0].st);
	
	//RGBA components
	gl_FragColor = color;
	
}
