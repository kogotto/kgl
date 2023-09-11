#shader vertex
#version 330 core

layout(location = 0) in vec4 i_Position;
layout(location = 1) in vec4 i_Color;

out vec4 v_Color;

void main() {
    gl_Position = i_Position;
    v_Color = i_Color;
}

#shader fragment
#version 330 core

out vec4 color;

in vec4 v_Color;

void main() {
    color = v_Color;
}
