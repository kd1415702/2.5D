#include "Player.h"
#include"../../../Scene/SceneManager.h"
#include"../../../Info/Info.h"

void Player::Init()
{
	//デバッグ表示したい時に実体化させる！
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//走っている板ポリゴン=========-
	m_RunPolygon.SetMaterial("Asset/Textures/Game/Player/Metroidvania - Roguelike Tamplate/Player Movement v1/player run.png");

	m_RunPolygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_RunPolygon.SetSplit(8, 1);

	//ジャンプ中の板ポリゴン============-
	m_JumpPolygon.SetMaterial("Asset/Textures/Game/Player/Metroidvania - Roguelike Tamplate/Player Movement v1/player jump.png");

	m_JumpPolygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_JumpPolygon.SetSplit(6, 1);

	//ローリング中の板ポリゴン
	m_RowlingPolygon.SetMaterial("Asset/Textures/Game/Player/Metroidvania - Roguelike Tamplate/Player Movement v2/Player Roll.png");

	m_RowlingPolygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_RowlingPolygon.SetSplit(7, 1);


	m_Pos = { -32.0f,1.0f,0.0f };

	m_Speed = 0.05f;

	m_Anim = 0.0f;

	m_Gravity = 0.0f;

	m_RunCnt = 0;

	m_JumpFlg = false;
	m_RowlingFlg = false;

	//m_mWorld = Math::Matrix::Identity;

	//実体化
	m_pCollider = std::make_unique<KdCollider>();

	//当たり判定の形状を登録
	m_pCollider->RegisterCollisionShape
	(
		"PlayerCollision", //当たり判定の名前
		{ 0,0.0,0 },	  //スフィアの位置(中心点)
		0.2f,			  //半径
		KdCollider::TypeDamage
	);
}

void Player::Update()
{

	m_Pos.x += m_Speed;

	m_RunCnt += 1;
	if (m_RunCnt >= 55)
	{
		m_RunCnt = 0;
		Info::Instance().SetRunDistance();
		
	}

	//重力処理
	m_Pos.y -= m_Gravity;
	m_Gravity += 0.005f;


	//アニメーション
	//走っている状態
	if (m_JumpFlg == false || m_RowlingFlg == false)
	{
		m_Anim += 0.1f;
		if (m_Anim >= 8)
		{
			m_Anim = 0;
		}
	}
	//ジャンプ中
	if(m_JumpFlg == true)
	{
		m_Anim += 0.1f;
		if (m_Anim >= 6)
		{
			m_Anim = 0;
		}
		m_JumpPolygon.SetUVRect(m_Anim);
	}

	//ローリング中
	if (m_RowlingFlg == true)
	{
		m_Anim += 0.09f;
		if (m_Anim >= 7)
		{
			m_Anim = 0;
			m_RowlingFlg = false;
		}
		m_RowlingPolygon.SetUVRect(m_Anim);
	}

	m_RunPolygon.SetUVRect(m_Anim);
	

	
}

void Player::Jump()
{
	//まだジャンプ中&Rowling中じゃなければ
	if (m_JumpFlg == false && m_RowlingFlg == false)
	{
		m_Gravity = -0.15f;
		m_JumpFlg = true;

		m_Anim = 0;
	}
}

void Player::Rowling()
{
	//まだローリング中&ジャンプ中じゃなければ
	if (m_RowlingFlg == false && m_JumpFlg == false)
	{
		m_RowlingFlg = true;

		m_Anim = 0;
	}
}

