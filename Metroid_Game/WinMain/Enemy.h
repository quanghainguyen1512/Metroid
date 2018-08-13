#pragma once
#include "GameObject.h"
//#include "BulletManager.h"
#include <time.h>

#define ANIMATE_ENEMY_RATE 7
#define ENEMY_FREEZE 500;

class Enemy : public GameObject
{
protected:
	ENEMY_TYPE enemy_type;
	LPDIRECT3DTEXTURE9 texture;
	float initPosX;
	float initPosY;
public:
	float time_freeze;	// thời gian dừng khi bị hit
	float health;		// Máu của object
	float damage;		// Lượng sát thương gây ra của object
	bool DeathByShoot;

	bool isActive = false;
	bool isDeath = false;

	Enemy();
	Enemy(LPD3DXSPRITE spriteHandler, World * manager);
	~Enemy();

	virtual void InitPostition();
	virtual void InitPostition(int x, int y);
	virtual void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);

	ENEMY_TYPE GetEnemyType();
	void SetEnemyType(ENEMY_TYPE enemy_type);

	//============== OVERRIDE VIRTUAL METHOD ===============
	virtual void Render();
	virtual void Update(float t);
	virtual void setEnemyStatefromString(string _state);
	virtual void startMoving();
	virtual void Destroy();
	virtual void setSamusLocation(int _posX, int _posY);
	virtual void startMovingBySamus(int _posX, int _posY);
	virtual void handleBullet(int bulletType);
	//============== END OVERRIDE VIRTUAL METHOD ============

	bool isInsideMapBound(RECT cameraBound);

	void setTexture(LPDIRECT3DTEXTURE9 texture);
	LPDIRECT3DTEXTURE9 getTexture();

	void setInitPosX(float x);
	float getInitPosX();
	void setInitPosY(float y);
	float getInitPosY();
};

