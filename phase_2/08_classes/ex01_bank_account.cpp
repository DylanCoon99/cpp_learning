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
	BankAccount(const std::string& owner, double initial_balance) : owner_(owner), id_(next_id_++), balance_(initial_balance)  {};
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

		double balance_before = balance_;

		withdraw(amount);

		if (balance_before != balance_){
			// this means that there were sufficient funds
			to.deposit(amount);
		}
		return *this;
	}


	void print() const {

		std::cout << "Account ID: "<< id() << std::endl;
		std::cout << "Owner: " << owner() << std::endl;
		std::cout << "Balance: " << balance() << std::endl;

	}


private:
	static int next_id_;
	std::string owner_;
	int id_;
	double balance_;

};


int BankAccount::next_id_ = 0;

int main() {


	BankAccount account1("John Smith");
	BankAccount account2("John Doe");

	// try to withdraw money that isn't there -> should print error
	account1.withdraw(100);

	account1.deposit(5000);
	account2.deposit(10000);

	std::cout << "Account 1 Balance: " << account1.balance() << std::endl;
	std::cout << "Account 2 Balance: " << account2.balance() << std::endl;


	// demonstrate chaining
	account1.deposit(1000).withdraw(500);
	account2.withdraw(1000).deposit(10000);

	std::cout << "Account 1 Balance: " << account1.balance() << std::endl; // 5500
	std::cout << "Account 2 Balance: " << account2.balance() << std::endl; // 19000


	// demonstrate transfer
	account2.transfer(account1, 1000);

	std::cout << "Account 1 Balance: " << account1.balance() << std::endl; // 6500
	std::cout << "Account 2 Balance: " << account2.balance() << std::endl; // 18000

}
