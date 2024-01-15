#pragma once
enum
{
	x = 0,
	y
};
struct RectEdge
{
	Vector3 LT;
	Vector3 LB;
	Vector3 RT;
	Vector3 RB;
};
struct AxisData
{
	Vector3 centerPos;
	Vector3 axisDir[2];
	float axisLen[2];
};
class BoundingBox
{
public:
	BoundingBox();
	~BoundingBox();

	void UpdataCollisionData(const Matrix world, const Vector3 verticesLocalPosition[]);

	static bool AABB(BoundingBox* a, BoundingBox* b);
	static bool OBB(BoundingBox* a, BoundingBox* b);
private:
	RectEdge* edge = nullptr;
	AxisData* data = nullptr;
};