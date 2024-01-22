#include "stdafx.h"
#include "Avoid_N_Surviver.h"


void ANS::Init()
{
	player = new Player(Vector3(WinMaxWidth * 0.5f, 100, 0), Vector3(30, 30, 1), 0.0f);
	player->Update();

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
	SAFE_DELETE(player);

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

	player->SetColor(Values::Green);
	player->Move();

	if (!m_EnemyPattern)
	{
		timer = timer + Time::Delta();
		if (timer >= 3.0f)
		{
			m_EnemyPattern = true;
			timer = 0.0f;
			
		}
	}
	EnemyPattern();


	player->Update();
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
	player->Render();

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
	// �÷��� ����
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
	{
		He->SetAlpha(1.0f);
		He->Update();
	}
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
	{
		SE->Update();
		SE->SetAlpha(0.0f);
	}
}

void ANS::IsGround()
{
	// �÷��̾� ������ �ҷ�����
	Vector3 p_pos = player->GetPosition();

	// �÷��̾ ���� �浹�� �۵�
	if (BoundingBox::AABB(player->GetCollision(), Ground->GetCollision()) == true)
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
	//		// �÷��̾ �÷��� ���� �Ʒ��� �ִ��� Ȯ��
	//		// �÷��� ���� �Ʒ����� �浹�� falling Ȱ��ȭ
	//		if (BoundingBox::AABB(Player->GetCollision(), i->GetCollision()) == true && Player->GetPosition().y <= i->GetPosition().y)
	//		{
	//			m_jump = false;
	//			m_falling = true;
	//		}
	//		// �÷��̾ �÷��� ���� ���� �ִ��� Ȯ��
	//		// �÷��� ���� ������ �浹�� �÷��� ���� ���� �Ҽ��ְ�
	//		else if (BoundingBox::AABB(Player->GetCollision(), i->GetCollision()) == true && Player->GetPosition().y >= i->GetPosition().y)
	//		{
	//			m_gravity = 0.0f;
	//			m_Platform = true;
	//			m_jump = false;
	//			m_falling = false;
	//			Player->SetPosition(Vector3(p_pos.x, i->GetPosition().y + 50, 0));
	//		}
	//		// �÷��̾ �÷���,�׶���� �浹�� �ƴҰ�� falling �� Ȱ��ȭ
	//		if (BoundingBox::AABB(Player->GetCollision(), i->GetCollision()) == false && BoundingBox::AABB(Player->GetCollision(), Ground->GetCollision()) == false)
	//		{
	//			m_falling = true;
	//		}
	//	}
		// �÷��̾� y ���� ground �� ����
	if (m_Ground)
	{
		player->SetPosition(Vector3(p_pos.x, Ground->GetPosition().y + 40, 0.0f));
	}
}

void ANS::Control()
{
	// �÷��̾� ������ �ҷ�����
	Vector3 p_pos = player->GetPosition();

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
	// m_Ground �� Ȱ��ȭ �Ǿ��ְ� spack Ű�� ������
	if (m_Ground && Keyboard::Get()->Down(VK_SPACE))
	{
		m_Ground = false;
		m_jump = true;
	}
	// m_Platform �� Ȱ��ȭ �Ǿ��ְ� space Ű�� ������
	if (m_Platform && Keyboard::Get()->Down(VK_SPACE))
	{
		m_Platform = false;
		m_jump = true;
	}

	// m_jump Ȱ���� ���� ��� ����
	if (m_jump)
	{
		printf("jump\n");
		m_falling = false;
		p_pos.y = p_pos.y + jumpPower - m_gravity;
		player->SetPosition(p_pos);
		m_gravity = m_gravity + 0.15f;
		// m_gravity ���� jumpPower �� �Ѿ���
		// m_jump ��Ȱ��ȭ m_falling Ȱ��ȭ
		if (m_gravity > jumpPower)
		{
			m_jump = false;
			m_falling = true;
			m_gravity = 0.0f;
		}
	}
	// m_falling Ȱ���� �Ʒ��� �߶��ϰ�
	if (m_falling)
	{
		printf("fall\n");
		p_pos.y = p_pos.y - m_gravity;
		player->SetPosition(p_pos);
		m_gravity = m_gravity + 0.15f;
	}



}

void ANS::EnemyPattern()
{
	Vector3 p_pos = player->GetPosition();
	Vector3 P_scl = player->Getsize();
	Vector3 g_pos = Ground->GetPosition();
	Vector3 g_scl = Ground->Getsize();



	if (m_EnemyPattern)
	{
		PatternTime = PatternTime + Time::Delta();
		printf("Pattern Time : %f \n", PatternTime);

		if (m_EnemyPattern && !m_RandomPattern)
		{
			m_EnemyPatternNumber = Random::GetRandomInt(1, 1);
			printf("%d\n", m_EnemyPatternNumber);
		}
		// Pattern 1
		if (m_EnemyPattern && m_EnemyPatternNumber == 1)
		{
			m_RandomPattern = true;

			if (Ground->GetPosition().y <= WinMaxHeight - 100)
			{
				//	p_pos.y = p_pos.y + 300 * Time::Delta();
				//	player->SetPosition(p_pos);

				g_pos.y = g_pos.y + 300 * Time::Delta();
				Ground->SetPosition(g_pos);
			}
			if (Ground->GetPosition().y > WinMaxHeight - 100)
			{
				if (Once == false)
				{
					Once = true;
					// �߾Ӻ��� ������
					SquareEnemy[0]->SetPosition(Vector3(Random::GetRandomInt(WinMaxWidth * 0.5f, WinMaxWidth - 25), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
					SquareEnemy[2]->SetPosition(Vector3(Random::GetRandomInt(WinMaxWidth * 0.5f, WinMaxWidth - 25), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
					SquareEnemy[4]->SetPosition(Vector3(Random::GetRandomInt(WinMaxWidth * 0.5f, WinMaxWidth - 25), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
					SquareEnemy[6]->SetPosition(Vector3(Random::GetRandomInt(WinMaxWidth * 0.5f, WinMaxWidth - 25), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
					SquareEnemy[8]->SetPosition(Vector3(Random::GetRandomInt(WinMaxWidth * 0.5f, WinMaxWidth - 25), Random::GetRandomInt(25, WinMaxHeight - 150), 0));

					// ���ʺ��� �߾�
					SquareEnemy[1]->SetPosition(Vector3(Random::GetRandomInt(25, WinMaxWidth * 0.5f), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
					SquareEnemy[3]->SetPosition(Vector3(Random::GetRandomInt(25, WinMaxWidth * 0.5f), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
					SquareEnemy[5]->SetPosition(Vector3(Random::GetRandomInt(25, WinMaxWidth * 0.5f), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
					SquareEnemy[7]->SetPosition(Vector3(Random::GetRandomInt(25, WinMaxWidth * 0.5f), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
					SquareEnemy[9]->SetPosition(Vector3(Random::GetRandomInt(25, WinMaxWidth * 0.5f), Random::GetRandomInt(25, WinMaxHeight - 150), 0));
				}
			}
			if (Once && SquareEnemy[9]->Getalpha() <= 1.0f)
			{
				for (Rect* SE : SquareEnemy)
				{
					SE->SetAlpha(SE->Getalpha() + 0.001f);
				}
			}

		}
		else if (m_EnemyPatternNumber == 2)
		{
			m_RandomPattern = true;
			printf("Pattern 2\n");
		}
		else if (m_EnemyPatternNumber == 3)
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
