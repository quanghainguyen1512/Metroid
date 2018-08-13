﻿#include "Enemy.h"
#include "Game.h"
#include "World.h"

Enemy::Enemy()
{
}

Enemy::Enemy(LPD3DXSPRITE spriteHandler, World * manager)
{
	this->spriteHandler = spriteHandler;
	this->manager = manager;

	this->time_freeze = ENEMY_FREEZE;
}

Enemy::~Enemy()
{
}

void Enemy::InitPostition()
{
}

void Enemy::InitPostition(int x, int y)
{
	this->pos_x = x;
	this->pos_y = y;
}

void Enemy::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;
}
ENEMY_TYPE Enemy::GetEnemyType()
{
	return enemy_type;
}
void Enemy::SetEnemyType(ENEMY_TYPE enemy_type)
{
	this->enemy_type = enemy_type;
}

void Enemy::Update(float t)
{
}

void Enemy::Render()
{
}

void Enemy::setEnemyStatefromString(string _state) {

}

void Enemy::startMoving()
{
}

void Enemy::startMovingBySamus(int _posX, int _posY)
{
}

void Enemy::handleBullet(int bulletType)
{
}

void Enemy::Destroy()
{
}

void Enemy::setSamusLocation(int _posX, int _posY)
{
}

bool Enemy::isInsideMapBound(RECT cameraBound)
{
	RECT bound = cameraBound;
	D3DXVECTOR2 point(this->pos_x, this->pos_y);
	//lam theo map.cpp
	if (Math::isPointinRectangle(point, bound)) {
		return true;
	}
	return false;
}

void Enemy::setTexture(LPDIRECT3DTEXTURE9 texture) {
	this->texture = texture;
}

LPDIRECT3DTEXTURE9 Enemy::getTexture() {
	return this->texture;
}

void Enemy::setInitPosX(float x) {
	this->initPosX = x;
}

float Enemy::getInitPosX() {
	return this->initPosX;
}

void Enemy::setInitPosY(float y) {
	this->initPosY = y;
}

float Enemy::getInitPosY() {
	return this->initPosY;
}
