#include "stdafx.h"
#include "Avoid_N_Surviver.h"
#include "Geomatries/Rect.h"

void ANS::Init()
{
	Player = new Rect(Vector3(WinMaxWidth * 0.5f, 100, 0), Vector3(30,30, 1), 0.0f);
	Player->Update();

	Ground = new Rect(Vector3(WinMaxWidth * 0.5f, 0, 0), Vector3(WinMaxWidth, 50, 1), 0.0f);
	Ground->Update();

	CreatePlatform();
	CreateVerticalEnemy();
	CreateHorizontalEnemy();
	CreateSquareEnemy();
}

void ANS::Destroy()
{
	SAFE_DELETE(Ground);
	SAFE_DELETE(Player);

	SquareEnemy.clear();
	HorizontalEnemy.clear();
	VerticalEnemy.clear();
	Platform.clear();
	
	
}

void ANS::Update()
{
	runTime += Time::Delta();
	IsGround();
	Control();

	Player->SetColor(Values::Green);
	Player->Move();
	
	if(!m_EnemyPattern)
	{
		timer = timer + Time::Delta();
		if (timer >= 5.0f)
		{
			timer = 0.0f;
			m_EnemyPattern = true;
		}
	}
	EnemyPattern();


	Player->Update();
	Ground->Update();
	for (Rect* i : VerticalEnemy)
		i->Update();
	for (Rect* i : HorizontalEnemy)
		i->Update();
	for (Rect* i : Platform)
		i->Update();
	for (Rect* Se : SquareEnemy)
		Se->Update();
}

void ANS::Render()
{
	Player->Render();
	
	Ground->Render();

	for (Rect* Ve : VerticalEnemy)
		Ve->Render();
	for (Rect* He : HorizontalEnemy)
		He->Render();
	for (Rect* Se : SquareEnemy)
		Se->Render();
	for (Rect* P : Platform)
		P->Render();
	
}

void ANS::PostRender()
{
}

void ANS::GUI()
{
}

void ANS::CreatePlatform()
{
	// 플랫폼 생성
	//Platform.push_back(new Rect(Vector3(200, WinMaxHeight * 0.5f-200, 0), Vector3(200, 50, 1), 0.0f));
	//Platform.push_back(new Rect(Vector3(200, WinMaxHeight * 0.5f, 0), Vector3(200, 50, 1), 0.0f));
	//Platform.push_back(new Rect(Vector3(200, WinMaxHeight * 0.5f+200, 0), Vector3(200, 50, 1), 0.0f));
}

void ANS::CreateVerticalEnemy()
{
	VerticalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(50, 200, 1), 0.0f));
	VerticalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(50, 200, 1), 0.0f));
	VerticalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(50, 200, 1), 0.0f));
	VerticalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(50, 200, 1), 0.0f));
	VerticalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(50, 200, 1), 0.0f));

	VerticalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(100, 500, 1), 0.0f));
	VerticalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(100, 500, 1), 0.0f));
	VerticalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(100, 500, 1), 0.0f));
	VerticalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(100, 500, 1), 0.0f));
	VerticalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(100, 500, 1), 0.0f));

	for (Rect* Ve : VerticalEnemy)
		Ve->Update();
}

void ANS::CreateHorizontalEnemy()
{
	HorizontalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(200, 50, 1), 0.0f));
	HorizontalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(200, 50, 1), 0.0f));
	HorizontalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(200, 50, 1), 0.0f));
	HorizontalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(200, 50, 1), 0.0f));
	HorizontalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(200, 50, 1), 0.0f));

	HorizontalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(200, 50, 1), 0.0f));
	HorizontalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(200, 50, 1), 0.0f));
	HorizontalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(200, 50, 1), 0.0f));
	HorizontalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(200, 50, 1), 0.0f));
	HorizontalEnemy.push_back(new Rect(Vector3(0, WinMaxHeight * 2, 0), Vector3(200, 50, 1), 0.0f));
	
	for (Rect* He : HorizontalEnemy)
		He->Update();
}

