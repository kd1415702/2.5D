#include "Ui.h"
#include"../../../Info/Info.h"

void Ui::Init()
{
	m_ScoreTex = std::make_shared<KdTexture>();
	m_ScoreTex->Load("Asset/Textures/Game/Ui/Score.png");
	
	m_ScorePos = { -500,300 };

	m_NumTex = std::make_shared<KdTexture>();
	m_NumTex->Load("Asset/Textures/Game/Ui/Number.png");

	m_NumPos = { m_ScorePos.x + 200,m_ScorePos.y };

	m_RunDistanceTex = std::make_shared<KdTexture>();
	m_RunDistanceTex->Load("Asset/Textures/Game/Ui/Rundistance.png");

	m_RunDistancePos = { 0,280 };

	m_MTex = std::make_shared<KdTexture>();
	m_MTex->Load("Asset/Textures/Game/Ui/m.png");

	m_MPos = { m_RunDistancePos.x + 200,m_RunDistancePos.y };
}

void Ui::Update()
{
	//デバッグ
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		Info::Instance().SetScore(10);
	}

	if ((Info::Instance().GetRunDistance() / 2) >= 10)
	{
		m_MPos.x = m_RunDistancePos.x + 250;
	}
}

void Ui::DrawSprite()
{
	//スコア（文字)
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_ScoreTex, -500, 300, 300, 60, nullptr);
	NumDraw(Info::Instance().GetScore(), m_NumPos);

	//走行距離(文字)
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_RunDistanceTex, m_RunDistancePos.x, m_RunDistancePos.y, 300, 60, nullptr);
	NumDraw(Info::Instance().GetRunDistance() / 2, {m_RunDistancePos.x + 150,m_RunDistancePos.y});

	//m(文字)
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_MTex, m_MPos.x, m_MPos.y, 100, 60, nullptr);

}


void Ui::NumDraw(int _num, Math::Vector2 _pos)
{
	//現在レベル

	//10以上なら桁数を求める
	if (_num >= 10)
	{
		//桁数を入れるワークスペース
		long w = 0;

		for (long long i = 1; i <= _num; i *= 10)
		{
			w++;
		}

		//分解した1桁数を入れる
		std::vector<int> w_num;

		for (int i = 0; i < w; i++)
		{
			int a = 1;
			for (int j = i; j < w - 1; j++)
			{
				a *= 10;
			}

			w_num.push_back((_num / a) % 10);
			_num %= a;


		}

		for (int i = 0; i < w_num.size(); i++)
		{
			//横切り取り範囲
			int recX = 30;

			//縦切り取り範囲
			int recY = 40;

			Math::Rectangle rect = { w_num[i] * recX,0,recX,recY };

			KdShaderManager::Instance().m_spriteShader.DrawTex(m_NumTex, _pos.x, _pos.y, 90, 90,&rect, nullptr);

			//次の数字を描画するために、描画後に行列を移動させる
			_pos.x += 50.0f;
		}
	}
	else
	{
		int recX = 30;
		int recY = 40;

		Math::Rectangle rect = { _num * recX,0,recX,recY };

		KdShaderManager::Instance().m_spriteShader.DrawTex(m_NumTex, _pos.x, _pos.y, 90, 90, &rect,nullptr);
	}
}
