# Triple Step

Basic dynamic programming problem where we want to compute the number of ways we
can climb up the stairs if we can take 1, 2 or 3 steps at the same time.

## Solution description

This is very similar to solving Fibonacci with memoization. The hint I got was:

> How would you compute how many possible ways there are to climb X steps?

There are three ways you can get to X: by taking 1, 2 or 3 steps from 1, 2 or 3
steps behind, meaning that you can sum all three of the combinations.

`steps(x) = steps(x-1) + steps(x-2) + steps(x-3)`

This can be solved in O(N) by memoization, saving the intermediates in a vector.
The initial states are just:

```c++
std::vector<size_t> step_comb(x);
x[0] = 1; // only one step
x[1] = 2; // one 2-step + x[0]
x[2] = 4; // one 3-step + x[1] + x[0]
```

## Tests

Got some tests to run (steps / combinations):

- 1 / 1
- 3 / 4
- 7 / 44
- 5 / 13
- 8 / 81
- 15 / 5768
- 20 / 121415
- 27 / 8646064