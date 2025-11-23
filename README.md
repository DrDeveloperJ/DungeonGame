# DungeonGame
My University Project for a quick dungeon crawler game to be made.

Overview
This project is a dungeon game where a monk character explores randomly generating
dungeons. (With Random rooms) The player is able to customize their name and
description, and they are to fight enemies in the dungeon to progress. They are also to be
given the opportunity to claim an upgrade if they wish in the designated “Upgrade Room”
and are allowed to heal by meditating in the “Empty Room”. They complete each dungeon
run by opening the treasure at the end of each dungeon in the “Treasure Room”. They are
allowed to go back and forth between rooms as they wish.

Design Patterns Below :

Mediator Pattern
The system utilizes a GameMediator class as a central communication hub to decouple game systems. All components hold a std::shared_ptr to the mediator that has a HashMap of active entities so you can dynamically add entities such as rooms or enemies etc... Communication is routed via string identifiers which supports both one-way event notifications and synchronous data requests between components without establishing direct dependencies.

Template Method Pattern
A Component base class serves as the structural template for all game entities, enforcing a consistent interface such as virtual methods for Draw, Notify, and Request.

State Design Pattern
To manage the application's lifecycle, the Game class acts as a context that delegates updates to distinct state objects such as HomePage or GeneratingDungeonRoom. Each state encapsulates its own specific UI layout and input handling logic seperately.

Description of Main Requirements
Dungeon Generation :
- Will be treated on a room creation basis, i.e when new non-visited room is created
that is the point where its type is determined by the system choosing a random
option.
- The user won’t get the same room twice in a row (This will be factored into the
random algorithm)
- If the player decides to move back and forth between the dungeon rooms they have
already visited, the random algorithm will not run here as there would already be the
dungeon background, type, and neighbours saved. The room will be created using
these existing variable parameters.
Customization :
- As this project will be in the form of a GUI built from scratch without any third party
tools, (SFML Library only) the input section for entering the name and description
will also have to be manually created. (i.e allowing the user to type and submit)
Enemies :
- The enemy will be visible on screen whilst it is alive.
- The enemy’s health will be displayed during combat.
- The Enemy move will be displayed during combat.
Player :
- The player’s health and attack points are always displayed
- The player’s move will be displayed during combat.
Moves :
- 2 Move options (Attack or Guard) when fighting (buttons)
- 4 Move States (Attack succeed, Attack fail, Guard succeed, Guard fail) of which to
be displayed based on each move made by both player and enemy
Explored Dungeons display :
- Displays each visited dungeon at the top left using an icon for their type
- For each visited dungeon the icon is either TreasureRoom icon, EmptyRoom icon,
MonsterRoom icon, or UpgradeRoom icon. (Or other if future developer adds more
rooms)
Difficulty :
- Easy or Hard, biases the randomness of the number of dungeon rooms to generate
(eg bias for less rooms until treasure for Easy and more rooms bias for Hard)
Upgrades :
- Allows the user to upgrade either attack points or maxHealth and can only claim
either one per room (notify Player via gameMediator)
- Once claimed for a given upgrade room, can’t reclaim in that same room (submit a
request through gameMediator to Player to see if claimed for each given room)
Meditate :
- Restores health to full upon press in an incremental fashion using game’s update
loop
Treasure :
- Sets state back to HomePage so that player can go through the loop again of
creating a new dungeon or customize

The diagram does not include the following Components (They would all inherit from the component class)
 	- DungeonBackgroundCache
 	- DungeonExploredDisplay
 	- EnemyHealthBar
 	- MovesDisplay
 	- PlayerHealthBar
 	- Button
 	- AttackPointsBar
 	- UiElement
 	- TextInput
 	- RoomSelector
 	- Text

To Run
A Release Folder is provided with a .exe file simply run this file. ENSURE The Assets Folder
is included in the release folder as well as the JdmgtR34raz9.ttf font.

Built and Tested On Windows

SFML Dependencies are included in dependencies folder

Visual Studio Version Used : 2022
SFML Version : 3.0.0
C++ Standard : ISO C++17 Standard (/std:c++17)

Follow SFML 3.0 Installation instructions on their website.

Configuration Properties → General → Character Set = Unicode

Configuration Properties → C/C++ → General → Additional Include Directories
$(SolutionDir)\dependencies\SFML\include;%(AdditionalIncludeDirectories)

DEBUG MODE : Configuration Properties → C/C++ → Preprocessor → Preprocessor Definitions
SFML_STATIC;WIN32;_DEBUG;_CONSOLE;%(PreprocessorDefinitions);SFML_STATIC

RELEASE MODE : Configuration Properties → C/C++ → Preprocessor → Preprocessor Definitions
SFML_STATIC;WIN32;NDEBUG;_CONSOLE;%(PreprocessorDefinitions);SFML_STATIC

DEBUG MODE : Configuration Properties → C/C++ → Code Generation → Runtime Library
Multi-threaded Debug DLL (/MDd)

RELEASE MODE : Configuration Properties → C/C++ → Code Generation → Runtime Library
Multi-threaded DLL (/MD)

Configuration Properties → Linker → General → Additional Library Directories
$(SolutionDir)\dependencies\SFML\lib;%(AdditionalLibraryDirectories)

DEBUG MODE : Configuration Properties → Linker → Input → Additional Dependencies
sfml-window-s-d.lib;sfml-graphics-s-d.lib;sfml-system-s-d.lib;sfml-audio-s-d.lib;sfml-network-s-d.lib;opengl32.lib;freetype.lib;winmm.lib;gdi32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;ws2_32.lib;%(AdditionalDependencies)

RELEASE MODE : Configuration Properties → Linker → Input → Additional Dependencies
sfml-window-s.lib;sfml-graphics-s.lib;sfml-system-s.lib;sfml-audio-s.lib;sfml-network-s.lib;opengl32.lib;freetype.lib;winmm.lib;gdi32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;ws2_32.lib;%(AdditionalDependencies)

Configuration Properties → Linker → System → Subsystem = Console or Windows
Console (/SUBSYSTEM:CONSOLE)