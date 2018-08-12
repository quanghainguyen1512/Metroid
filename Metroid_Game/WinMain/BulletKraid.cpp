#include "BulletKraid.h"

BulletKraid::BulletKraid() {
	this->isActive = false;
	this->isRendered = false;
	this->setType(BULLET_KRAID);
}

BulletKraid::BulletKraid(LPD3DXSPRITE spriteHandler, Grid * grid)
{
	this->spriteHandler = spriteHandler;
	this->isActive = false;
	this->isRendered = false;
	pos_x = 0.0f;
	pos_y = 0.0f;
	this->setType(BULLET_KRAID);
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

BulletKraid::~BulletKraid() {
	delete(this->sprite);
}

void BulletKraid::initBullet(float _Kraid_posX, float _Kraid_posY, float _Samus_posX) {
	this->pos_x = _Kraid_posX;
	this->pos_y = _Kraid_posY;
	if (Kraid_posX - _Samus_posX < 0) {
		bulletDirection = BULLET_RIGHT;
		collideDistanceX = _Kraid_posX + collideHeight * 4;
	}
		
	else {
		bulletDirection = BULLET_LEFT;
		collideDistanceX = _Kraid_posX - collideHeight * 4;
	}
	collideDistanceY = Kraid_posX - ENEMY_BULLET_DISTANCE;
	isUp = true;
	isDown = false;
}


void BulletKraid::Update(float t) {
	if (bulletDirection == BULLET_RIGHT) {
		if (pos_x < collideDistanceX) {
			if (isUp && !isDown) {
				vx = SKREE_BULLET_SPEED;
				if (pos_y > collideDistanceY) {
					vy = -SKREE_BULLET_SPEED;
				}
				else {
					isUp = false;
					isDown = true;
				}
			}
			else if (!isUp && isDown) {
				vx = SKREE_BULLET_SPEED;
				if (pos_y < collideDistanceY + collideHeight) {
					vy = SKREE_BULLET_SPEED;
				}
			}
		}
		else {
			vy = 0;
			isUp = false;
			isDown = false;
		}	
	}
	else if (bulletDirection == BULLET_LEFT) {
		if (pos_x > collideDistanceX) {
			if (isUp && !isDown) {
				vx = -SKREE_BULLET_SPEED;
				if (pos_y > collideDistanceY) {
					vy = -SKREE_BULLET_SPEED;
				}
				else {
					isUp = false;
					isDown = true;
				}
			}
			else if (!isUp && isDown) {
				vx = SKREE_BULLET_SPEED;
				if (pos_y < collideDistanceY + collideHeight) {
					vy = SKREE_BULLET_SPEED;
				}
			}
		}
		else {
			vy = 0;
			isUp = false;
			isDown = false;
		}
	}

	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);

	this->pos_x += vx * t;
	this->pos_y += vy * t;

	this->grid->handleCell(this, row, column);
	this->grid->updateGrid(this, this->pos_x, this->pos_y);

	if (isCollided) {
		Reset(Kraid_posX, Kraid_posY);
	}
}

void BulletKraid::Update(float t, float posX, float posY)
{

}


void BulletKraid::Render() {
	D3DXVECTOR3 position;
	position.x = pos_x;
	position.y = pos_y;
	position.z = 0;
	D3DXVECTOR3 pos = D3DXVECTOR3(pos_x, pos_y, 0);
	sprite->drawSprite(0, 0, WIDTH_BULLET, HEIGHT_BULLET, pos);
}

void BulletKraid::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture) {
	if (d3ddv == NULL) return;

	if (texture == NULL)
		trace(L"Unable to load BulletTexture");

	this->sprite = new Sprite(this->spriteHandler, texture, BULLET_SKREE_PATH, WIDTH_BULLET, HEIGHT_BULLET, 1);
}

void BulletKraid::Reset(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isCollided = false;
	this->isUp = false;
	this->isDown = false;
}


void BulletKraid::setIsRendered(bool isRendered) {
	this->isRendered = isRendered;
}

bool BulletKraid::getIsRendered() {
	return this->isRendered;
}
