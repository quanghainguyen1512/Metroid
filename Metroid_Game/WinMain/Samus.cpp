#include "Samus.h"
#include "Game.h"
#include <vector>
#include "trace.h"
#include "Metroid.h"

void Samus::Render()
{
	// Nếu không active thì không render
	if (!isActive)
		return;
	else {
		D3DXVECTOR3 position;
		position.x = pos_x;
		position.y = pos_y;
		if (this->state == STAND_SHOOT_UP_LEFT || this->state == STAND_SHOOT_UP_RIGHT || this->state == RUN_SHOOT_UP_LEFT || this->state == RUN_SHOOT_UP_RIGHT) {
			position.y -= 10;
		}

		position.z = 0;

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND| D3DXSPRITE_OBJECTSPACE);

		switch (state)
		{
		case STAND_RIGHT:
			standRight->drawSprite(standRight->getWidth(), standRight->getHeight(), position);
			break;
		case STAND_LEFT:
			standLeft->drawSprite(standLeft->getWidth(), standLeft->getHeight(), position);
			break;
		case RUNNING_RIGHT:
			runRight->drawSprite(runRight->getWidth(), runRight->getHeight(), position);
			break;
		case RUNNING_LEFT:
			runLeft->drawSprite(runLeft->getWidth(), runLeft->getHeight(), position);
			break;
		case STAND_SHOOT_UP_LEFT:
			standShootL->drawSprite(standShootL->getWidth(), standShootL->getHeight(), position);
			break;
		case STAND_SHOOT_UP_RIGHT:
			standShootR->drawSprite(standShootR->getWidth(), standShootR->getHeight(), position);
			break;
		case MORPH_LEFT:
			morphLeft->drawSprite(morphLeft->getWidth(), morphLeft->getHeight(), position);
			break;
		case MORPH_RIGHT:
			morphRight->drawSprite(morphRight->getWidth(), morphRight->getHeight(), position);
			break;
		case RUN_SHOOTING_LEFT:
			runShootL->drawSprite(runShootL->getWidth(), runShootL->getHeight(), position);
			break;
		case RUN_SHOOTING_RIGHT:
			runShootR->drawSprite(runShootR->getWidth(), runShootR->getHeight(), position);
			break;
		case RUN_SHOOT_UP_LEFT:
			runShootUpL->drawSprite(runShootUpL->getWidth(), runShootUpL->getHeight(), position);
			break;
		case RUN_SHOOT_UP_RIGHT:
			runShootUpR->drawSprite(runShootUpR->getWidth(), runShootUpR->getHeight(), position);
			break;
		case JUMP_LEFT:
			jumpLeft->drawSprite(jumpLeft->getWidth(), jumpLeft->getHeight(), position);
			break;
		case JUMP_RIGHT:
			jumpRight->drawSprite(jumpRight->getWidth(), jumpRight->getHeight(), position);
			break;
		case TRANSFORM_BALL_LEFT:
			ballLeft->drawSprite(ballLeft->getWidth(), ballLeft->getHeight(), position);
			break;
		case TRANSFORM_BALL_RIGHT:
			ballRight->drawSprite(ballRight->getWidth(), ballRight->getHeight(), position);
			break;
		case JUMP_SHOOT_UP_LEFT:
			jumpShootL->drawSprite(jumpShootL->getWidth(), jumpShootL->getHeight(), position);
			break;
		case JUMP_SHOOT_UP_RIGHT:
			jumpShootR->drawSprite(jumpShootR->getWidth(), jumpShootR->getHeight(), position);
			break;
		}

		spriteHandler->End();
	}	
}

Samus::Samus()
{
	this->isActive = true;
	this->isBall = false;

	this->setType(SAMUS);

	this->height = 64;
	this->width = 32;

	this->previousUnit = NULL;
	this->nextUnit = NULL;

	gravity = FALLDOWN_VELOCITY_DECREASE;
	state = STAND_RIGHT;
}

