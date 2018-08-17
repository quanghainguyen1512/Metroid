#include "MissileItem.h"
#include "World.h"

MissileItem::MissileItem(LPD3DXSPRITE spriteHandler, World* world) : Item(spriteHandler, world)
{
	this->width = 16;
	this->height = 16;
}

MissileItem::~MissileItem()
{
	delete(item);
}

void MissileItem::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
	item = new Sprite(spriteHandler, texture, ITEM_MISSILE, ITEM_MISSILE_WIDTH, ITEM_MISSILE_HEIGHT, ITEM_MISSILE_COUNT);
}

void MissileItem::Update(float t)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		item->updateSprite();
		last_time = now;
	}
}
void MissileItem::touchedBySamus(Samus *)
{
	// TODO: can use missile
	this->Destroy();
}

