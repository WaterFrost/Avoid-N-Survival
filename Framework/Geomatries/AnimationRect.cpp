#include "Framework.h"
#include "AnimationRect.h"

#include "Utilities/Animator.h"

AnimationRect::AnimationRect(Vector3 position, Vector3 size)
	: TextureRect(position, size, .0f)
{
	SetShader(ShaderPath + L"Animation.hlsl");

	animator = new Animator();
	Texture2D* srcTex = new Texture2D(TexturePath + L"player.png");
	AnimationClip* RunR = new AnimationClip(L"RunR", srcTex, 10, Values::ZeroVec2, { srcTex->GetWidth(), srcTex->GetHeight() * 0.5f });
	AnimationClip* RunL = new AnimationClip(L"RunL", srcTex, 10, { 0, srcTex->GetHeight() * 0.5f }, { srcTex->GetWidth(), srcTex->GetHeight() }, true);

	// �ִϸ��̼� ����
	animator->AddAnimClip(RunR);
	animator->AddAnimClip(RunL);
	animator->SetCurrentAnimClip(L"RunL");

	SAFE_DELETE(srcTex);

	// Sampler
	{
		// ���� ����
		D3D11_SAMPLER_DESC desc;
		States::GetSamplerDesc(&desc);
		States::CreateSampler(&desc, &point[0]);

		// point sampling
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		States::CreateSampler(&desc, &point[1]);
	}

	// Blend
	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &bPoint[0]);
		
		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &bPoint[1]);
	}
}

AnimationRect::~AnimationRect()
{

}

void AnimationRect::Update()
{
	animator->Update();

	MapVertexBuffer();
	{
		// uv ��ǥ�� ���� �� 3���� 0,0����
		vertices[0].uv.x = animator->GetCurrentFrame().x;
		vertices[0].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[1].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[1].uv.y = animator->GetCurrentFrame().y;

		vertices[2].uv.x = animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x;
		vertices[2].uv.y = animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y;

		vertices[3].uv.x = animator->GetCurrentFrame().x;
		vertices[3].uv.y = animator->GetCurrentFrame().y;
	}
	UnmapVertexBuffer();

	__super::Update();
}

void AnimationRect::Render()
{
	srv = animator->GetCurrentSRV();

	DC->PSSetSamplers(0, 1, &point[1]);
	DC->OMSetBlendState(bPoint[1], nullptr, (UINT)0xFFFFFFFF);

	__super::Render();

	//DC->PSSetSamplers(0, 1, &point[0]);
	//DC->OMSetBlendState(bPoint[0], nullptr, (UINT)0xFFFFFFFF);
}

void AnimationRect::Move()
{
	if (Keyboard::Get()->Press('A'))
	{
		position.x -= 100 * Time::Delta();
		animator->SetCurrentAnimClip(L"RunL");
	}

	else if (Keyboard::Get()->Press('D'))
	{
		position.x += 100 * Time::Delta();
		animator->SetCurrentAnimClip(L"RunR");
	}
}
