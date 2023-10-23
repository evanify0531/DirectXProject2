struct VS_INPUT
{
    float4 position : POSITION;
    float4 color : COLOR;
    //float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION; //System Value
    float4 color : COLOR;
    //float2 uv : TEXCOORD;
};

Texture2D texture0 : register(t0);
//Texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);

cbuffer TransformData : register(b0)
{
    row_major matrix matWorld;
    row_major matrix matView;
    row_major matrix matProjection;
}
    
//Input Assembler->Vertex Shader -> Rasterizer -> Pixel Shader -> Output Merger
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    
    //wvp
    float4 position = mul(input.position, matWorld);
    position = mul(position, matView);
    position = mul(position, matProjection);
    
    output.position = position;
    output.color = input.color;
    //output.uv = input.uv;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    //float4 color = texture0.Sample(sampler0, input.uv);
    //return color;
    
    return input.color;
}