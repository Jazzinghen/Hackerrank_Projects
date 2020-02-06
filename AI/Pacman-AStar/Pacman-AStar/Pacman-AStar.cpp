#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <stack>

#define PRINT_VISITED

// Point definition
// First: row
// Second: column
typedef std::pair<size_t, size_t> Point;

// AStar step definition
// Step: Matrix location
// Cost: Manhattan grid distance + distance
// Start_Dist: Distance from start
struct AStar_Step {
  Point step;
  size_t cost;
  size_t start_dist;
};

size_t compute_cost(const Point& start, const Point& food) {
  size_t cost = std::abs(int64_t(food.first) - int64_t(start.first));
  cost += std::abs(int64_t(food.second) - int64_t(start.second));

  return cost;
}

// This adds a new location to the stack and updates all the rest of the structures,
// visited and previous (for backtrack)
template<typename QueueT>
void add_location(const AStar_Step& start, const Point& next_location, const std::vector<std::string>& grid, QueueT& v_queue, std::vector<Point>& p_matrix, std::vector<bool>& vis_matrix)
{
  size_t flat_pos = (grid[0].size() * next_location.first) + next_location.second;
  size_t target_distance = start.start_dist + 1;
  size_t target_cost = compute_cost(start.step, next_location) + target_distance;
  if ((!vis_matrix[flat_pos]) && (grid[next_location.first][next_location.second] != '%')) {
      p_matrix[flat_pos] = start.step;
      vis_matrix[flat_pos] = true;
      AStar_Step target = { next_location, target_cost, target_distance };
      v_queue.push(target);
  }
}

// Seems like a pretty good function to split
// I HAD TO TEMPLATE THIS THING TO PASS THE PRIORITY QUEUE!
template<typename QueueT>
void update_visit_stack(const AStar_Step& start, const std::vector<std::string>& grid, QueueT& v_queue, std::vector<Point>& p_matrix, std::vector<bool> & vis_matrix)
{
  size_t row = start.step.first;
  size_t col = start.step.second;

  size_t max_row = grid.size();
  size_t max_col = grid[0].size();
  if (row > 0) {
      add_location(start, { row - 1, col }, grid, v_queue, p_matrix, vis_matrix);
  }
  if (col > 0) {
      add_location(start, { row, col - 1 }, grid, v_queue, p_matrix, vis_matrix);
  }
  if (col < (max_col - 1)) {
      add_location(start, { row, col + 1 }, grid, v_queue, p_matrix, vis_matrix);
  }
  if (row < (max_row - 1) ) {
      add_location(start, { row + 1, col }, grid, v_queue, p_matrix, vis_matrix);
  }
}


void astar(const Point& pacman_start, const Point& food_loc, const std::vector<std::string>& grid) {

  std::vector<Point> visit_path;

  // A flattened vector containing where did we reach that position from.
  size_t row = grid.size();
  size_t col = grid[0].size();
  std::vector<bool>  visited(row * col);
  std::vector<Point> precedent(row * col);

  // Comparison function to use for the priority queue
  auto astar_cmp = [](const AStar_Step& lhs, const AStar_Step& rhs)->bool {
      return lhs.cost > rhs.cost;
  };

  // The BFS queue
  std::priority_queue<AStar_Step, std::vector<AStar_Step>, decltype(astar_cmp)> visit_queue(astar_cmp);

  // Add the starting point as "visited"
  size_t flat_start = (pacman_start.first * col) + pacman_start.second;
  visited[flat_start] = true;

  size_t direct_distance = compute_cost(pacman_start, food_loc);
  AStar_Step start = { pacman_start, direct_distance, 0 };
  visit_queue.push(start);
  bool food_found = false;

  while (!visit_queue.empty() && !food_found) {
      AStar_Step current_loc = visit_queue.top();
      visit_queue.pop();

      Point loc = current_loc.step;

      visit_path.push_back(loc);

      char current_char = grid[loc.first][loc.second];
      if (current_char == '.') {
                food_found = true;
      } else {
                update_visit_stack(current_loc, grid, visit_queue, precedent, visited);
      }
  }

#ifdef PRINT_VISITED
  std::cout << "Visited nodes: " << std::endl;

  for (size_t r = 0; r < row; ++r) {
      for (size_t c = 0; c < col; ++c) {
                size_t flat_pos = (col * r) + c;
                if (visited[flat_pos]) {
                                          std::cout << "x";
                }
                else {
                                          std::cout << grid[r][c];
                }
      }
      std::cout << std::endl;
  }

  std::cout << std::endl;
#endif // PRINT_VISITED

  // Find the path we followed to get here and add it to a stack
  std::stack<Point> travelled_path;
  travelled_path.push(food_loc);

  Point prev_loc = food_loc;

  while (prev_loc != pacman_start) {
      size_t flat_pos = (col * prev_loc.first) + prev_loc.second;
      prev_loc = precedent[flat_pos];
      travelled_path.push(prev_loc);
  }

  // Print it in reverse order
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

  astar({ pacman_r, pacman_c }, { food_r, food_c }, grid);

  return 0;
}
