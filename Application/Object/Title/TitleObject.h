#pragma once

class TitleObject : public KdGameObject
{
public:
	TitleObject() {};
	~TitleObject()override { Release(); }

	void Init()override;
	void Update()override;
	//光の影響を受ける
	/*void DrawLit()override;*/
	//2D描画
	void DrawSprite()override;

	//矢印の座標セッター
	void SetArrowPos(Math::Vector2 _pos) { m_ArrowPos = _pos; }


	//矢印座標セット用の定位置
	Math::Vector2 GetGameStartPos() { return { m_GameStartPos.x - 300,m_GameStartPos.y }; }
	Math::Vector2 GetRankingPos() { return { m_RankingPos.x - 300,m_RankingPos.y }; }
	Math::Vector2 GetGameEndPos() { return { m_GameEndPos.x - 300,m_GameEndPos.y }; }

	//解放処理
	void Release() { m_isExpired = true; }

private:
	
	//タイトル名
	std::shared_ptr<KdTexture> m_TitleNameTex;
	Math::Vector2 m_TitleNamePos;
	Math::Vector2 m_TitleNameScale;

	//背景
	std::shared_ptr<KdTexture> m_BackTex;

	//ゲームスタート
	std::shared_ptr<KdTexture> m_GameStartTex;
	Math::Vector2 m_GameStartPos;
	Math::Vector2 m_GameStartScale;

	//ランキング
	std::shared_ptr<KdTexture> m_RankingTex;
	Math::Vector2 m_RankingPos;
	Math::Vector2 m_RankingScale;


	//ゲーム終了
	std::shared_ptr<KdTexture> m_GameEndTex;
	Math::Vector2 m_GameEndPos;
	Math::Vector2 m_GameEndScale;


	//矢印
	std::shared_ptr<KdTexture> m_ArrowTex;
	Math::Vector2 m_ArrowPos;
	Math::Vector2 m_ArrowScale;
	

	



	

};