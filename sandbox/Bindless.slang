module obsidium;

Texture2D textures[] : register(t1, space3);
SamplerState samplers[] : register(s1, space4);

public struct Texture2DHandle { public uint index; };
public struct SamplerHandle { public uint index; };

public float4 sample(Texture2DHandle texture, SamplerHandle sampler, float2 uv) {
    return textures[NonUniformResourceIndex(texture.index)]
        .Sample(samplers[NonUniformResourceIndex(sampler.index)], uv);
}



