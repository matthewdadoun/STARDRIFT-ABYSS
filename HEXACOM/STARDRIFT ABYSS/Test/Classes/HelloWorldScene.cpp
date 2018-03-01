#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"
#include "DisplayHandler.h"
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace cocos2d;
using namespace std;
USING_NS_CC;

int jump = 1;
int animate = 0;

//FUNCTION: createScene()
//Creates scene.
Scene* Game::createScene()
{
	Scene* scene = Scene::createWithPhysics(); // 'scene' is an autorelease object
	auto layer = Game::create();
	scene->addChild(layer);
	//sceneHandle = scene;
	physicsWorld = scene->getPhysicsWorld(); //Get the physics world from the scene so that we can work with it later
	return scene;
}


//FUNCTIONS: onEnter() / onExit()
//
void Game::onEnter()
{
	DISPLAY->createDebugConsole(true);
	printf(">> The console has opened.\n");
	Scene::onEnter();
}
void Game::onExit()
{
	printf(">> The console will now close.\n");
	Scene::onExit();
}

//FUNCTION: problemLoading()
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//FUNCTION: init()
//Initialization of all sprite instances occur here.
bool Game::init()
{
	if (!Scene::init()) { return false; }

	//Director
	director = Director::getInstance();

	//draw world
	DrawWorld();

	Point origin = Director::getInstance()->getVisibleOrigin();
	Size wsize = Director::getInstance()->getVisibleSize();  //default screen size (or design resolution size, if you are using design resolution)
	Point *center = new Point(wsize.width / 2 + origin.x, wsize.height / 2 + origin.y);

	//Physics and Gravity
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, -10000000000));

	//Music
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("Assets/Music/Opposition.mp3");
	audio->playBackgroundMusic("Assets/Music/Opposition.mp3", true);

//Orion
	orion = Sprite::create("Assets/Characters/Orion.png");
	orion->setName("Orion"); //Indentifies the node as "Orion"
	orion->setAnchorPoint(Vec2(0.5f, 0.0f));
	orion->setPosition(Vec2(PlayerPosition.x, PlayerPosition.y));
	//createBox() Creates hitbox based on getContentSize() dimensions
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* orion_body = PhysicsBody::createBox(orion->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.5f));
	orion_body->setDynamic(true);
	orion->setPhysicsBody(orion_body);
	this->addChild(orion);

/*//Animation
	runFrames.reserve(2);
	runFrames.pushBack(SpriteFrame::create("Assets/Characters/Orion.png", Rect(PlayerPosition.x, PlayerPosition.y,50,100)));
	runFrames.pushBack(SpriteFrame::create("Assets/Characters/Player.png", Rect(PlayerPosition.x, PlayerPosition.y,50,100)));

	//Run it and repeat it forever
	orion->runAction(animate);*/

//invisible camera target
	cameraTarget = Sprite::create();
	cameraTarget->setPosition(Vec2(PlayerPosition.x, PlayerPosition.y));
	//cameraTarget->retain();
	this->addChild(cameraTarget);

//Collisions Event Listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Game::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//Bitmasks assigned to sprites with PhysicsBody
	/*
	Orion - 1
	Ground - 2
	Enemy - 
	*/
	orion->getPhysicsBody()->setCollisionBitmask(1), orion->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	ground->getPhysicsBody()->setCollisionBitmask(2), ground->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[0]->getPhysicsBody()->setCollisionBitmask(2), platform[0]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[1]->getPhysicsBody()->setCollisionBitmask(2), platform[1]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[2]->getPhysicsBody()->setCollisionBitmask(2), platform[2]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[3]->getPhysicsBody()->setCollisionBitmask(2), platform[3]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[4]->getPhysicsBody()->setCollisionBitmask(2), platform[4]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[5]->getPhysicsBody()->setCollisionBitmask(2), platform[5]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[6]->getPhysicsBody()->setCollisionBitmask(2), platform[6]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[7]->getPhysicsBody()->setCollisionBitmask(2), platform[7]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[8]->getPhysicsBody()->setCollisionBitmask(2), platform[8]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[9]->getPhysicsBody()->setCollisionBitmask(2), platform[9]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[10]->getPhysicsBody()->setCollisionBitmask(2), platform[10]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[11]->getPhysicsBody()->setCollisionBitmask(2), platform[11]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[12]->getPhysicsBody()->setCollisionBitmask(2), platform[12]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[13]->getPhysicsBody()->setCollisionBitmask(2), platform[13]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[14]->getPhysicsBody()->setCollisionBitmask(2), platform[14]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[15]->getPhysicsBody()->setCollisionBitmask(2), platform[15]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[16]->getPhysicsBody()->setCollisionBitmask(2), platform[16]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[17]->getPhysicsBody()->setCollisionBitmask(2), platform[17]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected
	platform[18]->getPhysicsBody()->setCollisionBitmask(2), platform[18]->getPhysicsBody()->setContactTestBitmask(true); //Collisions can be detected

	this->scheduleUpdate(); //Allow for the update() function to be called by cocos

