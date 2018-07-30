#include "Energy.h"
#include "World.h"

Energy::Energy(LPD3DXSPRITE spriteHandler, World* world) : Item(spriteHandler, world)
{
	this->setType(ITEM);
	item_type = MARU_MARI;
	energy = NULL;
	isActive = true;

	this->previousUnit = NULL;
	this->nextUnit = NULL;
	this->width = 16;
	this->height = 16;
}

Energy::~Energy()
{
	delete(energy);
}

void Energy::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
	energy = new Sprite(spriteHandler, texture, ITEM_ENERGY, ITEM_ENERGY_WIDTH, ITEM_ENERGY_HEIGHT, ITEM_ENERGY_COUNT);
}

void Energy::Init(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isActive = true;
	time_survive = ITEM_TIME_SURVIVE;
}

void Energy::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	if (!isActive)
		return;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	energy->drawSprite(energy->getWidth(), energy->getHeight(), position);
	spriteHandler->End();
}

void Energy::Update(float t)
{
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		energy->updateSprite();
		last_time = now;
	}
}

void Energy::Destroy()
{
	isActive = false;
}
