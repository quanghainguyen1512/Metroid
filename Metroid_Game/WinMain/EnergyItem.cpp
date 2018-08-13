#include "EnergyItem.h"
#include "World.h"

EnergyItem::EnergyItem(LPD3DXSPRITE spriteHandler, World* world) : Item(spriteHandler, world)
{
	//item = NULL;
	//isActive = true;

	//this->previousUnit = NULL;
	//this->nextUnit = NULL;
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

//void EnergyItem::Init(float posX, float posY)
//{
//	this->pos_x = posX;
//	this->pos_y = posY;
//	this->isActive = true;
//	time_survive = ITEM_TIME_SURVIVE;
//}

//void EnergyItem::Render()
//{
//	D3DXVECTOR3 position;
//	position.x = pos_x;
//	position.y = pos_y;
//	position.z = 0;
//
//	if (!isActive)
//		return;
//
//	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
//	item->drawSprite(item->getWidth(), item->getHeight(), position);
//	spriteHandler->End();
//}

void EnergyItem::Update(float t)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		item->updateSprite();
		last_time = now;
	}
}

//void EnergyItem::Destroy()
//{
//	isActive = false;
//}

void EnergyItem::touchedBySamus(Samus * samus)
{
	// TODO: plus health
	this->Destroy();
}
