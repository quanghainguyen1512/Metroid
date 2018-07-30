#pragma once
#include "Item.h"
#include "Sprite.h"
#include "Define.h"

class Energy : public Item
{
private:
	Sprite * energy;
public:
	Energy(LPD3DXSPRITE spriteHandler, World* world);
	~Energy();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void Init(float posX, float posY);
	void Update(float t);
	void Render();
	void Destroy();
};