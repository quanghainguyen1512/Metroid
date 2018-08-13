#include "BombItem.h"

BombItem::BombItem(LPD3DXSPRITE spriteHandler, World* world) : Item(spriteHandler, world)
{
	this->width = 16;
	this->height = 16;
}

BombItem::~BombItem()
{
	delete(item);
}

void BombItem::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
	// TODO: BombItem sprite
	item = new Sprite(spriteHandler, texture, ITEM_BOMB_PATH, ITEM_BOMB_WIDTH, ITEM_BOMB_HEIGHT, ITEM_BOMB_COUNT);
}

void BombItem::Update(float t)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		item->updateSprite();
		last_time = now;
	}
}

void BombItem::touchedBySamus(Samus * samus)
{
	// TODO: affect to samus
	this->Destroy();
}