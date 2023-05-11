#pragma once
#include "Util.h";
#define MCMD_FILE							900
#define MCMD_FILE_OPEN						901
#define MCMD_FILE_SAVE						902
#define MCMD_FILE_EXIT						903
#define MCMD_FILE_ABOUT						904

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

class Menu {
private:
	std::map<const wchar_t*, int> _cmds;

public:
	HMENU hMenu = nullptr;

	inline Menu() : hMenu(CreateMenu()) { };
	
	void addItem(const wchar_t* caption, int pos, int cmdId, Menu* subMenu = nullptr);
	
	void setItemState(int cmdId, int fState, bool checked);
	
	void removeItemByCmd(int cmdId);
	
	inline static void update(HWND hWnd) { DrawMenuBar(hWnd); }
	
	inline ~Menu() { if (hMenu) { DestroyMenu(hMenu); } }

	bool _onWin32Command(HINSTANCE hInst, HWND hWnd, int cmdId);

};


