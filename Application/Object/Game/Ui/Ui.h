#pragma once

class Ui : public KdGameObject
{
public:
	Ui() {};
	~Ui() {};

	void Init()override;
	void Update()override;
	void DrawSprite()override;


	//任意の数字を任意の場所に2D表示で出す
	void NumDraw(int _num,Math::Vector2 _pos);

private:

	//スコア(文字)テクスチャ
	std::shared_ptr<KdTexture> m_ScoreTex = nullptr;

	//スコア座標
	Math::Vector2 m_ScorePos;

	//数字(0～9と,のテクスチャ)
	std::shared_ptr<KdTexture> m_NumTex = nullptr;

	//数字座標
	Math::Vector2 m_NumPos;

	//走行距離(文字)テクスチャ
	std::shared_ptr<KdTexture> m_RunDistanceTex = nullptr;

	//走行距離座標
	Math::Vector2 m_RunDistancePos;

	//m(文字)テクスチャ
	std::shared_ptr<KdTexture> m_MTex = nullptr;

	Math::Vector2 m_MPos;
};