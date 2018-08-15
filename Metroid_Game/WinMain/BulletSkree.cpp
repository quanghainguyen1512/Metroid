#include "BulletSkree.h"

BulletSkree::BulletSkree() {
	this->isActive = false;
	this->isRendered = false;
	this->setType(BULLET_SKREE);
}

BulletSkree::BulletSkree(LPD3DXSPRITE spriteHandler, Grid * grid)
{
	this->spriteHandler = spriteHandler;
	this->isActive = false;
	this->isRendered = false;
	pos_x = 0.0f;
	pos_y = 0.0f;
	this->setType(BULLET_SKREE);
	this->grid = grid;
	this->startX = 0.0f;
	this->startY = 0.0f;
	this->endX = 0.0f;
	this->endY = 0.0f;
	this->grid->add(this);
	this->width = 12;
	this->height = 14;
}

// isActive và isRendered khi nhận sự kiện bắn đạn sẽ = true, sự khác nhau là:
// isActive: Dùng để xác định đạn có được khởi tạo rồi hay chưa.
// isRendered: Dùng để xác định và tính toán khoản cách thời gian các viên đạn
// được bắn ra theo trình tự (ở đây là 3 viên đạn).

BulletSkree::~BulletSkree() {
	delete(this->sprite);
}

void BulletSkree::initBullet(float posX, float posY) {
	this->pos_x = posX;
	this->pos_y = posY;
}


void BulletSkree::Update(float t) {

	switch (bulletDirection) {
	case BULLET_RIGHT: {
		this->pos_x = this->pos_x + SKREE_BULLET_SPEED * t;
		break;
	}
	case BULLET_LEFT: {
		this->pos_x = this->pos_x - SKREE_BULLET_SPEED * t;
		break;
	}
	case BULLET_TOPRIGHT: {
		this->pos_x = this->pos_x + SKREE_BULLET_SPEED * t;
		this->pos_y = this->pos_y - SKREE_BULLET_SPEED * t;
		break;
	}
	case BULLET_TOPLEFT: {
		this->pos_x = this->pos_x - SKREE_BULLET_SPEED * t;
		this->pos_y = this->pos_y - SKREE_BULLET_SPEED * t;
		break;
	}
	}

	if ((this->bulletDirection == BULLET_RIGHT || this->bulletDirection == BULLET_TOPRIGHT) && this->pos_x > range) {
		this->isActive = false;
	}
	else if((this->bulletDirection == BULLET_LEFT || this->bulletDirection == BULLET_TOPLEFT) && this->pos_x < range) {
		this->isActive = false;
	}
}

void BulletSkree::Update(float t, float posX, float posY)
{

}


void BulletSkree::Render() {
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(pos_x, pos_y, 0);
	sprite->drawSprite(0, 0, WIDTH_BULLET, HEIGHT_BULLET, pos);
}

void BulletSkree::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture) {
	if (d3ddv == NULL) return;
	
	if (texture == NULL)
		trace(L"Unable to load BulletTexture");

	this->sprite = new Sprite(this->spriteHandler, texture, WIDTH_BULLET, HEIGHT_BULLET,1,1);
}

void BulletSkree::Reset(float posX, float posY)
{
}


void BulletSkree::setIsRendered(bool isRendered) {
	this->isRendered = isRendered;
}

bool BulletSkree::getIsRendered() {
	return this->isRendered;
}

void BulletSkree::setRange(float _range)
{
	range = _range;
}

float BulletSkree::getRange()
{
	return this->range;
}
