#pragma once

static const char* RECT_VERTEX_SHADER = R"END(
    #version 450 core
    in vec3 iPosition; 
    in vec4 iColor; 
    out vec3 fragPosition; 
    out vec4 fragDiffuseColor; 
    void main() {
        gl_Position = vec4(iPosition, 1.0); 
        fragPosition = iPosition; 
        fragDiffuseColor = iColor; 
    })END";


static const char* RECT_FRAG_SHADER = R"END(
    #version 450 core
    in vec3 fragPosition;
    in vec4 fragDiffuseColor; 
    out vec4 outputColor;

    float circle_sdf(vec2 samplePosition, vec2 centerPosition, float radius) {
        return distance(samplePosition, centerPosition) - radius;
    }

    float rect_sdf(vec2 samplePosition, vec2 centerPosition, vec2 halfSize) {
        vec2 edgeWiseDistance = abs(samplePosition) - halfSize; 
        return min(max(edgeWiseDistance.x, edgeWiseDistance.y), 0) + length(max(edgeWiseDistance, 0.0)); 
    }

    void main() {
        float signed_dist = rect_sdf(fragPosition.xy, vec2(0, 0), vec2(0.5, 0.5));

        if (signed_dist > 0) {
            discard;
        }

        outputColor = fragDiffuseColor;
    })END";

class Rectangle {

public:
    Rectangle(float x, float y, float width, float height); 

    void BufferData(); 

private:
    float x, y, width, height; 

};