#include "Framework.h"
#include "IShader.h"

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob** blob)
{
    // �����Ϸ� ���� �޼����� ������ Blob ������
    ID3DBlob* error = nullptr;

    // ���̴� ������ �������ϰ�, ����� Blob �����ͷ� ���� ����
    // HRESULT�� Dx�� ���� ���𰡸� ���鶧 ������ �߻��ϴ��� �ƴ��� Ȯ�����ִ� �뵵
    HRESULT hr = D3DCompileFromFile
    (
        path.c_str(),                   // �������� ���̴� ���� ���
        nullptr,                        // ���̴� ������ ����� ��Ÿ���� ������
        nullptr,                        // Include �������̽��� ������ Ŭ������ ����� ���̴� 
                                        // ���Ͽ��� �ٸ� ������ include�Ҷ� ����� �� �ִ� ���ý�Ʈ
        entryName.c_str(),              // �������� ���̴� ���Ͽ��� ���� ���������� ����� �Լ� �̸�
        profile.c_str(),                // �������� ���̴� ���Ͽ��� ����� ������ �̸�
        D3DCOMPILE_ENABLE_STRICTNESS,   // ������ ������ �ɼ� / ��� �޼����� ���� 1�� ����
        0,                              // ����� ������ ���Ե� ������ ����� �����ϱ� ���� �ɼ�
        blob,                           // ������ ����� ������ blob ������ �ּҰ�
        &error                          // �����Ϸ� ���� �޼����� ������ blob ������ �ּҰ�
    );
    CheckShaderError(hr, error);
    SAFE_RELEASE(error);            // I�� �����ϴ� �������̽� �������� ���� ������ ����� �Ѵ�.
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob* error)
{
    // HRESULT�� �������� ���
    if (FAILED(hr))
    {
        // error�� ������ ���
        if (error)
        {
            // error �޼����� ���ڿ��� �����ͼ� �޼��� �ڽ��� error�� ���
            string str = (const char*)error->GetBufferPointer();
            MessageBoxA(handle, str.c_str(), "Shader Error", MB_OK);
        }
        // ���α׷� �ߴ�
        CHECK(false);
    }
}

/*
ID3DBlob
- �޸𸮿� �Ҵ�� ������ ���
- ��ǥ������ ���̴� �ڵ峪 ���� ������ ��
- �޸𸮿� �Ҵ�� ������ ���̸� �����ϰ� ������ ������ �� ����
- I�� �����ϴ� �������̽� �̱� ������ ���� ����� ���°��� �ƴ� �̹� ������� �ִ�
���� ���� ���� ����
- �׷��⿡ �ش� Blob�� �����͸� ���������� ����� ���� ����.
*/