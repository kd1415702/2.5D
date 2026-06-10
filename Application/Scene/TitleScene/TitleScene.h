#pragma once

#include"../BaseScene/BaseScene.h"

//現在選んでいるメニュー
enum TitleType
{
	GAMESTART,	//ゲームスタート
	RANKING,	//ランキング
	GAMEEND		//ゲーム終了
};

//前方宣言
class TitleObject;
class Ground;

class TitleScene : public BaseScene
{
public :

	TitleScene()  { Init(); }
	~TitleScene() {}

private :

	void Event() override;
	void Init()  override;

	TitleType m_TitleType = GAMESTART;

	bool m_KeyFlg = false;

	//各タイプのフラグ
	bool StartFlg = true;
	bool RankingFlg = false;
	bool DownFlg = false;
	bool UpFlg = false;

	bool EndFlg = false;

	//カメラ座標
	Math::Vector3 m_CamPos;
	float m_CamMove;

	//タイトルオブジェクト
	std::shared_ptr<TitleObject> m_TitleObj = nullptr;

	//グラウンドの無限生成用カウント
	int m_GroundCnt;
	float m_GroundPos;
};
