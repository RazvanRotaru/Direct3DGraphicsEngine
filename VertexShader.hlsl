struct VSOut {
	float3 color : COLOR;
	float4 pos : SV_POSITION;
};

cbuffer CBuff {
	matrix transform;
};

VSOut main(float3 pos : POSITION, float3 color : COLOR)
{
	VSOut vso = {
		color,
		mul(float4(pos, 1.0f), transform),
	};

	return vso;
}