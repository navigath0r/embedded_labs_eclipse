#include <sys/time.h>
#include "CardReader.hpp"

int main()
{
	CardReader card;
	std::string card_number;
	int state = 0;
	std::string pin_code;
	std::string user_input;

	int amount = 250;

	while(1)
	{


		switch(state)
		{
		case 0:
		{
			std::cout << "Enter credit card number by pressing button" << std::endl;
			card_number = card.getCardNumberWrapper();
			state = 1;
		break;
		}
		case 1:
		{
			if(card_number == "fail")
			{
				std::cout << "Invalid card number, please retry" << std::endl;
				state = 0;
			}
			else
			{
				state = 2;
			}
		break;
		case 2:
		{
			std::cout << "Enter pin code, then enter" << std::endl;

			fd_set readSet;
			FD_ZERO(&readSet);
			FD_SET(STDIN_FILENO, &readSet);
			struct timeval tv = {10, 0};  // 10 seconds, 0 microseconds;
			if (select(STDIN_FILENO+1, &readSet, NULL, NULL, &tv) < 0) perror("select");

			bool b = (FD_ISSET(STDIN_FILENO, &readSet)) ? (std::cin >> pin_code) : false;

			if(b == 1)
			{	//process pin
				std::cout << "Amount to pay: " << amount << std::endl << "Press y to accept, anything else to reject, then enter" << std::endl;
				std::cin >> user_input;

				if (user_input == "y" || user_input == "Y")
				{
					card.logTransaction(0,amount,card_number,pin_code);
					//communication with the bank should happen here in state 3, but just resetting for now
					std::cout << "Transaction successful" << std::endl;
					state = 0;
				}
				else
				{
					std::cout << "Transaction cancelled by costumer" << std::endl;
					card.logTransaction(1,amount,card_number,pin_code);
					state = 0;
				}
			}
			else
			{	//process failed pin
				std::cout << "Pin timed out" << std::endl;
				card.logTransaction(2,amount,card_number,pin_code);
				state = 0;
			}
		break;
		}
		}
		}
	}

	return 0;
}
