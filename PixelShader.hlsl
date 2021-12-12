
SamplerState splr;
Texture2D tex;

cbuffer Material {
	float3 color;
	float shininess;
};


float4 main(float3 pos : POSITION, float3 normal : NORMAL, float2 uv : UV) : SV_Target
{
	float4 texColor = tex.Sample(splr, uv);
	return float4(normalize(texColor * 3u + color + normal), 1.0f);
}