#pragma once
#include "GameObject.h"
class Item : public GameObject
{
protected:
	float time_survive;
	int number_gain;
	Sprite * item;
public:
	Item(LPD3DXSPRITE sprietHandler, World * manager);
	virtual ~Item();
	int getNumberGain();
	void setNumberGain(int num);
	void disappear();
	//============= OVERRIDE VIRTUAL METHOD =================
	virtual void InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	virtual void Update(float t);
	virtual void touchedBySamus(Samus* samus) = 0;
	//============= END OVERRIDE VIRTUAL METHOD =============
	void Init(float posX, float posY);
	void Render();
	void Destroy();
};

