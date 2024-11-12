
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>


struct Node {
    int x, y;
    int g, h;
    Node* parent;

    Node(int x, int y, int g = 0, int h = 0, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    int f() const { return g + h; }

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};

struct CompareNode {
    bool operator()(const Node* a, const Node* b) {
        return a->f() > b->f();
    }
};

int heuristic(int x1, int y1, int x2, int y2) {
    // Using Manhattan distance as a heuristic for a grid
    return abs(x1 - x2) + abs(y1 - y2);
}
bool isValid(int x, int y, int rows, int cols) {
    // Check if the position is within bounds and is passable (-1)
    return x >= 0 && x < rows && y >= 0 && y < cols && mapHash[y][x] == -1;
}



std::vector<Node> getNeighbors(const Node& node, int rows, int cols) {
    std::vector<Node> neighbors;
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i) {
        int newX = node.x + dx[i];
        int newY = node.y + dy[i];
        if (isValid(newX, newY, rows, cols)) {
            neighbors.emplace_back(newX, newY);
        }
    }
    return neighbors;
}

std::vector<Node> reconstructPath(Node* endNode) {
    std::vector<Node> path;
    for (Node* node = endNode; node != nullptr; node = node->parent) {
        path.push_back(*node);
    }
    reverse(path.begin(), path.end());
    return path;
}

std::vector<Node> aStar(int startX, int startY, int endX, int endY) {
    int rows = mapHash.size();
    int cols = mapHash[0].size();

    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openSet;
    std::vector<std::vector<bool>> closedSet(rows, std::vector<bool>(cols, false));

    Node* startNode = new Node(startX, startY);
    startNode->h = heuristic(startX, startY, endX, endY);
    openSet.push(startNode);

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        if (*current == Node(endX, endY)) {
            std::vector<Node> path = reconstructPath(current);
            delete current;
            return path;
        }

        closedSet[current->x][current->y] = true;

        for (Node& neighbor : getNeighbors(*current, rows, cols)) {
            if (closedSet[neighbor.x][neighbor.y]) continue;

            int tentative_g = current->g + 1;
            neighbor.g = tentative_g;
            neighbor.h = heuristic(neighbor.x, neighbor.y, endX, endY);
            neighbor.parent = current;

            openSet.push(new Node(neighbor));
        }
    }

    return {};  // No path found
}

