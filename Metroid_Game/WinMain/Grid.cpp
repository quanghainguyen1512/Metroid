﻿#include "Grid.h"
#include "Samus.h"
// Lưu vào mảng 2 chiều
// Height khi quy đổi ra sẽ là row -> pos_y tương ứng với row
// Width khi quy đổi ra sẽ là column -> pos_x tương ứng column

Grid::Grid() {
	numOfRow = DEFINE_ROW;
	numOfColumn = DEFINE_COLUMN;
	for (int i = 0; i < numOfRow; i++)
	{
		for (int j = 0; j < numOfColumn; j++)
			cells[i][j] = NULL;
	}
	this->deltaTime = 0.0f;
}

Grid::Grid(int height, int width) {
	this->numOfRow = (int)ceil(height * BRICK_SIZE / CELL_SIZE);
	this->numOfColumn = (int)ceil(width * BRICK_SIZE / CELL_SIZE);

	for (int i = 0; i < numOfRow; i++)
	{
		for (int j = 0; j < numOfColumn; j++)
			cells[i][j] = NULL;
	}
	this->deltaTime = 0.0f;
}

Grid::~Grid() {
	
}

// Cái này là dùng danh sách liên kết đôi để lưu trữ và truy xuất object
// Nếu mà mình xác định vị trí object thuộc cell nào rồi thì mình đưa nó vào đầu danh sách liên kết đôi đó
// Ở đây 1 cell là 1 danh sách liên kết đôi
// Giải thuật ở dưới là thêm vào đầu dslk đôi
void Grid::add(GameObject* object) {
	// Lưu trữ lại giá trị cũ của object sau mỗi lần update
	object->setlastPosX(object->getPosX());
	object->setlastPosY(object->getPosY());

	// Xác định object đang nằm ở grid nào
	int column = floor(object->getPosX() / CELL_SIZE); // trừ đi 1 do mảng bắt đầu từ 0
	int row = floor(object->getPosY() / CELL_SIZE);


	// Thêm object vào đầu của list
	object->previousUnit = NULL;
	object->nextUnit = cells[row][column];
	cells[row][column] = object;

	if (object->nextUnit != NULL) {
		object->nextUnit->previousUnit = object;
	}
}

void Grid::resetGrid(int width, int height) {
	this->numOfRow = (int)ceil(height * BRICK_SIZE / CELL_SIZE);
	this->numOfColumn = (int)ceil(width * BRICK_SIZE / CELL_SIZE);

	for (int i = 0; i < numOfRow; i++)
	{
		for (int j = 0; j < numOfColumn; j++)
			cells[i][j] = NULL;
	}
	this->deltaTime = 0.0f;
}

// Dùng để xét cái ô cell hiện tại, như là va chạm của object mình đang xét với các object còn lại
// Kế bên đó là xét với các cell lân cận
// Theo người ta nói các cell càn xét thêm là:
//		1 ô trên,
//		1 ô trái trên
//		1 ô trái
//		1 ô trái dưới
// Ở đây ta cho vào vòng lặp là xét tất cả các object với nhau
bool Grid::handleCell(GameObject* object, int row, int column) {
	bool isCollision = false;
	GameObject *cell = cells[row][column];
	if (object != NULL) {
		if ((object->getType() != BRICK || object->getType() != ITEM) && object->isActive != false) {
			// Đầu tiên là xét trong chính cell của nó trước
			if (this->handleObject(object, cell))
				isCollision = true;

			// Còn đây là xét với các cell kế bên
			if (row > 0 && column > 0)
				if (this->handleObject(object, cells[row - 1][column - 1])) // trai tren
					isCollision = true;
			if (row > 0)
				if (this->handleObject(object, cells[row - 1][column])) // phia tren
					isCollision = true;
			if (column > 0)
				if (this->handleObject(object, cells[row][column - 1])) // phia trai
					isCollision = true;
			if (column > 0 && row < numOfRow - 1)
				if (this->handleObject(object, cells[row - 1][column + 1])) // trai duoi
					isCollision = true;
		}
	}
	return isCollision;
}

