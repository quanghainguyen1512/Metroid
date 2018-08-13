﻿#include "ExplodeEffect.h"
#include "World.h"
ExplodeEffect::ExplodeEffect()
{
}

ExplodeEffect::ExplodeEffect(LPD3DXSPRITE spriteHandler, World *manager, Grid * grid) : Effect(spriteHandler, manager, grid)
{
	this->spriteHandler = spriteHandler;
	this->grid = grid;
	this->manager = manager;
	explode = nullptr;
	isActive = false;
	this->width = EFFECT_EXPLOSION_WIDTH;
	this->height = EFFECT_EXPLOSION_HEIGHT;
	
}


ExplodeEffect::~ExplodeEffect()
{
	//delete explode;
	//delete manager;
	//delete grid;
}


void ExplodeEffect::Update(float t)
{

	if (isActive == true && manager->bombWeapon->getBombExplode() == true)
	{
		int row = (int)floor(this->pos_y / CELL_SIZE);
		int column = (int)floor(this->pos_x / CELL_SIZE);

		this->isRight = false;
		this->isLeft = false;
		this->isTop = false;
		this->isBottom = false;

		this->grid->updateGrid(this, this->pos_x, this->pos_y);

		// Xet va cham va cap nhat vi tri
		this->grid->handleCell(this, row, column);

		//time_survive = EFFECT_TIME_SURVIVE;
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / ANIMATE_RATE)
		{
			explode->updateSprite();
			last_time = now;
		}
		// Tính thời gian hiển thị
		time_survive -= t;
		if (time_survive < 0)
		{
			isActive = false;
		}

	}
	else
		return;


}

void ExplodeEffect::Render()
{
	if (time_survive <= 0)
		isActive = false;

	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;

	if (isActive == true && manager->bombWeapon->getBombExplode() == true && time_survive > 0)
	{
		//isRendering == true;
		explode->drawSprite(EFFECT_EXPLOSION_WIDTH, EFFECT_EXPLOSION_HEIGHT, position);
	}

}

void ExplodeEffect::CreateExplode(float x, float y)
{
	this->pos_y = y;
	this->pos_x = x;
	//currentSprite = explode;
}

void ExplodeEffect::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	explode = new Sprite(spriteHandler, texture, EFFECT_EXPLOSION, EFFECT_EXPLOSION_WIDTH, EFFECT_EXPLOSION_HEIGHT, EFFECT_EXPLOSION_COUNT);
}