void Samus::Destroy()
{
	//Ngưng active
	this->isActive = false;

	// TODO: Đưa Samus ra khỏi viewport
}

void Samus::collideEnemy()
{
	collideDistanceY = this->pos_y - collideHeight;
	if (getVelocityXLast() > 0) {		
		isCollideRight = true;
		collideDistanceX = this->pos_x - collideHeight * 2;
	}
	else {
		isCollideLeft = true;
		collideDistanceX = this->pos_x + collideHeight * 2;
	}
	isJumping = true;
	isFalling = false;
}

Samus::Samus(LPD3DXSPRITE spriteHandler, World * manager, Grid* grid) : Samus()
{
	this->grid = grid;
	
	this->spriteHandler = spriteHandler;
	this->manager = manager;
}

Samus::~Samus()
{
	delete(standRight);
	delete(standLeft);
	delete(runRight);
	delete(runLeft);
	delete(morphLeft);
	delete(morphRight);
	delete(standShootL);
	delete(standShootR);
	delete(runShootL);
	delete(runShootR);
	delete(runShootUpL);
	delete(runShootUpR);
	delete(ballLeft);
	delete(ballRight);
	delete(jumpShootR);
	delete(jumpShootL);
	delete(jumpRight);
	delete(jumpLeft);
}

void Samus::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;

	//Create instance of sprites
	standRight = new Sprite(spriteHandler, texture, STAND_RIGHT_PATH, WIDTH_SAMUS_STAND, HEIGHT_SAMUS_STAND, COUNT_SAMUS_STAND);
	standLeft = new Sprite(spriteHandler, texture, STAND_LEFT_PATH, WIDTH_SAMUS_STAND, HEIGHT_SAMUS_STAND, COUNT_SAMUS_STAND);
	runRight = new Sprite(spriteHandler, texture, RUNRIGHT_PATH, WIDTH_SAMUS_RUNRIGHT, HEIGHT_SAMUS_RUNRIGHT, COUNT_SAMUS_RUNRIGHT);
	runLeft = new Sprite(spriteHandler, texture, RUNLEFT_PATH, WIDTH_SAMUS_RUNLEFT, HEIGHT_SAMUS_RUNLEFT, COUNT_SAMUS_RUNLEFT);
	standShootL = new Sprite(spriteHandler, texture, STANDSHOOTUP_LEFT_PATH, WIDTH_SAMUS_STANDSHOOTUP, HEIGHT_SAMUS_STANDSHOOTUP, COUNT_SAMUS_STANDSHOOTUP);
	standShootR = new Sprite(spriteHandler, texture, STANDSHOOTUP_RIGHT_PATH, WIDTH_SAMUS_STANDSHOOTUP, HEIGHT_SAMUS_STANDSHOOTUP, COUNT_SAMUS_STANDSHOOTUP);
	morphLeft = new Sprite(spriteHandler, texture, MORPHLEFT_PATH, WIDTH_SAMUS_MORPHLEFT, HEIGHT_SAMUS_MORPHLEFT, COUNT_SAMUS_MORPHLEFT);
	morphRight = new Sprite(spriteHandler, texture, MORPHRIGHT_PATH, WIDTH_SAMUS_MORPHRIGHT, HEIGHT_SAMUS_MORPHRIGHT, COUNT_SAMUS_MORPHRIGHT);
	runShootL = new Sprite(spriteHandler, texture, RUNSHOOTleft_PATH, WIDTH_SAMUS_RUNSHOOTleft, HEIGHT_SAMUS_RUNSHOOTleft, COUNT_SAMUS_RUNSHOOTleft);
	runShootR = new Sprite(spriteHandler, texture, RUNSHOOTright_PATH, WIDTH_SAMUS_RUNSHOOTright, HEIGHT_SAMUS_RUNSHOOTright, COUNT_SAMUS_RUNSHOOTright);
	runShootUpL = new Sprite(spriteHandler, texture, RUN_SHOOTUP_left_PATH, WIDTH_SAMUS_RUN_SHOOTUP_left, HEIGHT_SAMUS_RUN_SHOOTUP_left, COUNT_SAMUS_RUN_SHOOTUP_left);
	runShootUpR = new Sprite(spriteHandler, texture, RUN_SHOOTUP_right_PATH, WIDTH_SAMUS_RUN_SHOOTUP_right, HEIGHT_SAMUS_RUN_SHOOTUP_right, COUNT_SAMUS_RUN_SHOOTUP_right);
	jumpLeft = new Sprite(spriteHandler, texture, JUMPLEFT_PATH, WIDTH_SAMUS_JUMP, HEIGHT_SAMUS_JUMP, COUNT_SAMUS_JUMP);
	jumpRight = new Sprite(spriteHandler, texture, JUMPRIGHT_PATH, WIDTH_SAMUS_JUMP, HEIGHT_SAMUS_JUMP, COUNT_SAMUS_JUMP);
	ballLeft = new Sprite(spriteHandler, texture, BALLLEFT_PATH, WIDTH_SAMUS_BALLLEFT, HEIGHT_SAMUS_BALLLEFT, COUNT_SAMUS_BALLLEFT);
	ballRight = new Sprite(spriteHandler, texture, BALLRIGHT_PATH, WIDTH_SAMUS_BALLRIGHT, HEIGHT_SAMUS_BALLRIGHT, COUNT_SAMUS_BALLRIGHT);
	jumpShootL = new Sprite(spriteHandler, texture, JUMPSHOOTleft_PATH, WIDTH_SAMUS_JUMPSHOOT, HEIGHT_SAMUS_JUMPSHOOT, COUNT_SAMUS_JUMPSHOOT);
	jumpShootR = new Sprite(spriteHandler, texture, JUMPSHOOTright_PATH, WIDTH_SAMUS_JUMPSHOOT, HEIGHT_SAMUS_JUMPSHOOT, COUNT_SAMUS_JUMPSHOOT);
}

