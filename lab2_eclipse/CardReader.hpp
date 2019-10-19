#ifndef CARDREADER_HPP_
#define CARDREADER_HPP_

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cmath>
#include <ctime>
#include <chrono>
#include <numeric>
#include <stdio.h>

class CardReader
{
private:
	std::string card_number_str;


	int logError();
	int logSuccess();

public:
	CardReader();
	~CardReader();

	std::string getCardNumberStr();
	int getCardNumber();
	int validateCardNumber();
	int logDebug(std::string tag = "0", std::string first_var = "0", int one = 0, std::string sec_var = "0", int two = 0, std::string third_var = "0", int three = 0);
	int logTransaction(int transaction_type, int amount, std::string card_number, std::string pin);
	std::string getCardNumberWrapper();
};

#endif
