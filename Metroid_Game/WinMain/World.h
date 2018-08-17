﻿#pragma once
#include "MaruMari.h"
#include "Define.h"
#include "Samus.h"
#include "Zoomer.h"
#include "Skree.h"
#include <vector>
#include "Texture.h"
#include "Bullet.h"
#include "ExplodeEffect.h"
#include "BombWeapon.h"
#include "Gate.h"
#include "GateBlock.h"
#include "Ridley.h"
#include "Kraid.h"
#include "BulletSkree.h"
#include "BulletKraid.h"
#include "KraidBoomerang.h"

using namespace std;

class World
{
public:
	Metroid * metroid;
	Samus * samus;
	MaruMari * maruMari;
	ExplodeEffect* explodeEffect;
	BombWeapon* bombWeapon;

	Gate * gateLeftRoom1;
	Gate * gateRightRoom1;
	Gate * gateLeftRoom2;
	Gate * gateRightRoom2;
	Gate * gateLeftBoss1;
	Gate * gateRightBoss1;
	GateBlock * gateBlockRoom1;
	GateBlock * gateBlockRoom2;
	GateBlock * gateBlockBoss1;
	Kraid * kraid;
	Ridley * ridley;

	vector<Bullet*> samusBullet;
	vector<Enemy*> enemy;
	vector<BulletSkree*> skreeBullet;
	LPD3DXSPRITE spriteHandler;

	vector<BulletKraid*> kraidBullet;
	vector<KraidBoomerang*> kraidBomerang;

	World();
	World(LPD3DXSPRITE spriteHandler, Metroid * metroid);
	~World();

	void Update(float t);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);

	void loadEnemyPositions(string filePath);
	vector<string> World::split(string s, string c);
	Metroid * getMetroid();

	void setDirectionForZoomer(Enemy*, string str);
};