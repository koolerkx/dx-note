#include "texture.h";

#include "direct3d.h"
#include "DirectXTex.h"
using namespace DirectX;
#include <string>;

static constexpr int TEXTURE_MAX = 256;	///< �ő�Ǘ���

// ���ӁI�������ŊO������ݒ肳�����́BRelease�s�v�B
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;

/**
* @struct Texture
* @brief Texture ���Ǘ��������
*/
struct Texture {
	std::wstring filename;
	ID3D11ShaderResourceView* pTexture;
	unsigned int width;
	unsigned int height;
};

static Texture g_Textures[TEXTURE_MAX]{};
static unsigned int g_SetTextureIndex = -1;

/**
* @pre Direct3D_Initialize() Shader_Initialize() �̌�Ŏg�� 
*/
void Texture_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// �O�̂��߁A�S������������
	for (Texture& t : g_Textures) {
		t.pTexture = nullptr;
	}

	g_SetTextureIndex = -1;

	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̕ۑ�
	g_pDevice = pDevice;
	g_pContext = pContext;
}

void Texture_Finalize(void)
{
	Texture_AllRelease();
}

int Texture_Load(const wchar_t* pFilename)
{
	// ���łɓǂݍ��񂾃t�@�C���͓ǂݍ��܂Ȃ�
	for (int i = 0; i < TEXTURE_MAX; i++) {
		if (g_Textures[i].filename == pFilename) {
			return i;
		}
	}
	
	// �󂢂Ă���Ǘ��̈��T��
	for (int i = 0; i < TEXTURE_MAX; i++) {
		if (g_Textures[i].pTexture) continue;	// �g�p���Ȃ玟�̃X���b�g��T��

		// �e�N�X�`���̓ǂݍ���
		TexMetadata metadata;
		ScratchImage image;

		HRESULT hr = LoadFromWICFile(pFilename, WIC_FLAGS_NONE, &metadata, image);
		if (FAILED(hr)) {
			MessageBoxW(nullptr, L"�e�N�X�`���̏������Ɏ��s���܂���", pFilename, MB_OK);
			return -1;
		}

		g_Textures[i].filename = pFilename;
		g_Textures[i].height = metadata.width;
		g_Textures[i].height = metadata.height;
		hr = CreateShaderResourceView(
			g_pDevice,
			image.GetImages(),
			image.GetImageCount(),
			metadata,
			&g_Textures[i].pTexture
		);

		return i;
	}

	return -1;
}

void Texture_AllRelease()
{
	for (Texture& t : g_Textures) {
		t.filename.clear();
		SAFE_RELEASE(t.pTexture);
	}
}

void Texture_SetTexture(int texid)
{
	if (texid < 0) return;
	if (g_SetTextureIndex == texid) return;	// ���łɁAShaderResources�ɐݒ肵������

	g_SetTextureIndex = texid;

	// �e�N�X�`���ݒ�
	g_pContext->PSSetShaderResources(0, 1, &g_Textures[texid].pTexture);
}

unsigned int Texture_Width(int texid)
{
	if (texid < 0) return -1;

	return g_Textures[texid].width;
}

unsigned int Texture_Height(int texid)
{
	if (texid < 0) return -1;

	return g_Textures[texid].height;
}
