#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "trace.h"
#include "World.h"


class Samus : public GameObject
{
protected:
	Sprite * standRight;
	Sprite * standLeft;
	Sprite * runRight;
	Sprite * runLeft;
	Sprite * standShootL;
	Sprite * standShootR;
	Sprite * morphLeft;
	Sprite * morphRight;
	Sprite * runShootL;
	Sprite * runShootR;
	Sprite * runShootUpL;
	Sprite * runShootUpR;
	Sprite * jumpLeft;
	Sprite * jumpRight;
	Sprite * ballLeft;
	Sprite * ballRight;
	Sprite * jumpShootL;
	Sprite * jumpShootR;

	SAMUS_STATE state;	

	int tempX;
	bool isBall;
	bool canMorph = true;
public:
	bool isJumping = false;	// Trạng thái đang nhảy của Samus
	bool isFalling = false;
	bool isMorphing = false;
	bool isCollideLeft = false;
	bool isCollideRight = false;

	float health;	// Máu của Samus
	bool isDeath = false;	// Trạng thái chết của Samus
	Samus();
	Samus(LPD3DXSPRITE spriteHandler, World * manager, Grid* grid);
	~Samus();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void InitPostition();

	SAMUS_STATE GetState();
	void SetState(SAMUS_STATE value);
	bool isSamusJumping();
	//bool isSamusCrouch();
	bool isSamusDeath();

	void ResetAllSprites();
	bool GetStateActive();

	void setIsBall(bool isBall);
	bool getIsBall();

	void setCanMorph(bool canRoll);
	bool getCanMorph();
	//================ OVERRIDE VIRTUAL METHOD ==================
	void Reset(float  x, float y);
	void Update(float t);
	void Render();
	void Destroy();
	//================= END OVERRIDE VIRTUAL METHOD =============

	float collideDistanceX = 0;
	float collideDistanceY = 0;
	bool canControl = true;
	float checkpoint = 0;
	void collideEnemy();
};


