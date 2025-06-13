#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "game_window.h"
#include "direct3d.h"
#include "sprite.h"
#include "shader.h"
#include "texture.h"

// ���C��
int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE,
	_In_ LPSTR,
	_In_ int nCmdShow)
{
	static_cast<void>(CoInitializeEx(nullptr, COINIT_MULTITHREADED));

	HWND hWnd = GameWindow_Create(hInstance);

	Direct3D_Initialize(hWnd);
	Shader_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());
	Sprite_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());
	Texture_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());

	// �e�N�X�`���ǂݍ���
	int texid_knight_winter = Texture_Load(L"knight_3.png");
	int texid_knight_summer = Texture_Load(L"knight_3_summer.png");

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// �Q�[�����[�v�����b�Z�[�W���[�v
	MSG msg;

	float x = 0.0f;

	do {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) { // �E�B���h�E���b�Z�[�W�����Ă����� 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else { // �Q�[���̏��� 
			
		Direct3D_Clear();

		for (int i = 0; i < 4; i++) {
			Texture_SetTexture(texid_knight_winter);
			Sprite_Draw(x, 0.0f, 256.0f, 256.0f);

			Texture_SetTexture(texid_knight_summer);
			Sprite_Draw(x, 256.0f, 256.0f, 256.0f);

			//x += 0.3f;
		}

		Direct3D_Present();
		}
	} while (msg.message != WM_QUIT);

	Texture_Finalize();
	Sprite_Finalize();
	Shader_Finalize();
	Direct3D_Finalize();

	return (int)msg.wParam;
}
