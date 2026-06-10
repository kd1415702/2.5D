#include "Rock.h"
#include"../../../Scene/SceneManager.h"

void Rock::Init()
{
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//メモリ確保
	m_Model = std::make_shared<KdModelData>();

	//モデル読み込み
	m_Model->Load("Asset/Models/Rock/projectile_catapult.gltf");

	m_Pos = {};

	//移動スピード初期化
	m_Speed = 0.01f;

	//角度(回転用初期化)
	m_Angle = 0;
}

void Rock::Update()
{
	//座標更新
	m_Pos.x -= m_Speed;

	//回転
	m_Angle += 1.0f;

	//行列合成
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_Pos);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(3, 3, 3);
	Math::Matrix rotationZMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_Angle));
	m_mWorld = scaleMat * rotationZMat * transMat;
}

void Rock::PostUpdate()
{
	//球(スフィア)判定======================

	//球判定用の変数を用意
	KdCollider::SphereInfo sphere;

	//旧の中心座標を設定	
	sphere.m_sphere.Center = m_Pos + Math::Vector3(0, 0, 0);

	//球の半径を設定
	sphere.m_sphere.Radius = 0.3f;

	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeDamage;

	//デバッグ
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, nullptr) == true)
		{
			//プレイヤー被弾
			obj->Hit();
		}
	}
}

void Rock::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}

void Rock::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}
