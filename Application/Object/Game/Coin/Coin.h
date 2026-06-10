#pragma once

class Coin : public KdGameObject
{
public:

	Coin() {};
	~Coin()override { Release(); }

	//初期化
	void Init()override;

	//更新
	void Update()override;

	//光の影響を受けるオブジェクトの描画
	void DrawLit()override;

	//影を生み出す
	void GenerateDepthMapFromLight()override;

	//座標セッター
	void SetPos(const Math::Vector3& _pos)override { m_Pos = _pos; }

	//当たられた時の処理
	void Hit()override;

	void Release() { m_isExpired = true; }

private:

	std::shared_ptr<KdModelData> m_Model = nullptr;

	Math::Vector3 m_Pos;
};

