# Black Jack Game

Welcome to the Jack Black Black Jack Game! This is a console-based implementation of the classic card game Black Jack. The game allows users to play against a dealer, with the goal of having a hand value as close to 21 as possible without exceeding it.

## Game Overview

In this game, players can start a new game, load a previous game, or exit the application. The game uses a text file called `deck.txt` to generate the deck of cards and includes functionality for saving and loading player data.

## Classes

### Player Class

The `Player` class is responsible for managing player data. It handles reading from and writing to a text file to either load or save user data for the Black Jack game. This allows players to retain their progress, statistics, and preferences between gaming sessions. The class includes methods to:

- **Load Player Data**: Read player information from a saved text file to restore the player's previous state.
- **Save Player Data**: Write the current player's state to a text file, ensuring progress is not lost when exiting the game.

### Deck Class

The `Deck` class is responsible for creating and managing the deck of cards used in the game. It reads card data from a text file called `deck.txt`, which contains information about the cards in the deck. The class performs the following tasks:

- **Load Cards**: Read the card data from `deck.txt` and create an array of card objects to represent the deck.
- **Draw Cards**: Provide functionality to draw cards from the deck for the player and dealer using a random seed generator.

### Game Class

The `Game` class controls all the logic of the Black Jack game. It coordinates the interaction between the player and the dealer, manages the game flow, and implements the rules of Black Jack. Key responsibilities include:

- **Game Initialization**: Set up the game environment, including loading the deck and initializing player data.
- **Gameplay Logic**: Implement the main gameplay loop, including dealing cards and determining the value of the player/dealer hands to determine who is close to 21 without going over. 


## Getting Started

1. Clone the repository to your local machine.
2. Ensure you have a file named `deck.txt` in the project directory with the card data.
3. Compile and run the main program.
4. Follow the on-screen menu to start a new game or load a saved game.

Example code run would be:

```bash
# Run this first to make the executable file.
make -f Makefile 

# Next run the following for automated input testing
./blackjack.exe < test.txt

# Or do it without the testing to try it yourself
./blackjack.exe

```

## Contributing

Feel free to contribute to the project by opening issues or submitting pull requests. Suggestions for improvements and additional features are welcome!

## License

This project is open-source and available under the MIT License.

Happy playing!
