#pragma once

class Rect
{
public:
    Rect(Vector3 position, Vector3 size, float rotation);
    ~Rect();

    void Update();
    void Render();

    void GUI();
    
    void SetPosition(Vector3 position) { this->position = position; }
    void Setsize(Vector3 size) { this->size = size; }
    void SetRotation(float rotation) { this->rotation = rotation; }
    void Move();
    
    Vector3 GetPosition() { return position; }
    Vector3 Getsize() { return size; }
    float GetRotation() { return rotation; }
    void UpdateColor();
    string MakeLabel(string preFix);

    void UpdateWorld();

    void SetColor(Color color);
    BoundingBox* GetCollision() { return collision; }

    

private:

    vector<VertexColor> vertices;
    VertexBuffer* vb = nullptr;

    vector<UINT> indices;
    IndexBuffer* ib = nullptr;

    InputLayout* il = nullptr;

    VertexShader* vs = nullptr;
    PixelShader* ps = nullptr;

    D3DXMATRIX world;
    D3DXMATRIX S, R, T;

    Vector3 position;
    Vector3 size;
    float rotation;

    Color color = Color(1, 0, 0, 1);

    WorldBuffer* wb = nullptr;

    RectEdge* edge = nullptr;
    BoundingBox* collision = nullptr;

    Vector3 verticesPosition[4];
    bool moveD = false;
    bool moveR = false;
};