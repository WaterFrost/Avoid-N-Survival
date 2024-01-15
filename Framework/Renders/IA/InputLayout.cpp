#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{
	SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, uint count, ID3DBlob* blob)
{
	// �ŰԺ����� �޴� ��û��, ����, ��� �� �ϳ��� ������ ���α׷��� ���Ľ�Ų��.
	if (!descs || !count || !blob)
		CHECK(false);

	HRESULT hr = DEVICE->CreateInputLayout
	(
		descs,						// InputLayout�� �����ϴ� �� ������� �迭
		count,						// InputLayout�� �����ϴ� ������ ��
		blob->GetBufferPointer(),	// ���̴� �ڵ带 �����ϴ� ����� ���� ������
		blob->GetBufferSize(),		// ���̴� �ڵ� ����� ũ��
		&inputLayout
	);

	// blob = �޸� ���
}

void InputLayout::SetIA()
{
	// ��ǲ ����÷� ������������ ����� ��ǲ ���̾ƿ��� ����
	DC->IASetInputLayout(inputLayout);
}
