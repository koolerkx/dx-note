/*==============================================================================

   �e�N�X�`���Ǘ� [texture.h]
														 Author : KOOLER FAN
														 Date   : 2025/06/12
--------------------------------------------------------------------------------

==============================================================================*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d11.h>

void Texture_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);

void Texture_Finalize(void);

/**
* @brief �e�N�X�`���摜�̓ǂݍ���
* @param pFilename �ǂݍ��݂����t�@�C����
* @pre Texture_Initialize()�ŏ�������
* @return �Ǘ��ԍ�
* @retval -1 �ǂݍ��߂Ȃ������ꍇ
*/
int Texture_Load(const wchar_t* pFilename);

void Texture_AllRelease();

/**
* @param texid �Ǘ��ԍ�
*/
void Texture_SetTexture(int texid);

unsigned int Texture_Width(int texid);
unsigned int Texture_Height(int texid);

#endif