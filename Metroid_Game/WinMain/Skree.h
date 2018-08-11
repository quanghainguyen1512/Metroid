#pragma once
#pragma once
#include "Enemy.h"
#include "Define.h"
#include "Math.h"

enum SKREE_STATE
{
	ON_HANGING,
	ON_FALLING,
	LANDED,
	SHOT,
	EXPLOSION_STATE,
	KILLED
};

class Skree : public Enemy
{
protected:
	Sprite * skree;
	int animate_rate;	// cần biến này vì khi dí theo Samus animate rate thay đổi

	//

private:
	bool isLeftCollided;
	bool isRightCollided;
	bool isTopCollided;
	bool isBottomCollided;
	bool isCollisionHandled;

	bool isInCameraAfterDestroyed;

public:
	Skree();
	Skree(LPD3DXSPRITE spriteHandler, World * manager, OBJECT_TYPE enemy_type);

	~Skree();

	SKREE_STATE state;
	void setState(SKREE_STATE _state);
	SKREE_STATE getState();

	int samus_PosX = 0;
	int samus_PosY = 0;

	float range;
	float liveTime = 0;


	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	//============== OVERRIDE VIRTUAL METHOD ===================
	void Update(float t);
	void Render();
	void setEnemyStatefromString(string _state);
	void startMoving();
	void setSamusLocation(int _posX, int _posY);
	void handleBullet(int bulletType);
	//============== END OVERRIDE VIRTUAL METHOD ===============
	void Destroy();
	void Destroy(float x, float y);


	void reset();
	void setIsInCameraAfterDestroyed(bool value) { isInCameraAfterDestroyed = value; }
	bool getIsInCameraAfterDestroyed() { return isInCameraAfterDestroyed; }

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
};