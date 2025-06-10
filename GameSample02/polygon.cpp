/*==============================================================================

   �|���S���`�� [polygon.cpp]
														 Author : Youhei Sato
														 Date   : 2025/05/15
--------------------------------------------------------------------------------

==============================================================================*/
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "shader.h"
#include "debug_ostream.h"


static constexpr int NUM_VERTEX = 12; // ���_��


static ID3D11Buffer* g_pVertexBuffer = nullptr; // ���_�o�b�t�@

// ���ӁI�������ŊO������ݒ肳�����́BRelease�s�v�B
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;


// ���_�\����
struct Vertex
{
	XMFLOAT3 position; // ���_���W
};


void Polygon_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̃`�F�b�N
	if (!pDevice || !pContext) {
		hal::dout << "Polygon_Initialize() : �^����ꂽ�f�o�C�X���R���e�L�X�g���s���ł�" << std::endl;
		return;
	}

	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̕ۑ�
	g_pDevice = pDevice;
	g_pContext = pContext;

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	g_pDevice->CreateBuffer(&bd, NULL, &g_pVertexBuffer);
}

void Polygon_Finalize(void)
{
	SAFE_RELEASE(g_pVertexBuffer);
}

void Polygon_Draw(void)
{
	// �V�F�[�_�[��`��p�C�v���C���ɐݒ�
	Shader_Begin();

	// ���_�o�b�t�@�����b�N����
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾
	Vertex* v = (Vertex*)msr.pData;

	// ���_������������
	const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();
	const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();

	// ��ʂ̍��ォ��E���Ɍ�����������`�悷�� -> ���v���
	v[0].position = { 0.1f * SCREEN_WIDTH, 0.1f * SCREEN_HEIGHT, 0.0f };	// LT
	v[1].position = { 0.2f * SCREEN_WIDTH, 0.1f * SCREEN_HEIGHT, 0.0f };	// RT
	v[2].position = { 0.15f * SCREEN_WIDTH, 0.2f * SCREEN_HEIGHT, 0.0f };	// LB
	v[3].position = { 0.2f * SCREEN_WIDTH, 0.1f * SCREEN_HEIGHT, 0.0f };	// RT
	v[4].position = { 0.25f * SCREEN_WIDTH, 0.2f * SCREEN_HEIGHT, 0.0f };	// RB
	v[5].position = { 0.15f * SCREEN_WIDTH, 0.2f * SCREEN_HEIGHT, 0.0f };	// LB

	v[6].position = { 0.7f * SCREEN_WIDTH, 0.7f * SCREEN_HEIGHT, 0.0f };	// LT
	v[7].position = { 0.8f * SCREEN_WIDTH, 0.7f * SCREEN_HEIGHT, 0.0f };	// RT
	v[8].position = { 0.75f * SCREEN_WIDTH, 0.8f * SCREEN_HEIGHT, 0.0f };	// LB
	v[9].position = { 0.8f * SCREEN_WIDTH, 0.7f * SCREEN_HEIGHT, 0.0f };	// RT
	v[10].position = { 0.85f * SCREEN_WIDTH, 0.8f * SCREEN_HEIGHT, 0.0f };	// RB
	v[11].position = { 0.75f * SCREEN_WIDTH, 0.8f * SCREEN_HEIGHT, 0.0f };	// LB
	
	// ���_�o�b�t�@�̃��b�N������
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// ���_�V�F�[�_�[�ɕϊ��s���ݒ�
	Shader_SetMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));

	// �v���~�e�B�u�g�|���W�ݒ�
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// �|���S���`�施�ߔ��s
	g_pContext->Draw(NUM_VERTEX, 0);
}
