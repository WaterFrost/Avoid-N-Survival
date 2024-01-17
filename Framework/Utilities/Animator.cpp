#include "Framework.h"
#include "Animator.h"

AnimationClip::AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, bool bReversed)
	:clipName(clipName), frameCount(frameCount), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	// �ؽ�ó�� �ʺ�� ���̸� �����ͼ� �̹����� ����
	float imageWidth  = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	// Ŭ�� ������ (�ִϸ��̼��� �׷����ִ� �ؽ�ó�� ����)
	Vector2 clipSize = endPos - startPos;

	// ������ ������ (�ִϸ��̼� �� �׸� �ϳ�)
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount;
	frameSize.y = clipSize.y;

	// �ؼ� ������ �ʺ�� ���� ��� (UV ��ǥ������ ũ�� ���)
	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	// �ؼ� ���� ��ġ
	Vector2 texelStartPos;
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	// ���� ����Ǵ� ������
	Vector2 keyframe;

	for (UINT i = 0; i < frameCount; i++) // �����ӿ� ���� �ݺ�
	{
		// Ű �������� x, y ��ǥ ���
		keyframe.x = texelStartPos.x + (texelFrameSize.x * i);
		keyframe.y = texelStartPos.y;
		// Ű �������� keyFrame ���Ϳ� �߰�
		keyFrames.push_back(keyframe);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto clip : animClips)
		SAFE_DELETE(clip.second);
}

void Animator::Update()
{
	if (deltaTime > playRate)
	{
		// ������� �ƴ� ���
		if (currentClip->bReversed == false)
		{
			currentFrameIndex++; // ������ �ε��� ����

			// ���� ������ �ε����� ������ ���� ���� ���
			if (currentFrameIndex == currentClip->frameCount)
				currentFrameIndex = 0; // ������ �ε����� 0���� ����

			// ���� �������� ������Ʈ
			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		else // ������� ���
		{
			currentFrameIndex--; // ������ �ε��� ����

			// ���� ������ �ε����� -1�� ���
			if (currentFrameIndex == -1)
				// ���� ������ �ε����� ������ �� - 1 �� ����
				currentFrameIndex = currentClip->frameCount - 1;

			// ���� �������� ������Ʈ
			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		deltaTime = 0.0f; // deltaTime�� �ʱ�ȭ
	}
	else
		deltaTime += Time::Delta(); // deltaTime�� ��� �ð��� ���Ѵ�
}

void Animator::AddAnimClip(AnimationClip* animClip)
{
	animClips.insert(make_pair(animClip->clipName, animClip));
}

void Animator::SetCurrentAnimClip(wstring clipName)
{
	// ���� Ŭ���� ����, �ִϸ��̼��� ������ ��
	if (currentClip == nullptr && CheckExist(clipName) == true)
		currentClip = animClips.find(clipName)->second; // ���� Ŭ���� clipName���� ����
	// �̹� Ŭ���� �ְ�, �ִϸ��̼��� ���� ����Ǵ� �Ͱ� ���� ��
	else if (currentClip != nullptr && currentClip->clipName == clipName)
		return;

	// Ŭ���� �����Ѵٸ�
	if (CheckExist(clipName))
	{
		// ���� Ŭ���� clipName���� ����
		currentClip = animClips.find(clipName)->second;
		deltaTime = 0.0f;

		// ������� Ȱ��ȭ �Ǿ� �ִٸ�
		if (currentClip->bReversed == true)
			// ���� ������ �ε����� ������ �� - 1�� ����
			currentFrameIndex = currentClip->frameCount - 1;
		else
			// ���� ������ �ε����� 0���� ����
			currentFrameIndex = 0;

		// ���� �������� ������Ʈ
		currentFrame = currentClip->keyFrames[currentFrameIndex];
	}
}
