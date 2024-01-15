#include "stdafx.h"
#include "01_TextureDemo.h"

void TextureDemo::Init()
{
    tr = new TextureRect(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0),
        Vector3(500, 500, 1), 0.0f, TexturePath + L"sample.jpg");
}

void TextureDemo::Destroy()
{
    SAFE_DELETE(tr);
}

void TextureDemo::Update()
{
    Vector3 pos = tr->GetPosition();
    // D�� ������ ���� ���
    if (Keyboard::Get()->Press('D'))
    {
        pos.x += 100 * Time::Delta();

        tr->SetPosition(pos);
    }
    if (Keyboard::Get()->Press('A'))
    {
        pos.x -= 100 * Time::Delta();

        tr->SetPosition(pos);
    }

    // �����̽��ٸ� ��������
    if (Keyboard::Get()->Down(VK_SPACE))
    {
        // �����ϴ� ����� ����� ����
        jump = true;
    }
    if (jump)
    {
        pos.y = pos.y + 10 - gravity;
        gravity = gravity + 0.15f;
        tr->SetPosition(pos);
    }
    if (pos.y <= WinMaxHeight * 0.5f)
    {
        pos.y = WinMaxHeight * 0.5f;
        gravity = 0.0f;
        jump = false;
        tr->SetPosition(pos);
    }

    tr->Update();
}

void TextureDemo::Render()
{
    tr->Render();
}

void TextureDemo::PostRender()
{
}

void TextureDemo::GUI()
{
}
