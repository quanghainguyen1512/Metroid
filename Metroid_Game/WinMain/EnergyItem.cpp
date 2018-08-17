#include "EnergyItem.h"
#include "World.h"

EnergyItem::EnergyItem(LPD3DXSPRITE spriteHandler, World* world) : Item(spriteHandler, world)
{
	this->width = 16;
	this->height = 16;
}

EnergyItem::~EnergyItem()
{
	delete(item);
}

void EnergyItem::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
	item = new Sprite(spriteHandler, texture, ITEM_ENERGY, ITEM_ENERGY_WIDTH, ITEM_ENERGY_HEIGHT, ITEM_ENERGY_COUNT);
}

void EnergyItem::Update(float t)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		item->updateSprite();
		last_time = now;
	}
}


void EnergyItem::touchedBySamus(Samus * samus)
{
	// TODO: plus health
	this->Destroy();
}
