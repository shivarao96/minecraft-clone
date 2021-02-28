#version 440 core

layout(location = 0) in vec3 aChunkPos;
layout(location = 1) in vec2 aChunkTex;

out vec2 ChunkTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(aChunkPos, 1.0); 
	ChunkTexCoords = aChunkTex;
}