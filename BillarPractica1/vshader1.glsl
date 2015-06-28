#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec4 vPosition;
IN vec4 vNormal;
IN vec2 vCoordTexture;

OUT vec4 normal;
OUT vec4 position;
OUT vec2 v_texcoord;

uniform mat4 model_view;
uniform mat4 projection;

void main()
{
  gl_Position = projection*model_view*vPosition;
  position=vPosition;
  normal=vPosition;
  // Pas de les coordenades de textura al fragment shader
  // El valor del color i les coordenades de textura s'interpolaran automaticament
  // en els fragments interiors a les cares dels polígons
  v_texcoord = vCoordTexture;
}
