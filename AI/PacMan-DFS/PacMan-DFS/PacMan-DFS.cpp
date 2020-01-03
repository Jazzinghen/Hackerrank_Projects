#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_set>
#include <stack>

// Point definition
// First: row
// Second: column
typedef std::pair<int, int> Point;

// Define a hash structure to use an unordered set with our pair
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

// Seems like a pretty good function to split
void update_visit_stack(const Point& start, const std::vector<std::string>& grid, std::stack<Point>& v_stack)
{
    if (start.first > 0) {
        v_stack.push({ start.first - 1, start.second });
    }
    if (start.second > 0) {
        v_stack.push({ start.first, start.second - 1 });
    }
    if (start.first < (grid.size() - 1) ) {
        v_stack.push({ start.first + 1, start.second });
    }
    if (start.second < (grid[0].size() - 1) ) {
        v_stack.push({ start.first, start.second + 1 });
    }
}


void dfs(const Point& pacman_start, const Point& food_loc, const std::vector<std::string>& grid) {
    // Use a set with O(1) insert/search for the visited
    std::unordered_set<Point, hash_pair> visited;
    
    // However, since the stuff is not stored in insertion order we have to use a vector to
    // keep the visit path.
    std::vector<Point> visit_path;

    // A flattened vector containing where did we reach that position from.
    size_t row = grid.size();
    size_t col = grid[0].size();
    std::vector<Point> precedent(row*col);

    // The DFS stack
    std::stack<Point> visit_stack;

    visit_stack.push(pacman_start);
    bool food_found = false;
    Point prev_loc = pacman_start;
    
    while (!visit_stack.empty() && !food_found) {
        Point current_loc = visit_stack.top();
        visit_stack.pop();

        auto visit_check = visited.find(current_loc);
        char current_char = grid[current_loc.first][current_loc.second];

        bool not_visited = visit_check == visited.end();

        if (current_char == '.') {
            visited.emplace(current_loc);
            visit_path.push_back(current_loc);

            size_t flat_pos = (col * current_loc.first) + current_loc.second;
            precedent[flat_pos] = prev_loc;
            prev_loc = current_loc;
            food_found = true;
        } else if (not_visited && (current_char != '%')) {
            visited.emplace(current_loc);
            visit_path.push_back(current_loc);

            size_t flat_pos = (col * current_loc.first) + current_loc.second;
            precedent[flat_pos] = prev_loc;
            prev_loc = current_loc;

            update_visit_stack(current_loc, grid, visit_stack);
        }
    }

    size_t visited_nodes = visit_path.size();
    std::cout << visited_nodes << std::endl;
    for (const auto& coords : visit_path) {
        std::cout << coords.first << " " << coords.second << std::endl;
    }

    std::stack<Point> travelled_path;
    travelled_path.push(prev_loc);
    
    while (prev_loc != pacman_start) {
        size_t flat_pos = (col * prev_loc.first) + prev_loc.second;
        prev_loc = precedent[flat_pos];
        travelled_path.push(prev_loc);
    }

    size_t path_length = travelled_path.size() - 1;
    std::cout << path_length << std::endl;
    while (!travelled_path.empty()) {
        Point current = travelled_path.top();
        std::cout << current.first << " " << current.second << std::endl;
        travelled_path.pop();
    }
}

int main(void) {

    int r, c, pacman_r, pacman_c, food_r, food_c;

    std::cin >> pacman_r >> pacman_c;
    std::cin >> food_r >> food_c;
    std::cin >> r >> c;

    std::vector<std::string> grid;

    for (int i = 0; i < r; i++) {
        std::string s;
        std::cin >> s;
        assert(s.size() == c);
        grid.push_back(s);
    }

    dfs({ pacman_r, pacman_c }, { food_r, food_c }, grid);

    return 0;
}