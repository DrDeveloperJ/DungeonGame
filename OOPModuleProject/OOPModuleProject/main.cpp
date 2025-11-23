#include "Component.h"
#include "Game.h"
#include "GameMediator.h"
#include "Reuseables/Text.h"
#include "Reuseables/AttackPointsBar.h"
#include "Reuseables/PlayerHealthBar.h"
#include "Reuseables/Buttons/ChangeDescriptionButton.h"
#include "Reuseables/Buttons/ChangeNameButton.h"
#include "Reuseables/Buttons/CustomizeButton.h"
#include "Reuseables/Buttons/CustomizeDescriptionButton.h"
#include "Reuseables/Buttons/CustomizeNameButton.h"
#include "Reuseables/Buttons/EasyDiffButton.h"
#include "Reuseables/Buttons/ExploreButton.h"
#include "Reuseables/Buttons/HardDiffButton.h"
#include "Reuseables/Buttons/HomePageButton.h"
#include "RoomLogic/RoomSelector.h"
#include "RoomLogic/TreasureRoom.h"
#include "RoomLogic/EmptyRoom.h"
#include "RoomLogic/MonsterRoom.h"
#include "RoomLogic/UpgradeRoom.h"
#include "Reuseables/Buttons/BackButton.h"
#include "Reuseables/Buttons/TreasureButton.h"
#include "Reuseables/Buttons/ForwardButton.h"
#include "Reuseables/Buttons/MeditateButton.h"
#include "Reuseables/Buttons/AttackButton.h"
#include "Reuseables/Buttons/GuardButton.h"
#include "Reuseables/Buttons/UpgradeAttackButton.h"
#include "Reuseables/Buttons/UpgradeMaxHealthButton.h"
#include "Reuseables/EnemyHealthBar.h"
#include "EnemyLogic/CombatMediator.h"
#include "EnemyLogic/MovesDisplay.h"
#include "Reuseables/PreLoadedElement.h"

