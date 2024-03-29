#include "stdafx.h"
#include "Program.h"

#include "Systems/Window.h"

#include "Demos/00_RectDemo.h"
#include "Demos/01_TextureDemo.h"
//#include "Demos/02_CollisionDemo.h"
#include "Demos/03_ShadedDemo.h"
#include "Demos/04_AnimDemo.h"
#include "Demos/Avoid_N_Surviver.h"

void Program::Init()
{
	States::Create();

	// Create Buffer
	{
		vpb = new VPBuffer();

		// View 행렬 생성
		{
			D3DXMatrixLookAtLH
			(
				&view,
				&Vector3(0, 0, 0), // 카메라 위치(원점)
				&Vector3(0, 0, 1), // 카메라가 바라보는 방향
				&Vector3(0, 1, 0)  // 카메라의 위쪽 방향
			);
		}

		// Projection 행렬 생성
		{
			// 직교 투영 행렬
			D3DXMatrixOrthoOffCenterLH
			(
				&proj,
				0.0f,				// 왼쪽 면의 위치
				(float)WinMaxWidth, // 오른쪽 면의 위치
				0.0f,				// 아래쪽 면의 위치
				(float)WinMaxHeight,// 위쪽 면의 위치
				0,					// 니어 (깊이 시작)
				1					// 파	(깊이 끝)
			);
		}

		// 버퍼 세팅
		vpb->SetView(view);
		vpb->SetProj(proj);
	}

//	Push(new RectDemo);
//	Push(new TextureDemo);
// 
//	Push(new CollisionDemo);
//	Push(new ShootingGame);
// 
//	Push(new ShadedDemo);
	Push(new ANS);
//	Push(new AnimDemo);
}

void Program::Destroy()
{
	SAFE_DELETE(vpb);

	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
}

void Program::Update()
{
	for (IObject* obj : objs)
		obj->Update();
}

void Program::Render()
{
	vpb->SetVSBuffer(1);

	for (IObject* obj : objs)
		obj->Render();
}

void Program::PostRender()
{
	for (IObject* obj : objs)
		obj->PostRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
	{
		obj->GUI();
	}
}

void Program::Push(IObject* obj)
{
	objs.push_back(obj);
	obj->Init();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);
	WPARAM wParam = window->Run(program);

	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;

}
