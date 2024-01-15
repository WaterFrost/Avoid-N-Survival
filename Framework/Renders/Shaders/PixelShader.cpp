#include "Framework.h"
#include "IShader.h"
#include "PixelShader.h"

PixelShader::~PixelShader()
{
    Clear();
}

void PixelShader::Create(const wstring path, const string entryName)
{
    // ���̴� ��ο� ��Ʈ�� �̸��� ����
    this->path = path;
    this->entryName = entryName;

    // ���̴� �������� ps(�ȼ� ���̴�)5.0 �������� �ض�
    CompileShader(path, entryName, "ps_5_0", &blob);

    // ���ý� ���̴� ����
    HRESULT hr = DEVICE->CreatePixelShader
    (
        blob->GetBufferPointer(),
        blob->GetBufferSize(),
        nullptr,
        &shader
    );
    CHECK(hr);
}

void PixelShader::Clear()
{
    SAFE_RELEASE(blob);
    SAFE_RELEASE(shader);
}

void PixelShader::SetShader()
{
    DC->PSSetShader(shader, nullptr, 0);
}
