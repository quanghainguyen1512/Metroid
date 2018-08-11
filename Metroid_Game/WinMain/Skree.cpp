#include "Skree.h"
#include "World.h"

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
}
void Skree::Update(float t)
{
	//	grid->add(this);
	if (!isActive) return;
	if (this->isEnemyFreezed) {
		this->isEnemyFreezed = false;
		return;
	}

	this->setIsTopCollided(false);
	setIsBottomCollided(false);
	setIsRightCollided(false);
	setIsLeftCollided(false);
	setIsCollisionHandled(false);
	

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
			isDeath = true;

			for (int i = 0; i < manager->bulletSkree.size(); i++) {
				manager->bulletSkree[i]->isActive = true;
				manager->bulletSkree[i]->pos_x = this->pos_x;
				manager->bulletSkree[i]->pos_y = this->pos_y + 32;
			}		

			manager->bulletSkree[0]->bulletDirection = BULLET_RIGHT;
			manager->bulletSkree[1]->bulletDirection = BULLET_LEFT;
			manager->bulletSkree[2]->bulletDirection = BULLET_TOPRIGHT;
			manager->bulletSkree[3]->bulletDirection = BULLET_TOPLEFT;

			manager->bulletSkree[0]->setRange(this->pos_x + SKREE_BULLET_DISTANCE);
			manager->bulletSkree[2]->setRange(this->pos_x + SKREE_BULLET_DISTANCE);

			manager->bulletSkree[1]->setRange( this->pos_x - SKREE_BULLET_DISTANCE);
			manager->bulletSkree[3]->setRange(this->pos_x - SKREE_BULLET_DISTANCE);
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
}

void Skree::Render()
{
	spriteHandler->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
	if (isActive && !isDeath) {
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


void Skree::handleBullet(int bulletType)
{

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

void Skree::Destroy(float x, float y)
{
	if (this->health == 0)
	{
		//comment vì chưa add explodeEffect vào manager, ai merge thì bỏ comment nhe :v

		manager->explodeEffect->setTimeSurvive(EFFECT_TIME_SURVIVE);
		if (manager->explodeEffect->getTimeSurvive() > 0)
		{
			manager->explodeEffect->setActive(true);
			manager->explodeEffect->setPosX(x - 32);
			manager->explodeEffect->setPosY(y - 32);
		}
		this->isDeath = true;
		this->isEnemyFreezed = false;

		this->reset();
		GameObject* object = static_cast<GameObject*>(this);
		object->setActive(false);
		this->manager->grid->updateGrid(object, this->getPosX(), this->getPosY());
	}
}

void Skree::reset()
{
	this->pos_x = this->getInitPosX();
	this->pos_y = this->getInitPosY();
	//this->direction = this->getInitDirection();
	//this->state = this->getInitState();
}

void Skree::setIsLeftCollided(bool isLeft) {
	this->isLeftCollided = isLeft;
}

bool Skree::getIsLeftCollided() {
	return this->isLeftCollided;
}

void Skree::setIsRightCollided(bool isRight) {
	this->isRightCollided = isRight;
}

bool Skree::getIsRightCollided() {
	return this->isRightCollided;
}

void Skree::setIsTopCollided(bool isTop) {
	this->isTopCollided = isTop;
}

bool Skree::getIsTopCollided() {
	return isTopCollided;
}

void Skree::setIsBottomCollided(bool isBottom) {
	isBottomCollided = isBottom;
}

bool Skree::getIsBottomCollided() {
	return isBottomCollided;
}

void Skree::setIsCollisionHandled(bool isHandled) {
	isCollisionHandled = isHandled;
}

bool Skree::getIsCollisionHandled() {
	return isCollisionHandled;
}