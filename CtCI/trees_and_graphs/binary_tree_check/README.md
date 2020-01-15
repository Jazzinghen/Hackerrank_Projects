# Binary node search tree check

We define a binary tree to be a binary search tree with the following ordering requirements:

> - The value of every node in a node's left subtree is less than the data value of that node.
> - The value of every node in a node's right subtree is greater than the data value of that node.

Given the root node of a binary tree, can you determine if it's also a binary search tree? 

I couldn't compile this thing on HackerRank, so I just made a local version. This also required me to
actually load and handle the tree and stuff. We have to define how we input a binary tree that could be
not balanced as well. We would need some `nil` values, but using the `nil` string would have required
me to use Exceptions for this and I think that using Exceptions for code flow is kinda bad.

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