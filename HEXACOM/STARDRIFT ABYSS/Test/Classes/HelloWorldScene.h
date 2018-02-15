#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <iostream>
#include <fstream>
#include <ui\UITextField.h>
using namespace cocos2d;


class Game : public cocos2d::Scene
{
	//Public Data
public:
	virtual bool			init();
	virtual void			onEnter(), onExit();
	void					update(float deltaTime);
	void					updateKeyboardInputs();
	void					DrawWorld();
	void					setupAnimations();
	void					menuCloseCallback(cocos2d::Ref* pSender);
	static					cocos2d::Scene* createScene();
	bool					onContactBegin(PhysicsContact &contact); //collision
	void                    pause(bool isPaused);

																	 //Implement "static create()" method manually
	CREATE_FUNC(Game);

	// FIELDS
	Director* director;
	Follow* camera;
	Scene* scene;
	//static Scene* sceneHandle;

	//Sprites
	Sprite* orion; //Character
	Sprite* cameraTarget; //Camera
	Sprite* background; //BG
	Sprite* ground; //ground

					//Animations
	Animate* walkLeft;
	Animate* walkRight;
	Animate* jumping;
	Animate* falling;

	// VARIABLES

	//total time game runtime
	float gameTime = 0.0f;

	//Player Attributes
	float PlayerSpeed = 4.5f;
	Vec2 PlayerPosition = Vec2(100, 100); //Player Spawnpoint

										  //This scene's physics world
										  //Reference to the physics world used within the scene. Prevents having to call: director->getRunningScene()->getPhysicsWorld() every time we want to do something
										  //HAS to be static because the create function we set its value in is a static function. The compiler will complain if we try to use a non-static member in a static function
	static PhysicsWorld* physicsWorld;
};

#endif // __HELLOWORLD_SCENE_H__