// Dùng để xét giữa object đang xét với các object còn lại trong cell hoặc cell lân cận
// Nếu mà khoảng cách giữa object đang xét với các object khác nhỏ hơn khoảng cách có thể va chạm
// Lúc đó sẽ xét va chạm
bool Grid::handleObject(GameObject *object, GameObject* otherObject) {
	bool isCollision = false;
	while (otherObject != NULL) {
		if (object != otherObject) {
			// Mình phải tính va chạm là từ khoảng cách giữa 2 điểm từ tâm của nó
			int x1 = (int)((object->pos_x + object->width) / 2);
			int y1 = (int)((object->pos_y + object->height) / 2);
			D3DXVECTOR2 objectPos(x1, y1);

			int x2 = (int)((otherObject->pos_x + otherObject->width) / 2);
			int y2 = (int)((otherObject->pos_y + otherObject->height) / 2);
			D3DXVECTOR2 otherPos(x2, y2);
			if (Math::distance(objectPos, otherPos) < 50) {
				if (handleCollision(object, otherObject))
					isCollision = true;
			}
		}
		otherObject = otherObject->nextUnit;
	}
	return isCollision;
}

// Xét va chạm và cập nhật tình trạng của 2 object
bool Grid::handleCollision(GameObject *object, GameObject *otherObject) {
	COLLISION_DIRECTION collisionDirection = NONE;
	float collisionTime = object->sweptAABB(otherObject, collisionDirection, this->getDeltaTime());
	
	if (collisionDirection != NONE) {
		if (object->getType() == SAMUS) {
			this->handleSamus(object, otherObject, collisionDirection, collisionTime);
		}
		return true;
	}
	else {
		return false;
	}
}

void Grid::handleSamus(GameObject* object, GameObject* otherObject, COLLISION_DIRECTION collisionDirection, float collisionTime) {
	Samus* samus = dynamic_cast<Samus*>(object);
	if (collisionDirection == LEFT) {
		if (samus->vx < 0) {
			samus->SetState(STAND_LEFT);
		}
	}

	object->pos_x += object->vx * collisionTime*this->getDeltaTime();
	object->pos_y += object->vy * collisionTime*this->getDeltaTime();
}

bool Grid::updateGrid(GameObject* object, float newPosX, float newPosY) {
	// Kiểm tra xem nó có thay đổi cell hay không
	int oldRow = floor(object->getlastPosY() / CELL_SIZE);
	int oldColumn = floor(object->getlastPosX() / CELL_SIZE);

	int newRow = floor(newPosY / CELL_SIZE);
	int newColumn = floor(newPosX / CELL_SIZE);

	// Nếu không thay đổi cell thì thoát ra
	if (oldRow == newRow && oldColumn == newColumn) {
		return this->handleCell(object, oldRow, oldColumn);
	}

	// Xóa object ra khỏi cell hiện tại và cập nhật và cell mới
	if (object->previousUnit != NULL)
		object->previousUnit->nextUnit = object->nextUnit;
	if (object->nextUnit != NULL)
		object->nextUnit->previousUnit = object->previousUnit;

	// Nếu object đang là đứng đầu
	if (cells[oldRow][oldColumn] == object)
		cells[oldRow][oldColumn] = object->nextUnit;

	bool isCollision = false;
	isCollision = this->handleCell(object, oldRow, oldColumn);

	this->add(object);

	// Cập nhật lại vị trí last Post của object
	object->setlastPosX(object->getPosX());
	object->setlastPosY(object->getPosY());
	return isCollision;
}

void Grid::setDeltaTime(float deltaTime) {
	this->deltaTime = deltaTime;
}

float Grid::getDeltaTime() {
	return this->deltaTime;
}