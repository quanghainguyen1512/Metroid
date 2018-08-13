#include "MissileItem.h"
#include "World.h"

MissileItem::MissileItem(LPD3DXSPRITE spriteHandler, World* world) : Item(spriteHandler, world)
{
	//item = NULL;
	//isActive = true;

	//this->previousUnit = NULL;
	//this->nextUnit = NULL;
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

//void MissileItem::Init(float posX, float posY)
//{
//	this->pos_x = posX;
//	this->pos_y = posY;
//	this->isActive = true;
//	time_survive = ITEM_TIME_SURVIVE;
//}

//void MissileItem::Render()
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

