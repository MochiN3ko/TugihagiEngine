#include"BasicShaderHeader.hlsli"

[maxvertexcount(3)]
void main(
	triangle VSOutput input[3] : SV_POSITION, 
	inout TriangleStream< GSOutput > output
)
{
	for (uint i = 0; i < 3; i++)
	{
		GSOutput element;
		element.svpos = input[i].svpos;// +float4(input[i].normal.xyz, 0) * 2;
		element.normal = input[i].normal;
		element.uv = input[i].uv;
		output.Append(element);
	}
}