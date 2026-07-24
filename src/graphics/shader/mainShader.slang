struct VSInput {
    float3 position;
    float3 color;
    float2 uv;
};

struct UniformBuffer {
    float4x4 model;
    float4x4 view;
    float4x4 proj;
};
ConstantBuffer<UniformBuffer> ubo;

SamplerState sampler;

Texture2D textures[];

struct PushConstants {
    uint textureIndex;
} pc;

struct VSOutput {
    float4 position : SV_Position;
    float3 color;
    float2 uv;
};

[shader("vertex")]
VSOutput vertMain(VSInput input) {
    VSOutput output;
    output.position = mul(ubo.proj, mul(ubo.view, mul(ubo.model, float4(input.position, 1.0))));
    output.color = input.color;
    output.uv = input.uv;
    return output;
}

[shader("fragment")]
float4 fragMain(VSOutput vertIn) : SV_Target {
    return (pc.textureIndex != ~0) ? float4(vertIn.color, 1.0) * textures[pc.textureIndex].Sample(sampler, vertIn.uv) : float4(vertIn.color, 1.0);
}