void Player::PostUpdate()
{
	//当たり判定
//レイ判定(重い）

//当たる側の処理
//レイ判定用の変数を設定
	KdCollider::RayInfo ray;

	//レイの発射位置を設定
	ray.m_pos = m_Pos;

	//ちょっと上からの位置にする
	ray.m_pos.y += 0.1f;

	//段差の許容範囲を設定
	float enableStepHigh = 0.2f;
	ray.m_pos.y += enableStepHigh;

	//レイの発射方向を設定
	ray.m_dir = { 0,-1,0 };

	//レイの長さを設定
	ray.m_range = m_Gravity + enableStepHigh;

	//当たり判定を行いたいタイプを設定
	ray.m_type = KdCollider::TypeGround;

	//デバッグ表示
//	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	//レイに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retRayList;

	//全オブジェクトと当たり判定
	for (auto obj : SceneManager::Instance().GetObjList())
	{

		//当たり判定を行う関数
		obj->Intersects(ray, &retRayList);
	}

	//レイに当たったリストから一番近いオブジェクトを探す
	float maxOverLap = 0;
	Math::Vector3 hitPos;
	bool hit = false;

	for (auto& ret : retRayList)
	{
		//レイを遮断しオーバーした長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			//更新
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			hit = true;
		}
	}

	if (hit == true)
	{
		//当たっていたらプレイヤー座標を更新
		m_Pos = hitPos + Math::Vector3(0, -0.1f, 0);

		//重力をゼロ
		m_Gravity = 0.0f;

		m_JumpFlg = false;
	}

	//球(スフィア)判定======================

	//球判定用の変数を用意
	KdCollider::SphereInfo sphere;

	//旧の中心座標を設定				  //原点が足元なので上に0.5上げる
	sphere.m_sphere.Center = m_Pos + Math::Vector3(0, 0.5f, 0);

	//球の半径を設定
	sphere.m_sphere.Radius = 0.3f;

	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround;

	//デバッグ
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//球に当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retSphereList;

	//全オブジェクトと当たり判定をする
	for (auto obj : SceneManager::Instance().GetObjList())
	{

		//当たり判定を行う関数
		obj->Intersects(sphere, &retSphereList);
	}

	//球に当たったリストから一番近いオブジェクトを探す

	//レイ判定で宣言した物を使いまわす
	maxOverLap = 0;
	hit = false;

	//当たった方向を格納する変数
	Math::Vector3 hitDir;
	for (auto& ret : retSphereList)
	{
		//球にめり込んだ長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			//更新
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			hit = true;
		}
	}

	if (hit == true)
	{
		//Z方向への押し出し無効
		hitDir.z = 0;

		//方向ベクトルは長さ1
		//ベクトルを正規化する
		hitDir.Normalize();


		m_Pos += hitDir * maxOverLap;
	}


	//球の中心座標を設定
	sphere.m_sphere.Center = m_Pos;

	sphere.m_sphere.Radius = 0.1f;

	//当たり判定をしたいタイプを設定
	//アイテムとの当たり判定
	sphere.m_type = KdCollider::TypeItem;


	//全オブジェクトと当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//設定したタイプと同じオブジェに当たっていれば
		if (obj->Intersects(sphere, nullptr) == true)
		{
			obj->Hit();
			Info::Instance().SetCoin(1);
		}
	}

	//行列を作成
	m_mWorld = Math::Matrix::CreateTranslation(m_Pos);
}

void Player::GenerateDepthMapFromLight()
{
	//走っているポリゴン
	if (m_JumpFlg == false && m_RowlingFlg == false)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_RunPolygon, m_mWorld);
	}

	//ジャンプしているポリゴン
	if (m_JumpFlg == true)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_JumpPolygon, m_mWorld);
	}

	//ローリングのポリゴン
	if (m_RowlingFlg == true)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_RowlingPolygon, m_mWorld);
	}
}

void Player::DrawLit()
{
	//走っているポリゴン
	if (m_JumpFlg == false && m_RowlingFlg == false)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_RunPolygon, m_mWorld);
	}

	//ジャンプポリゴン
	if (m_JumpFlg == true)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_JumpPolygon, m_mWorld);
	}

	//ローリングのポリゴン
	if (m_RowlingFlg == true)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_RowlingPolygon, m_mWorld);
	}
}

void Player::Hit()
{
	m_isExpired = true;
	//SceneManager::Instance().SetNextScene(SceneManager::SceneType::TITLE);
}


