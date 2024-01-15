#pragma once
#include "Framework.h"

// GPU���� ����ϴ� �����͸� CPU���� �����ϰ� ������ �� �ֵ��� �ϴ� ����
class ShaderBuffer
{
public:
	void SetVSBuffer(uint slot)
	{
		MapData();
		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}

	void SetPSBuffer(uint slot)
	{
		MapData();
		DC->PSSetConstantBuffers(slot, 1, &buffer);
	}

protected:
	ShaderBuffer(void* data, uint dataSize)
		:data(data), dataSize(dataSize)
	{
		// ������ ��� �뵵	// USAGE_DYNAMIC �� CPU���� ���� ����
		desc.Usage = D3D11_USAGE_DYNAMIC;
		// ������ ũ��
		desc.ByteWidth = dataSize;
		// ���ε��� ���
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		// CPU���� ���ۿ� �����ϴ� ���
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &buffer);
		CHECK(hr);
	}

private:
	void MapData()
	{
		// ������ ������ ���� ����ü
		D3D11_MAPPED_SUBRESOURCE subResource;
		// ������ ����
		HRESULT hr = DC->Map
		(
			buffer,						// ������ �׷��� ���ҽ�
			0,							// ������ ���� ����Ʈ ��ġ
			D3D11_MAP_WRITE_DISCARD,	
			// ���� ��� (WRITE_DISCARD�� ������ ���� ����.)
			0,							// ������ ���ϴ� ���� ���ҽ�
			&subResource				// ���ε� �޸� �ּҸ� ����
		);
		CHECK(hr);
		// ������ ����
		memcpy(subResource.pData, data, dataSize);
		// ���� �����
		DC->Unmap(buffer, 0);
	}

private:
	D3D11_BUFFER_DESC desc = { 0 };
	ID3D11Buffer* buffer = nullptr;

	void* data = nullptr;
	uint dataSize = 0;
};