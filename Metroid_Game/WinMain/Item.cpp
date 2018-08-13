#include  "Item.h"
#include "World.h"

Item::Item(LPD3DXSPRITE sprietHandler, World * manager)
{
	this->type = ITEM;
	this->spriteHandler = spriteHandler;
	this->manager = manager;
	this->time_survive = ITEM_TIME_SURVIVE;

	item = NULL;
	isActive = true;

	this->previousUnit = NULL;
	this->nextUnit = NULL;

	vx = 0;
	vy = 0;
}

Item::~Item()
{
	delete(item);
}

int Item::getNumberGain()
{
	return number_gain;
}

void Item::setNumberGain(int num)
{
	number_gain = num;
}

void Item::disappear()
{
}

void Item::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
}

void Item::Init(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isActive = true;
	time_survive = ITEM_TIME_SURVIVE;
}

void Item::Update(float t)
{
	if (!isActive)
		return;

	// Tính thời gian hiển thị
	time_survive -= t;

	// Nếu hết thời gian thì không hiển thị nữa
	if (time_survive <= 0)
	{
		isActive = false;
	}
}

void Item::Render()
{
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	if (!isActive)
		return;

	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	item->drawSprite(item->getWidth(), item->getHeight(), position);
	spriteHandler->End();
}

void Item::Destroy()
{
	this->setActive(false);
}
