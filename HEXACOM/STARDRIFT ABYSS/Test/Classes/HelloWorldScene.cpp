#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"
#include "DisplayHandler.h"
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace cocos2d;
USING_NS_CC;


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
	scene->getPhysicsWorld()->setGravity(Vec2(0, -50000000));

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

							// add thecc.director.pause();p sprite as a child to this layer
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
	updateKeyboardInputs(); //Keyboard Input
	INPUTS->clearForNextFrame();//Clears existing inputs for next frame

}




//FUNCTION: updateKeyboardInputs()
//The player's key presses.

void Game::updateKeyboardInputs()
{
	int i = 0;

	//JUMPING//
	if (INPUTS->getKeyPress(KeyCode::KEY_W)) //Key press
	{
		PlayerPosition += Vec2(0, +1) * PlayerSpeed;
		orion->setPositionY(PlayerPosition.y);
		//orion->getPhysicsBody()->setVelocity(Vect(0, 300));
		orion->getPhysicsBody()->applyForce(Vect(0, 10000000));
	}
	if (INPUTS->getKey(KeyCode::KEY_W)) //Key hold
	{
		PlayerPosition += Vec2(0, +1) * PlayerSpeed;
		orion->setPositionY(PlayerPosition.y);
		//orion->getPhysicsBody()->setVelocity(Vect(0, -150));
		//orion->getPhysicsBody()->applyForce(Vect(0, -10000000));
	}

	//CROUCHING//
	if (INPUTS->getKey(KeyCode::KEY_S))
	{
		orion->getPhysicsBody()->applyForce(Vect(0, -5000000));
		//orion->setScaleY(0.5f);
	}
	if (INPUTS->getKeyRelease(KeyCode::KEY_S)) {
		//orion->setScaleY(1.0f);
	}

	//MOVE LEFT//
	if (INPUTS->getKey(KeyCode::KEY_A)) {
		PlayerPosition += Vec2(-1, 0) * PlayerSpeed;
		orion->setPositionX(PlayerPosition.x);
		orion->getPhysicsBody()->setVelocity(Vect(-20, 0));
		//orion->getPhysicsBody()->applyForce(Vect(-50000, 0));
		orion->setScaleX(-1.0f); //Orion faces left
	}
	if (INPUTS->getKeyRelease(KeyCode::KEY_A)) {
		//orion->getPhysicsBody()->applyForce(Vect(750000, 0));
	}

	//MOVE RIGHT//
	if (INPUTS->getKey(KeyCode::KEY_D))
	{
		PlayerPosition += Vec2(+1, 0) * PlayerSpeed;
		orion->setPositionX(PlayerPosition.x);
		orion->getPhysicsBody()->setVelocity(Vect(20, 0));
		//orion->getPhysicsBody()->applyForce(Vect(50000, 0));
		orion->setScaleX(1.0f); //Orion faces right
	}
	if (INPUTS->getKeyRelease(KeyCode::KEY_D)) {
		orion->getPhysicsBody()->applyForce(Vect(-750000, 0));
		Director::getInstance()->resume();

	}

	if (INPUTS->getKeyPress(KeyCode::KEY_ENTER)) {
		{
			i++;
			if (i == 1) {
				Director::getInstance()->getRunningScene()->pause();
				Director::getInstance()->getRunningScene()->resume();
			}
			if (i > 1) {
				Director::getInstance()->getRunningScene()->pause();
				Director::getInstance()->getRunningScene()->resume();
			
			}
		}
	}
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
	}
	return true;
}



//FUNCTION: DrawWorld()
//Initialization of the world (background, platforms, etc.) occur here.
void Game::DrawWorld()
{
	//Background
	background = Sprite::create("Assets/World/Background.png");
	background->setAnchorPoint(Vec2(0.5f, 0.5f)); //Center of object, objects rotate around this
	background->setPosition(Director::getInstance()->getWinSizeInPixels().width / 2, Director::getInstance()->getWinSizeInPixels().height / 2);
	this->addChild(background, -100);

	//Ground
	ground = Sprite::create("Assets/World/Level.png");
	ground->setName("Ground"); //Indentifies the node as "Ground"
	ground->setAnchorPoint(Vec2(0.0f, 0.0f)); //Center of object, objects rotate around this
	ground->setPosition(0, 0);

	//NOTE: RADIUS = name->getContentSize() / 2;
	//PhysicsMaterial() adjusts floats for Density, Restitution, and Friction
	PhysicsBody* ground_body = PhysicsBody::createBox(ground->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	ground_body->setDynamic(false); //Allows objects to have forces applied to it
	ground->setPhysicsBody(ground_body);
	this->addChild(ground);
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