# Simple game engine
This is a project created while watching the series [Handmade Hero](https://handmadehero.org/). Progress has been stopped since roughly 2016.

To run the engine, download and extract the repository files. Then run "win32_Game.exe" found in the "data" directory.

## Key bindings
### Player
- F5 - Spawn a player
- W/A/S/D - Move up/left/down/right
- Space - Jump (hold to bunny hop)/Ascend (when swimming)
- Shift - Descend (when swimming)
- N - Toggle gravity on player
### Camera
- F3 - Lock camera
- F4 - Toggle free/follow camera (scroll wheel adjusts camera height in free camera mode)
### General
- F11 - Toggle full-screen
- L - Toggle frame advance
- P - Progress game state by one frame (when frame advance is enabled)
### Level
- F1 - Save level ("test.level" in "data" directory)
- F2 - Load level
	#### Editing
	* Level editing is done through a combination of on-screen UI and key bindings.
	* To create new geometry in the level, click on the "CreateEntity" button in the top-left.
	* The buttons found in the top-right control a set of stepping functions for editing parameters of entities. These buttons can be toggled on (button appears red) and off (button appears gray) by clicking them with the middle mouse button.
	* The title and number on each stepping button indicates what setting is being specified (translation/rotation/scale) and the amount each step applies. Translation and scale uses in-world units, rotation uses degrees. These buttons can be incremented and decremented by 5 via left or right-clicking on the respective button.
	* If the stepping function is disabled, there is granular control using mouse movement.
	* <b>Geometry is selected by left-clicking on it (hold control key while clicking to select multiple entities).</b>
		#### Key binds (when geometry is selected)
		<i>Left-click the appearing UI elements and move your mouse to adjust.</i>
		- E - Change position (red:X, green:Y, blue:Z, yellow:X/Y)
			- END - Snap to floor  
		- R - Change rotation
		- T - Change texture (left/right direction keys: change texture, up/down direction keys: change texture repeat factor, purple box: change texture offset)
		- Y - Change scale (red:X, green:Y, blue:Z, cyan:X/Y)
		- U - Change type
			- COLLIDE: Standard rectangular collision entity.
			- WATER: Emulates swimming physics when volume is touched by player.
			- COLLIDESLOPE: Entity becomes a slope.
			- PLAYERSPAWN: Player spawn point.
	
		<i>If multiple entities are selected, rotation and scaling application is done from the center point of all selected entities and scale stepping is disabled.</i>
## Features
- Hardware accelerated rendering
	- RGBA primitives with screen-door transparency
	- Texture array
	- FXAA antialiasing
	- Perspective projection
- Spatial partitioning
	- Entities are placed into an indexing grid using their axis-aligned bounding boxes to speed up location queries
	- Ray cast marching through spatial cube for efficient entity index collision list generation
	- Uses custom "stretchy-buffer" dynamic array that outperforms C++ vector by multiple orders of magnitude
- Collision system
	- Uses minkowski sum to perform efficient rectangle intersection checks
	- Resolves collisions accurately at any scale, including players and objects with zero dimensionality
	- Resolves collisions accurately at any player speed
	- Efficient ray casting of spatial grid creates small collision candidate list
- Player movement
	- Physics based movement with gravity and friction
	- Swimming physics
	- Implements 2D bunny hopping mechanic based on Valve's "Half-Life"
	- "Auto-stepping" feature for automatic traversal up small differences in height compared to player's feet
