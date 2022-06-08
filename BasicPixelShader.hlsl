#include "BasicShaderHeader.hlsli"
Texture2D<float4> tex : register(t0); // 0 �ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); // 0 �ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

//float4 PSmain(VSOutput input) : SV_TARGET{
float4 PSmain(GSOutput input) :SV_TARGET{

	float3 light = normalize(float3(0, -1, 2)); // �E���� �����̃��C�g
	float diffuse = saturate(dot(-light, input.normal)); // diffuse ��[0,1]�͈̔͂� Clamp ����
	float brightness = diffuse + 0.3f; // �A���r�G���g���� 0.3 �Ƃ��Čv�Z
	float4 texcolor = tex.Sample(smp, input.uv)*color;
	//return float4(input.svpos.w / input.svpos.xyz, 1);
	return float4(texcolor.rgb * brightness+float3(0,0,0), texcolor.a);

}
