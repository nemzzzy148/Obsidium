import Bindless;

struct VertexInput {
    float2 position;
    float2 uv;
};

struct Parameters {
    float textureBrightness;
    float2 textureOffset;
    SamplerHandle sampler;
    Texture2DHandle texture;
};
ConstantBuffer<Parameters> param;

struct VertexOutput {
    float4 position : SV_Position;
    float2 uv;
};

[shader("vertex")]
VertexOutput vertMain(VertexInput input) {
    VertexOutput output;
    output.position = float4(input.position, 0.0, 1.0);
    output.uv = input.uv;
    return output;
}

[shader("fragment")]
float4 fragMain(VertexOutput output) : SV_Target {
    return sample(param.texture, param.sampler, output.uv + param.textureOffset) * param.textureBrightness;
}