#include "Ground.h"

void Ground::Init()
{
	//実体化
	m_Model = std::make_shared<KdModelData>();

	//モデルデータの読み込み
	m_Model->Load("Asset/Models/Road/hex_road_A.gltf");

	//オブジェクトタイプ
	m_ObjType = GROUND;

	m_LifeCnt = 0;

	//当たられる側の処理=============

	//当たり判定をつけたいので実体化
	m_pCollider = std::make_unique<KdCollider>();

	//モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"GroundCollision",				//識別用の名前
		m_Model,
		KdCollider::Type::TypeGround	//タイプ
	);
}


void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}

void Ground::Update()
{
	

	//プレイヤー座標の入れ物
	Math::Vector3 targetPos;

	//プレイヤーが生存していれば
	//if (m_Target.expired() == false)
	//{
	//	//weakポインタ経由でプレイヤー座標を所得
	//	targetPos = m_Target.lock()->GetPos();

	//	//プレイヤー座標よりも後ろに合った場合
	//	if (targetPos.x >= m_Pos.x + 33.0f)
	//	{
	//		//存在を削除(メモリの開放)
	//		m_isExpired = true;
	//	}
	//}

	m_LifeCnt++;
	if (m_LifeCnt > 700)
	{
		m_isExpired = true;
	}
	

	Math::Matrix scaleMat = Math::Matrix::CreateScale(2.0f, 2.0f, 2.0f);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_Pos);

	m_mWorld = scaleMat * transMat;
}


