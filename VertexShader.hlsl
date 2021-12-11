struct VSOut {
	float3 color : COLOR;
	float4 pos : SV_POSITION;
};

VSOut main(float2 pos : POSITION, float3 color : COLOR)
{
	VSOut vso = {
		color,
		float4(pos, 0.0f, 1.0f),
	};

	return vso;
}