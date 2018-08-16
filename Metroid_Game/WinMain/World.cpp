﻿#include "World.h"
World::World()
{
}

World::World(LPD3DXSPRITE spriteHandler, Metroid * metroid)
{
	this->spriteHandler = spriteHandler;
	this->metroid = metroid;

	//Khởi tạo các đối tượng trong World
	samus = new Samus(spriteHandler, this, this->getMetroid()->getGrid());
	
	// Khởi tạo đạn (3 viên)
	Bullet *bullet1 = new Bullet(spriteHandler, this->getMetroid()->getGrid());
	Bullet *bullet2 = new Bullet(spriteHandler, this->getMetroid()->getGrid());
	Bullet *bullet3 = new Bullet(spriteHandler, this->getMetroid()->getGrid());
	this->samusBullet.push_back(bullet1);
	this->samusBullet.push_back(bullet2);
	this->samusBullet.push_back(bullet3);

	BulletKraidMissle *bulletKraidMissle1 = new BulletKraidMissle(spriteHandler, this->getMetroid()->getGrid());
	BulletKraidMissle *bulletKraidMissle2 = new BulletKraidMissle(spriteHandler, this->getMetroid()->getGrid());
	BulletKraidMissle *bulletKraidMissle3 = new BulletKraidMissle(spriteHandler, this->getMetroid()->getGrid());
	this->kraidMissle.push_back(bulletKraidMissle1);
	this->kraidMissle.push_back(bulletKraidMissle2);
	this->kraidMissle.push_back(bulletKraidMissle3);

	BulletKraid *bulletKraid1 = new BulletKraid(spriteHandler, this->getMetroid()->getGrid());
	BulletKraid *bulletKraid2 = new BulletKraid(spriteHandler, this->getMetroid()->getGrid());
	this->bulletKraid.push_back(bulletKraid1);
	this->bulletKraid.push_back(bulletKraid2);

	BulletRidley *bulletRidley1 = new BulletRidley(spriteHandler, this->getMetroid()->getGrid());
	BulletRidley *bulletRidley2 = new BulletRidley(spriteHandler, this->getMetroid()->getGrid());
	BulletRidley *bulletRidley3 = new BulletRidley(spriteHandler, this->getMetroid()->getGrid());
	BulletRidley *bulletRidley4 = new BulletRidley(spriteHandler, this->getMetroid()->getGrid());

	this->bulletRidley.push_back(bulletRidley1);
	this->bulletRidley.push_back(bulletRidley2);
	this->bulletRidley.push_back(bulletRidley3);
	this->bulletRidley.push_back(bulletRidley4);

	maruMari = new MaruMari(spriteHandler, this);

	explodeEffect = new ExplodeEffect(spriteHandler, this, this->getMetroid()->getGrid());
	bombWeapon = new BombWeapon(spriteHandler, this);

	gateRightRoom1 = new Gate(spriteHandler, this);
	gateLeftRoom1 = new Gate(spriteHandler, this);
	gateRightRoom2 = new Gate(spriteHandler, this);
	gateLeftRoom2 = new Gate(spriteHandler, this);
	gateRightBoss1 = new Gate(spriteHandler, this);
	gateLeftBoss1 = new Gate(spriteHandler, this);

	gateBlockRoom1 = new GateBlock(spriteHandler, this, metroid->getGrid());
	gateBlockRoom2 = new GateBlock(spriteHandler, this, metroid->getGrid());
	gateBlockBoss1 = new GateBlock(spriteHandler, this, metroid->getGrid());

	loadEnemyPositions("Monster_Room1.txt");

	ridley = new Ridley(spriteHandler, this);
	kraid = new Kraid(spriteHandler, this);
}

World::~World()
{
	delete(samus);
	delete(maruMari);
	delete(metroid);
	delete(explodeEffect);
	delete(bombWeapon);
	delete(gateLeftRoom1);
	delete(gateRightRoom1);
	delete(gateLeftRoom2);
	delete(gateRightRoom2);
	delete(gateLeftBoss1);
	delete(gateRightBoss1);
	delete(gateBlockRoom1);
	delete(gateBlockRoom2);
	delete(gateBlockBoss1);
	delete(ridley);
	delete(kraid);
}

