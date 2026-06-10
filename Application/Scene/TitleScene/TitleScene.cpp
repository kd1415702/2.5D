#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../Object/Title/TitleObject.h"
#include"../../../Application/main.h"
#include"../../Object/Game/Ground/Ground.h"
#include"../../Object/Game/Rock/Rock.h"
void TitleScene::Event()
{
	
	//デバッグ
	KdDebugGUI::Instance().ClearLog();
	KdDebugGUI::Instance().AddLog(U8("オブジェクト数 : %d"), (int)m_objList.size());


	//現在のタイトルタイプによって処理を変える=======
	switch (m_TitleType)
	{
		//ゲームスタートにカーソルがある場合
	case GAMESTART:
	{

		//↓を押した時
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			StartFlg = false;
		}
		else
		{
			if (!StartFlg)
			{
				//ランキングへカーソルが移動
				m_TitleObj->SetArrowPos({ m_TitleObj->GetRankingPos() });
				RankingFlg = true;
				m_TitleType = RANKING;
			}
		}

		//Enterを押した時
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			//ゲームシーンへ移動
			SceneManager::Instance().SetNextScene
			(
				SceneManager::SceneType::GAME
			);
		}


		break;
	}
	case RANKING:
	{
		//↓を押した時
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			RankingFlg = false;
			DownFlg = true;
		}
		else
		{
			if (!RankingFlg && DownFlg == true)
			{

				//カーソルがゲーム終了へ移動
				m_TitleType = GAMEEND;
				m_TitleObj->SetArrowPos({ m_TitleObj->GetGameEndPos() });

				DownFlg = false;
				EndFlg = true;

			}
		}


		//↑を押した時
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			RankingFlg = false;
			UpFlg = true;
		}
		else
		{
			if (!RankingFlg && UpFlg == true)
			{
				//カーソルがゲームスタートに移動
				m_TitleType = GAMESTART;
				m_TitleObj->SetArrowPos({ m_TitleObj->GetGameStartPos() });

				UpFlg = false;
				StartFlg = true;
		}

		}
		break;
	}
	case GAMEEND:
	{
		//↑を押した時
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			EndFlg = false;
		}
		else
		{
			if (!EndFlg)
			{
				//カーソルがランキングに移動
				m_TitleType = RANKING;
				m_TitleObj->SetArrowPos({ m_TitleObj->GetRankingPos() });

				RankingFlg = true;
			}
		}

		//Enterでゲーム終了
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			Application::Instance().End();
		}
	}


	}

	//================================

	m_CamPos.x += m_CamMove;
	m_GroundPos = m_CamPos.x;

	//全オブジェクトループ
	for (auto obj : m_objList)
	{
		//グラウンドタイプのみ
		if (obj->GetObjType() == 1)
		{
			//カメラ座標より後ろであれば
			if (obj->GetPos().x + 15 <= m_CamPos.x)
			{
				//存在を消す
				obj->SetisExpired(true);
			}
		}
	}

	// --- Ground の無限生成処理 ---
	
	std::shared_ptr<Ground> ground;
	std::shared_ptr<Rock> rock;
	m_GroundCnt++;
	if (m_GroundCnt >= 80)
	{
		for (float z : { 0.0f, 5.0f })
		{
			ground = std::make_shared<Ground>();
			ground->Init();
			ground->SetPos({ m_CamPos.x + 20, 0.0f, z });
			m_objList.push_back(ground);
		}



		m_GroundCnt = 0;
	}

	



	//	const float spawnAhead = 50.0f; // カメラ前方にこれだけの余裕があれば生成しない
	//	const float groundWidth = 4.0f; // 既存配置と同じ幅

	//	// 現在の地面オブジェクトの最大 X を探す
	//	float maxGroundX = -1e9f;
	//	for (auto &obj : m_objList)
	//	{
	//		if (obj->GetObjType() == 1) 
	//		{
	//			maxGroundX = std::max(maxGroundX, obj->GetPos().x);
	//		}
	//	}

	//	std::shared_ptr<Ground> ground;
	//	// 最大 X が見つかっていて、カメラ前方に spawnAhead の余裕が無ければ生成
	//	if (maxGroundX > -1e8f && maxGroundX < m_CamPos.x + spawnAhead)
	//	{
	//		// 2列分（z = 0 と z = 5）を追加
	//		for (float z : { 0.0f, 5.0f })
	//		{
	//			
	//			ground = std::make_shared<Ground>();
	//			ground->Init();
	//			ground->SetPos({ maxGroundX + groundWidth, 0.0f, z });
	//			m_objList.push_back(ground);
	//		}
	//	}
	//}




	Math::Matrix trans = Math::Matrix::CreateTranslation(m_CamPos);

	Math::Matrix rotationX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(40.0f));

	Math::Matrix world = rotationX * trans;

	m_camera->SetCameraMatrix(world);

}

void TitleScene::Init()
{
	srand(time(0));

	//カメラ用意
	m_camera = std::make_unique<KdCamera>();
	//視野角設定
	m_camera->SetProjectionMatrix(60);

	m_CamPos = { -25,5,-6 };
	m_CamMove = 0.05f;

	//タイトルオブジェクト設置
	m_TitleObj = std::make_shared<TitleObject>();
	m_TitleObj->Init();
	m_objList.push_back(m_TitleObj);

	//地形初期化
	std::shared_ptr<Ground> ground;

	for (int i = 0; i < 10; ++i)
	{
		ground = std::make_shared<Ground>();
		ground->Init();
		ground->SetPos({ (float)i * 4.0f - 40,0,0 });
		//ground->SetTarget(m_Player);
		m_objList.push_back(ground);
	}


	//地形2初期化
	for (int i = 0; i < 10; ++i)
	{
		ground = std::make_shared<Ground>();
		ground->Init();
		ground->SetPos({ (float)i * 4.0f - 40,0,5.0f });
		//ground->SetTarget(m_Player);
		m_objList.push_back(ground);
	}



	//キーフラグ初期化
	m_KeyFlg = false;

	//グラウンド生成カウント初期化
	m_GroundCnt = 0;
}
