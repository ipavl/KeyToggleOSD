#include "KeyToggleOSD.h"

#include <time.h>

// Coordinates for the on-screen display
const long rectTop = 50;
const long rectLeft = rectTop;
const long rectBottom = rectTop + 75;
const long rectRight = rectLeft + 350;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow) {

	// Register the Caps Lock and Num Lock keys as hotkeys
	RegisterHotKey(NULL, VK_CAPITAL, MOD_NOREPEAT, VK_CAPITAL);
	RegisterHotKey(NULL, VK_NUMLOCK, MOD_NOREPEAT, VK_NUMLOCK);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		// Detected a hotkey key press
		if (msg.message == WM_HOTKEY) {
			switch (msg.wParam) {
			case VK_CAPITAL:
				handleHotKeyPress(msg.wParam, "Caps Lock");
				break;
			case VK_NUMLOCK:
				handleHotKeyPress(msg.wParam, "Num Lock");
				break;
			}
		}
	}

	UnregisterHotKey(NULL, VK_CAPITAL);
	UnregisterHotKey(NULL, VK_NUMLOCK);

	return 0;
}

void handleHotKeyPress(WORD key, std::string keyName) {
	// Emulate the key press since we consumed it
	emulateKeyPress(key);

	// Append the key's toggle state to the text that will be displayed
	((GetKeyState(key) & 0x0001) != 0) ? keyName += " ON" : keyName += " OFF";
	
	showOnScreenDisplay(keyName.c_str());
}

void showOnScreenDisplay(LPCTSTR text) {
	const HDC hdc = GetDC(NULL);
	const time_t messageStartTime = time(NULL);

	RECT rect = {
		rectLeft,
		rectTop,
		rectRight,
		rectBottom,
	};

	// Wait for the specified amount of time
	// TODO: Improve implementation
	while (time(NULL) < messageStartTime + messageDuration) {
		DrawText(hdc, text, strlen(text), &rect, DT_SINGLELINE | DT_NOCLIP);
	}

	// Clear the display
	InvalidateRect(NULL, &rect, TRUE);
}

void emulateKeyPress(WORD key) {
	INPUT input;
	input.type = INPUT_KEYBOARD;

	input.ki.wVk = key;
	input.ki.wScan = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;

	// Free the hotkey temporarily
	UnregisterHotKey(NULL, key);

	// Key down
	input.ki.dwFlags = 0;
	SendInput(1, &input, sizeof(INPUT));

	// Key up
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT));

	// Re-register the hotkey
	RegisterHotKey(NULL, key, MOD_NOREPEAT, key);
}
