#include "Bullet.h"

Bullet::Bullet()
{
	object = std::make_unique<Object3d>();
	smokeParticle = std::make_unique<SmokeParticle>();
}

Bullet::~Bullet()
{
}

void Bullet::Initialize(DirectXCommon* dxCommon, TextureManager* textureManager, UINT texNum)
{
	object->Initialize(loader->GetModel(Loader::ModelIndex::MISSILE));
	smokeParticle->Initialize(dxCommon, textureManager, texNum);

	scale = Vector3(0.3f, 0.3f, 0.3f);
	rotation = Vector3::Zero;
	liveFlag = false;
	time = 0;
	intervalX = 0.2f;
	intervalZ = 0.7f;
	pointSize = 0.2f;
	reverseCount = 2;

	rightPoint = Vector3(position.x + intervalX, position.y, position.z);
	leftPoint = Vector3(position.x - intervalX, position.y, position.z);
	frontPoint = Vector3(position.x, position.y, position.z + intervalZ);
	behindPoint = Vector3(position.x, position.y, position.z - intervalZ);
}

void Bullet::Update()
{
	object->SetPosition(position);
	object->SetRotation(rotation);
	object->SetScale(scale);
	object->Update();
	smokeParticle->Update(position);
	if (liveFlag)
	{
		//”­ŽË‚³‚ê‚Ä‚©‚ç‚ÌƒJƒEƒ“ƒg
		position += velocity;
		rightPoint = Vector3(position.x + intervalX, position.y, position.z);
		leftPoint = Vector3(position.x - intervalX, position.y, position.z);
		frontPoint = Vector3(position.x , position.y, position.z + intervalZ);
		behindPoint= Vector3(position.x, position.y, position.z - intervalZ);
	}
}
void Bullet::Draw(DirectXCommon* dxCommon)
{
	if (liveFlag)
	{
		object->Draw(dxCommon->GetCommandList());
		smokeParticle->Draw(dxCommon);
	}
}

void Bullet::Counting()
{
	reverseCount--;
}
