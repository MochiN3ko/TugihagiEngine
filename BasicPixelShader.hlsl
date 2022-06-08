#include "BasicShaderHeader.hlsli"
Texture2D<float4> tex : register(t0); // 0 番スロットに設定されたテクスチャ
SamplerState smp : register(s0); // 0 番スロットに設定されたサンプラー

//float4 PSmain(VSOutput input) : SV_TARGET{
float4 PSmain(GSOutput input) :SV_TARGET{

	float3 light = normalize(float3(0, -1, 2)); // 右下奥 向きのライト
	float diffuse = saturate(dot(-light, input.normal)); // diffuse を[0,1]の範囲に Clamp する
	float brightness = diffuse + 0.3f; // アンビエント項を 0.3 として計算
	float4 texcolor = tex.Sample(smp, input.uv)*color;
	//return float4(input.svpos.w / input.svpos.xyz, 1);
	return float4(texcolor.rgb * brightness+float3(0,0,0), texcolor.a);

}
