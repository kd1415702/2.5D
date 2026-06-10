#pragma once

class Ground : public KdGameObject
{
public:

	Ground() {};
	~Ground()override { Release(); }

	//初期化
	void Init()override;
	//光の影響を受けるオブジェクトの描画
	void DrawLit()override;

	void Update()override;

	//座標セッター
	void SetPos(const Math::Vector3& _pos) { m_Pos = _pos; }

	void Release() { m_isExpired = true; }

	//持ってきたい対象のポインタを入れる
	void SetTarget(std::shared_ptr<KdGameObject> _target)
	{
		m_Target = _target;
	}

private:

	//モデルデータ
	std::shared_ptr<KdModelData> m_Model = nullptr;

	//座標
	Math::Vector3 m_Pos;

	//持ってきたい対象のweekポインタ
	std::weak_ptr<KdGameObject> m_Target;


	//生存カウント
	int m_LifeCnt;

};