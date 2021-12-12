cbuffer CBuf {
	matrix MV;
	matrix MVP;
};

struct VSOut {
	float3 worldPos : POSITION;
	float3 normal : NORMAL;
	float2 uv : UV;
	float4 pos : SV_Position;
};

VSOut main(float3 pos : POSITION, float3 n : NORMAL, float2 uv : UV) {
	VSOut vso;
	vso.worldPos = (float3)mul(float4(pos, 1.0f), MV);
	//vso.normal = mul(n, (float3x3)MV);
	vso.normal = abs(n);
	vso.pos = mul(float4(pos, 1.0f), MVP);
	vso.uv = uv;
	return vso;
}