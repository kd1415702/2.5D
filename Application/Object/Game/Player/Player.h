#pragma once

class Player : public KdGameObject
{

public:

	Player() {};
	~Player()override {};

	//初期化
	void Init()override;

	//更新
	void Update()override;

	//ジャンプ
	void Jump();

	//ローリング
	void Rowling();
	
	//後更新
	void PostUpdate()override;

	//影を生み出す
	void GenerateDepthMapFromLight()override;

	//光の影響を受ける
	void DrawLit()override;

	//座標セッター
	void SetPos(const Math::Vector3& _pos) { m_Pos = _pos; }

	//解放処理
	void Release() { m_isExpired = true; }

	//被弾処理
	void Hit()override;

private:

	//板ポリゴン
	KdSquarePolygon m_RunPolygon;
	KdSquarePolygon m_JumpPolygon;
	KdSquarePolygon m_RowlingPolygon;

	//座標
	Math::Vector3 m_Pos;

	//スピード
	float m_Speed;

	//アニメーション
	float m_Anim;

	//重力
	float m_Gravity;

	//ジャンプフラグ
	bool m_JumpFlg;

	//ローリングフラグ
	bool m_RowlingFlg;

	//距離カウンター
	float m_RunCnt;

};
