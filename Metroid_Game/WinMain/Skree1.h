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
	SHOT
};

class Skree : public Enemy
{
protected:
	Sprite * skree;

	int animate_rate;	// cần biến này vì khi dí theo Samus animate rate thay đổi
public:
	Skree();
	Skree(LPD3DXSPRITE spriteHandler, World * manager, OBJECT_TYPE enemy_type);

	~Skree();

	SKREE_STATE state;
	void setState(SKREE_STATE _state);
	SKREE_STATE getState();

	int samus_PosX = 0;
	int samus_PosY = 0;

	vector<Bullet*> skreeBullet;

	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	//============== OVERRIDE VIRTUAL METHOD ===================
	virtual void Update(float t);
	virtual void Render();
	virtual void setEnemyStatefromString(string _state);
	virtual void startMoving();
	virtual void setSamusLocation(int _posX, int _posY);
	virtual void startMovingBySamus(int _posX, int _posY);
	virtual void handleBullet(int bulletType);
	//============== END OVERRIDE VIRTUAL METHOD ===============
	virtual void Destroy();
};