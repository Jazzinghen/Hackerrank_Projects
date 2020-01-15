#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include "binary_tree_check.h"

struct Node {
    int data;
    Node* left;
    Node* right;
};

std::pair<bool, std::pair<int, int>> getMinMax(const Node* root) {
    int current_max = root->data;
    if (root->left != nullptr) {

    }

    std::pair<bool, std::pair<int, int>> result;
    result.first = false;
    result.second = std::make_pair(0,0);

    return result;
}

bool checkBST(Node* root) {
    // I'll try to write an iterative post-order visit and check how it works and
    // why.
    std::stack<Node*> visit_stack;

    Node* current_node = root;
    Node* previous_node = nullptr;

    while ((!visit_stack.empty()) || (current_node != nullptr)) {
        if (current_node != nullptr) {
            // This populates the DFS stack with all the lefts we can find
            // until we get to the end of the left path.
            visit_stack.push(current_node);
            current_node = current_node->left;
        } else {
            // If there are no more left nodes to add to the visit stack retrieve
            // the next to visit in the stack
            Node* next_in_stack = visit_stack.top();
            // If there's something on the right and we are not coming from the right
            if ((next_in_stack->right) != nullptr
                && (previous_node != next_in_stack->right)) {
                current_node = next_in_stack->right;
            } else {
                std::cerr << next_in_stack->data << " ";
                previous_node = next_in_stack;
                visit_stack.pop();
            }
        }
    }

    return false;
}

int main(int argc, char **argv)
{
    int tree_size = 0;
    std::cin >> tree_size;
    std::cin.ignore();

    std::string nodes_string;
    std::getline(std::cin, nodes_string);


    std::vector<Node> nodes;
    std::string token;
    std::istringstream tokenStream(nodes_string);
    // Store data as RAII stuff :3
    while (std::getline(tokenStream, token, ' '))
    {
        nodes.push_back({std::stoi(token), nullptr, nullptr});
    }

    // After storing the data, connect the nodes for later reuse.
    size_t nodes_qty = nodes.size();
    for (size_t i = 0; i < nodes_qty; ++i) {
        size_t left_i = i * 2 + 1;
        if ((left_i < nodes_qty) && (nodes[left_i].data != -1)) {
            nodes[i].left = &nodes[left_i];
        }

        size_t right_i = i * 2 + 2;
        if ((right_i < nodes_qty) && (nodes[right_i].data != -1)) {
            nodes[i].right = &nodes[right_i];
        }
    }

    bool result = checkBST(&nodes[0]);

    return 0;
}