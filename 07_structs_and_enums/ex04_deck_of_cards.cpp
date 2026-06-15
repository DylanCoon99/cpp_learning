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
#include <string>
#include <iostream>
#include <random>
#include <iomanip>


enum class Suit { Hearts, Diamonds, Clubs, Spades };

enum class Rank { Ace = 1, Two, Three, Four, Five, Six, Seven,
                     Eight, Nine, Ten, Jack, Queen, King };


std::string suit_to_string(Suit s) {

	switch (s) {
	case Suit::Hearts:
		return "Hearts";
	case Suit::Diamonds:
		return "Diamonds";
	case Suit::Clubs:
		return "Clubs";
	case Suit::Spades:
		return "Spades";
	}
}


std::string rank_to_string(Rank r) {
	switch (r) {
	case Rank::Ace:
		return "Ace";
	case Rank::Two:
		return "Two";
	case Rank::Three:
		return "Three";
	case Rank::Four:
		return "Four";
	case Rank::Five:
		return "Five";
	case Rank::Six:
		return "Six";
	case Rank::Seven:
		return "Seven";
	case Rank::Eight:
		return "Eight";
	case Rank::Nine:
		return "Nine";
	case Rank::Ten:
		return "Ten";
	case Rank::Jack:
		return "Jack";
	case Rank::Queen:
		return "Queen";
	case Rank::King:
		return "King";
	}
}


struct Card {
	Rank rank;
	Suit suit;

	Card() {}
	Card(Rank r, Suit s) : rank(r), suit(s) {}

	std::string to_string() const{ 
		// "Ace of Spades", "Ten of Hearts"
		return rank_to_string(rank)+ " of " + suit_to_string(suit);
	}
};


std::vector<Card> create_deck() {

	std::vector<Card> deck;

	for (int s = 0; s < 4; ++s) {
		Suit suit = static_cast<Suit>(s);
		for (int r = 1; r <= 13; ++r) {
			Rank rank = static_cast<Rank>(r);
			// create a card with Rank and Suit
			deck.push_back(Card(rank, suit));
		}
    }

    return deck;
}


void shuffle_deck(std::vector<Card>& deck) {

//     — Shuffle the deck using the Fisher-Yates algorithm:
//         for i from deck.size()-1 down to 1:
//             j = random int in [0, i]
//             swap deck[i] and deck[j]
//     — Use <random> for the random number (like step 03)

	std::random_device rd;
	std::mt19937 gen(rd());
	int j;
	Card temp;
	
	for (int i = 1; i < static_cast<int>(deck.size()); ++i){
		std::uniform_int_distribution<> distrib(1, i);
		j = distrib(gen);
		temp = deck[j];
		deck[j] = deck[i];
		deck[i] = temp;
	}

}



void print_deck(const std::vector<Card>& deck) {
	// print deck; 4 per line

	// i = 4   i < 52   j = 0    j < 4
	std::cout << std::setw(20);

	int j = 0;
	for (int i = 4; i < static_cast<int>(deck.size()); i+=4) {
		for (j; j < i; ++j) {
			std::cout << deck[j].to_string() << std::setw(20);
		}
		std::cout << std::endl;
		j = i;
	}

	std::cout << std::endl;
	
}


std::vector<Card> deal(std::vector<Card>& deck, int n) {

	std::vector<Card> hand;

	while (n > 0) {
		hand.push_back(deck.back());
		deck.pop_back(); // removes card from back
		--n;
	}

	return hand;

}



int main() {


	std::vector<Card> deck = create_deck();

	std::cout << "Size: " << deck.size() << std::endl;

	//std::cout << "Card 0: " << deck[0].to_string() << std::endl;

	print_deck(deck);

	shuffle_deck(deck);

	std::vector<Card> player1_hand = deal(deck, 5);
	std::vector<Card> player2_hand = deal(deck, 5);


	std::cout << "Size: " << deck.size() << std::endl;

	print_deck(deck);




}