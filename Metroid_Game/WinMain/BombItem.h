#pragma once
#include "Item.h"
#include "Sprite.h"
#include "Define.h"

class BombItem : public Item
{
private:
	Sprite * bomb;
public:
	BombItem(LPD3DXSPRITE spriteHandler, World* world);
	~BombItem();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	//void Init(float posX, float posY);
	void Update(float t);
	//void Render();
	//void Destroy();
	void touchedBySamus(Samus*);
};