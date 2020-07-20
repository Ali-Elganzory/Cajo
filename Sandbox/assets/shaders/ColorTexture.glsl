#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TextureCoord;

void main()
{
	v_TextureCoord = a_TextureCoord;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextureCoord;

uniform vec4 u_Color;
uniform float u_TileFactor;
uniform sampler2D u_Texture;

void main()
{
	color = u_Color * texture(u_Texture, v_TextureCoord * u_TileFactor);
}