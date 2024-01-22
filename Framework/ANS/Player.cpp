#include "Framework.h"
#include "Player.h"

Player::Player(Vector3 position, Vector3 size, float rotate)
	:Rect(position, size, rotate)
{
}

Player::~Player()
{
}