void World::Update(float t)
{
	this->samus->Update(t);
	int row = (int)floor(this->samus->getlastPosY() / CELL_SIZE);
	int column = (int)floor(this->samus->getlastPosX() / CELL_SIZE);

	maruMari->Update(t);

	for (int i = 0; i < this->samusBullet.size(); i++) {
		this->samusBullet[i]->Update(t, this->samus->getPosX(), this->samus->getPosY());
	}

	/*START UPDATING ENEMY*/
	for (int i = 0; i < this->enemy.size(); i++) {
		if (this->enemy[i]->isInsideMapBound(this->metroid->camera->getBoundary())) {
			if (!this->enemy[i]->isActive) {
				if (this->enemy[i]->isDeath) {
				}
				else {
					enemy[i]->isActive = true;
				}

			}
			else if (this->enemy[i]->isActive && !this->enemy[i]->isDeath) {
				if (enemy[i]->getType() == SKREE) {
					enemy[i]->setSamusLocation(this->samus->pos_x, this->samus->pos_y);
				}
				enemy[i]->Update(t);
				
			}
		}
		else {
			this->enemy[i]->isDeath = false;
			this->enemy[i]->health = 100.0f;
			
		}
	}
	/*END UPDATING ENEMY*/

	bombWeapon->Update(t);
	explodeEffect->Update(t);

	gateBlockRoom1->Update(t);
	gateBlockRoom2->Update(t);
	gateBlockBoss1->Update(t);

	gateLeftRoom1->Update(t);
	gateRightRoom1->Update(t);
	gateLeftRoom2->Update(t);
	gateRightRoom2->Update(t);
	gateLeftBoss1->Update(t);
	gateRightBoss1->Update(t);

	kraid->Update(t);
	ridley->Update(t);

	if (this->kraid->isActive) {
		for (int i = 0; i < this->kraidMissle.size(); i++) {
			if (kraidMissle[i]->isActive) {
				kraidMissle[i]->Update(t);
			}
			else {
				kraidMissle[i]->initBullet(this->kraid->pos_x, this->kraidMissle[i]->pos_y, this->samus->pos_x);
			}
		}

		for (int i = 0; i < this->bulletKraid.size(); i++) {
			if (bulletKraid[i]->isActive) {
				bulletKraid[i]->Kraid_posX = this->kraid->pos_x;
				bulletKraid[i]->Kraid_posY = this->kraid->pos_y;
				bulletKraid[i]->Update(t);
			}
			else {
				if (i == 0)
					bulletKraid[i]->initBullet(this->kraid->pos_x, this->kraid->pos_y, this->samus->pos_x);
				else 
					bulletKraid[i]->initBullet(this->kraid->pos_x + 16, this->kraid->pos_y, this->samus->pos_x);
			}
		}
	}

	if (this->ridley->isActive) {
		for (int i = 0; i < this->bulletRidley.size(); i++) {
			if (bulletRidley[i]->isActive) {
				bulletRidley[i]->Ridley_posX = this->ridley->pos_x;
				bulletRidley[i]->Ridley_posY = this->ridley->pos_y;
				bulletRidley[i]->Update(t);
			}
			else {
				if (i % 2 == 0)
					bulletRidley[i]->initBullet(this->ridley->pos_x, this->ridley->pos_y, this->samus->pos_x);
				else
					bulletRidley[i]->initBullet(this->ridley->pos_x + 16, this->ridley->pos_y, this->samus->pos_x);
			}
		}
	}
}

void World::Render()
{
	this->samus->Render();
	maruMari->Render();
	for (int i = 0; i < this->samusBullet.size(); i++) {
		this->samusBullet[i]->Render();
	}


	for (int i = 0; i < this->enemy.size(); i++) {
		if (this->enemy[i]->isInsideMapBound(this->metroid->camera->getBoundary())) {
			if (this->enemy[i]->isActive && !this->enemy[i]->isDeath) {
				this->enemy[i]->Render();

			}
		}
	}



	bombWeapon->Render();
	explodeEffect->Render();

	gateBlockRoom1->Render();
	gateBlockRoom2->Render();
	gateBlockBoss1->Render();

	gateRightRoom1->Render();
	gateLeftRoom1->Render();
	gateRightRoom2->Render();
	gateLeftRoom2->Render();
	gateRightBoss1->Render();
	gateLeftBoss1->Render();
	ridley->Render();
	kraid->Render();

	if (this->kraid->isActive) {
		for (int i = 0; i < this->kraidMissle.size(); i++) {
			if (kraidMissle[i]->isActive) {
				kraidMissle[i]->Render();
			}
		}
		for (int i = 0; i < this->bulletKraid.size(); i++) {
			if (bulletKraid[i]->isActive) {
				bulletKraid[i]->Render();
			}
		}
	}

	if (this->ridley->isActive) {
		for (int i = 0; i < this->bulletRidley.size(); i++) {
			if (bulletRidley[i]->isActive) {
				bulletRidley[i]->Render();
			}
		}
	}

}

