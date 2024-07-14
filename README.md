# Pac-Man 

This is a clone of the classic Pac-Man game made with C++. It uses the SFML graphics library for graphics and CMAKE for building.

### Requirements:
* [SFML](https://www.sfml-dev.org/)
* CMAKE
* A compatible compiler for SFML (check download instructions)

### Building the Project:
1. **Set Up SFML**: Add SFML to your environment variables or place it in the project directory.
2. **Select Build Toolkit**: If using VS Code, select a compatible build toolkit (e.g., mingw for mingw builds).
3. **Build and Run**: Build the project using CMAKE and run the executable "PAC-MAN.exe".

### Modifying the Arena or Map:
The game features 5 different levels. You can customize these levels using the following symbols:

* `-1`  ==> empty space
* `1`   ==> walls
* `0`   ==> normal pill
* `2`   ==> large pill

To modify a map:
1. Navigate to the `assets/maps` directory.
2. Open the desired text file for the level you want to change.
3. Edit the file using the symbols above.
4. Save your changes.

### Adding a New Arena/Map:
Although adding a new arena is possible, it requires some effort. A more user-friendly method is in progress. For now, follow these steps to add a new map:

1. **Create a New Map File**: In the `assets/maps` directory, create a new text file for your map.
2. **Define the Map Layout**: Use the symbols `-1`, `1`, `0`, and `2` to design your map.
3. **Update Game Code**: You will need to update the game code to recognize and load your new map file.

### Additional Information:
* **Game Controls**: The game uses standard arrow keys for navigation.
* **Scoring and Lives**: The scoring system is similar to the original Pac-Man game. Collect pills to score points and avoid ghosts to stay alive. You have multiple lives to complete each level.
* **Ghost Behavior**: The ghosts follow specific patterns to chase the player, making the game challenging and engaging.

### Troubleshooting:
* **SFML Issues**: Ensure SFML is correctly installed and configured in your environment.
* **Compilation Errors**: Check that you have selected the correct compiler and that all dependencies are properly linked.
* **Runtime Errors**: Verify the map files are correctly formatted and located in the right directory.

By following these steps, you can build, modify, and enjoy your Pac-Man clone game.

