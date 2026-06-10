#pragma once

class CoinEffect : public KdGameObject
{
public:

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void DrawBright()override;

private:

	Math::Vector2 m_Pos;

	std::shared_ptr<KdTexture> m_Tex = nullptr;


};