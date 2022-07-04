#version 130
// vertex shader operates on each vertex!!!

// passing this positions throw the shader
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 P;	// Camera2D - ortho-graphic projection matrix! (to get NDC)


void main() {
	// gl_Position - has 4 floats! (2D, 3D, Depth)
	gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;	// convert to vec4 - convert to vec2
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
	
	fragmentPosition = vertexPosition;
	fragmentColor = vertexColor;
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}