int main()
{
    sf::Font font = sf::Font("JdmgtR34raz9.ttf");
    std::shared_ptr<GameMediator> gameMediator = std::make_shared<GameMediator>();

    // Entities used by GameMediator
    std::shared_ptr<Player> player = std::make_shared<Player>(gameMediator);
    std::shared_ptr<Goblin> enemy = std::make_shared<Goblin>(gameMediator);

    // Components
    std::shared_ptr<RoomSelector> roomSelector = std::make_shared<RoomSelector>(7, 3); // Selects room when generating dungeon
    std::shared_ptr<CombatMediator> combatMediator = std::make_shared<CombatMediator>(gameMediator); // Handles combat actions
    std::shared_ptr<MovesDisplay> movesDisplay = std::make_shared<MovesDisplay>(gameMediator, "Assets/AttackSuccess.png", "Assets/AttackFail.png", "Assets/GuardSuccess.png", "Assets/GuardFail.png", 30.0f, 350.0f, 1125.0f, 350.0f, 0.7f, 0.7f);
    std::shared_ptr<DungeonExploredDisplay> exploredDungeonsDisplay = std::make_shared<DungeonExploredDisplay>(gameMediator, "Assets/EmptyRoomExplored.png", "Assets/MonsterRoomExplored.png", "Assets/UpgradeRoomExplored.png", "Assets/TreasureRoomExplored.png", 1.0f, 10.0f, 65.0f, 0.0f);;

    std::shared_ptr<DungeonBackgroundCache> dungeonBackgroundCache = std::make_shared<DungeonBackgroundCache>(gameMediator);
	sf::Texture background1Texture;
    if (background1Texture.loadFromFile("Assets/DungeonRoom1.png"))
    {
        std::shared_ptr<PreLoadedElement> background1 = std::make_shared<PreLoadedElement>("DungeonRoom1", background1Texture, 0.0f, 0.0f, 1.0f, 1.0f);
        dungeonBackgroundCache->addBackground(background1);
    }
    sf::Texture background2Texture;
    if (background2Texture.loadFromFile("Assets/DungeonRoom2.png"))
    {
        std::shared_ptr<PreLoadedElement> background2 = std::make_shared<PreLoadedElement>("DungeonRoom2", background2Texture, 0.0f, 0.0f, 1.0f, 1.0f);
        dungeonBackgroundCache->addBackground(background2);
    }
    sf::Texture background3Texture;
    if (background3Texture.loadFromFile("Assets/DungeonRoom3.png"))
    {
        std::shared_ptr<PreLoadedElement> background3 = std::make_shared<PreLoadedElement>("DungeonRoom3", background3Texture, 0.0f, 0.0f, 1.0f, 1.0f);
        dungeonBackgroundCache->addBackground(background3);
    }
    sf::Texture background4Texture;
    if (background4Texture.loadFromFile("Assets/DungeonRoom4.png"))
    {
        std::shared_ptr<PreLoadedElement> background4 = std::make_shared<PreLoadedElement>("DungeonRoom4", background4Texture, 0.0f, 0.0f, 1.0f, 1.0f);
        dungeonBackgroundCache->addBackground(background4);
    }
    sf::Texture background5Texture;
    if (background5Texture.loadFromFile("Assets/DungeonRoom5.png"))
    {
        std::shared_ptr<PreLoadedElement> background5 = std::make_shared<PreLoadedElement>("DungeonRoom5", background5Texture, 0.0f, 0.0f, 1.0f, 1.0f);
        dungeonBackgroundCache->addBackground(background5);
    }
    sf::Texture background6Texture;
    if (background6Texture.loadFromFile("Assets/DungeonRoom6.png"))
    {
        std::shared_ptr<PreLoadedElement> background6 = std::make_shared<PreLoadedElement>("DungeonRoom6", background6Texture, 0.0f, 0.0f, 1.0f, 1.0f);
        dungeonBackgroundCache->addBackground(background6);
    }
    sf::Texture background7Texture;
    if (background7Texture.loadFromFile("Assets/DungeonRoom7.png"))
    {
        std::shared_ptr<PreLoadedElement> background7 = std::make_shared<PreLoadedElement>("DungeonRoom7", background7Texture, 0.0f, 0.0f, 1.0f, 1.0f);
        dungeonBackgroundCache->addBackground(background7);
    }

	std::shared_ptr<TreasureRoom> treasureRoom = std::make_shared<TreasureRoom>(gameMediator);
	std::shared_ptr<EmptyRoom> emptyRoom = std::make_shared<EmptyRoom>(gameMediator);
	std::shared_ptr<MonsterRoom> monsterRoom = std::make_shared<MonsterRoom>(gameMediator);
	std::shared_ptr<UpgradeRoom> upgradeRoom = std::make_shared<UpgradeRoom>(gameMediator);

    std::shared_ptr<PlayerHealthBar> healthBar = std::make_shared<PlayerHealthBar>(gameMediator, "PlayerHealthBar", "Assets/HealthBar.png", 925.0f, 20.0f, 1.0f, 0.8f);
    std::shared_ptr<AttackPointsBar> attackPointsBar = std::make_shared<AttackPointsBar>(gameMediator, "AttackPointsBar", "Assets/AttackPointsBar.png", 925.0f, 80.0f, 1.0f, 0.8f);
    std::shared_ptr<EnemyHealthBar> enemyHealthBar = std::make_shared<EnemyHealthBar>(gameMediator, "EnemyHealthBar", "Assets/EnemyHealthBar.png", 525.0f, 110.0f, 1.0f, 0.8f);

    // HomePageButtons
    std::shared_ptr<CustomizeButton> customizeButton = std::make_shared<CustomizeButton>(gameMediator, "CustomizeButton", "Assets/CustomizeButton.png", "Assets/OnCustomizeButton.png", 325.0f, 150.0f, 1.0f, 1.0f);
    std::shared_ptr<ExploreButton> exploreButton = std::make_shared<ExploreButton>(gameMediator, "ExploreButton", "Assets/ExploreButton.png", "Assets/OnExploreButton.png", 725.0f, 150.0f, 1.0f, 1.0f);
    std::shared_ptr<EasyDiffButton> easyDiffButton = std::make_shared<EasyDiffButton>(gameMediator, "EasyDifficultyButton", "Assets/EasyDifficultyButton.png", "Assets/OnEasyDifficultyButton.png", 325.0f, 450.0f, 1.0f, 1.0f);
    std::shared_ptr<HardDiffButton> hardDiffButton = std::make_shared<HardDiffButton>(gameMediator, "HardDifficultyButton", "Assets/HardDifficultyButton.png", "Assets/OnHardDifficultyButton.png", 725.0f, 450.0f, 1.0f, 1.0f);

    // CustomizeRoomStuff
    std::shared_ptr<Text> name = std::make_shared<Text>(font, player->getName());
    name->setCharacterSize(30);
    name->setPosition({ 550, 125 });

    std::shared_ptr<Text> description = std::make_shared<Text>(font, player->getDescription());
    description->setCharacterSize(30);
    description->setPosition({ 300, 200 });

    std::shared_ptr<HomePageButton> homePageButton = std::make_shared<HomePageButton>(gameMediator, "HomePageButton", "Assets/BackButton.png", "Assets/OnBackButton.png", 925.0f, 150.0f, 0.8f, 0.8f);
    std::shared_ptr<CustomizeNameButton> customizeNameButton = std::make_shared<CustomizeNameButton>(gameMediator, "CustomizeNameButton", "Assets/ChangeNameButton.png", "Assets/OnChangeNameButton.png", 425.0f, 550.0f, 0.7f, 0.7f);
    std::shared_ptr<CustomizeDescriptionButton> customizeDescriptionButton = std::make_shared<CustomizeDescriptionButton>(gameMediator, "CustomizeDescriptionButton", "Assets/ChangeDescriptionButton.png", "Assets/OnChangeDescriptionButton.png", 625.0f, 550.0f, 0.7f, 0.7f);

    // Register TextInput Page stuff
    std::shared_ptr<TextInput> textInput = std::make_shared<TextInput>(gameMediator, 350.0f, 350.0f, 30, sf::Vector2f(600, 50), 30);
    std::shared_ptr<ChangeNameButton> changeNameButton = std::make_shared<ChangeNameButton>(gameMediator, "ChangeNameButton", "Assets/ChangeNameButton.png", "Assets/OnChangeNameButton.png", 425.0f, 550.0f, 0.7f, 0.7f);
    std::shared_ptr<ChangeDescriptionButton> changeDescriptionButton = std::make_shared<ChangeDescriptionButton>(gameMediator, "ChangeDescriptionButton", "Assets/ChangeDescriptionButton.png", "Assets/OnChangeDescriptionButton.png", 625.0f, 550.0f, 0.7f, 0.7f);

    std::shared_ptr<BackButton> backButton = std::make_shared<BackButton>(gameMediator, "BackButton", "Assets/BackButton.png", "Assets/OnBackButton.png", 25.0f, 225.0f, 0.5f, 0.5f);
	std::shared_ptr<TreasureButton> treasure = std::make_shared<TreasureButton>(gameMediator, "Treasure", "Assets/Treasure.png", "Assets/OnTreasure.png", 525.0f, 350.0f, 1.0f, 1.0f);
    std::shared_ptr<ForwardButton> forwardButton = std::make_shared<ForwardButton>(gameMediator, "ForwardButton", "Assets/ForwardButton.png", "Assets/OnForwardButton.png", 1150.0f, 225.0, 0.5f, 0.5f);
    std::shared_ptr<MeditateButton> meditateButton = std::make_shared<MeditateButton>(gameMediator, "MeditateButton", "Assets/MeditateButton.png", "Assets/OnMeditateButton.png", 525.0f, 350.0f, 0.7f, 0.7f);

    std::shared_ptr<AttackButton> attackButton = std::make_shared<AttackButton>(gameMediator, "AttackButton", "Assets/AttackButton.png", "Assets/OnAttackButton.png", 425.0f, 550.0f, 0.7f, 0.7f);
    std::shared_ptr<GuardButton> guardButton = std::make_shared<GuardButton>(gameMediator, "GuardButton", "Assets/GuardButton.png", "Assets/OnGuardButton.png", 625.0f, 550.0f, 0.7f, 0.7f);

    std::shared_ptr<UpgradeAttackButton> upgradeAttackButton = std::make_shared<UpgradeAttackButton>(gameMediator, "UpgradeAttackButton", "Assets/UpgradeAttackButton.png", "Assets/OnUpgradeAttackButton.png", 425.0f, 550.0f, 0.7f, 0.7f);
    std::shared_ptr<UpgradeMaxHealthButton> upgradeMaxHealthButton = std::make_shared<UpgradeMaxHealthButton>(gameMediator, "UpgradeMaxHealthButton", "Assets/OnUpgradeMaxHealthButton.png", "Assets/OnUpgradeMaxHealthButton.png", 625.0f, 550.0f, 0.7f, 0.7f);

    // Register Components with GameMediator so it can interact with them
    gameMediator->registerComponent("RoomSelector", roomSelector);
    gameMediator->registerComponent("CombatMediator", combatMediator);
    gameMediator->registerComponent("DungeonBackgroundCache", dungeonBackgroundCache);
    gameMediator->registerComponent("MovesDisplay", movesDisplay);
    gameMediator->registerComponent("ExploredDungeonsDisplay", exploredDungeonsDisplay);

    gameMediator->registerComponent("PlayerHealthBar", healthBar);
    gameMediator->registerComponent("AttackPointsBar", attackPointsBar);
    gameMediator->registerComponent("EnemyHealthBar", enemyHealthBar);

    // Register Entities (Componenet) with GameMediator so it can interact with them
    gameMediator->registerComponent("Player", player);
    gameMediator->registerComponent("Enemy", enemy);

    // Register HomePage Buttons with GameMediator
    gameMediator->registerComponent(customizeButton->getName(), customizeButton);
    gameMediator->registerComponent(exploreButton->getName(), exploreButton);
    gameMediator->registerComponent(easyDiffButton->getName(), easyDiffButton);
    gameMediator->registerComponent(hardDiffButton->getName(), hardDiffButton);

    // Register CustomizePage Stuff with GameMediator
    gameMediator->registerComponent("NameDisplay", name);
    gameMediator->registerComponent("DescriptionDisplay", description);
    gameMediator->registerComponent(homePageButton->getName(), homePageButton);
    gameMediator->registerComponent(customizeNameButton->getName(), customizeNameButton);
    gameMediator->registerComponent(customizeDescriptionButton->getName(), customizeDescriptionButton);

    // Register TextInput Page stuff
    gameMediator->registerComponent("TextInput", textInput);
    gameMediator->registerComponent(changeNameButton->getName(), changeNameButton);
    gameMediator->registerComponent(changeDescriptionButton->getName(), changeDescriptionButton);

    // Room Stuff
    gameMediator->registerComponent(backButton->getName(), backButton);
    gameMediator->registerComponent(treasure->getName(), treasure);
	gameMediator->registerComponent(forwardButton->getName(), forwardButton);

	gameMediator->registerComponent(meditateButton->getName(), meditateButton);

	gameMediator->registerComponent(attackButton->getName(), attackButton);
	gameMediator->registerComponent(guardButton->getName(), guardButton);

	gameMediator->registerComponent(upgradeAttackButton->getName(), upgradeAttackButton);
	gameMediator->registerComponent(upgradeMaxHealthButton->getName(), upgradeMaxHealthButton);

	// Register Rooms with GameMediator
	gameMediator->registerComponent("TreasureRoom", treasureRoom);
	gameMediator->registerComponent("EmptyRoom", emptyRoom);
	gameMediator->registerComponent("MonsterRoom", monsterRoom);
	gameMediator->registerComponent("UpgradeRoom", upgradeRoom);

    std::shared_ptr<Game> game = std::make_shared<Game>(gameMediator); // Create an instance of the Game
    gameMediator->registerComponent("Game", game);

    game->run(); // Run the game instance

    return 0;
}