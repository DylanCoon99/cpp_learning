// Exercise 1: Bank Account Class
//
// Task: Build a BankAccount class with proper encapsulation and validation.
//
// Class definition:
//
//   class BankAccount {
//   public:
//       BankAccount(const std::string& owner, double initial_balance);
//       explicit BankAccount(const std::string& owner);  // delegates, balance = 0
//
//       // Getters
//       const std::string& owner() const;
//       double balance() const;
//       int id() const;
//
//       // Operations — all return *this for chaining
//       BankAccount& deposit(double amount);
//       BankAccount& withdraw(double amount);
//
//       // Transfer from this account to another
//       BankAccount& transfer(BankAccount& to, double amount);
//
//       void print() const;
//
//   private:
//       static int next_id_;
//       int id_;
//       std::string owner_;
//       double balance_;
//   };
//
// Requirements:
//   - deposit() must reject negative amounts (print error, do nothing)
//   - withdraw() must reject negative amounts and amounts > balance
//   - transfer() must use withdraw + deposit internally
//   - All operations return *this to enable chaining:
//       account.deposit(100).withdraw(20).deposit(50);
//   - Use the trailing underscore convention for private members
//   - Use member initializer lists in all constructors
//   - Use a delegating constructor for the single-arg version
//   - Mark the single-arg constructor explicit
//
// In main():
//   - Create two accounts
//   - Demonstrate deposits, withdrawals, and a transfer
//   - Demonstrate method chaining
//   - Try to withdraw more than the balance — verify error
//   - Print both accounts at the end
//
// Compile: g++ -std=c++20 -Wall -Wextra -o ex01 ex01_bank_account.cpp

// YOUR CODE HERE
#include <iostream>
#include <string>


class BankAccount {

public:


	// Constructors
	BankAccount(const std::string& owner, double initial_balance) : owner_(owner), balance_(initial_balance), id_(next_id_++) {};
	explicit BankAccount(const std::string& owner) : BankAccount(owner, 0.0) {};


	const std::string& owner() const {
		return owner_;
	}

	double balance() const {
		return balance_;
	}

	int id() const {
		return id_;
	}


	// Operations — all return *this for chaining
	BankAccount& deposit(double amount) {
		balance_ += amount;
		return *this;
	}


	BankAccount& withdraw(double amount) {
		if (amount < 0) {
			std::cout << "Amount must be positive" << std::endl;
		}
		if (amount > balance_) {
			std::cout << "Insufficient Funds." << std::endl;
		} else {
			balance_ -= amount;
		}

		return *this;
	}


	// Transfer from this account to another
	BankAccount& transfer(BankAccount& to, double amount) {

		withdraw(amount);
		to.deposit(amount);
		return *this;
	}


	void print() const {

	}





private:
	static int next_id_;
	int id_;
	std::string owner_;
	double balance_;

};


int BankAccount::next_id_ = 0;

int main() {



}
