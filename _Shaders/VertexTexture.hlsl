
// VertexInput ����ü ����
struct VertexInput
{
	// position�̶�� ������ POSITION0 ��Ʈ���� ��ġ�� ���� ������ �����Ѵ�.
	float4 position : POSITION0;	// ���� ��ġ
	float2 uv	: TEXCOORD0;		// uv��ǥ
};

// PixelInput ����ü ����
struct PixelInput
{
	// SV�� �ý��� ���� ����ƽ ��
	float4 position : SV_POSITION0; // ���� ��ġ
	float2 uv : TEXCOORD0;			// uv��ǥ
};

// ��� ���� �������� b0�� �Ҵ�� ���� ����� �����ϴ� ��� ����
cbuffer WorldBuffer : register(b0)
{
	matrix _world;
};

// ��� ���� �������� b1�� �Ҵ�� �� ��İ�, �������� ����� �����ϴ� ��� ����
cbuffer VPBuffer : register(b1)
{
	matrix _view;
	matrix _projection;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;
	
	output.position = mul(input.position, _world);		// ������ ��ġ�� ���� ����� ����
	output.position = mul(output.position, _view);		// ����� �� ����� ����
	output.position = mul(output.position, _projection);// ����� �������� ����� ����
	// �� ������� ����� �����ָ� �۷ι� �������� ��ǥ�� �˾Ƴ��� �ִ�.
	
	output.uv = input.uv;
	return output;
}

// �ؽ�ó �����͸� ����, �ؽ�ó ���� 0���� �Ҵ�
Texture2D _sourceTex : register(t0);

// ���ø� ����� ����, ���÷� ���� 0���� �Ҵ�
SamplerState _samp : register(s0);

float4 PS(PixelInput input)	: SV_Target
{
	float4 color = _sourceTex.Sample(_samp, (float2)input.uv);
	
	return color;
}

/*
Semantic : ����ƽ
- HLSL ���̴����� �������� �ǹ̸� �����ϴ� �� ���Ǵ� ����
- ���̴��� �Է� �����Ϳ� ��� �����͸� �ùٸ��� �ؼ��ϰ� ó���� �� �ֵ��� ���ش�.
- ���� �̸� �ڿ� : �� �Ա� ����
- �ý��� �� ����ƽ�� SV_ ���λ�� �����ϸ�, Direct3D���� ���ǵ� Ư���� �ǹ̸� ���Ѵ�.
- �ý��� �� ����ƽ�� ���̴� �������� ���� �����͸� �����ϴµ� ���ȴ�.
(VS���� output�� ���� PixelInput���� PS���� SV_Target���� ��ƿ� ����ߴ�.)

slot
- GPU���� ����ϴ� ��� ����, �ؽ�ó, ���÷� ���� �ڿ����� �ĺ��ϴ� �ε���
- �� ������ ������ ��ȣ�� ������, �ش� �ڿ��� ������ ���ҿ� ���� �ٸ��� �Ҵ��Ѵ�.
- register��� Ű���带 ����Ͽ� ����
- �� �ڿ��� � ���Կ� �Ҵ� �� �������� ��������� ������ �� �ִ�.
- �ֿ� ����
	1) ��� ���� ����
	- ��� �����͸� �����ϴµ� ���Ǹ�, VS�� PS���� ������ �� �ִ�.
	- �� ���� ������ register(b#)�� ����Ͽ� ����

	2) �ؽ��� ����
	- �̹��� �����͸� �����ϴµ� ���
	- �ؽ�ó ���� ������ register(t#)�� ����Ͽ� ����

	3) ���÷� ����
	- �ý�ó�� ���ø� �ϴµ� ���
	- ���ø��� �׸��� ��� �ҷ��� ������ �����θ� �����ص� ����ϴ�.
	- ���÷� ������ register(s#)�� ����Ͽ� ����

cbuffer = Constant Buffer : ��� ����
- ���̴����� ����ϴ� ���� ������ �����ϴµ� ���
- �� ��� ���� �������Ϳ��� �� ���� ��� ���۸� �Ҵ��� �� �ִ�.
- ��� ���� ���ο��� ���� ���� ������ �����ϴ°��� �����ϴ�.

Sampler : ���÷�
- �ؽ�ó���� �ʼ� ���� �������� ����� �����ϴ� ��ü
- �ؽ�ó ���ø��� �ؽ�ó �̹����� ���� �ؼ� ���� ����ϴ� �۾��̴�.
(�ؼ� : �ؽ�ó�� �ȼ� ��)
*/