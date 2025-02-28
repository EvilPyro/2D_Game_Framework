#include "Player.h"
#include <iostream>
#include "Engine.h"
#include <utility>
#include "InputComponent.h"
#include <cmath>

Player::Player(b2Body* Body) {
	this->Body = Body;
	Body->SetType(b2_dynamicBody);
	b2CircleShape Shape;
	Shape.m_radius = 14;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &Shape;
	fixtureDef.density = 1;
	Body->CreateFixture(&fixtureDef);
	//LoadPlayer();

	auto InputComponent = EngineUtils::getInputComponent();
	Bindings.push_back(InputComponent->InputBind(SDLK_w, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressW)));
	Bindings.push_back(InputComponent->InputBind(SDLK_a, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressA)));
	Bindings.push_back(InputComponent->InputBind(SDLK_s, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressS)));
	Bindings.push_back(InputComponent->InputBind(SDLK_d, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressD)));
	Bindings.push_back(InputComponent->InputBind(SDLK_e, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressE)));

	Bindings.push_back(InputComponent->InputBind(SDLK_DOWN, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressArrowDown)));
	Bindings.push_back(InputComponent->InputBind(SDLK_UP, fastdelegate::MakeDelegate(this, &Player::ON_KeyPressArrowUp)));

	auto texture = EngineUtils::getRenderComponent()->GetTexture("runner-export.png");
	SDL_Rect first = {0, 0, 128, 128};
	std::vector<float> v = {150, 100, 140, 150, 100, 140};
	Animations[WalkR].Construct(texture, first, 6, v);
	Animations[WalkR].SetResize(64, 0);
}



bool Player::Update() {
Movement();
	// Update Viewport with Player position
	auto Econf = EngineUtils::getConfiguration();
	auto MapSize = EngineUtils::getGame().lock()->getMapSize(std::get<2>(getPosition()));
	EngineUtils::getRenderComponent()->GetViewport()->Update(getPosition(), Econf.WsizeX, Econf.WsizeY, MapSize.first, MapSize.second);

	// TESTING:
	Animations[WalkR](getPosition(), getRotation(), 5);

	return true;
}

void Player::Movement() {
	b2Vec2 Speed = {0, 0};
	if (W_hold)
		Speed.y -= WalkSpeed;
	if (A_hold)
		Speed.x -= WalkSpeed;
	if (S_hold)
		Speed.y += WalkSpeed;
	if (D_hold)
		Speed.x += WalkSpeed;
	if (Speed.x || Speed.y) {
		float angleInRadians = std::atan2(Speed.y, Speed.x);
		Rotation Rot;
		Rot = (angleInRadians / M_PI) * 180.0 + 90;
		setRotation(Rot);
		// Speed magnitude correction
		float m = std::sqrt(Speed.x*Speed.x + Speed.y*Speed.y);
		Speed.x = std::abs(Speed.x) * Speed.x / m;
		Speed.y = std::abs(Speed.y) * Speed.y / m;
	}
	Body->SetLinearVelocity(Speed);
}

void Player::ON_KeyPressW(Uint8 state) {
	W_hold = (state == SDL_PRESSED);
}
void Player::ON_KeyPressA(Uint8 state) {
	A_hold = (state == SDL_PRESSED);
}
void Player::ON_KeyPressS(Uint8 state) {
	S_hold = (state == SDL_PRESSED);
}
void Player::ON_KeyPressD(Uint8 state) {
	D_hold = (state == SDL_PRESSED);
}
void Player::ON_KeyPressE(Uint8 state) {
	if (state == SDL_PRESSED) {
		Object::create("DebugEnemy", getPosition());
	}
}
void Player::ON_KeyPressArrowDown(Uint8 state) {
	auto LevelIDinterval = EngineUtils::getGame().lock()->getMapLevelsInterval();
	auto P = getPosition();
	if (std::get<2>(P) > LevelIDinterval.first){
		std::get<2>(P) -= 1;
		setPosition(P);
	}
}
void Player::ON_KeyPressArrowUp(Uint8 state) {
	auto LevelIDinterval = EngineUtils::getGame().lock()->getMapLevelsInterval();
	auto P = getPosition();
	if (std::get<2>(P) < LevelIDinterval.second) {
		std::get<2>(P) += 1;
		setPosition(P);
	}
}
