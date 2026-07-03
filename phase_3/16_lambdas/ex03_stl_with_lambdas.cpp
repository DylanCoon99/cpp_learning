// Exercise 3: Data Analysis with Lambdas + STL
//
// Task: Analyze a dataset using STL algorithms with lambda expressions
//       for all predicates, comparators, and transformations.
//
// No raw loops — every operation should use an STL algorithm + lambda.
//
// Dataset:

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <map>

struct Movie {
    std::string title;
    int year;
    double rating;
    std::string genre;
    int runtime_min;
};

int main() {

    std::vector<Movie> movies = {
        {"The Shawshank Redemption",  1994, 9.3, "Drama",     142},
        {"The Dark Knight",           2008, 9.0, "Action",    152},
        {"Inception",                 2010, 8.8, "Sci-Fi",    148},
        {"Pulp Fiction",              1994, 8.9, "Crime",     154},
        {"The Matrix",                1999, 8.7, "Sci-Fi",    136},
        {"Interstellar",              2014, 8.6, "Sci-Fi",    169},
        {"Fight Club",                1999, 8.8, "Drama",     139},
        {"Forrest Gump",              1994, 8.8, "Drama",     142},
        {"The Lord of the Rings",     2003, 9.0, "Fantasy",   201},
        {"Goodfellas",                1990, 8.7, "Crime",     146},
        {"The Silence of the Lambs",  1991, 8.6, "Thriller",  118},
        {"Schindler's List",          1993, 9.0, "Drama",     195},
        {"Gladiator",                 2000, 8.5, "Action",    155},
        {"The Departed",              2006, 8.5, "Crime",     151},
        {"Whiplash",                  2014, 8.5, "Drama",     107},
        {"Parasite",                  2019, 8.5, "Thriller",  132},
        {"Alien",                     1979, 8.5, "Sci-Fi",    117},
        {"Blade Runner 2049",         2017, 8.0, "Sci-Fi",    164},
        {"No Country for Old Men",    2007, 8.2, "Crime",     122},
        {"Mad Max: Fury Road",        2015, 8.1, "Action",    120},
    };

    // Queries — use STL algorithms + lambdas for each. No raw loops.
    //
    // 1.  Find the highest-rated movie
    // 2.  Find all Sci-Fi movies (copy_if → new vector, print titles)
    // 3.  Sort by rating descending, print top 5
    // 4.  Average rating of all movies
    // 5.  Average runtime of movies rated above 8.7
    // 6.  Count movies per decade (1990s, 2000s, 2010s) — use count_if
    // 7.  Find the longest movie
    // 8.  Check: are all movies rated above 7.0? (all_of)
    // 9.  Create a vector of just the titles of movies from the 1990s
    //     (filter by year, then transform to extract title)
    // 10. Sort by genre, then by rating within genre (stable_sort twice,
    //     or single sort with compound comparator)

    // YOUR CODE HERE

}