//	camera = Follow::create(orion, Rect::ZERO);
//	camera->retain();

	/*/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program. You may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Game::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Amtoj Uppal - 100656592", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");
	if (sprite == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}*/

	return true;
}

//FUNCTION: update(float deltaTime)
//The game's main update loop!
void Game::update(float deltaTime)
{
	gameTime += deltaTime; //total game time
	PlayerPosition = orion->getPosition(); //Sets player position
	director->getRunningScene()->runAction(Follow::create(orion)); //camera scrolling!
	orion->setRotation(0); //Orion's Rotation is constantly set to zero.
	orion->getPhysicsBody()->applyForce(Vect(0, -10000000));
	updateKeyboardInputs(); //Keyboard Input
	INPUTS->clearForNextFrame();//Clears existing inputs for next frame
}

//FUNCTION: onContactBegin()
//Runs logical check of when sprites collide using bitmaps (representations of corresponding information bits, as the name implies)
bool Game::onContactBegin(PhysicsContact &contact)
{
	auto *a = contact.getShapeA()->getBody();
	auto *b = contact.getShapeB()->getBody();

	if (1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() || 2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()) {
		//Player is standing on the ground!
		CCLOG("> Player is on the ground");
		jump = 1;
		orion->setTexture("Assets/Characters/Orion.png");
		orion->getPhysicsBody()->resetForces();
	}
	return true;
}

//FUNCTION: updateKeyboardInputs()
//The player's key presses.
void Game::updateKeyboardInputs()
{
	//CROUCHING//
	if (INPUTS->getKey(KeyCode::KEY_S))
	{
		orion->getPhysicsBody()->applyForce(Vect(0, -7500000));
		orion->setTexture("Assets/Characters/OrionC.png");
	}
	if (INPUTS->getKeyRelease(KeyCode::KEY_S)) {
		orion->setTexture("Assets/Characters/Orion.png");
	}
	//MOVE LEFT//
	if (INPUTS->getKey(KeyCode::KEY_A)) {
		PlayerPosition += Vec2(-1.33, 0) * PlayerSpeed;
		orion->setPositionX(PlayerPosition.x);
		//orion->getPhysicsBody()->setVelocity(Vect(-200, 0));
		//orion->getPhysicsBody()->applyForce(Vect(-50000, 0));
		orion->setScaleX(-1.0f); //Orion faces left
		orion->setTexture("Assets/Characters/OrionR.png");
	}
	if (INPUTS->getKeyRelease(KeyCode::KEY_A)){
		//orion->getPhysicsBody()->applyForce(Vect(750000, 0));
		orion->setTexture("Assets/Characters/Orion.png");
	}
	//MOVE RIGHT//
	if (INPUTS->getKey(KeyCode::KEY_D))
	{
		PlayerPosition += Vec2(+1.33, 0) * PlayerSpeed;
		orion->setPositionX(PlayerPosition.x);
		//orion->getPhysicsBody()->setVelocity(Vect(200, 0));
		//orion->getPhysicsBody()->applyForce(Vect(50000, 0));
		orion->setScaleX(1.0f); //Orion faces right
		orion->setTexture("Assets/Characters/OrionR.png");
	}
	if (INPUTS->getKeyRelease(KeyCode::KEY_D)) {
		//orion->getPhysicsBody()->applyForce(Vect(-750000, 0));
		orion->setTexture("Assets/Characters/Orion.png");
	}
	//JUMPING//
	if (INPUTS->getKeyPress(KeyCode::KEY_W) && jump == 1) //Key press
	{
		//PlayerPosition += Vec2(0, +1) * PlayerSpeed;
		//orion->setPositionY(PlayerPosition.y);
		//orion->getPhysicsBody()->setVelocity(Vect(0, 300));
		orion->getPhysicsBody()->applyForce(Vect(0, 250000000));
		jump = 0;
	}
	if (INPUTS->getKey(KeyCode::KEY_W) || jump == 0) //Key press
	{
		orion->setTexture("Assets/Characters/OrionJ.png");
	}
	if (INPUTS->getKeyRelease(KeyCode::KEY_W))
	{
		orion->getPhysicsBody()->applyForce(Vect(0, -75000000));
	}
}

