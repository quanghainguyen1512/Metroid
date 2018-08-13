#include "Skree.h"
#include "World.h"
#include "Define.h"

Skree::Skree()
{
}

Skree::Skree(LPD3DXSPRITE spriteHandler, World * manager, OBJECT_TYPE enemy_type) : Enemy(spriteHandler, manager)
{
	this->setType(enemy_type);
	this->isActive = false;
	this->width = SKREE_WIDTH;
	this->height = SKREE_HEIGHT;
	this->grid = manager->grid;
	//Set animate rate ban đầu
	animate_rate = SKREE_STANDARD_ANIMATE_RATE;
	setState(ON_HANGING);

	Bullet* bullet1 = new Bullet(spriteHandler);
	Bullet* bullet2 = new Bullet(spriteHandler);
	Bullet* bullet3 = new Bullet(spriteHandler);
	Bullet* bullet4 = new Bullet(spriteHandler);

	skreeBullet.push_back(bullet1);
	skreeBullet.push_back(bullet2);
	skreeBullet.push_back(bullet3);
	skreeBullet.push_back(bullet4);
}

Skree::~Skree()
{
	delete(skree);
}

void Skree::setState(SKREE_STATE _state)
{
	state = _state;
}

SKREE_STATE Skree::getState()
{
	return state;
}

void Skree::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;
	//Create sprite handler
	HRESULT result = D3DXCreateSprite(d3ddv, &spriteHandler);
	if (result != D3D_OK) return;

	this->texture = texture;
	if (texture == NULL)
		trace(L"Unable to load skreeTexture");

	// Khởi tạo sprite
	skree = new Sprite(spriteHandler, texture, SKREE_PATH, SKREE_WIDTH, SKREE_HEIGHT, SKREE_COUNT);

	Texture * texture1 = new Texture();
	// Bullet Texture
	LPDIRECT3DTEXTURE9 bulletTexture = texture1->loadTexture(d3ddv, SAMUS_BULLET_PATH);
	if (bulletTexture == NULL)
		trace(L"Unable to load BulletTexture");
	for (int i = 0; i < this->skreeBullet.size(); i++) {
		this->skreeBullet[i]->InitSprites(d3ddv, bulletTexture);
	}
	
	Texture * texture2 = new Texture();
	LPDIRECT3DTEXTURE9 explosionTexture = texture2->loadTexture(d3ddv, EXPLOSION);
	if (explosionTexture == NULL)
		trace(L"Unable to load explosion texture");
	explosion = new Sprite(spriteHandler, explosionTexture, EXPLOSION_PATH, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, EXPLOSION_COUNT);
}
void Skree::Update(float t)
{
	//	grid->add(this);
	if (!isActive) return;

	

	if (getState() != LANDED && getState() != SHOT) {
		//tinh khoang cach voi samus bang dinh luat Pytago
		float rs = sqrt(((abs)(pos_x - samus_PosX)) * ((abs)(pos_x - samus_PosX)) + ((abs)(pos_y - samus_PosY) * (abs)(pos_y - samus_PosY)));
		
		if (rs < SKREE_DISTANCE_TO_SAMUS && getState() != LANDED) {
			animate_rate = SKREE_BOOST_ANIMATE_RATE;
			setState(ON_FALLING);
			setActive(true);
			vy = SKREE_SPEED;
			if (samus_PosX < pos_x)
				vx = -SKREE_SPEED;
			else if (samus_PosX > pos_x)
				vx = SKREE_SPEED;
			else
				vx = 0;
		}

		pos_x = this->pos_x + vx * t;
		pos_y = this->pos_y + vy * t;

		int oldRow = floor(this->pos_y / CELL_SIZE);
		int oldColumn = floor(this->pos_x / CELL_SIZE);

		this->grid->handleCell(this, oldRow, oldColumn);
		this->grid->updateGrid(this, this->pos_x, this->pos_y);
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / animate_rate)
		{
			skree->updateSprite();
			last_time = now;
		}
	}
	else if (getState() == LANDED) {
		liveTime += t*75;
		if (liveTime > SKREE_LIVE_TIME) {
			for (int i = 0; i < skreeBullet.size(); i++) {
				skreeBullet[i]->isActive = true;
				skreeBullet[i]->pos_x = this->pos_x;
				skreeBullet[i]->pos_y = this->pos_y + 32;
			}
			range = this->pos_x + SKREE_BULLET_DISTANCE;
			setState(SHOT);
		}
		else {
			DWORD now = GetTickCount();
			if (now - last_time > 1000 / animate_rate)
			{
				skree->updateSprite();
				last_time = now;
			}
		}
	}
	else if (getState() == SHOT){
		
		skreeBullet[0]->pos_x = skreeBullet[0]->getPosX() - SKREE_BULLET_SPEED * t;

		skreeBullet[1]->pos_x = skreeBullet[1]->getPosX() - SKREE_BULLET_SPEED * t;
		skreeBullet[1]->pos_y = skreeBullet[1]->getPosY() - SKREE_BULLET_SPEED * t;

		skreeBullet[2]->pos_x = skreeBullet[2]->getPosX() + SKREE_BULLET_SPEED * t;
		skreeBullet[2]->pos_y = skreeBullet[2]->getPosY() - SKREE_BULLET_SPEED * t;

		skreeBullet[3]->pos_x = skreeBullet[3]->getPosX() + SKREE_BULLET_SPEED * t;

		if (skreeBullet[3]->pos_x > range) {
			isDeath = true;
			isActive = false;
			setState(EXPLOSION_STATE);
		}
	}
}

