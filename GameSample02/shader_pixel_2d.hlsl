/*==============================================================================

   2D�`��p�s�N�Z���V�F�[�_�[ [shader_pixel_2d.hlsl]
														 Author : Youhei Sato
														 Date   : 2025/05/15
--------------------------------------------------------------------------------

==============================================================================*/

struct PS_INPUT
{
    float4 posH : SV_POSITION;
    float4 color : COLOR0;
};

float4 main(PS_INPUT ps_in) : SV_TARGET
{
    return ps_in.color;
}