//FUNCTION: DrawWorld()
//Initialization of the world (background, platforms, etc.) occur here.
void Game::DrawWorld()
{
	//Background
	background = Sprite::create("Assets/World/Background_t.png");
	background->setAnchorPoint(Vec2(0.5f, 0.0f)); //Center of object, objects rotate around this
	background->setPosition(0, 0);
	this->addChild(background, -100);

	//Ship
	ship = Sprite::create("Assets/World/Ship.png");
	ship->setAnchorPoint(Vec2(0.5f, 0.0f)); //Center of object, objects rotate around this
	ship->setPosition(0, 470);
	this->addChild(ship, -50);

	//Ground
	ground = Sprite::create("Assets/World/Level_t.png");
	ground->setName("Ground"); //Indentifies the node as "Ground"
	ground->setAnchorPoint(Vec2(0.5f, 0.0f)); //Center of object, objects rotate around this
	ground->setPosition(0, 0);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* ground_body = PhysicsBody::createBox(ground->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	ground_body->setDynamic(false); //Allows objects to have forces applied to it
	ground->setPhysicsBody(ground_body);
	this->addChild(ground);

	//Platform1
	platform[0] = Sprite::create("Assets/World/Platform1_t.png");
	platform[0]->setName("Platform1"); //Indentifies the node as "Platform1"
	platform[0]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[0]->setPosition(-3750, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform1_body = PhysicsBody::createBox(platform[0]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform1_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[0]->setPhysicsBody(platform1_body);
	this->addChild(platform[0]);

	//Platform2
	platform[1] = Sprite::create("Assets/World/Platform2_t.png");
	platform[1]->setName("Platform2"); //Indentifies the node as "Platform2"
	platform[1]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[1]->setPosition(-2950, 600);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform2_body = PhysicsBody::createBox(platform[1]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform2_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[1]->setPhysicsBody(platform2_body);
	this->addChild(platform[1]);

	//Platform3
	platform[2] = Sprite::create("Assets/World/Platform3_t.png");
	platform[2]->setName("Platform3"); //Indentifies the node as "Platform3"
	platform[2]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[2]->setPosition(-8000, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform3_body = PhysicsBody::createBox(platform[2]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform3_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[2]->setPhysicsBody(platform3_body);
	this->addChild(platform[2]);

	//Platform4
	platform[3] = Sprite::create("Assets/World/Platform4_t.png");
	platform[3]->setName("Platform4"); //Indentifies the node as "Platform4"
	platform[3]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[3]->setPosition(7310, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform4_body = PhysicsBody::createBox(platform[3]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform4_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[3]->setPhysicsBody(platform4_body);
	this->addChild(platform[3]);

	//Platform5
	platform[4] = Sprite::create("Assets/World/Platform5_t.png");
	platform[4]->setName("Platform5"); //Indentifies the node as "Platform5"
	platform[4]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[4]->setPosition(1250, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform5_body = PhysicsBody::createBox(platform[4]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform5_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[4]->setPhysicsBody(platform5_body);
	this->addChild(platform[4]);

	//Platform6
	platform[5] = Sprite::create("Assets/World/Platform6_t.png");
	platform[5]->setName("Platform6"); //Indentifies the node as "Platform6"
	platform[5]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[5]->setPosition(1640, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform6_body = PhysicsBody::createBox(platform[5]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform6_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[5]->setPhysicsBody(platform6_body);
	this->addChild(platform[5]);

	//Platform7
	platform[6] = Sprite::create("Assets/World/Platform7_t.png");
	platform[6]->setName("Platform7"); //Indentifies the node as "Platform7"
	platform[6]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[6]->setPosition(2720, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform7_body = PhysicsBody::createBox(platform[6]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform7_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[6]->setPhysicsBody(platform7_body);
	this->addChild(platform[6]);

	//Platform8
	platform[7] = Sprite::create("Assets/World/Platform8_t.png");
	platform[7]->setName("Platform8"); //Indentifies the node as "Platform8"
	platform[7]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[7]->setPosition(2770, 555);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform8_body = PhysicsBody::createBox(platform[7]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform8_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[7]->setPhysicsBody(platform8_body);
	this->addChild(platform[7]);

	//Platform9
	platform[8] = Sprite::create("Assets/World/Platform9_t.png");
	platform[8]->setName("Platform9"); //Indentifies the node as "Platform9"
	platform[8]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[8]->setPosition(4820, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform9_body = PhysicsBody::createBox(platform[8]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform9_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[8]->setPhysicsBody(platform9_body);
	this->addChild(platform[8]);

	//Platform10
	platform[9] = Sprite::create("Assets/World/Platform10_t.png");
	platform[9]->setName("Platform10"); //Indentifies the node as "Platform10"
	platform[9]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[9]->setPosition(4970, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform10_body = PhysicsBody::createBox(platform[9]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform10_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[9]->setPhysicsBody(platform10_body);
	this->addChild(platform[9]);
	
	//Platform11
	platform[10] = Sprite::create("Assets/World/Platform11_t.png");
	platform[10]->setName("Platform11"); //Indentifies the node as "Platform11"
	platform[10]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[10]->setPosition(5720, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform11_body = PhysicsBody::createBox(platform[10]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform11_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[10]->setPhysicsBody(platform11_body);
	this->addChild(platform[10]);

	//Platform12
	platform[11] = Sprite::create("Assets/World/Platform12_t.png");
	platform[11]->setName("Platform12"); //Indentifies the node as "Platform12"
	platform[11]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[11]->setPosition(5920, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform12_body = PhysicsBody::createBox(platform[11]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform12_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[11]->setPhysicsBody(platform12_body);
	this->addChild(platform[11]);

	//Platform13
	platform[12] = Sprite::create("Assets/World/Platform13_t.png");
	platform[12]->setName("Platform13"); //Indentifies the node as "Platform13"
	platform[12]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[12]->setPosition(6420, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform13_body = PhysicsBody::createBox(platform[12]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform13_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[12]->setPhysicsBody(platform13_body);
	this->addChild(platform[12]);

	//Platform14
	platform[13] = Sprite::create("Assets/World/Platform14_t.png");
	platform[13]->setName("Platform14"); //Indentifies the node as "Platform14"
	platform[13]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[13]->setPosition(-4550, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform14_body = PhysicsBody::createBox(platform[13]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform14_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[13]->setPhysicsBody(platform14_body);
	this->addChild(platform[13]);

	//Platform15
	platform[14] = Sprite::create("Assets/World/Platform15_t.png");
	platform[14]->setName("Platform15"); //Indentifies the node as "Platform15"
	platform[14]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[14]->setPosition(-5250, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform15_body = PhysicsBody::createBox(platform[14]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform15_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[14]->setPhysicsBody(platform15_body);
	this->addChild(platform[14]);

	//Platform16
	platform[15] = Sprite::create("Assets/World/Platform16_t.png");
	platform[15]->setName("Platform16"); //Indentifies the node as "Platform16"
	platform[15]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[15]->setPosition(-5550, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform16_body = PhysicsBody::createBox(platform[15]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform16_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[15]->setPhysicsBody(platform16_body);
	this->addChild(platform[15]);

	//Platform17
	platform[16] = Sprite::create("Assets/World/Platform17_t.png");
	platform[16]->setName("Platform17"); //Indentifies the node as "Platform17"
	platform[16]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[16]->setPosition(-6710, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform17_body = PhysicsBody::createBox(platform[16]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform17_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[16]->setPhysicsBody(platform17_body);
	this->addChild(platform[16]);

	//Platform18
	platform[17] = Sprite::create("Assets/World/Platform18_t.png");
	platform[17]->setName("Platform18"); //Indentifies the node as "Platform18"
	platform[17]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[17]->setPosition(-7000, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform18_body = PhysicsBody::createBox(platform[17]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform18_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[17]->setPhysicsBody(platform18_body);
	this->addChild(platform[17]);

	//Platform19
	platform[18] = Sprite::create("Assets/World/Platform19_t.png");
	platform[18]->setName("Platform19"); //Indentifies the node as "Platform18"
	platform[18]->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	platform[18]->setPosition(-7320, 480);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* platform19_body = PhysicsBody::createBox(platform[18]->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	platform19_body->setDynamic(false); //Allows objects to have forces applied to it
	platform[18]->setPhysicsBody(platform19_body);
	this->addChild(platform[18]);
}


//Init static physics world pointer. Set it to nullptr (points to nothing)
PhysicsWorld* Game::physicsWorld = nullptr;
//Scene* Game::sceneHandle = nullptr;


//MenuCloseCallback
//void Game::menuCloseCallback(Ref* pSender)
//{
//	//Close the cocos2d-x game scene and quit the application
//	Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	exit(0);
//#endif
//
//	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
//
//	//EventCustom customEndEvent("game_scene_close_event");
//	//_eventDispatcher->dispatchEvent(&customEndEvent);
//
//}