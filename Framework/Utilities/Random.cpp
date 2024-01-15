#include "Framework.h"
#include "Random.h"

int Random::GetRandomInt(int minValue, int maxValue)
{
	// random_device : ���α׷��Ӱ� ����Ұ��� �������� ������ �������� ����� �ڵ����� �Ҹ��Ѵ�
	// ����, random_device �� ȣ���� �� ���� �ٸ� �������� ���.

	random_device randDevice; // ��Ű srand

	//	uniform_int_distribution<�ڷ���> ������(�ּҰ�,�ִ밪) : �̾Ƴ� �������� �ڷ���,������ ���� ����
	//  uniform_int �� ���� �۵������ �������� ������ ������ ������
	// () �ȿ� �ۼ��� �ּҰ��� �ִ밪�� �����ϴ� ������ ���� ����Ѵ�.
	// Ex) intRand(0, 200); �ϰ�� 0 ~ 200 ���� �� ���ڰ� ���´�.

	uniform_int_distribution<int> intRand(minValue, maxValue);
	
	// �������� ����ϱ� ���ؼ��� unoform�� rand_device�� �����Ͽ� ��µ� �����͸� ������ �־�����Ѵ�.
	// �̶� ������ �־��ֱ� �������� ������ �����ͷν� �νĵ��� �ʱ� ������ �ش� �����͸� ���̷�Ʈ�� ����,������ ������ �߻��Ҽ��ִ�.
	// �߰��� intRand(randDevice)�� �Ȱ��� ������ �����͸� ������ ȣ���� ������ ����־ �Ź� �ٸ� ������� �����Ͱ� ����.

	int aValue = intRand(randDevice);

	return aValue;
}

float Random::GetRandomFloat(float minValue, float maxValue)
{
	random_device randDevice;

	// �Ǽ����� �������� ��� ���ؼ��� uniform_real ������Ŭ������ ����ϸ� �ȴ�.
	// ���ǻ����� �Ǽ����� ������ �Ϲ����� �������� �޸� ǥ���Ҽ��ִ� �ڸ����� ��簪�� ������ ������ ���� ������ �������� ��� �ſ� ��ư� �ſ� ���� ������ �����ؾ� �ϱ⿡ ��õ���� ����
	// Ex) floatRand(0.0f,1.0f)
	//0.0000000 ~ 1.0000000 ������ �����̱� ����
	uniform_real_distribution<float> floatRand(minValue, maxValue);

	float aValue = floatRand(randDevice);
	return aValue;
}
