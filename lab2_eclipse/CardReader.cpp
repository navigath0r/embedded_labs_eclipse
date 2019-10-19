#include "CardReader.hpp"

CardReader::CardReader() {};

CardReader::~CardReader(){};

int CardReader::getCardNumber()
{
	std::string swipe_path = "/dev/swipe";

	std::ifstream read_swipe(swipe_path);

	if(!read_swipe.is_open())
    {
        std::cerr << "Unable to open card number generator" << std::endl;
        return -1;
    }

    // read value
    read_swipe >> this->card_number_str;
    return 1;
}

int CardReader::validateCardNumber()
{
	int card_number_digits[15];
	int partial_checksum = 0;

	//logDebug("validateCardNumber started");


	for (int i = 0; i <= 15; i++)
	{
		card_number_digits[i] = card_number_str[i] - '0'; 																										//static_cast<int>(floor(card_number_int / pow(10, i))) % 10;
		//logDebug("cardnumber-to-digits loop","i",i,"card_number_digits[i]",card_number_digits[i]);
	}

	for (int i = 14; i >= 0; i -= 2)
	{
		if(card_number_digits[i] * 2 < 9)
		{
			partial_checksum += card_number_digits[i];
		}
		else
		{
			partial_checksum += card_number_digits[i] % 10 + card_number_digits[i] / 10 % 10;
		}
		//logDebug("checksum calc loop","i",i,"partial checksum",partial_checksum);
	}

	int checksum = (partial_checksum + card_number_digits[15]) % 10;

	//logDebug("checksum check","checksum",checksum);

	if (checksum == 0)
	{
		std::cout << card_number_str;
		logSuccess();
		//logDebug("Card number should be here",card_number_str);
		card_number_str.clear();
		//logDebug("Card number should reset after success",card_number_str);
		return 1;
	}
	else
	{
		logError();
		card_number_str.clear();
		//logDebug("Card number should reset after fail",card_number_str);
		return 2;
	}
}

int CardReader::logError()
{
	std::string log_file_path = "/home/cardreader.log";

	std::ofstream log_file(log_file_path, std::ofstream::app);

	if(!log_file.is_open())
    {
        std::cerr << "Unable to open " << log_file_path << std::endl;
        return -1;
    }

	time_t now = time(0);
	char* error_timestamp = ctime(&now);

    log_file << "Wrong card number: " << this->card_number_str << " at " << error_timestamp << std::endl;

    return 1;
}

int CardReader::logSuccess()
{
	std::string log_file_path = "/home/cardreader.log";

	std::ofstream log_file(log_file_path, std::ofstream::app);

	if(!log_file.is_open())
    {
        std::cerr << "Unable to open " << log_file_path << std::endl;
        return -1;
    }

	time_t now = time(0);
	char* error_timestamp = ctime(&now);

    log_file << "Successful card read: " << this->card_number_str << " at " << error_timestamp << std::endl;

    return 1;
}

int CardReader::logDebug(std::string tag, std::string first_var, int one, std::string sec_var, int two, std::string third_var, int three)
{
	std::string log_file_path = "/home/cardreader.log";

	std::ofstream log_file(log_file_path, std::ofstream::app);

	if(!log_file.is_open())
    {
        std::cerr << "Unable to open " << log_file_path << std::endl;
        return -1;
    }

    log_file << tag << ": " << first_var << " = " << one << " " << sec_var << " = " << two << " " << third_var << " = " << three << " " << std::endl;

    return 1;
}

int CardReader::logTransaction(int transaction_type, int amount, std::string card_number, std::string pin)
{
	std::string log_file_path = "/home/cardreader.log";

	std::ofstream log_file(log_file_path, std::ofstream::app);

	if(!log_file.is_open())
	{
	    std::cerr << "Unable to open " << log_file_path << std::endl;
	    return -1;
	}

	std::string type_string;

	if (transaction_type == 0)
	{
		type_string = "Succesful";
	}
	else if (transaction_type == 1)
	{
		type_string = "Customer aborted";
	}
	else if (transaction_type == 2)
	{
		type_string = "Pin error prevented";
	}

	time_t now = time(0);
	char* timestamp = ctime(&now);

	log_file << type_string << " payment of " << amount << " with card no. " << card_number << " with PIN: " << pin << " at " << timestamp << std::endl;

	return 1;
}


std::string CardReader::getCardNumberStr()
{
	return this->card_number_str;
}

std::string CardReader::getCardNumberWrapper()
{
	while(1)
	{
		getCardNumber();

		if(!getCardNumberStr().empty())
		{
			if (validateCardNumber() == 1)
			{
				return getCardNumberStr();
			}
			else
			{
				return "fail";
			}
		}
	}
}
