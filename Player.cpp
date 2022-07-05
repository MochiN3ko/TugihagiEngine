#include "Player.h"

using namespace DirectX;

Input* Player::input = nullptr;
bool Player::isInput = false;

Player::Player()
{
	turretObj = std::make_unique<Object3d>();
	bodyObj = std::make_unique<Object3d>();
	nBullet = std::make_unique<NormalBullet>(20);
	//fireParticle = std::make_unique<FireParticle>();
	hitParticle = std::make_unique<HitParticle>();
	laser = std::make_unique<Laser>();
}

Player::~Player()
{
}

//初期化
void Player::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	turretObj->Initialize(loader->GetModel(Loader::ModelIndex::TURRET));
	turretObj->SetColor(Vector3(0.7f,0.13f,0.13f));

	bodyObj->Initialize(loader->GetModel(Loader::ModelIndex::BODY));
	bodyObj->SetColor(Vector3(0.7f, 0.13f, 0.13f));

	position = Vector3(0.0f, 0.0f, -20.0f);

	scale = Vector3(0.6f, 0.6f, 0.6f);
	rotation = Vector3::Zero;
	
	//カメラ関連
	distanceY = 1.0f;
	distanceZ = 3.5f;
	eye = Vector3(position.x, position.y + distanceY, position.z - distanceZ);
	target = position;
	cameraRightAngle = 0.0f;//カメラ軸の横方向の回転角度(経度のような)
	sensibility = 0.001f;

	adjustment = Vector3(0.0f, -0.4f, 0.0f);
	bodyRotation = Vector3(0.0f, 90.0f, 0.0f);
	
	hp = 5;//プレイヤーの体力
	speed = 0.6f;//弾のスピード

	interval = 0;

	knockBack = false;

	invincible = 120;
	normal = invincible;

	//弾
	nBullet->Initialize(dxCommon, textureManager, texNum);//弾の初期化

	//fireParticle->Initialize(dxCommon, textureManager, texNum);
	hitParticle->Initialize(dxCommon, textureManager, texNum);//当たった際のパーティクルの初期化
	hitParticle->SetRedFlag(true);

	laser->Initialize(dxCommon, textureManager, texNum);//補助線の初期化
	laser->SetParent(turretObj.get());//プレイヤーオブジェクトを補助線オブジェクトの親にする
}
//更新処理
void Player::Update()
{
	//戦車の砲塔の処理
	turretObj->Update();
	turretObj->SetPosition(position + adjustment);
	turretObj->SetRotation(rotation);
	turretObj->SetScale(scale);
	//戦車の車体の処理
	bodyObj->Update();
	bodyObj->SetPosition(position + adjustment);
	bodyObj->SetRotation(bodyRotation);
	bodyObj->SetScale(scale);

	if (liveFlag)
	{
		TPSCameraUpdate();//カメラの動き
		ObjectRot();//オブジェクトの回転
		Move();//プレイヤーの動き
	}
}

void Player::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		if (normal > invincible)
		{
			turretObj->Draw(dxCommon->GetCommandList());//プレイヤー
			bodyObj->Draw(dxCommon->GetCommandList());//プレイヤー
			laser->Draw(dxCommon);//補助線
		}
		else
		{
			if (normal % 4 == 0)
			{
				turretObj->Draw(dxCommon->GetCommandList());//プレイヤー
				bodyObj->Draw(dxCommon->GetCommandList());//プレイヤー
				laser->Draw(dxCommon);//補助線
			}
		}
		nBullet->Draw(dxCommon);//弾
		hitParticle->Draw(dxCommon);
		//fireParticle->Draw(dxCommon);//発射時のパーティクル
	}
}

void Player::Move()
{
	//向きの計算
	Vector3 direction = Vector3(target.x - eye.x, 0.0f, target.z - eye.z);
	//正規化
	direction.Normalize();
	velocity = Vector3::Zero;
	//操作
	if (input->KeyPress(DIK_W) || input->KeyPress(DIK_S))
	{
		if (input->KeyPress(DIK_W))
		{
			velocity += direction * 0.1f;
			dirVel = direction * 0.1f;
		}
		if (input->KeyPress(DIK_S))
		{
			velocity -= direction * 0.1f;
			dirVel = direction * 0.1f;
		}
		isInput = true;
	}

	if (interval == 0)
	{
		//左クリックで弾の発射
		if (input->MouseButtonTrigger(0))
		{
			nBullet->Fire();//弾の発射関数呼び出し
			vel = Vector3(direction.x * 0.125f, 0.0f, direction.z * 0.125f);//ノックバック用のvelocity
			recoil = Vector3(direction.x * 0.01f, 0.0f, direction.z * 0.01f);
			knockBack = true;
			//fireParticle->SetSpawnFlag(true);
		}
	}

	position += velocity;
	
	//弾を撃った際の反動
	if (knockBack)
	{
		interval++;
		if (interval <= 26)
		{
			position -= vel;
			vel -= recoil;
		}
		else if(interval > 26)
		{
			vel = Vector3::Zero;
			interval = 0;
			knockBack = false;
		}
	}
	else
	{
		vel = Vector3::Zero;
		interval = 0;
	}

	//ダメージ受けた際の無敵時間
	if (normal != invincible + 1)
	{
		normal++;
	}

	nBullet->Update(position, direction * speed);//弾の更新処理

	hitParticle->Update(position);
	//fireParticle->Update(position);//発射した際のパーティクルの更新処理

	laser->Update();//補助線の更新処理

	//押してなかったら最後にFalseを返す
	isInput = false;

	//体力が0になったら死亡
	if (hp <= 0)
	{
		liveFlag = false;
	}
}

void Player::TPSCameraUpdate()
{
	//カメラの追従
	eye = Vector3(position.x, position.y + distanceY, position.z - distanceZ);
	target = position;
	//カメラの回転
	cameraRightAngle += input->MouseXMove() * sensibility;
	eye.x = target.x - (sinf(cameraRightAngle) * distanceZ);
	eye.z = target.z - (cosf(cameraRightAngle) * distanceZ);
}

void Player::ObjectRot()
{
	//戦車の砲塔の向きの計算
	Vector3 TurretDirection = target - eye;
	rotation.y = atan2f(TurretDirection.z, TurretDirection.x) * (-57.325f) + 180.0f;

	//戦車の車体の向きの計算
	if (fabsf(dirVel.z) > 0 && fabsf(dirVel.x) > 0)
	{
		float bodyDirection = atan2f(dirVel.z, dirVel.x);

		bodyRotation.y = bodyDirection * (-57.325f) + 180.0f;
	}
}

void Player::Reset()
{
	nBullet->Reset();
	SetHp(5);
	cameraRightAngle = 0;
}

void Player::Damage()
{
	if (normal > invincible)
	{
		hp--;
		hitParticle->SetSpawnFlag(true);
		normal = 0;
	}
}

