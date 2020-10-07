#include <iostream>
#include <tuple>
#include <vector>

struct Node {
  int f, g, h;
  int x, y;

  Node *parent;

  Node(Node *parent, int _x, int _y) : parent(parent), x(_x), y(_y) {
    f = 0;
    g = 0;
    h = 0;
  }

  bool operator==(const Node &other) { return x == other.x && y == other.y; }
};

std::vector<std::tuple<int, int>> aStar(std::vector<std::vector<int>> maze) {
  Node startNode(NULL, 0, 0);
  Node endNode(NULL, 7, 6);

  std::vector<Node> openList;
  std::vector<Node> closedList;
  std::vector<std::vector<int>> path;

  openList.push_back(startNode);

  while (openList.size()) {
    Node currentNode = openList[0];
    int currentIndex = 0;

    for (int i = 0; i < openList.size(); i++) {
      if (openList[i].f < currentNode.f) {
        currentNode = openList[i];
        currentIndex = i;
      }
    }

    openList.erase(openList.begin() + currentIndex);
    closedList.push_back(currentNode);

    // found the end
    if (currentNode == endNode) {
      Node *current = &currentNode;

      while (current != NULL) {
        path.push_back({current->x, current->y});
        current = current->parent;
      }
    }
  }
}

int main() {
  std::vector<std::vector<int>> maze(10, std::vector<int>(10, 0));
  maze = {{0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  std::vector<std::vector<int>> maze2 = {{0}, {0}};

  // aStar(maze);
}