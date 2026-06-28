// Exercise 4: Data Processing Pipeline
//
// Task: Chain multiple STL algorithms to solve data processing problems.
//       This is the STL equivalent of Unix pipes.
//
// Part A — Text analysis:
//   Given a string of text:
//     "the quick brown fox jumps over the lazy dog the fox the dog"
//
//   1. Split into words (istringstream)
//   2. Sort the words
//   3. Use std::unique to find unique words
//   4. Count total unique words
//   5. Find the most frequent word:
//      - Sort the original word list
//      - Use std::adjacent_find or manual counting to find the mode
//   6. Print all words that are longer than 3 characters
//      (use std::copy_if with back_inserter)
//
// Part B — Numeric processing:
//   Given: vector<int> grades = {85, 92, 67, 78, 95, 88, 73, 91, 82, 69, 76, 94};
//
//   1. Sort the grades
//   2. Find the median (middle element)
//   3. Find the mean (accumulate / size)
//   4. Find grades above the mean (copy_if)
//   5. Curve all grades: transform each to min(grade + 5, 100)
//   6. Count how many are now A's (>= 90)
//   7. Compute the running total (partial_sum)
//   8. Find the grade range (max - min)
//
// Part C — Record processing:
//   Define:
//     struct Sale {
//         std::string product;
//         std::string region;
//         double amount;
//         int quarter;
//     };
//
//   Create 15-20 sales records across different products, regions, quarters.
//
//   Using STL algorithms, compute:
//   1. Total sales (accumulate with custom op or transform + accumulate)
//   2. Sales by region (sort by region, then manually group and sum)
//   3. Top 3 sales by amount (partial_sort)
//   4. Average sale amount
//   5. All sales above $500 (copy_if)
//   6. Number of sales per quarter (count_if for each)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_data_pipeline.cpp

// YOUR CODE HERE
