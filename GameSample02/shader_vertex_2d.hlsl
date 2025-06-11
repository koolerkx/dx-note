/*==============================================================================

   2D�`��p���_�V�F�[�_�[ [shader_vertex_2d.hlsl]
														 Author : Youhei Sato
														 Date   : 2025/05/15
--------------------------------------------------------------------------------

==============================================================================*/

// �萔�o�b�t�@
float4x4 mtx;

struct VS_INPUT
{
    float4 posL : POSITION0; // ���[�J�����W 
    float4 color : COLOR0; // Color
    float2 uv : TEXCOORD0;
};
struct VS_OUTPUT
{
    float4 posH : SV_POSITION; // �ϊ��ςݍ��W 
    float4 color : COLOR0; // Color
    float2 uv : TEXCOORD0;
};

//=============================================================================
// ���_�V�F�[�_
//=============================================================================

VS_OUTPUT main(VS_INPUT vs_in)
{
    VS_OUTPUT vs_out;
    vs_out.posH = mul(vs_in.posL, mtx);
    vs_out.color = vs_in.color;
    vs_out.uv = vs_in.uv;
    return vs_out;
}
