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
	////
	float vertNoise = WhiteNoise(float2(floor((input.uv.x) / time) * time, time * 0.1));
	float horzNoise = WhiteNoise(float2(floor((input.uv.y) / time) * time, time * 0.2));
	float vertGlitchStrength = vertNoise / time;
	float horzGlitchStrength = horzNoise / time;
	vertGlitchStrength = vertGlitchStrength * 2.0 - 1.0;
	horzGlitchStrength = horzGlitchStrength * 2.0 - 1.0;
	float V = step(vertNoise, time * 2) * vertGlitchStrength;
	float H = step(horzNoise, time) * horzGlitchStrength;

	float2 samplePoint = input.uv;
	float sinv = sin(samplePoint.y * 2 - time * -0.1);
	float steped = 1 - step(0.99, sinv * sinv);
	float timeFrac = steped * step(0.8, frac(time));
	samplePoint.x += timeFrac * (V + H);


	////
	float2 resurtUV = samplePoint;
	resurtUV -= float2(0.5, 0.5);
	float distPower = pow(length(resurtUV), dist);

	resurtUV *= float2(distPower, distPower);
	resurtUV += float2(0.5, 0.5);

	float4 color = tex0.Sample(smp, resurtUV);
	resurtUV.x += rgbshift;
	color.r = tex0.Sample(smp, resurtUV).r;

	float noise = WhiteNoise(input.uv * time) - 0.5;
	color.rgb += float3(noise, noise, noise);
	
	return color;
}

