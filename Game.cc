#include "Game.h"
#include "Map.h"
#include "Camera.h"
#include "Input.h"
#include <iostream>

Game::Game() {
	GameMap.Reload("Map.tmx");

	auto MainPlayer = new Player();
	OBJList.push_back(MainPlayer);
	Players.push_back(MainPlayer);
}

Game::~Game() {
	for (auto OBJ : OBJList)
		delete OBJ;
	for (auto Player : Players)
		delete Player;
}

Player* Game::getPlayer(int id) {
	if (id < Players.size())
		return Players[id];
	return nullptr;
}

void Game::Update() {
	UpdateObjects();

	//GameMap.Update();
}

void Game::UpdateObjects() {
	auto it = OBJList.begin();
	while (it != OBJList.end()) {
		if (!((*it)->Update()))
			it = OBJList.erase(it);
		else
			++it;
	}
}

std::pair<uint32_t,uint32_t> Game::getMapSize(const int z) const {
	return GameMap.getLevelSize(z);
}

std::pair<int,int> Game::getMapLevelsInterval() {
	return std::make_pair(GameMap.getMinLevel(), GameMap.getMaxLevel());
}
