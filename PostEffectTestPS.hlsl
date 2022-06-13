#include "PostEffectTest.hlsli"
Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
	float d = distance(drawUV, pickUV);
	return exp(-(d * d)) / (2 * sigma * sigma);
}

float WhiteNoise(float2 coord)
{
	return frac(sin(dot(coord, float2(8.7819, 3.255))) * 437.645);
}

float4 main(VSOutput input) : SV_TARGET
{
	float vertNoise = WhiteNoise(float2(floor((input.uv.x) / time) * time, time * 10));
	float horzNoise = WhiteNoise(float2(floor((input.uv.y) / 30) * 10, time * 10));
	float vertGlitchStrength = vertNoise / 20;
	float horzGlitchStrength = horzNoise / 20;
	vertGlitchStrength = vertGlitchStrength * 2.0 - 1.0;
	horzGlitchStrength = horzGlitchStrength * 2.0 - 1.0;
	float V = step(vertNoise, 10 * 2) * vertGlitchStrength;
	float H = step(horzNoise, 10) * horzGlitchStrength;

	//湾曲&ずらし
	float2 resultUv = input.uv;
	resultUv -= float2(0.5, 0.5);
	float distPower = pow(length(resultUv), dist);
	resultUv *= float2(distPower,distPower);
	resultUv += float2(0.5 , 0.5);

	float sinv = sin(resultUv.y * 2 - time * 10 * -0.1);
	float steped = 1 - step(0.99, sinv * sinv);
	float timeFrac = steped * step(0.8, frac(time * 100));
	resultUv.x += timeFrac * (V + H);

	//ノイズ
	float noise = WhiteNoise(input.uv * time * 100) - 0.6;

	float4 color = tex0.Sample(smp, resultUv);
	//ノイズ加算
	color.rgb += float3(noise * 0.5, noise * 0.5, noise * 0.5);
	//RGBずらし
	resultUv.x += rgbshift;

	color.r = tex0.Sample(smp, resultUv).r;
	return color;

	//ポストエフェクトなし
	//return tex0.Sample(smp, input.uv);

}



