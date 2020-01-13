// Image texture dimensions are normalized to the range [0, 1] and its values are intensity at each point.
uniform sampler3D image;

// Curve texture independent variable is normalized to the range [0, 1] and its values at each point denote an (x, y) coordinate
// in the normalized image space.
uniform sampler2D curveTexture;
uniform sampler1D transferFuncofWindowLevel;

// Slice offset must be normalized to Y boundaries of the image.
uniform float slice;

void main()
{

	vec4 xyInImage = texture(curveTexture, vec2(gl_TexCoord[0].x, slice));
	vec3 positionInImage = vec3(xyInImage.x, xyInImage.y, 1 - gl_TexCoord[0].y);
	vec4 color = texture(image, positionInImage /*vec3(gl_TexCoord[0].x,gl_TexCoord[0].y,.5)*/);
	vec4 rayCastingColor = texture(transferFuncofWindowLevel, color.x);
	///gl_FragColor = xyInImage;
	//gl_FragColor.r=1;
	gl_FragColor=rayCastingColor;
}
