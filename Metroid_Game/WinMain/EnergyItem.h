#pragma once
#include "Item.h"
#include "Sprite.h"
#include "Define.h"

class EnergyItem : public Item
{
public:
	EnergyItem(LPD3DXSPRITE spriteHandler, World* world);
	~EnergyItem();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	//void Init(float posX, float posY);
	void Update(float t);
	//void Render();
	//void Destroy();
	void touchedBySamus(Samus*);
};