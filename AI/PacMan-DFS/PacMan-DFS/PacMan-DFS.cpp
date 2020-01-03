#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_set>
#include <stack>

// Point definition
// First: row
// Second: column
typedef std::pair<size_t, size_t> Point;

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

void add_location(const Point& start, const Point& next_location, const Point& grid_size, std::stack<Point>& v_stack, std::vector<Point>& p_matrix, const std::vector<bool>& vis_matrix)
{
    size_t flat_pos = (grid_size.second * next_location.first) + next_location.second;
    if (!vis_matrix[flat_pos]) {
        p_matrix[flat_pos] = start;
    }
    v_stack.push({ next_location.first, next_location.second });
}

// Seems like a pretty good function to split
void update_visit_stack(const Point& start, const std::vector<std::string>& grid, std::stack<Point>& v_stack, std::vector<Point>& p_matrix, const std::vector<bool> & vis_matrix)
{
    size_t row = start.first;
    size_t col = start.second;

    size_t max_row = grid.size();
    size_t max_col = grid[0].size();
    if (row > 0) {
        add_location(start, { row - 1, col }, { max_row, max_col }, v_stack, p_matrix, vis_matrix);
    }
    if (col > 0) {
        add_location(start, { row, col - 1 }, { max_row, max_col }, v_stack, p_matrix, vis_matrix);
    }
    if (col < (max_col - 1)) {
        add_location(start, { row, col + 1 }, { max_row, max_col }, v_stack, p_matrix, vis_matrix);
    }
    if (row < (max_row - 1) ) {
        add_location(start, { row + 1, col }, { max_row, max_col }, v_stack, p_matrix, vis_matrix);
    }
}


void dfs(const Point& pacman_start, const Point& food_loc, const std::vector<std::string>& grid) {
    
    std::vector<Point> visit_path;

    // A flattened vector containing where did we reach that position from.
    size_t row = grid.size();
    size_t col = grid[0].size();
    std::vector<bool>  visited(row * col);
    std::vector<Point> precedent(row * col);

    // The DFS stack
    std::stack<Point> visit_stack;

    visit_stack.push(pacman_start);
    bool food_found = false;
    
    while (!visit_stack.empty() && !food_found) {
        Point current_loc = visit_stack.top();
        visit_stack.pop();

        size_t flat_pos = (col * current_loc.first) + current_loc.second;
        char current_char = grid[current_loc.first][current_loc.second];

        if (current_char == '.') {
            visit_path.push_back(current_loc);

            food_found = true;
        } else if ((!visited[flat_pos]) && (current_char != '%')) {
            visited[flat_pos] = true;
            visit_path.push_back(current_loc);

            update_visit_stack(current_loc, grid, visit_stack, precedent, visited);
        }
    }

    std::cout << "Visited nodes: " << std::endl;

    for (size_t r = 0; r < row; ++r) {
        for (size_t c = 0; c < col; ++c) {
            size_t flat_pos = (col * r) + c;
            if (visited[flat_pos]) {
                std::cout << "x";
            } else {
                std::cout << grid[r][c];
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    size_t visited_nodes = visit_path.size();
    std::cout << visited_nodes << std::endl;
    for (const auto& coords : visit_path) {
        std::cout << coords.first << " " << coords.second << std::endl;
    }

    std::stack<Point> travelled_path;
    travelled_path.push(food_loc);

    Point prev_loc = food_loc;

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