void World::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	Texture * texture = new Texture();
	LPDIRECT3DTEXTURE9 samus_texture = texture->loadTexture(d3ddv, TEXTURE_GAME_CHARACTERS);
	samus->InitSprites(d3ddv, samus_texture);

	LPDIRECT3DTEXTURE9 maru_texture = texture->loadTexture(d3ddv, ITEM_SPRITE_PATH);
	maruMari->InitSprites(d3ddv, maru_texture);

	// Bullet Texture
	LPDIRECT3DTEXTURE9 bulletTexture = texture->loadTexture(d3ddv, SAMUS_BULLET_PATH);
	for (int i = 0; i < this->samusBullet.size(); i++) {
		this->samusBullet[i]->InitSprites(d3ddv, bulletTexture);
	}

	//texture for kraid missle <- change here
	for (int i = 0; i < this->kraidMissle.size(); i++) {
		this->kraidMissle[i]->InitSprites(d3ddv, bulletTexture);
	}

	//texture for kraid bullet <- change here
	for (int i = 0; i < this->bulletKraid.size(); i++) {
		this->bulletKraid[i]->InitSprites(d3ddv, bulletTexture);
	}
	//texture for ridley bullet <- change here
	for (int i = 0; i < this->bulletRidley.size(); i++) {
		this->bulletRidley[i]->InitSprites(d3ddv, bulletTexture);
	}


	// Explode Texture
	LPDIRECT3DTEXTURE9 explode_texture = texture->loadTexture(d3ddv, EFFECT_SPRITE_PATH);
	explodeEffect->InitSprites(d3ddv, explode_texture);

	// Bomb Texture
	LPDIRECT3DTEXTURE9 bomb_texture = texture->loadTexture(d3ddv, BOMB_TEXTURE);
	bombWeapon->InitSprites(d3ddv, bomb_texture);
	
	// Enemy Texture
	LPDIRECT3DTEXTURE9 enemyTexture = texture->loadTexture(d3ddv, ENEMY_SPRITE_PATH);
	for (int i = 0; i < this->enemy.size(); i++) {
		enemy[i]->InitSprites(d3ddv, enemyTexture);
	}

	// Gate Texture
	LPDIRECT3DTEXTURE9 gate_texture = texture->loadTexture(d3ddv, GATE_SPRITES_PATH);
	gateRightRoom1->InitSprites(d3ddv, gate_texture, GATE_RIGHT);
	gateLeftRoom1->InitSprites(d3ddv, gate_texture, GATE_LEFT);
	gateRightRoom2->InitSprites(d3ddv, gate_texture, GATE_RIGHT);
	gateLeftRoom2->InitSprites(d3ddv, gate_texture, GATE_LEFT);
	gateRightBoss1->InitSprites(d3ddv, gate_texture, GATE_RIGHT);
	gateLeftBoss1->InitSprites(d3ddv, gate_texture, GATE_LEFT);

	gateBlockRoom1->InitSprites(d3ddv, gate_texture);
	gateBlockRoom2->InitSprites(d3ddv, gate_texture);
	gateBlockBoss1->InitSprites(d3ddv, gate_texture);

	// boss texture
	LPDIRECT3DTEXTURE9 boss_texture = texture->loadTexture(d3ddv, BOSS_TEXTURE);
	ridley->InitSprites(d3ddv, boss_texture);
	kraid->InitSprites(d3ddv, boss_texture);
}

void World::loadEnemyPositions(string filePath) {
	ifstream file_txt(filePath);
	string str;
	vector<string> v;
	while (getline(file_txt, str)) {
		v = split(str, "\t");
		Enemy *monster = nullptr;
		int value = atoi(v[0].c_str());
		switch (value)
		{
		case ZOOMER_CASE: {
			monster = new Zoomer(spriteHandler, this, ZOOMER_YELLOW);
			this->setDirectionForZoomer(monster, v[5]);
			monster->setEnemyStatefromString(v[6]);
			
			break;
		}
		case SKREE_CASE: {
			monster = new Skree(spriteHandler, this, SKREE);
			break;
		}
		default:
			break;
		}
		if (monster != nullptr) {
			monster->setPosX(stoi(v[3]));
			monster->setInitPosX(stoi(v[3]));
			monster->setPosY(stoi(v[4]));
			monster->setInitPosY(stoi(v[4]));
			monster->setActive(false);
			monster->setVelocityX(0);
			monster->setVelocityY(0);
			this->enemy.push_back(monster);
			v.clear();
			this->getMetroid()->getGrid()->add(monster);
		}
			
	}
	if (v.size() != NULL)
		trace(L"Unable to load EnemyPosition");
}

vector<string> World::split(string s, string c) {
	string::size_type i = 0;
	string::size_type j = s.find(c);
	vector<string> v;
	while (j != string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j == string::npos)
			v.push_back(s.substr(i, s.length()));
	}
	return v;
}

Metroid * World::getMetroid()
{
	return this->metroid;
}

void World::setDirectionForZoomer(Enemy* enemy, string str) {
	Zoomer* zoomer = dynamic_cast<Zoomer*>(enemy);
	if (str == "RIGHT") {
		zoomer->setDirection(ZOOMER_RIGHT);
	}
	else if (str == "LEFT") {
		zoomer->setDirection(ZOOMER_LEFT);
	}
	else if (str == "UP") {
		zoomer->setDirection(ZOOMER_UP);
	}
	else if (str == "DOWN") {
		zoomer->setDirection(ZOOMER_DOWN);
	}
	zoomer->setInitDirection(zoomer->getDirection());
}