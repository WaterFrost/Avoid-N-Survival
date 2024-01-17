#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;
vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
	:filePath(filePath)
{
	Textures::Load(this);
}

void Texture2D::ReadPixel(vector<Color>* pixels)
{
	ID3D11Texture2D* texture;
	srv->GetResource((ID3D11Resource**)&texture);

	ReadPixel(texture, pixels);
}

// �ؽ�ó �ȼ��� �о ����
void Texture2D::ReadPixel(ID3D11Texture2D* texture, vector<Color>* pixels)
{
	D3D11_TEXTURE2D_DESC srcDesc;	// ���� �ؽ�ó�� ����
	texture->GetDesc(&srcDesc);		// �ؽ�ó�� ���� ����

	D3D11_TEXTURE2D_DESC destDesc;	// �ؽ�ó ������ ���纻
	ZeroMemory(destDesc, );

	// ������ �ؽ�ó desc ����
	destDesc.Usage = D3D11_USAGE_STAGING;				// ��� ��� ����
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;	// CPU ���� ���� ����
	destDesc.Width = srcDesc.Width;						// �ʺ� ���� �ؽ�ó�� ���� ����
	destDesc.Height = srcDesc.Height;					// ���̸� ���� �ؽ�ó�� ���� ����
	destDesc.MipLevels = 1;								// MipMap ���� 1�� ����
	destDesc.ArraySize = 1;								// �迭 ũ�� 1�� ����
	destDesc.Format = srcDesc.Format;					// ������ ������ ���� ����
	destDesc.SampleDesc = srcDesc.SampleDesc;			// ���ø� ����� ������ ���� ����

	ID3D11Texture2D* destTex = nullptr;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &destTex);	// ������ �ؽ�ó�� ���� �� �Ҵ�
	CHECK(hr);
	D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);		// ���� �ؽ�ó���� ������ �ؽ�ó�� �����͸� ����

	UINT* colors = new UINT[destDesc.Width * destDesc.Height];			// �ȼ� �����͸� ������ �迭

	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subResource);
	{
		// subResource ����ü�� �⸮Ű�� �����͸� colors �迭�� ����
		memcpy(colors, subResource.pData, sizeof(UINT) * destDesc.Width * destDesc.Height);
	}
	DC->Unmap(destTex, 0);

	// �ȼ� ���� ���
	int pixelNum = destDesc.Width * destDesc.Height;

	// ���� �������� RGBA ä���� ������ ������ �迭 ����
	UINT* alpha = new UINT[destDesc.Width * destDesc.Height];
	UINT* red   = new UINT[destDesc.Width * destDesc.Height];
	UINT* green = new UINT[destDesc.Width * destDesc.Height];
	UINT* blue  = new UINT[destDesc.Width * destDesc.Height];

	for (int i = 0; i < pixelNum; i++)
	{
		// colors �迭�� i ��° ���ҿ��� ���� ä���� ��Ʈ�� �����Ͽ� �迭�� ����
		alpha[i] = (colors[i] & 0xFF000000);
		red[i]   = (colors[i] & 0x00FF0000);
		green[i] = (colors[i] & 0x0000FF00);
		blue[i]  = (colors[i] & 0x000000FF);

		// �ϴܿ� ����
		red[i]  = colors[i] >> 16;
		blue[i] = colors[i] << 16;

		// ��� �迭�� i��° ���Ҹ� or �����Ͽ� colors �迭�� �ٽ� ����
		colors[i] = alpha[i] | red[i] | green[i] | blue[i];
	}

	// pixels ���Ϳ� colors �迭�� �����͸� �Ҵ�
	pixels->assign(&colors[0], &colors[destDesc.Width * destDesc.Height - 1]);

	SAFE_DELETE_ARRAY(colors);
	SAFE_RELEASE(destTex);
}

void Textures::Delete()
{
	for (TextureDesc desc : descs)
		SAFE_RELEASE(desc.srv);
}

// texture ��ü�� �̹��� ���Ϸκ��� �ؽ�ó �����Ϳ� ���̴� ���ҽ� �並 ������ �ȴ�
void Textures::Load(Texture2D* texture)
{
	HRESULT hr;
	TexMetadata metaData;

	// texture ��ü�� filePath �Ӽ����� �̹��� ������ Ȯ���ڸ� ���´�
	wstring ext = Path::GetExtension(texture->filePath);
	if (ext == L"tga")
	{
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		CHECK(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, metaData);
		CHECK(hr);
	}
	else
	{
		hr = GetMetadataFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, metaData);
		CHECK(hr);
	}

	// ��Ÿ �����Ϳ��� �ʺ�� ���̸� ����
	UINT width = metaData.width;
	UINT height = metaData.height;

	TextureDesc desc;
	desc.filePath = texture->filePath;	// ����ü�� �ؽ�ó ��� ����
	desc.width = width;					// ����ü�� �ؽ�ó �ʺ� ����
	desc.height = height;				// ����ü�� �ؽ�ó ���� ����

	TextureDesc exist;
	bool bExist = false;				// �̹� �����ϴ��� �˻��ϴ� �뵵
	for (TextureDesc temp : descs)		// descs�� �ִ� ��� TextureDesc ����ü�� ���� �ݺ�
	{
		if (desc == temp)				// ���� �ؽ�ó�� ���� �ؽ�ó�� �����ϸ�
		{
			bExist = true;
			exist = temp;

			break;
		}
	}

	// �ؽ�ó�� �̹� �����Ѵٸ�
	if (bExist == true)
		texture->srv = exist.srv;	// texture��ü srv �Ӽ��� exist ����ü�� srv �Ӽ��� �Ҵ�
	// �������� �ʴ´ٸ�
	else
	{
		// �̹��� ���Ϸκ��� �ؽ�ó �����͸� �а� ���� ���� ���
		ScratchImage image;

		// Ȯ���� �˻� �� Ȯ���ڿ� �´� �Լ��� ȣ���Ͽ� �̹��� ������ �а� image ��ü�� ����
		if (ext == L"tga")
		{
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			CHECK(hr);
		}
		else if (ext == L"dds")
		{
			hr = LoadFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}
		else
		{
			hr = LoadFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}

		ID3D11ShaderResourceView* srv = nullptr;
		// image ��ü�κ��� ���̴� ���ҽ� �並 �����ϰ� srv �����Ϳ� �Ҵ�
		hr = CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), metaData, &srv);
		CHECK(hr);

		desc.srv = srv;
		texture->srv = srv;
		texture->metaData = metaData;

		descs.push_back(desc);
	}
}

/*
DirectXTex
- �ؽ�ó ó�� ���̺귯��
- DDS ������ �б�, ����, ������¡, ���� ��ȯ, ���θ� ���� �� ���� �ؽ�ó ������ ó�� �۾��� ����

Metadata
- �ʺ�, ����, ����, �迭 ũ��, ���θ� �� �� ���İ� ���� ������ ����
*/