void ANS::CreateSquareEnemy()
{
	SquareEnemy.push_back(new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
	SquareEnemy.push_back(new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
	SquareEnemy.push_back(new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
	SquareEnemy.push_back(new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
	SquareEnemy.push_back(new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
	SquareEnemy.push_back(new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
	SquareEnemy.push_back(new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
	SquareEnemy.push_back(new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
	SquareEnemy.push_back(new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));
	SquareEnemy.push_back(new Rect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 2, 0), Vector3(50, 50, 1), 0.0f));

	for (Rect* SE : SquareEnemy)
		SE->Update();
}

void ANS::IsGround()
{ 
	// 플레이어 포지션 불러오기
	Vector3 p_pos = Player->GetPosition();

	// 플레이어가 땅과 충돌시 작동
	if (BoundingBox::AABB(Player->GetCollision(), Ground->GetCollision()) == true)
	{
		Ground->SetColor(Values::White);
		m_Ground = true;
		m_falling = false;
		m_jump = false;
		m_DoubleJump = false;
		m_gravity = 0.0f;
	}
//	for (Rect* i : Platform)
//	{
//		// 플레이어가 플랫폼 보다 아래에 있는지 확인
//		// 플랫폼 보다 아래에서 충돌시 falling 활성화
//		if (BoundingBox::AABB(Player->GetCollision(), i->GetCollision()) == true && Player->GetPosition().y <= i->GetPosition().y)
//		{
//			m_jump = false;
//			m_falling = true;
//		}
//		// 플레이어가 플랫폼 보다 위에 있는지 확인
//		// 플랫폼 보다 위에서 충돌시 플랫폼 위에 착지 할수있게
//		else if (BoundingBox::AABB(Player->GetCollision(), i->GetCollision()) == true && Player->GetPosition().y >= i->GetPosition().y)
//		{
//			m_gravity = 0.0f;
//			m_Platform = true;
//			m_jump = false;
//			m_falling = false;
//			Player->SetPosition(Vector3(p_pos.x, i->GetPosition().y + 50, 0));
//		}
//		// 플레이어가 플랫폼,그라운드와 충돌이 아닐경우 falling 을 활성화
//		if (BoundingBox::AABB(Player->GetCollision(), i->GetCollision()) == false && BoundingBox::AABB(Player->GetCollision(), Ground->GetCollision()) == false)
//		{
//			m_falling = true;
//		}
//	}
	// 플레이어 y 축을 ground 에 고정
	if (m_Ground)
	{
		Player->SetPosition(Vector3(p_pos.x, Ground->GetPosition().y+40, 0.0f));
	}
}

void ANS::Control()
{
	// 플레이어 포지션 불러오기
	Vector3 p_pos = Player->GetPosition();

	if (m_jump && !m_DoubleJump && Keyboard::Get()->Down(VK_SPACE))
	{
		m_gravity = 0.0f;
		m_DoubleJump = true;
	}
	else if (m_falling && !m_DoubleJump && Keyboard::Get()->Down(VK_SPACE))
	{
		m_gravity = 0.0f;
		m_falling = false;
		m_jump = true;
		m_DoubleJump = true;
	}
	// m_Ground 가 활성화 되어있고 spack 키를 누를시
	if (m_Ground && Keyboard::Get()->Down(VK_SPACE))
	{
		m_Ground = false;
		m_jump = true;
	}
	// m_Platform 이 활성화 되어있고 space 키를 누를시
	if (m_Platform && Keyboard::Get()->Down(VK_SPACE))
	{
		m_Platform = false;
		m_jump = true;
	}
	
	// m_jump 활성시 점프 기능 구현
	if (m_jump)
	{
		printf("jump\n");
		m_falling = false;
		p_pos.y = p_pos.y + jumpPower - m_gravity;
		Player->SetPosition(p_pos);
		m_gravity = m_gravity + 0.15f;
		// m_gravity 값이 jumpPower 를 넘어갈경우
		// m_jump 비활성화 m_falling 활성화
		if (m_gravity > jumpPower)
		{
			m_jump = false;
			m_falling = true;
			m_gravity = 0.0f;
		}
	}
	// m_falling 활성시 아래로 추락하게
	if (m_falling)
	{
		printf("fall\n");
		p_pos.y = p_pos.y - m_gravity;
		Player->SetPosition(p_pos);
		m_gravity = m_gravity + 0.15f;
	}
	
		
	
}

void ANS::EnemyPattern()
{
	Vector3 p_pos = Player->GetPosition();
	Vector3 P_scl = Player->Getsize();
	Vector3 g_pos = Ground->GetPosition();
	Vector3 g_scl = Ground->Getsize();

	

	if(m_EnemyPattern)
	{
		PatternTime = PatternTime + Time::Delta();
		printf("Pattern Time : %f \n", PatternTime);
		if (!m_RandomPattern)
		{
			m_EnecmyPatternNumber = Random::GetRandomInt(1, 1);
		}
		// Pattern 1
		if (m_EnecmyPatternNumber == 1)
		{
			m_RandomPattern = true;
			
			if (Ground->GetPosition().y <= WinMaxHeight - 100)
			{
				p_pos.y = p_pos.y + 300 * Time::Delta();
				Player->SetPosition(p_pos);

				g_pos.y = g_pos.y + 300 * Time::Delta();
				Ground->SetPosition(g_pos);
			}

			else if (!Once && Ground->GetPosition().y >= WinMaxHeight - 100)
			{
				SquareEnemy[0]->SetPosition(Vector3(Random::GetRandomInt(WinMaxWidth * 0.5f, WinMaxWidth - 25), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
				SquareEnemy[1]->SetPosition(Vector3(Random::GetRandomInt(25, WinMaxWidth * 0.5f), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
				SquareEnemy[2]->SetPosition(Vector3(Random::GetRandomInt(WinMaxWidth * 0.5f, WinMaxWidth - 25), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
				SquareEnemy[3]->SetPosition(Vector3(Random::GetRandomInt(25, WinMaxWidth * 0.5f), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
				SquareEnemy[4]->SetPosition(Vector3(Random::GetRandomInt(WinMaxWidth * 0.5f, WinMaxWidth - 25), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
				SquareEnemy[5]->SetPosition(Vector3(Random::GetRandomInt(25, WinMaxWidth * 0.5f), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
				SquareEnemy[6]->SetPosition(Vector3(Random::GetRandomInt(WinMaxWidth * 0.5f, WinMaxWidth - 25), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
				SquareEnemy[7]->SetPosition(Vector3(Random::GetRandomInt(25, WinMaxWidth * 0.5f), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
				SquareEnemy[8]->SetPosition(Vector3(Random::GetRandomInt(WinMaxWidth * 0.5f, WinMaxWidth - 25), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
				SquareEnemy[9]->SetPosition(Vector3(Random::GetRandomInt(25, WinMaxWidth * 0.5f), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
				
				Once = true;
			}
		}
		else if (m_EnecmyPatternNumber == 2)
		{
			m_RandomPattern = true;
			printf("Pattern 2\n");
		}
		else if (m_EnecmyPatternNumber == 3)
		{
			m_RandomPattern = true;
			printf("Pattern 3\n");
		}
		else
		{
			printf("Error\n");
		}
	}
	

}
