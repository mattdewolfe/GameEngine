#ifndef MOVEMENTCONTROLLERCOMPONENT_H
#define MOVEMENTCONTROLLERCOMPONENT_H

#include "IGameComponent.h"

enum MOTIONTYPE
{
	FORWARD = 0, 
	BACKWARD,
	LEFT, 
	RIGHT,
	USE
};

class MovementControllerComponent : public IGameComponent 
{
public:
	MovementControllerComponent(bool _isHumanPlayer);
	~MovementControllerComponent();

	virtual bool Init();
	virtual void Destroy();
	// Check for key presses and alter velocity as needed
	virtual void Update(float _deltaTime);
	// Register a given key with a specified type of motion
	void RegisterKey(MOTIONTYPE _motion, int _keyVal);
	// used to issue movement to a target location (either for AI or in-game cinematics)
	void IssueMovementCommand(float3 _target);
	void SetVelocity();
	float3 GetVelocity();

protected:
	// If this is a human player, we will register/check key values
	// Otherwise it is an AI and will get movement commands from its AI component
	bool isHumanPlayer;
	// Register ascii values for key controllers
	int regForwardKey;
	int regBackwardKey;
	int regLeftKey;
	int regRightKey;
	int regUseKey;
	float3 velocity;
};

#endif