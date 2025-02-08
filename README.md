# **CUB3D**

Cub3D is a game emulating the style of Wolfenstein 3D, fully written in C. It is a project in Hive Helsinki's curriculum completed in a team of two with [Szabina Korbai](https://github.com/Lisly25).
I personally focussed on implementing the DDA algorithm to make the 3D effect work.

## **Overview**

Cub3D lets the player explore a maze, which is displayed at a dynamically-changing, 3D-adjacent perspective. The map data - the layout and the textures - are read from a configurable file upon program launch. Some bonus features added on top of the basic project's requirements that we have implemented include:

* wall collision
* minimap
* animated sprite
* mouse input for rotating view
* doors that open and close

Cub3D uses the [MLX42](https://github.com/codam-coding-college/MLX42) graphics library to create the window the game is running in, and to display images. However, the raycasting algorithm that is used to display a semi-3D maze is our own implementation, as well as the game engine as a whole. (That is to say, except for the contents of the mlx directory, all code within the repository is our own work.)

The textures being used in the default maps have been made by [Pixel_Ametist](https://pixel-ametist.itch.io/pixel-background-and-textures)

## **How to install**

The files necessary for the installation of MLX42 are included in this repository - however, MLX42 is dependant on glfw, which is NOT included.

   1. Install glfw and cmake. (You can find OS-specific instructions for doing so on MLX42's github page [here](https://github.com/codam-coding-college/MLX42/tree/master?tab=readme-ov-file#installing-the-dependencies))

   2. Clone this repository 
	
  ```bash
	git clone git@github.com:Lisly25/cub3d.git cub3D
  ```
	
   3. Navigate inside the cloned repository

  ```bash
	cd cub3D
  ```

   4. Open the Makefile at the root of the repository, and find the macro "GLFW_DIR". This is the file path to glfw - change it to reflect where you installed it on your system in the first step.
   5. Open a terminal, and navigate to the root of the repository. 
       
   6. Compile the program
      
  ```bash
   make bonus
  ``` 
You should now have an executable called "cub3D_bonus"

Note: this will be the version of the game which includes all available features. Running only the command "make" in step 6 will result in compiling the game without the bonus features, but this is not the recommended way to experience the game.

## **How to play**

1. Open a terminal window, and navigate to where the executable "cub3D_bonus" is located
2. Run the executable while specifiying as argument the path to a map configuration file

There are several maps included in the repository within the "maps_bonus" directory, so running either of these commands will start the game:

```bash
./cub3D_bonus maps_bonus/level0.cub
./cub3D_bonus maps_bonus/level1.cub
./cub3D_bonus maps_bonus/level42.cub
./cub3D_bonus maps_bonus/ultimate_maze.cub
```

Controls:

| Key | Description |
| --- |---------------|
|WASD | Movement |
|Left and right arrow key / Mouse | Rotate view |
| Spacebar | Activate the staff |
| Esc | Exit the game |

If facing a door, activating the staff will cause it to blink out of existence - but it will re-materialize after a few seconds. Only one door can disappear at a time.

This information about the controls, and other game messages, also get printed to the terminal.

The goal of the game is to find the exit portal. You can achieve a game over by standing inside a door that is about to re-appear.

## **How to make your own map**

Configuration files must have the .cub extension, and cannot be 500 or more lines long.

### ***1. Textures***

Cub3D allows you to select what textures to use when building the maze. The types of textures, and the keys used to refer to them in the configuration file are as follows:

| Key | Texture type |
| ---   | ----------------|
| NO | northern walls' texture |
| SO | southern walls' texture |
| EA | eastern walls' texture |
| WE | western walls' texture |
| DO | doors' texture - these can be made to disappear |
| PO | the exit portal's texture |

To define a texture, you must specify the path to the texture (either absolute path, or relative to the excecutable) following the key and one or more space. The texture must be a .png file, ideally square-shaped for the best end result.

The key-texture pairs can be in any order, but must be separated from each other by one or more newlines. All keys need to have a texture defined for them, and all keys can appear only once.

Example of a valid texture-section from a configuration file:

---

NO ./textures/42_N.png

SO ./textures/42_S.png

EA ./textures/42_E.png

WE ./textures/42_W.png

DO ./textures/42_DO.png

PO ./textures/42_PO.png

---

### ***2. Floor and ceiling colours***

The colour of the floor and ceiling can be configured similarly to the textures, but instead of a file, an RGB colour code is what needs to be specified

| Key | Texture type |
| ---   | ----------------|
| C | ceiling colour |
| F | floor colour |

The key and the values must be separated by one or more spaces. The values must be given in decimal format, with the values for each channel separated by commas. The key-colour pairs can be in any order, but must be separated from each other by one or more newlines. All keys need to have a color defined for them, and all keys can appear only once.

Example of a valid colour-section from a configuration file:

---

C  0,0,0

F  255,255,255

---

### ***3. Map layout***

The map must be the last thing defined in the configuration file, and mustn't end with a newline. It can be at most a 64x64 grid in size. It can be made up of the following characters:

| Character | Represents | Rules |
| ------------ | -----------|-----------|
| 1   | Walls | - |
| 0 | Empty space that the player can traverse | - |
| P | Exit portal | Only one per map |
| D | Door | Can not be placed next to each other |
| N/S/W/E | Starting position and -orientation | Only one per map (either N, S, W or E) |
| space | Can be used as padding outside of walls | - |

The map must be surrounded by walls (only walls can be adjacent to the map's boundaries and space characters). Maps where the exit is not reachable from the start position will be rejected. Maps that have other, inaccessible areas will cause the program to display a warning, but the option to play the game regardless is available after answering a prompt.

Example of a valid map layout:

---

111111\
1P0DN1\
100101\
111111

---

Thank you Szabina Korbai (https://github.com/Lisly25) for this readme!
