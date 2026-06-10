#include "Coin.h"
#include "../../../Info/Info.h"

void Coin::Init()
{


	m_Model = std::make_shared<KdModelData>();

	m_Model->Load("Asset/Models/Coin/coin.gltf");

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_Pos);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(3, 3, 3);

	m_mWorld = scaleMat * transMat;

	//当たられる側の処理

	//実体化
	m_pCollider = std::make_unique<KdCollider>();

	//当たり判定の形状を登録
	m_pCollider->RegisterCollisionShape
	(
		"CoinCollision", //当たり判定の名前
		{ 0,0.0,0 },	  //スフィアの位置(中心点)
		0.2f,			  //半径
		KdCollider::TypeItem
	);

}

void Coin::Update()
{
	
}

void Coin::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}

void Coin::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}

void Coin::Hit()
{
	m_isExpired = true;

	Info::Instance().SetScore(10);

}
