#pragma once

class Rock : public KdGameObject
{
public:

	Rock() {};
	~Rock()override {};


	void Init()override;
	void Update()override;
	void PostUpdate()override;

	//光の影響を受ける
	void DrawLit()override;

	//影を生み出す
	void GenerateDepthMapFromLight()override;

	void SetBorder(float _border) { m_Border = _border; }

	//セッター
	void SetPos(const Math::Vector3& _pos)override { m_Pos = _pos; }

private:

	//モデルデータ
	std::shared_ptr<KdModelData> m_Model = nullptr;

	//座標
	Math::Vector3 m_Pos;

	//スピード
	float m_Speed;

	//Z角度(回転用)
	float m_Angle;

	//消滅ライン
	float m_Border;
};