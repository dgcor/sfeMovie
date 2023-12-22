#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "sfeMovie/Movie.hpp"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Usage: path to movie");
		return EXIT_FAILURE;
	}

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Load a movie from args
	sfe::Movie movie;
	if (!movie.openFromFile(argv[1])) {
		printf("Failed to load movie: %s\n", argv[1]);
		printf("Make sure the ffmpeg libraries (.dll or .so) are in the same folder as this program.");
		return EXIT_FAILURE;
	}

	movie.fit(0, 0, 800, 600, true);
	movie.play();

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Clear screen
		window.clear();

		// Draw and update the movie
		window.draw(movie);
		movie.update();

		// Update the window
		window.display();

		if (movie.getStatus() != sfe::Playing)
			window.close();
	}
	return EXIT_SUCCESS;
}
