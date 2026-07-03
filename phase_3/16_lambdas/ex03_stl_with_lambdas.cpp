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

void print_movie(const Movie& movie) {
    std::cout << "Title: " << movie.title << std::endl;
    std::cout << "Year: " << movie.year << std::endl;
    std::cout << "Rating: " << movie.rating << std::endl;
    std::cout << "Genre: " << movie.genre << std::endl;
    std::cout << "Runtime (mins): " << movie.runtime_min << std::endl;
    std::cout << std::endl;
}

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
    Movie highest_rated = *std::max_element(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.rating < b.rating;
    });
    std::cout << "Highest Rated Movie: " << std::endl;
    print_movie(highest_rated);
    std::cout << std::endl;
    // 2.  Find all Sci-Fi movies (copy_if → new vector, print titles)
    std::vector<Movie> scifi_movies;
    std::copy_if(movies.begin(), movies.end(), std::back_inserter(scifi_movies), [](const Movie& movie) { return movie.genre == "Sci-Fi";});
    for (auto &movie : scifi_movies) {
        print_movie(movie);
    }
    std::cout << std::endl;
    // 3.  Sort by rating descending, print top 5
    std::partial_sort(movies.begin(), movies.begin() + 5, movies.end(), [](const Movie& a, const Movie& b) { return a.rating > b.rating; });
    for (auto it = movies.begin(); it != movies.begin() + 5; ++it) {
        print_movie(*it);
    }
    std::cout << std::endl;
    // 4.  Average rating of all movies
    double avg = std::accumulate(movies.begin(), movies.end(), 0.0, [](int acc, const Movie& movie) { return acc + movie.rating; }) / movies.size();
    std::cout << "Average Rating: " << avg << std::endl;
    // 5.  Average runtime of movies rated above 8.7
    int count_high_rated_movies = 0;
    double avg_runtime = std::accumulate(movies.begin(), movies.end(), 0.0, [&count_high_rated_movies](int acc, const Movie& movie) { 
        
        if (movie.rating > 8.7) {
            ++count_high_rated_movies;
            return acc + movie.runtime_min;
        }
        return acc;
    }) / count_high_rated_movies;

    std::cout << "Avg_runtime: " << avg_runtime << "min" << std::endl;

    // 6.  Count movies per decade (1990s, 2000s, 2010s) — use count_if
    int movies_1990s, movies_2000s, movies_2010s;

    movies_1990s = count_if(movies.begin(), movies.end(), [](const Movie movie) {
        return movie.year >= 1990 && movie.year < 2000;
    });

    movies_2000s = count_if(movies.begin(), movies.end(), [](const Movie movie) {
        return movie.year >= 2000 && movie.year < 2010;
    });

    movies_2010s = count_if(movies.begin(), movies.end(), [](const Movie movie) {
        return movie.year >= 2010 && movie.year < 2020;
    });
    
    std::cout << std::endl;
    std::cout << "1990s count: " << movies_1990s << std::endl;
    std::cout << "2000s count: " << movies_2000s << std::endl;
    std::cout << "2010s count: " << movies_2010s << std::endl;
    std::cout << std::endl;

    // 7.  Find the longest movie
    Movie longest_movie = *std::max_element(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        return a.runtime_min < b.runtime_min;
    });
    std::cout << "Longest Runtime Movie: " << std::endl;
    print_movie(longest_movie);
    // 8.  Check: are all movies rated above 7.0? (all_of)
    bool over_7 = std::all_of(movies.begin(), movies.end(), [](const Movie& movie) { return movie.rating > 7.0; });
    std::cout << "over 7.0: " << (over_7 ? "true" : "false") << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    // 9.  Create a vector of just the titles of movies from the 1990s
    //     (filter by year, then transform to extract title)
    std::cout << "Nineties Titles: " << std::endl;
    std::vector<Movie> nineties;                                                                                                                                                       
    std::copy_if(movies.begin(), movies.end(), std::back_inserter(nineties),                                                                                                           
    [](const Movie& m) { return m.year >= 1990 && m.year < 2000; });                                                                                                               

    std::vector<std::string> titles(nineties.size());                                                                                                                                
    std::transform(nineties.begin(), nineties.end(), titles.begin(),                                                                                                                   
      [](const Movie& m) { return m.title; });    
    for (auto & title : titles) {
        std::cout << title << std::endl;
    }
    std::cout << std::endl;
    // 10. Sort by genre, then by rating within genre (stable_sort twice,
    //     or single sort with compound comparator)
    std::sort(movies.begin(), movies.end(), [](const Movie& a, const Movie& b) {
        if (a.genre != b.genre) { 
            return a.genre < b.genre;
        }
        return a.rating < b.rating;
    });

    for (auto &movie : movies) {
        print_movie(movie);
    }
    std::cout << std::endl;

}
