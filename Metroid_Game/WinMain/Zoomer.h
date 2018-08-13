#pragma once
#include "Enemy.h"
#include "Define.h"


class Zoomer : public Enemy
{
protected:
	ZOOMER_STATE state;
	ZOOMER_DIRECTION direction;
	ZOOMER_DIRECTION initDirection;

	Sprite * top;
	Sprite * bottom;
	Sprite * left;
	Sprite * right;

private:
	bool isLeftCollided;
	bool isRightCollided;
	bool isTopCollided;
	bool isBottomCollided;
	bool isCollisionHandled;
public:
	Zoomer();
	Zoomer(LPD3DXSPRITE spriteHandler, World * manager, OBJECT_TYPE enemy_type);
	~Zoomer();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void setState(ZOOMER_STATE _state);
	ZOOMER_STATE getState();

	void setDirection(ZOOMER_DIRECTION direction);
	ZOOMER_DIRECTION getDirection();
	
	void setInitDirection(ZOOMER_DIRECTION direction);
	ZOOMER_DIRECTION getInitDirection();

	void setVelocity();

	void setIsLeftCollided(bool isLeft);
	bool getIsLeftCollided();
	void setIsRightCollided(bool isRight);
	bool getIsRightCollided();
	void setIsTopCollided(bool isTop);
	bool getIsTopCollided();
	void setIsBottomCollided(bool isBottom);
	bool getIsBottomCollided();
	void setIsCollisionHandled(bool handled);
	bool getIsCollisionHandled();
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(float t);
	virtual void Render();
	virtual void setEnemyStatefromString(string _state);
	virtual void startMoving();
	//============== END OVERRIDE VIRTUAL METHOD ===============
	void Destroy(float x, float y);


};
