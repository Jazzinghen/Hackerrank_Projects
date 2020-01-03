#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <stack>

// Point definition
// First: row
// Second: column
typedef std::pair<int, int> Point;

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
    std::set<Point> visited;
    std::vector<Point> path;
    std::stack<Point> visit_stack;

    visit_stack.push(pacman_start);
    bool food_found = false;
    
    while (!visit_stack.empty() && !food_found) {
        Point current_loc = visit_stack.top();
        visit_stack.pop();

        auto visit_check = visited.find(current_loc);
        if (visit_check != visited.end() && (grid[current_loc.first][current_loc.second] != '%')) {
            visited.emplace(current_loc);
            path.push_back(current_loc);


        }
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