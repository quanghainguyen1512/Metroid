#pragma once
#include "GameObject.h"
#include "Define.h"
#include "Texture.h"
#include "Grid.h"


class BulletSkree : public GameObject
{
private:

	bool isRendered;
	float startX;
	float startY;
	float endX;
	float endY;
	float range;

public:
	Sprite * sprite;


	void initBullet(float posX, float posY);
	void Update(float t);
	void Update(float t, float posX, float posY);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Reset(float posX, float posY);
	BulletSkree();
	BulletSkree(LPD3DXSPRITE spriteHandler, Grid* grid);
	~BulletSkree();

	void setIsRendered(bool isRendered);
	bool getIsRendered();

	Bullet_Skree_Direction bulletDirection;

	void setRange(float _range);
	float getRange();

};