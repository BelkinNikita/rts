sf::Clock game_ticks;
sf::Clock one_second;

int FPS_NUMBER = 0;
int GAME_TICKS = 0;

void timeUpdate() {
	sf::Time elapsed = game_ticks.getElapsedTime();
	//game ticks for logic
	if (elapsed.asSeconds() > 1) {
		std::cout << std::endl;
		game_ticks.restart();
		/*for (int i = 0; i < size(mapHash); ++i) {
			std::cout << std::endl;
			for (int j = 0; j < size(mapHash[i]); ++j) {
				std::cout << mapHash[i][j];
			}
		}*/
	}
	sf::Time second = one_second.getElapsedTime();
	if (second.asSeconds() < 1) {
		++FPS_NUMBER;
	}
	else {
		std::cout << "FPS: " << FPS_NUMBER << std::endl;
		FPS_NUMBER = 0;
		one_second.restart();

	}
	if (GAME_TICKS == 24) { GAME_TICKS = 0; }
	else {
		++GAME_TICKS;
	}
}