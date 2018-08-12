#include "World.h"
#include <vector>

using namespace std;

World::World()
{

}

World::World(LPD3DXSPRITE spriteHandler, Metroid * metroid, int width, int height)
{
	this->spriteHandler = spriteHandler;
	this->metroid = metroid;

	grid = new Grid(height, width);

	//Khởi tạo các đối tượng trong World
	samus = new Samus(spriteHandler, this, this->grid);
	
	// Khởi tạo đạn (3 viên)
	Bullet *bullet1 = new Bullet(spriteHandler, grid);
	Bullet *bullet2 = new Bullet(spriteHandler, grid);
	Bullet *bullet3 = new Bullet(spriteHandler, grid);
	this->samusBullet.push_back(bullet1);
	this->samusBullet.push_back(bullet2);
	this->samusBullet.push_back(bullet3);

	BulletSkree *bulletSkree1 = new BulletSkree(spriteHandler, grid);
	BulletSkree *bulletSkree2 = new BulletSkree(spriteHandler, grid);
	BulletSkree *bulletSkree3 = new BulletSkree(spriteHandler, grid);
	BulletSkree *bulletSkree4 = new BulletSkree(spriteHandler, grid);
	this->bulletSkree.push_back(bulletSkree1);
	this->bulletSkree.push_back(bulletSkree2);
	this->bulletSkree.push_back(bulletSkree3);
	this->bulletSkree.push_back(bulletSkree4);

	BulletKraidMissle *bulletKraidMissle1 = new BulletKraidMissle(spriteHandler, grid);
	BulletKraidMissle *bulletKraidMissle2 = new BulletKraidMissle(spriteHandler, grid);
	BulletKraidMissle *bulletKraidMissle3 = new BulletKraidMissle(spriteHandler, grid);
	this->bulletKraidMissle.push_back(bulletKraidMissle1);
	this->bulletKraidMissle.push_back(bulletKraidMissle2);
	this->bulletKraidMissle.push_back(bulletKraidMissle3);

	BulletKraid *bulletKraid1 = new BulletKraid(spriteHandler, grid);
	BulletKraid *bulletKraid2 = new BulletKraid(spriteHandler, grid);
	BulletKraid *bulletKraid2 = new BulletKraid(spriteHandler, grid);
	this->bulletKraid.push_back(bulletKraid1);
	this->bulletKraid.push_back(bulletKraid2);

	BulletRidley *bulletRidley1 = new BulletRidley(spriteHandler, grid);
	BulletRidley *bulletRidley2 = new BulletRidley(spriteHandler, grid);
	BulletRidley *bulletRidley3 = new BulletRidley(spriteHandler, grid);
	BulletRidley *bulletRidley4 = new BulletRidley(spriteHandler, grid);
	this->bulletRidley.push_back(bulletRidley2);
	this->bulletRidley.push_back(bulletRidley4);
	this->bulletRidley.push_back(bulletRidley3);
	this->bulletRidley.push_back(bulletRidley4);

	maruMari = new MaruMari(spriteHandler, this);

	explodeEffect = new ExplodeEffect(spriteHandler, this, grid);
	bombWeapon = new BombWeapon(spriteHandler, this);

	loadEnemyPositions("Monster_Room1.txt");
}

World::~World()
{
	//delete(samus);
	//delete(maruMari);
	//delete(grid);
	//delete(metroid);
	//delete(explode);
	//delete(bomb);
}

void World::Update(float t)
{
	this->grid->setDeltaTime(t);
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
					enemy[i]->setSamusLocation(this->samus->getPosX(), this->samus->getPosY());
					enemy[i]->startMoving();
				}

			}
			else if (this->enemy[i]->isActive && !this->enemy[i]->isDeath) {
				enemy[i]->setSamusLocation(this->samus->getPosX(), this->samus->getPosY());
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

	for (int i = 0; i < bulletSkree.size(); i++) {
		if (bulletSkree[i]->isActive) {
			bulletSkree[i]->Update(t);
		}
	}

	//if (this->Kraid->isActive) {
		for (int i = 0; i < this->bulletKraidMissle.size(); i++) {
			if (bulletKraidMissle[i]->isActive) {
				bulletKraidMissle[i]->Update(t);
			}
			else {
				//bulletKraidMissle[i]->initBullet(this->Kraid->pos_x, this->Kraid->pos_y, this->Samus->pos_x);
			}
		}


		//for (int i = 0; i < this->bulletKraid.size(); i++) {
		//	if (bulletKraid[i]->isActive) {
		//		bulletKraid[i]->Update(t);
		//	}
		//else {
		//	//bulletKraidMissle[i]->initBullet(this->Kraid->pos_x, this->Kraid->pos_y, this->Samus->pos_x);

		//}
		//}
	//}


		//if (this->bulletRidley->isActive) {
			//for (int i = 0; i < this->bulletRidley.size(); i++) {
			//	if (bulletRidley[i]->isActive) {
			//		bulletRidley[i]->Update(t);
			//	}
		//else {
		//	bulletRidley[i]->initBullet(this->Kraid->pos_x, this->Kraid->pos_y, this->Samus->pos_x);
		//}
			//}
		//}

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

	for (int i = 0; i < bulletSkree.size(); i++) {
		if (bulletSkree[i]->isActive) {
			bulletSkree[i]->Render();
		}
	}

	//if (this->Kraid->isActive) {
	//for (int i = 0; i < this->bulletKraidMissle.size(); i++) {
	//	if (bulletKraidMissle[i]->isActive) {
	//		bulletKraidMissle[i]->Render();
	//	}
	//}

	//for (int i = 0; i < this->bulletKraid.size(); i++) {
	//	if (bulletKraid[i]->isActive) {
	//		bulletKraid[i]->Render();
	//	}
	//}
	//}


	//if (this->Ridley->isActive) {
		//for (int i = 0; i < this->bulletRidley.size(); i++) {
		//	if (bulletRidley[i]->isActive) {
		//		bulletRidley[i]->Render();
		//	}
		//}
	//}
}

