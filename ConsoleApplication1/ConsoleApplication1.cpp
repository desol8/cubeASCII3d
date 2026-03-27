#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>

struct Point3D { float x, y, z; };

void project(float x, float y, float z, int& xp, int& yp, int width, int height, float fov, float viewer_distance) {
    float factor = fov / (viewer_distance + z);
    xp = static_cast<int>(width / 2 + x * factor);
    yp = static_cast<int>(height / 2 - y * factor);
}

Point3D rotate(Point3D p, float angleX, float angleY) {
    float cosX = cos(angleX), sinX = sin(angleX);
    float y = p.y * cosX - p.z * sinX;
    float z = p.y * sinX + p.z * cosX;

    float cosY = cos(angleY), sinY = sin(angleY);
    float x = p.x * cosY + z * sinY;
    z = -p.x * sinY + z * cosY;

    return { x, y, z };
}

void drawLine(int x0, int y0, int x1, int y1, char screen[][60], int width, int height) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)
            screen[y0][x0] = '#';
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

int main() {
    const int width = 60;
    const int height = 20;
    const float fov = 40;
    const float viewer_distance = 4;

    std::vector<Point3D> vertices = {
        {-0.6f, -0.6f, -0.6f}, {0.6f, -0.6f, -0.6f},
        {0.6f, 0.6f, -0.6f}, {-0.6f, 0.6f, -0.6f},
        {-0.6f, -0.6f, 0.6f}, {0.6f, -0.6f, 0.6f},
        {0.6f, 0.6f, 0.6f}, {-0.6f, 0.6f, 0.6f}
    };

    std::vector<std::pair<int, int>> edges = {
        {0,1}, {1,2}, {2,3}, {3,0},
        {4,5}, {5,6}, {6,7}, {7,4},
        {0,4}, {1,5}, {2,6}, {3,7}
    };

    float angleX = 0;
    float angleY = 0;

    while (true) {
        char screen[height][width];
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                screen[i][j] = ' ';

        std::vector<std::pair<int, int>> projected;
        for (auto& v : vertices) {
            Point3D rotated = rotate(v, angleX, angleY);
            int x2d, y2d;
            project(rotated.x, rotated.y, rotated.z, x2d, y2d, width, height, fov, viewer_distance);
            projected.push_back({ x2d, y2d });
        }

        for (auto& edge : edges) {
            int x1 = projected[edge.first].first;
            int y1 = projected[edge.first].second;
            int x2 = projected[edge.second].first;
            int y2 = projected[edge.second].second;
            drawLine(x1, y1, x2, y2, screen, width, height);
        }

        std::cout << "\x1b[2J\x1b[H";
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                std::cout << screen[i][j];
            std::cout << '\n';
        }

        angleX += 0.05f;
        angleY += 0.03f;

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}
