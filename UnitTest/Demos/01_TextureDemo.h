#pragma once

#include "Geomatries/TextureRect.h"

class TextureDemo : public IObject
{
public:
    // IObject��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Destroy() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUI() override;

private:
    class TextureRect* tr = nullptr;
    bool jump = false;
    float gravity = 0.0f;
};