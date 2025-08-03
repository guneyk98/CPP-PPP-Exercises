import std;

int main()
{
	constexpr std::array<const char*, 3> moves = {"Rock", "Paper", "Scissors"};
	constexpr int rock = 0, paper = 1, scissors = 2, invalid = 3;

	int player_score = 0, com_score = 0;
	for (;;) {
		std::cout << "Choose your move (r, p, s, or q to quit): ";
		
		char input;
		std::cin >> input;
		
		if (input == 'Q' || input == 'q')
			break;

		int player_move = invalid;

		switch (input) {
		case 'r': case 'R': player_move = rock; break;
		case 'p': case 'P': player_move = paper; break;
		case 's': case 'S': player_move = scissors; break;
		default: 
			std::cout << "Invalid move, try again.\n\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		int com_move = std::rand() % 3;
		std::cout << "Computer plays " << moves[com_move] << ".\n";

		if (com_move == player_move)
			std::cout << "Draw!\n";
		else if ((player_move == rock && com_move == scissors) ||
				 (player_move == scissors && com_move == paper) ||
				 (player_move == paper && com_move == rock)) {
			++player_score;
			std::cout << "You win!\n";
		} else {
			++com_score;
			std::cout << "You lose!\n";
		}

		std::cout << "Score: Player: " << player_score << "\tComputer: " <<
			com_score << ".\n\n";
	}

	std::cout << "Final Score: Player: " << player_score << "\tComputer: " <<
		com_score << ".\n";
}