void Skree::Render()
{
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	if (getState() == EXPLOSION_STATE) {
		D3DXVECTOR3 position;
		position.x = pos_x;
		position.y = pos_y;
		position.z = 0;
		
		explosion->drawSprite(explosion->getWidth(), explosion->getHeight(), position);

		setState(KILLED);
	}
	else if (isActive && !isDeath) {
		if (getState() != SHOT) {
			D3DXVECTOR3 position;
			position.x = pos_x;
			position.y = pos_y;
			position.z = 0;

			// Nếu không active thì không render
			if (!isActive)
				return;
			skree->drawSprite(skree->getWidth(), skree->getHeight(), position);
		}
		else if (getState() == SHOT) {
			for (int i = 0; i < skreeBullet.size(); i++) {
				D3DXVECTOR3 position;
				position.x = skreeBullet[i]->pos_x;
				position.y = skreeBullet[i]->pos_y;
				position.z = 0;
				D3DXVECTOR3 pos = D3DXVECTOR3(skreeBullet[i]->pos_x, skreeBullet[i]->pos_y, 0);
				skreeBullet[i]->bulletSprite->drawSprite(0, 0, WIDTH_BULLET, HEIGHT_BULLET, pos);
			}
		}
	}
	spriteHandler->End();
}

void Skree::setEnemyStatefromString(string _state)
{

}

void Skree::startMoving()
{
}

void Skree::setSamusLocation(int _posX, int _posY)
{
	samus_PosX = _posX;
	samus_PosY = _posY;
}

void Skree::startMovingBySamus(int _posX, int _posY)
{
	samus_PosX = _posX;
	samus_PosY = _posY;
}

void Skree::handleBullet(int bulletType)
{
	switch (bulletType) {
	case 1: {
		health -= BULLET_DAMGE;
		break;
	}
	}
}


void Skree::Destroy()
{
	//// Effect explosion

	//// Destroy
	//vx = 0;

	//manager->explsEffect->Init(this->pos_x, this->pos_y);	 // Xảy ra lỗi khi giết những mục tiêu to (Ridley, Mother Brain)
	//														 // Drop item after destroyed
	//int random;

	///* initialize random seed: */
	//srand(time(NULL));

	///* generate secret number between 1 and 10: */
	//random = rand() % 10 + 1;

	//if (random == 1 || random == 5)
	//	manager->energyItem->Init(this->pos_x, this->pos_y);
	//else if (random == 7 || random == 9)
	//	manager->missileItem->Init(this->pos_x, this->pos_y);
	//Enemy::Destroy();
}