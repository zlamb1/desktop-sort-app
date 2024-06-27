#pragma once

static const char* RECT_VERTEX_SHADER = R"END(
    #version 450 core
    in vec3 iPosition; 
    in vec4 iColor; 
    out vec4 color; 
    void main() {
        gl_Position = vec4(iPosition, 1.0); 
        color = iColor; 
    })END";


static const char* RECT_FRAG_SHADER = R"END(
    #version 450 core
    in vec4 color; 
    out vec4 oColor;
    void main() {
        oColor = color;
    })END";

class Rectangle {

public:
    Rectangle(); 

private:

};