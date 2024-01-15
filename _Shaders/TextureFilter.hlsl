
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

// VS ���� ����� cbuffer
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

// PS ���� ����� cbuffer
cbuffer ShadedBuffer : register(b0)
{
    int _selection;
    int _blurCount;
    float2 _textureSize;
};

// �ؽ�ó �����͸� ����, �ؽ�ó ���� 0���� �Ҵ�
Texture2D _sourceTex : register(t0);

// ���ø� ����� ����, ���÷� ���� 0���� �Ҵ�
SamplerState _samp : register(s0);

float4 PS(PixelInput input)	: SV_Target
{
	float4 color = _sourceTex.Sample(_samp, (float2)input.uv);
    float4 resultColor = 0;
	
    if (_selection == 1)
    {
        return color;
    }
    else if (_selection == 2)
    {
		// Gray
        float3 gray = dot(color.rgb, float3(0.299f, 0.587f, 0.114f));
        resultColor = float4(gray, color.a);
    }
    else if (_selection == 3)
    {
		// Sepia
        float3 sepia = dot(color.rgb, float3(0.393f, 0.769f, 0.189f));
        sepia.r += 0.2f;
        sepia.g += 0.1f;
        resultColor = float4(sepia, color.a);
    }
    else if (_selection == 4)
    {
		// Negative
        float3 negative = 1 - abs(color.rgb);
        resultColor = float4(negative, color.a);

    }
    else if (_selection == 5)
    {
        // Posterize
        float3 value = float3(4.0f, 4.0f, 4.0f);
        // ���� �������� ���� ������
        float3 posterize = round(color.rgb * value) / value;
        resultColor = float4(posterize, color.a);
    }
    else if (_selection == 6)
    {
        float2 arr[8] =
        {
            float2(-1, +1), float2(0, +1), float2(+1, +1),
            float2(-1, 0),   /*���� ����*/  float2(+1, 0),
            float2(-1, -1), float2(0, -1), float2(+1, -1),
        };
        
        // �� ī��Ʈ ��ŭ �ݺ�
        for (int blur = 1; blur < _blurCount; blur++)
        {
            // �ֺ� �����鿡 ���� �ݺ�
            for (int i = 0; i < 8; i++)
            {
                // �Է� �ؽ�ó���� ���ø��� �ֺ� �ȼ����� ������� ��ġ�� ���
                float x = arr[i].x * (float) blur / _textureSize.x;
                float y = arr[i].y * (float) blur / _textureSize.y;

                //�ֺ� �ȼ���  uv �� ���� �� uv�� ���
                float2 uv = input.uv + float2(x, y);
                
                // �ֺ� �ȼ��� ���� ���Ե� ���� color �� ����
                color += _sourceTex.Sample(_samp, uv);
            }
        }
        int blurInterations = _blurCount - 1;
        int offsetCount = 8;
        int totalSamples = blurInterations * offsetCount + 1;
        
        return color /= totalSamples;
    }
    else
    {
        resultColor = color;
    }
    return resultColor;
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