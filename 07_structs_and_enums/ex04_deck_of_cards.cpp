// Exercise 4: Deck of Cards
//
// Task: Model a standard 52-card deck using enums and structs.
//
// Define:
//   enum class Suit { Hearts, Diamonds, Clubs, Spades };
//   enum class Rank { Ace = 1, Two, Three, Four, Five, Six, Seven,
//                     Eight, Nine, Ten, Jack, Queen, King };
//
//   struct Card {
//       Rank rank;
//       Suit suit;
//       std::string to_string() const;  // "Ace of Spades", "Ten of Hearts"
//   };
//
// Implement:
//
//   std::string suit_to_string(Suit s)
//   std::string rank_to_string(Rank r)
//
//   std::vector<Card> create_deck()
//     — Build a full 52-card deck
//     — Use nested loops over all suits and ranks
//     — To loop over enum values, you can cast:
//         for (int s = 0; s < 4; ++s) {
//             Suit suit = static_cast<Suit>(s);
//             ...
//         }
//
//   void shuffle_deck(std::vector<Card>& deck)
//     — Shuffle the deck using the Fisher-Yates algorithm:
//         for i from deck.size()-1 down to 1:
//             j = random int in [0, i]
//             swap deck[i] and deck[j]
//     — Use <random> for the random number (like step 03)
//
//   void print_deck(const std::vector<Card>& deck)
//     — Print all cards, 4 per line
//
//   std::vector<Card> deal(std::vector<Card>& deck, int n)
//     — Remove and return the top n cards from the deck
//     — "Top" = back of the vector (use pop_back)
//
// In main():
//   - Create a deck, print its size (should be 52)
//   - Shuffle it
//   - Deal 5 cards to "Player 1", print them
//   - Deal 5 cards to "Player 2", print them
//   - Print remaining deck size (should be 42)
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex04 ex04_deck_of_cards.cpp

// YOUR CODE HERE
