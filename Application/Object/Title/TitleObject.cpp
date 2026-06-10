#include "TitleObject.h"

void TitleObject::Init()
{
	//タイトル名前================

	//実体化
	m_TitleNameTex = std::make_shared<KdTexture>();
	m_BackTex = std::make_shared<KdTexture>();
	m_GameStartTex = std::make_shared<KdTexture>();
	m_GameEndTex = std::make_shared<KdTexture>();
	m_RankingTex = std::make_shared <KdTexture>();
	m_ArrowTex = std::make_shared<KdTexture>();

	//テクスチャの読み込み
	m_TitleNameTex->Load("Asset/Textures//Title/Press Enter.png");
	m_BackTex->Load("Asset/Textures/Title/BlackBack.png");
	m_GameStartTex->Load("Asset/Textures/Title/GameStart.png");
	m_GameEndTex->Load("Asset/Textures/Title/GameEnd.png");
	m_RankingTex->Load("Asset/Textures/Title/Ranking.png");
	m_ArrowTex->Load("Asset/Textures/Title/Arrow.png");

	//座標
	m_TitleNamePos = { 0,200 };
	m_GameStartPos = { 0,100 };
	m_RankingPos   = { 0,-50 };
	m_GameEndPos   = { -10,-200 };
	m_ArrowPos	   = { m_GameStartPos.x - 300,m_GameStartPos.y };
	
	//拡縮
	m_TitleNameScale = { 800,120 };
	m_GameStartScale = { 400,120 };
	m_RankingScale   = { 420,80 };
	m_GameEndScale	 = { 420,80 };
	m_ArrowScale	 = { 150,150 };

}

void TitleObject::Update()
{

}


void TitleObject::DrawSprite()
{


	//タイトル名
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_TitleNameTex, m_TitleNamePos.x,m_TitleNamePos.y,m_TitleNameScale.x,m_TitleNameScale.y,nullptr);

	//ゲームスタート
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_GameStartTex, m_GameStartPos.x, m_GameStartPos.y,m_GameStartScale.x,m_GameStartScale.y, nullptr);

	//ランキング
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_RankingTex, m_RankingPos.x, m_RankingPos.y, m_RankingScale.x, m_RankingScale.y,nullptr);

	//ゲーム終了
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_GameEndTex, m_GameEndPos.x, m_GameEndPos.y, m_GameEndScale.x, m_GameEndScale.y, nullptr);

	//操作説明

	//矢印
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_ArrowTex, m_ArrowPos.x, m_ArrowPos.y, m_ArrowScale.x, m_ArrowScale.y, nullptr);
}


