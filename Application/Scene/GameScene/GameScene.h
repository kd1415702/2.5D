#pragma once

#include"../BaseScene/BaseScene.h"

class Player;
class Info;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene()override {}

private:

	void Event() override;
	void Init()  override;

	//カメラ座標
	Math::Vector3 m_CamPos;


	//プレイヤー
	std::shared_ptr<Player> m_Player = nullptr;
	std::shared_ptr<Player> m_Player2 = nullptr;

	std::shared_ptr<Info> m_Info = nullptr;

	int m_GroundCnt;
};
