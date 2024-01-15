#include "Framework.h"
#include "IShader.h"
#include "VertexShader.h"

VertexShader::~VertexShader()
{
    Clear();
}

void VertexShader::Create(const wstring path, const string entryName)
{
    // ���̴� ��ο� ��Ʈ�� �̸��� ����
    this->path = path;
    this->entryName = entryName;

    // ���̴� �������� vs(���ؽ� ���̴�)5.0 �������� �ض�
    CompileShader(path, entryName, "vs_5_0", &blob);

    // ���ý� ���̴� ����
    HRESULT hr = DEVICE->CreateVertexShader
    (
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    );
    CHECK(hr);
}

void VertexShader::Clear()
{
    SAFE_RELEASE(blob);
    SAFE_RELEASE(shader);
}

void VertexShader::SetShader()
{
    DC->VSSetShader(shader, nullptr, 0);
}
