#include "BulletRidley.h"

BulletRidley::BulletRidley() {
	this->isActive = false;
	this->isRendered = false;
	this->setType(BULLET_KRAID);
}

BulletRidley::BulletRidley(LPD3DXSPRITE spriteHandler, Grid * grid)
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

BulletRidley::~BulletRidley() {
	delete(this->sprite);
}

void BulletRidley::initBullet(float _Kraid_posX, float _Kraid_posY, float _Samus_posX) {
	this->pos_x = _Kraid_posX;
	this->pos_y = _Kraid_posY;
	if (_Kraid_posX - _Samus_posX < 0) {
		bulletDirection = BULLET_RIGHT;
	}
	else {
		bulletDirection = BULLET_LEFT;
	}
	collideDistanceY = _Kraid_posY - 40;
	isUp = true;
	isDown = false;
	isActive = true;
	liveTime = rand() % 50 + 1;
	speed = rand() % 30 + 50;
}


void BulletRidley::Update(float t) {
	liveTime += t * 75;
	if (liveTime > 100) {
		if (isWaiting == false) {
			isWaiting = true;
			this->pos_x = Ridley_posX;
			this->pos_y = Ridley_posY;
		}
		if (bulletDirection == BULLET_RIGHT) {
			vx = speed;
			if (isUp && !isDown) {
				if (pos_y > collideDistanceY) {
					vy = -SKREE_BULLET_SPEED;
				}
				else {
					isUp = false;
					isDown = true;
				}
			}
			else if (!isUp && isDown) {
				if (pos_y < collideDistanceY + collideHeight + 400) {
					vy = SKREE_BULLET_SPEED;
				}
				else {
					vy = 0;
					isUp = false;
					isDown = false;
					isActive = false;
					isWaiting = false;
				}
			}
		}
		else if (bulletDirection == BULLET_LEFT) {
			vx = -speed;
			if (isUp && !isDown) {
				if (pos_y > collideDistanceY) {
					vy = -SKREE_BULLET_SPEED;
				}
				else {
					isUp = false;
					isDown = true;
				}
			}
			else if (!isUp && isDown) {
				if (pos_y < collideDistanceY + collideHeight + 400) {
					vy = SKREE_BULLET_SPEED;
				}
				else {
					vy = 0;
					isUp = false;
					isDown = false;
					isActive = false;
					isWaiting = false;
				}
			}

		}

		int row = (int)floor(this->pos_y / CELL_SIZE);
		int column = (int)floor(this->pos_x / CELL_SIZE);

		this->pos_x += vx * t;
		this->pos_y += vy * t;

		//this->grid->handleCell(this, row, column);
		//this->grid->updateGrid(this, this->pos_x, this->pos_y);

		//if (isCollided) {
		//	isActive= false;
		//}
	}
}

void BulletRidley::Update(float t, float posX, float posY)
{

}


void BulletRidley::Render() {
	if (liveTime > 100) {
		D3DXVECTOR3 position;
		position.x = pos_x;
		position.y = pos_y;
		position.z = 0;
		D3DXVECTOR3 pos = D3DXVECTOR3(pos_x, pos_y, 0);
		sprite->drawSprite(0, 0, WIDTH_BULLET, HEIGHT_BULLET, pos);
	}
}

void BulletRidley::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture) {
	if (d3ddv == NULL) return;

	if (texture == NULL)
		trace(L"Unable to load BulletTexture");

	this->sprite = new Sprite(this->spriteHandler, texture, SAMUS_BULLET_PATH, WIDTH_BULLET, HEIGHT_BULLET, 1);
}

void BulletRidley::Reset(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isCollided = false;
	this->isUp = false;
	this->isDown = false;
}


void BulletRidley::setIsRendered(bool isRendered) {
	this->isRendered = isRendered;
}

bool BulletRidley::getIsRendered() {
	return this->isRendered;
}
