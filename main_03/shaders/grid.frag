#version 330 core

// fragment shader

out vec4 FragColor;  // output: final color value as rgba-value
uniform vec3	gridColor;

void main() {
  FragColor = vec4(gridColor, 1);
}
