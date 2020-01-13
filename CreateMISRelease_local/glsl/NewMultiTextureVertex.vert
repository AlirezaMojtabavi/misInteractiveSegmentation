varying vec4 vTexCoord1;
varying vec4 vTexCoord2;


void main(void)
{
  gl_Position = ftransform();
  vTexCoord1 = gl_MultiTexCoord0;
  vTexCoord2 = gl_MultiTexCoord1;
}