cbuffer Material {
	float3 color;
	float shininess;
};

//Texture2D tex;
//SamplerState splr;

float4 main(float3 pos : POSITION, float3 normal : NORMAL, float2 uv : UV) : SV_Target
{
	return float4(normalize(color + normal), 1.0f);
}