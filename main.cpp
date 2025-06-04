#include <Windows.h>

// WinMain: program entry
int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	//_In_opt_ HINSTANCE hPrevInstance,
	_In_opt_ HINSTANCE,	// keep type only to remove the warning
	_In_ LPSTR lpCmdLine, 
	_In_ int nCmdShow)
{
	int result = MessageBox(
		nullptr,	// for owner window, nullptr means no owner
		"Hello",	// message text
		"World",	// title text
		MB_ABORTRETRYIGNORE	// button
	);

	switch (result)
	{
	case IDABORT:
		MessageBox(nullptr, "You pressed Abort", "Info", MB_OK);
		break;
	case IDRETRY:
		MessageBox(nullptr, "You pressed Retry", "Info", MB_OK);
		break;
	case IDIGNORE:
		MessageBox(nullptr, "You pressed Ignore", "Info", MB_OK);
		break;
	default:
		break;
	}

	return 0;
}