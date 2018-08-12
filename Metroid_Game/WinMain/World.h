﻿#pragma once
#include "MaruMari.h"
#include <d3dx9.h>
#include "Define.h"
#include "Samus.h"
#include "Zoomer.h"
#include <vector>
#include "Texture.h"
#include "Grid.h"
#include "Bullet.h"
#include "ExplodeEffect.h"
#include "BombWeapon.h"
#include "BulletSkree.h"
#include "Skree.h"
#include "BulletKraid.h"
#include "BulletKraidMissle.h"
#include "BulletRidley.h"

using namespace std;

/*
Class này chứa tất cả những thứ trong Game
Các class khác chứa con trỏ đến class này để thao tác với các đối tượng trong class này
*/

class World
{
public:
	Metroid * metroid;
	Grid *grid;
	Samus * samus;
	MaruMari * maruMari;
	ExplodeEffect* explodeEffect;
	BombWeapon* bombWeapon;

	vector<Bullet*> samusBullet;
	vector<Enemy*> enemy;
	LPD3DXSPRITE spriteHandler;

	vector<BulletSkree*> bulletSkree;
	vector<BulletKraidMissle*> bulletKraidMissle;
	vector<BulletKraid*> bulletKraid;
	vector<BulletRidley*> bulletRidley;


	World();
	World(LPD3DXSPRITE spriteHandler, Metroid * metroid, int width, int height);
	~World();

	void Update(float t);
	void Render();
	void InitSprites(LPDIRECT3DDEVICE9 d3ddv);

	void loadEnemyPositions(string filePath);
	vector<string> World::split(string s, string c);

	void setDirectionForZoomer(Enemy*, string str);
};