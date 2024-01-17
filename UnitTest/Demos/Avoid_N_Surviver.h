#pragma once
#pragma once
class ANS : public IObject
{
	// IObject을(를) 통해 상속됨
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
	// 랜덤 스피드 변수
	int r_speed;
	// 중력 변수
	float m_gravity = 0.0f;
	// 점프파워 변수
	float jumpPower = 7.0f;

	// 시간관련 변수
	float runTime = 0.0f;
	float timer = 0.0f;
	float PatternTime = 0.0f;

	// 패턴 순서
	int m_EnecmyPatternNumber = 0;
	// 점수 변수
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