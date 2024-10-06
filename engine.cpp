#include <iostream>
#include <cmath>
#include <vector>

const float PI = 3.14159265359f;

// Function to rotate a point in 3D space around the Z-axis
void RotateZ(float& x, float& y, float angle) {
    float s = std::sin(angle);
    float c = std::cos(angle);
    float newX = x * c - y * s;
    float newY = x * s + y * c;
    x = newX;
    y = newY;
}

// Function to rotate a point in 3D space around the X-axis
void RotateX(float& y, float& z, float angle) {
    float s = std::sin(angle);
    float c = std::cos(angle);
    float newY = y * c - z * s;
    float newZ = y * s + z * c;
    y = newY;
    z = newZ;
}

// Function to project 3D points into 2D
void Project(float x, float y, float z, int& screenX, int& screenY, int width, int height) {
    // Simple orthographic projection
    float scale = 0.1f;  // Control the scale of the cube on the screen
    screenX = static_cast<int>(width / 2 + x * scale);
    screenY = static_cast<int>(height / 2 - y * scale);  // Invert y to match screen coordinates
}

// Function to draw a cube
void DrawCube(int sizeX, int sizeY, int sizeZ, float angleZ, float angleX) {
    const int width = 80;  // Console width
    const int height = 40; // Console height
    std::vector<std::string> screen(height, std::string(width, ' '));  // Screen buffer

    // Define the 8 vertices of the cube
    float vertices[8][3] = {
        { -sizeX / 2.0f, -sizeY / 2.0f, -sizeZ / 2.0f },  // Bottom-back-left
        { sizeX / 2.0f, -sizeY / 2.0f, -sizeZ / 2.0f },   // Bottom-back-right
        { sizeX / 2.0f, sizeY / 2.0f, -sizeZ / 2.0f },    // Top-back-right
        { -sizeX / 2.0f, sizeY / 2.0f, -sizeZ / 2.0f },   // Top-back-left
        { -sizeX / 2.0f, -sizeY / 2.0f, sizeZ / 2.0f },   // Bottom-front-left
        { sizeX / 2.0f, -sizeY / 2.0f, sizeZ / 2.0f },    // Bottom-front-right
        { sizeX / 2.0f, sizeY / 2.0f, sizeZ / 2.0f },     // Top-front-right
        { -sizeX / 2.0f, sizeY / 2.0f, sizeZ / 2.0f }     // Top-front-left
    };

    // Rotate each vertex around the Z and X axes
    for (int i = 0; i < 8; i++) {
        RotateZ(vertices[i][0], vertices[i][1], angleZ);
        RotateX(vertices[i][1], vertices[i][2], angleX);
    }

    // Project the 3D vertices onto a 2D screen
    int screenVertices[8][2];
    for (int i = 0; i < 8; i++) {
        Project(vertices[i][0], vertices[i][1], vertices[i][2], screenVertices[i][0], screenVertices[i][1], width, height);
    }

    // Define the 12 edges of the cube
    int edges[12][2] = {
        { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },  // Back face
        { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 },  // Front face
        { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }   // Connecting edges
    };

    // Draw the edges of the cube using Bresenham's line algorithm
    for (auto& edge : edges) {
        int x1 = screenVertices[edge[0]][0];
        int y1 = screenVertices[edge[0]][1];
        int x2 = screenVertices[edge[1]][0];
        int y2 = screenVertices[edge[1]][1];

        int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = dx - dy, e2;

        while (true) {
            if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height)
                screen[y1][x1] = '#';  // Draw point

            if (x1 == x2 && y1 == y2)
                break;
            e2 = err * 2;
            if (e2 > -dy) { err -= dy; x1 += sx; }
            if (e2 < dx) { err += dx; y1 += sy; }
        }
    }

    // Print the screen buffer
    for (const auto& line : screen) {
        std::cout << line << '\n';
    }
}

int main() {
    int sizeX, sizeY, sizeZ;
    float degreesHorizontal, degreesVertical;

    // Prompt user for cube dimensions
    std::cout << "Enter the size of the cube along X-axis: ";
    std::cin >> sizeX;
    std::cout << "Enter the size of the cube along Y-axis: ";
    std::cin >> sizeY;
    std::cout << "Enter the size of the cube along Z-axis: ";
    std::cin >> sizeZ;

    // Prompt user for rotation angles
    std::cout << "Enter the horizontal rotation (in degrees): ";
    std::cin >> degreesHorizontal;
    std::cout << "Enter the vertical rotation (in degrees): ";
    std::cin >> degreesVertical;

    // Convert degrees to radians
    float angleZ = degreesHorizontal * PI / 180.0f;
    float angleX = degreesVertical * PI / 180.0f;

    // Draw the cube with the specified parameters
    DrawCube(sizeX, sizeY, sizeZ, angleZ, angleX);

    return 0;
}
