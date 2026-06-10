#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Game/Player/Player.h"
#include"../../Object/Game/Ground/Ground.h"
#include"../../Object/Game/Coin/Coin.h"
#include"../../Object/Game/Ui/Ui.h"
#include"../../Info/Info.h"
#include"../../Object/Game/Rock/Rock.h"

void GameScene::Event()
{
	//デバッグ情報
	KdDebugGUI::Instance().ClearLog();
	//KdDebugGUI::Instance().AddLog(U8("走った距離 : %d"), Info::Instance().GetRunDistance());
	//KdDebugGUI::Instance().AddLog(U8("現在コイン : %d"), Info::Instance().GetCoin());
	KdDebugGUI::Instance().AddLog(U8("オブジェクト数 : %d"), (int)m_objList.size());




	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::TITLE
		);
	}


	//自機ジャンプ処理
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_Player->Jump();
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_Player2->Jump();
	}
	
	//自機ローリング処理
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		m_Player->Rowling();
	}

	if (GetAsyncKeyState('X') & 0x8000)
	{
		m_Player2->Rowling();
	}



	m_CamPos = { 3,6,-6 };

	//岩生成
	std::shared_ptr<Rock> rock;
	if (rand() % 150 == 1)
	{
		rock = std::make_shared<Rock>();
		rock->Init();
		rock->SetBorder(m_CamPos.x);
		rock->SetPos({ m_Player->GetPos().x + 30.0f,0.2f,0.0f});
		m_objList.push_back(rock);
	}

	std::shared_ptr<Ground> ground;
	m_GroundCnt++;
	if (m_GroundCnt >= 80)
	{
		for (float z : { 0.0f, 5.0f })
		{
			ground = std::make_shared<Ground>();
			ground->Init();
			ground->SetPos({ m_Player->GetPos().x + 20, 0.0f, z});
			m_objList.push_back(ground);
		}


		m_GroundCnt = 0;
	}


	Math::Matrix trans = Math::Matrix::CreateTranslation(m_CamPos.x + m_Player->GetPos().x,m_CamPos.y,m_CamPos.z);

	Math::Matrix rotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(40.0f));

	Math::Matrix world = rotationX * trans;

	m_camera->SetCameraMatrix(world);
}

void GameScene::Init()
{
	//アンビエントライト(環境光)										RGBA		
	//KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 1.00f, 0.57f, 0.00f,1.0 });

	//KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0,-1,0.1 }, { 1.0f,0.5f,0 });

	//カメラ用意
	m_camera = std::make_unique<KdCamera>();
	m_camera->SetProjectionMatrix(60);

	//プレイヤー初期化
	m_Player = std::make_shared<Player>();
	m_Player->Init();
	m_objList.push_back(m_Player);

	//プレイヤー2初期化
	m_Player2 = std::make_shared<Player>();
	m_Player2->Init();
	m_Player2->SetPos({ -32.0f,1.0f,5.0f });
	m_objList.push_back(m_Player2);


	//地形初期化
	std::shared_ptr<Ground> ground;

	for (int i = 0; i < 10; ++i)
	{
		ground = std::make_shared<Ground>();
		ground->Init();
		ground->SetPos({ (float)i * 4.0f - 40,0,0 });
		ground->SetTarget(m_Player);
		m_objList.push_back(ground);
	}


	//地形2初期化
	for (int i = 0; i < 10; ++i)
	{	
		ground = std::make_shared<Ground>();
		ground->Init();
		ground->SetPos({ (float)i * 4.0f - 40,0,5.0f });
		ground->SetTarget(m_Player);
		m_objList.push_back(ground);
	}

	//コイン
	std::shared_ptr<Coin> coin;
	for (int i = 0; i < 5; ++i)
	{
		coin = std::make_shared<Coin>();
		coin->SetPos({ -20.0f + (i * 5),1.0f,0.0f });
		coin->Init();
		m_objList.push_back(coin);
	}

	//奥側のコイン
	for (int i = 0; i < 5; ++i)
	{
		coin = std::make_shared<Coin>();
		coin->SetPos({ -20.0f + (i * 5),1.0f,5.0f });
		coin->Init();
		m_objList.push_back(coin);
	}




	//Ui初期化
	std::shared_ptr<Ui> ui;
	ui = std::make_shared <Ui>();
	ui->Init();
	m_objList.push_back(ui);

	//Info
	m_Info = std::make_shared<Info>();
	m_Info->Init();

	//グラウンド生成カウンター
	m_GroundCnt = 0;
}
