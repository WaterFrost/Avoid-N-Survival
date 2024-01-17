#pragma once
#pragma once
class ANS : public IObject
{
	// IObject��(��) ���� ��ӵ�
	void Init() override;
	void Destroy() override;
	void Update() override;
	void Render() override;
	void PostRender() override;
	void GUI() override;

	void CreatePlatform();
	void CreateVerticalEnemy();
	void CreateHorizontalEnemy();
	void CreateSquareEnemy();

	void IsGround();
	void Control();
	void EnemyPattern();


private:
	// ���� ���ǵ� ����
	int r_speed;
	// �߷� ����
	float m_gravity = 0.0f;
	// �����Ŀ� ����
	float jumpPower = 7.0f;

	// �ð����� ����
	float runTime = 0.0f;
	float timer = 0.0f;
	float PatternTime = 0.0f;

	// ���� ����
	int m_EnecmyPatternNumber = 0;
	// ���� ����
	int score = 0;

	bool m_jump = false;
	bool m_DoubleJump = false;
	bool m_falling = true;
	bool m_Ground = false;
	bool m_Platform = false;
	bool m_EnemyPattern = false;
	bool m_RandomPattern = false;
	bool Once = false;

	class Rect* Player;
	class Rect* Ground;
	vector<class Rect*> Platform;
	vector<class Rect*> SquareEnemy;
	vector<class Rect*> VerticalEnemy;
	vector<class Rect*> HorizontalEnemy;
};