void Samus::InitPostition()
{
	// TODO: This code will be edited soon
	/*pos_x = 992;	
	pos_y = 320;*/	
	this->pos_x = 1140;
	this->pos_y = 352;
	vx = 0;
	vx_last = 1.0f;
	vy = 0.0f;
}

SAMUS_STATE Samus::GetState()
{
	return state;
}

void Samus::SetState(SAMUS_STATE value)
{
	state = value;
}

bool Samus::isSamusJumping()
{
	return isJumping;
}

void Samus::ResetAllSprites()
{
	standRight->Reset();
	standLeft->Reset();
	runRight->Reset();
	runLeft->Reset();
	standShootL->Reset();
	standShootR->Reset();
	morphLeft->Reset();
	morphRight->Reset();
	runShootL->Reset();
	runShootR->Reset();
	runShootUpL->Reset();
	runShootUpR->Reset();
	jumpLeft->Reset();
	jumpRight->Reset();
	ballLeft->Reset();
	ballRight->Reset();
	jumpShootL->Reset();
	jumpShootR->Reset();

}

bool Samus::GetStateActive()
{
	return isActive;
}

void Samus::Reset(float x, float y)
{
	//manager->maruMari->Init(704, 186);
	// Cho samus active trở lại
	this->isActive = true;

	//Đặt lại vị trí
	this->pos_x = x;
	this->pos_y = y;
}

bool Samus::isSamusDeath()
{
	return isDeath;
}

