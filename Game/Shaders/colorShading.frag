#version 130
//fragment shader operates on each pixel in a givel polygon - ALL DATA in NDC (-1; 1)! - ONLY RETURN COLOR! - (MATRIX & VECTORS)

// from vertex shader
in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

// tell to OpenGL
out vec4 color;

uniform sampler2D mySampler;	// texture


void main() {

	vec4 textureColor = texture(mySampler, fragmentUV);	// func to CONNECT texture & UV (UV coord of texture)
	
	color = fragmentColor * textureColor;
}