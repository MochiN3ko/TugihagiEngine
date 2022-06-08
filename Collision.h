#include"Vector2.h"
#include"Vector3.h"
#include <DirectXMath.h>
//���Ƌ�
static bool SphereAndSphere(Vector3 pos1, Vector3 pos2, float r1, float r2)
{
	float sum = r1 + r2;
	float x = pos1.x - pos2.x;
	float y = pos1.y - pos2.y;
	float z = pos1.z - pos2.z;
	float a = x * x + y * y + z * z;
	if (a < sum * sum)
	{
		return true;
	}
	return false;
}
//��]���Ȃ������`�Ƌ�
static bool RectangleAndSphere2D(Vector3 downleft, Vector3 upright, Vector3 spherepos, float r)
{
	if (spherepos.x + r > downleft.x && spherepos.z + r > downleft.z)
	{
		if (spherepos.x - r < upright.x && spherepos.z - r < upright.z)
		{
			return true;
		}
	}
	return false;
}
//���ƃJ�v�Z��
static bool SphereAndCapsule(Vector3 sphere,float sRadius,Vector3 cEnd,Vector3 cStart,float cRadius)
{
	Vector3 vStartToEnd =cEnd - cStart;

	Vector3 n = vStartToEnd;
	n.Normalize();

	float t = (sphere - cStart).Dot(n);

	Vector3 vPsPn = n * t;
	Vector3 posPn = cStart + vPsPn;

	float lengthRate = t / vStartToEnd.Length();

	float distance;
	if (lengthRate < 0)
	{
		distance = (sphere - cStart).Length() - cRadius;
	}
	else if (lengthRate <= 1.0f)
	{
		distance = (sphere - posPn).Length() - cRadius;
	}
	else
	{
		distance = (sphere -cEnd).Length() - cRadius;
	}

	if (distance < sRadius)
	{
		return true;
	}
	return false;

}
//�O�p�`�ƒ��_
static bool TriangleAndPoint(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 pointPos)
{

	Vector3 p1p2 = p2 - p1;
	Vector3 p2po = pointPos-p2;

	Vector3 p2p3 = p3-p2;
	Vector3 p3po = pointPos - p3;;

	Vector3 p3p1 = p1 - p3;
	Vector3 p1po = pointPos - p1;

	//�O�� 
	double c1 = p1p2.x * p2po.y - p1p2.y * p2po.x;
	double c2 = p2p3.x * p3po.y - p2p3.y * p3po.x;
	double c3 = p3p1.x * p1po.y - p3p1.y * p1po.x;

	if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) {
		//�O�p�`�̓����ɓ_������
		return true;
	}

	//�O�p�`�̊O���ɓ_������
	return false;
}
//�����Ƌ���
static bool LineAndSphere(Vector3 p1, Vector3 p2, Vector3 pointPos,float r)
{
	Vector3 p1p2 = p2 - p1;
	Vector3 p2po = pointPos - p2;
	
	double c1 = p1p2.x * p2po.y - p1p2.y * p2po.x;
	
	if (abs(c1 / p1p2.Length()) < r)
	{
		return true;
	}
	return false;
}
//�l�p�`�ƒ��_
static bool QuadrilateralAndPoint(Vector3 p1, Vector3 p2, Vector3 p3,Vector3 p4, Vector3 pointPos)
{

	Vector3 p1p2 = p2 - p1;
	Vector3 p2po = pointPos - p2;

	Vector3 p2p3 = p3 - p2;
	Vector3 p3po = pointPos - p3;;

	Vector3 p3p4 = p4 - p3;
	Vector3 p4po = pointPos - p4;

	Vector3 p4p1 = p1 - p4;
	Vector3 p1po = pointPos - p1;

	//�O�� 
	double c1 = p1p2.x * p2po.y - p1p2.y * p2po.x;
	double c2 = p2p3.x * p3po.y - p2p3.y * p3po.x;
	double c3 = p3p4.x * p4po.y - p3p4.y * p4po.x;
	double c4 = p4p1.x * p1po.y - p4p1.y * p1po.x;

	if ((c1 > 0 && c2 > 0 && c3 > 0 && c4 > 0) || (c1 < 0 && c2 < 0 && c3 < 0 && c4 < 0)) {
		//�l�p�`�̓����ɓ_������
		return true;
	}

	//�l�p�`�̊O���ɓ_������
	return false;
}
