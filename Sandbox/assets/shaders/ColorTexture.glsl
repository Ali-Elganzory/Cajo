#type vertex
#version 330 core

layout(location = 0) in vec3  a_Position;
layout(location = 1) in vec4  a_Color;
layout(location = 2) in vec2  a_TextureCoord;
layout(location = 3) in float a_TextureSlot;
layout(location = 4) in float a_TileFactor;

uniform mat4 u_ViewProjection;

out vec4  v_Color;
out vec2  v_TextureCoord;
out float v_TextureSlot;
out float v_TileFactor;

void main()
{
	v_Color = a_Color;
	v_TextureCoord = a_TextureCoord;
	v_TextureSlot  = a_TextureSlot;
	v_TileFactor   = a_TileFactor;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4  v_Color;
in vec2  v_TextureCoord;
in float v_TextureSlot;
in float v_TileFactor;

uniform float u_TileFactor;
uniform sampler2D u_Texture[32];

void main()
{
	color = v_Color * texture(u_Texture[int(v_TextureSlot)], v_TextureCoord * v_TileFactor);
}