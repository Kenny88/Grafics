#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif
struct tipusLlum {
    vec4 LightPosition;
    float coef_a; // Aqui s'han de definir tots els atributs d'una llum ...
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};
struct Material{

    vec4 Specular;
    vec4 Diffuse;
    vec4 Ambient;
    float Shininess;
};
uniform Material material;
uniform tipusLlum light;
uniform tipusLlum light2;
uniform tipusLlum light3;
uniform mat4 model_view;
uniform mat4 projection;

IN vec4 normal;
IN vec4 position;
IN vec2 v_texcoord;

uniform sampler2D texMap;

void main()
{
    vec3 diffuse, ambient, specular, N, V, L, H;
    float d = length((light.LightPosition - normal).xyz);

    float color2=1.0/(0.5+0.003*d+0.003*(d*d));
    N = normalize(normal.xyz);
    V = normalize(vec3(model_view * position));
    L = normalize((light.LightPosition - position).xyz);

    diffuse = (light.diffuse.xyz * material.Diffuse.xyz) * max(dot(L, N), 0.0);
    specular = (light.specular.xyz * material.Specular.xyz) * max(pow(dot(N, H), material.Shininess) , 0.0);
    ambient = light.ambient.xyz * material.Ambient.xyz;
    vec3 color=(ambient + diffuse + specular)*color2;
   // float color2=1.0/(d*d);

    gl_FragColor = texture2D(texMap, v_texcoord)*0.25*color2+color*0.75;
}