// Update samus status
void Samus::Update(float t)
{
	if (checkpoint != 0) {
		pos_x = this->pos_x + checkpoint * t;
		pos_y = this->pos_y + vy * t;
	}
	else {
		pos_x = this->pos_x + vx * t;
		pos_y = this->pos_y + vy * t;
	}


	int oldRow = floor(this->pos_y / CELL_SIZE);
	int oldColumn = floor(this->pos_x / CELL_SIZE);

	this->grid->handleCell(this, oldRow, oldColumn);
	this->grid->updateGrid(this, this->pos_x, this->pos_y);

	//dang bi va cham vang ra, ben phai va ben trai
	if (isCollideRight) {
		if (pos_x > collideDistanceX) {
			vx = -SAMUS_SPEED;
			if (isJumping == true && isFalling == false) {
				if (pos_y > collideDistanceY) {
					vy = -100;
				}
				else {
					isJumping = false;
					isFalling = true;
				}				
			}
			else if (isJumping == false && isFalling == true) {
				if (pos_y < collideDistanceY + collideHeight) {
					vy = 100;
				}
				else {
					isJumping = false;
					isFalling = false;
				}
			}
		}
		else {
			isCollideRight = false;
		}
	}
	if (isCollideLeft) {
		if (pos_x < collideDistanceX) {
			vx = +SAMUS_SPEED;
			if (isJumping == true && isFalling == false) {
				if (pos_y > collideDistanceY) {
					vy = -100;
				}
				else {
					isJumping = false;
					isFalling = true;
				}
			}
			else if (isJumping == false && isFalling == true) {
				if (pos_y < collideDistanceY + collideHeight) {
					vy = 100;
				}
				else {
					isJumping = false;
					isFalling = false;
				}
			}
		}
		else {
			isCollideLeft = false;
		}
	}
	/*this->grid->showAllObject();
	float newPosX = pos_x + vx * t;
	float newPosY = pos_y + vy * t;

	int row = (int)floor(this->pos_y / CELL_SIZE);
	int column = (int)floor(this->pos_x / CELL_SIZE);

	if (!this->grid->handleCell(this, row, column)) {
		pos_x = newPosX;
		pos_y = newPosY;
	}

	this->grid->updateGrid(this, this->pos_x, this->pos_y);
*/
	//if (!this->grid->updateGrid(this, newPosX, newPosY)) {
	//	pos_x = newPosX;
	//	pos_y = newPosY;
	//}
	//pos_x = newPosX;
	//pos_y = newPosY;

	// Animate samus if he is running
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / ANIMATE_RATE)
	{
		switch (state)
		{
		case STAND_RIGHT:
			standRight->updateSprite();
			break;
		case STAND_LEFT:
			standLeft->updateSprite();
			break;
		case RUNNING_LEFT:
			runLeft->updateSprite();
			break;
		case RUNNING_RIGHT:
			runRight->updateSprite();
			break;
		case STAND_SHOOT_UP_LEFT:
			standShootL->updateSprite();
			break;
		case STAND_SHOOT_UP_RIGHT:
			standShootR->updateSprite();
			break;
		case MORPH_LEFT:
			morphLeft->updateSprite();
			break;
		case MORPH_RIGHT:
			morphRight->updateSprite();
			break;
		case RUN_SHOOTING_LEFT:
			runShootL->updateSprite();
			break;
		case RUN_SHOOTING_RIGHT:
			runShootR->updateSprite();
			break;
		case RUN_SHOOT_UP_LEFT:
			runShootUpL->updateSprite();
			break;
		case RUN_SHOOT_UP_RIGHT:
			runShootUpR->updateSprite();
			break;
		case JUMP_LEFT:
			jumpLeft->updateSprite();
			break;
		case JUMP_RIGHT:
			jumpRight->updateSprite();
			break;
		case TRANSFORM_BALL_LEFT:
			ballLeft->updateSprite();
			break;
		case TRANSFORM_BALL_RIGHT:
			ballRight->updateSprite();
			break;
		case JUMP_SHOOT_UP_LEFT:
			jumpShootL->updateSprite();
			break;
		case JUMP_SHOOT_UP_RIGHT:
			jumpShootR->updateSprite();
			break;
		}
		last_time = now;
	}
	
}
//----------------------------------------------------------

void Samus::setIsBall(bool isBall) {
	this->isBall = isBall;
}

bool Samus::getIsBall() {
	return this->isBall;
}

void Samus::setCanMorph(bool canMorph) {
	this->canMorph = canMorph;
}

bool Samus::getCanMorph() {
	return this->canMorph;
}