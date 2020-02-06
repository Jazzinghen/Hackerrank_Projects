#include <iostream>
#include <vector>
#include "triple_step.h"

size_t triple_step(int steps)
{
  std::vector<size_t> combos(steps);

  combos[0] = 1;
  combos[1] = 2;
  combos[2] = 4;

  for (int i = 3; i < steps; ++i)
  {
      combos[i] = combos[i - 1] + combos[i - 2] + combos[i - 3];
  }

  return combos[steps - 1];
}

int main(int argc, char **argv)
{
  int target = 0;
  std::cin >> target;

  size_t combinations = triple_step(target);
  std::cout << combinations;

  return 0;
}
