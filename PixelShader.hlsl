
SamplerState splr;
Texture2D tex;

cbuffer Light
{
    float3 light_pos;
    float3 specular_color;
    float3 light_dir;
    float cut_off_angle;
    float is_active;
    float att_lin;
    float att_quad;
};

cbuffer Material 
{
    float3 color;
	float shininess;
    float kd;
    float ks;
};


cbuffer Camera
{
    float3 cam_pos;
};


float4 main(float3 pos : POSITION, float3 normal : NORMAL, float2 uv : UV) : SV_Target
{
	float4 tex_color = tex.Sample(splr, uv);
    return float4(saturate(tex_color.xyz * light_dir), 1.0f);
    //return tex_color;
    //return float4(saturate(tex_color.xyz * specular_color), 1.0f);

    //float linear_att = att_lin;
    //float quadratic_att = att_quad;

    //float3 N = normal;
    //float3 L = normalize(light_pos - pos);
    //float3 V = normalize(cam_pos  - pos);
    //float3 H = normalize(L + V);
    //float3 R = reflect(L, N);

    //if (is_active == 1.0f)
    //{
    //    float cut_off = radians(cut_off_angle);
    //    float spot_light = dot(-L, light_dir);

    //    if (spot_light > cos(cut_off))
    //    {
    //        linear_att = (1.0f - cos(cut_off)) / (spot_light - cos(cut_off));
    //        quadratic_att = pow(linear_att, 2);
    //    }
    //    else
    //    {
    //        return float4(0.0f, 0.0f, 0.0f, 0.0f);
    //    }
    //}

    //float ambient_light = 0.25f * kd;

    //float diffuse_light = kd * max(dot(N, L), 0.0f);

    //float specular_light = 0.0f;

    //if (diffuse_light > 0.0f)
    //{
    //    specular_light = ks * 1.0f * pow(max(dot(H, N), 0.0f), shininess);
    //}

    //float d = distance(pos, light_pos);
    //float attenF = 1.0f / (1.0f + d * linear_att + pow(d, 2.0f) * quadratic_att);

    //float3 phong_col = specular_color + ambient_light + attenF * (diffuse_light + specular_light);

    //return float4(saturate(phong_col * tex_color.xyz * color), 1.0f);
}