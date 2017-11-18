//============================================================================
// SpriteShader.hlsl
//
// Vertex and pixel shader functions for sprites
//============================================================================

struct vsIN
{
	float4 Pos : POSITION;
	float2 UV : TEXCOORD;
};

struct vsOUT
{
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD;
};

cbuffer ShaderConstants : register(b0)
{
	row_major matrix matWorldViewProj;
	float brightness;
};

vsOUT VS(vsIN IN)
{
	vsOUT OUT;
	OUT.Pos = mul(IN.Pos, matWorldViewProj);
	OUT.UV = IN.UV;
	return OUT;
}


Texture2D spriteTex : register(t0);
SamplerState spriteSampler : register(s0);


float4 PS(vsOUT IN) : SV_Target
{
	float4 c = spriteTex.Sample(spriteSampler, IN.UV);
	c.rgb *= brightness;
	return c;
}