void World::InitSprites(LPDIRECT3DDEVICE9 d3ddv)
{
	Texture * texture = new Texture();
	LPDIRECT3DTEXTURE9 samus_texture = texture->loadTexture(d3ddv, TEXTURE_GAME_CHARACTERS);
	if (samus_texture == NULL)
		trace(L"Unable to load PlayerTexture");
	samus->InitSprites(d3ddv, samus_texture);

	Texture * texture1 = new Texture();
	LPDIRECT3DTEXTURE9 maru_texture = texture1->loadTexture(d3ddv, ITEM_SPRITE_PATH);
	if (maru_texture == NULL)
		trace(L"Unable to load PlayerTexture");
	maruMari->InitSprites(d3ddv, maru_texture);

	// Bullet Texture
	LPDIRECT3DTEXTURE9 bulletTexture = texture1->loadTexture(d3ddv, SAMUS_BULLET_PATH);
	if (bulletTexture == NULL)
		trace(L"Unable to load BulletTexture");
	for (int i = 0; i < this->samusBullet.size(); i++) {
		this->samusBullet[i]->InitSprites(d3ddv, bulletTexture);
	}

	// Explode Texture
	Texture * textureExplode = new Texture();
	LPDIRECT3DTEXTURE9 explode_texture = textureExplode->loadTexture(d3ddv, EFFECT_SPRITE_PATH);
	if (explode_texture == NULL)
		trace(L"Unable to load Explode Texture");
	explodeEffect->InitSprites(d3ddv, explode_texture);

	// Bomb Texture
	Texture * textureBomb = new Texture();
	LPDIRECT3DTEXTURE9 bomb_texture = textureBomb->loadTexture(d3ddv, BOMB_TEXTURE);
	if (bomb_texture == NULL)
		trace(L"Unable to load Bomb Texture");
	bombWeapon->InitSprites(d3ddv, bomb_texture);
	
	// Enemy Texture
	LPDIRECT3DTEXTURE9 enemyTexture = texture1->loadTexture(d3ddv, ENEMY_SPRITE_PATH);
	//Enemy (Zoomer) Texture
	for (int i = 0; i < this->enemy.size(); i++) {
		this->enemy[i]->InitSprites(d3ddv, enemyTexture);
	}

	// Bomb Texture
	Texture * textureBulletSkree = new Texture();
	LPDIRECT3DTEXTURE9 bulletSkreeTexture = textureBulletSkree->loadTexture(d3ddv, SAMUS_BULLET_PATH);
	if (bomb_texture == NULL)
		trace(L"Unable to load Bomb Texture");
	for (int i = 0; i < this->bulletSkree.size(); i++) {
		this->bulletSkree[i]->InitSprites(d3ddv, bulletSkreeTexture);
	}

	for (int i = 0; i < this->bulletKraidMissle.size(); i++) {
		this->bulletKraidMissle[i]->InitSprites(d3ddv, bulletSkreeTexture);
	}

	for (int i = 0; i < this->bulletKraid.size(); i++) {
		this->bulletKraid[i]->InitSprites(d3ddv, bulletSkreeTexture);
	}

	for (int i = 0; i < this->bulletRidley.size(); i++) {
		this->bulletRidley[i]->InitSprites(d3ddv, bulletSkreeTexture);
	}
}

void World::loadEnemyPositions(string filePath) {
	ifstream file_txt(filePath);
	string str;
	vector<string> v;
	while (getline(file_txt, str)) {
		v = split(str, "\t");
		Enemy *monster;
		int value = atoi(v[0].c_str());
		switch (value)
		{
		case ZOOMER_YELLOW_CASE: {
			monster = new Zoomer(spriteHandler, this, ZOOMER_YELLOW);
			this->setDirectionForZoomer(monster, v[5]);
			monster->setEnemyStatefromString(v[6]);
			
			break;
		}
		case ZOOMER_PINK_CASE: {
			monster = new Zoomer(spriteHandler, this, ZOOMER_PINK);
			this->setDirectionForZoomer(monster, v[5]);
			monster->setEnemyStatefromString(v[6]);
			break;
		}
		case SKREE_CASE: {
			monster = new Skree(spriteHandler, this, SKREE);
			break;
		}
		case RIO_CASE: {

			break;
		}
		default:
			break;
		}

		monster->setPosX(stoi(v[3]));
		monster->setInitPosX(stoi(v[3]));
		monster->setPosY(stoi(v[4]));
		monster->setInitPosY(stoi(v[4]));
		monster->setActive(false);
		monster->setVelocityX(0);
		monster->setVelocityY(0);
		this->enemy.push_back(monster);
		v.clear();
		if(monster != NULL)
			this->grid->add(monster);
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