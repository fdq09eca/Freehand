#include "Menu.h"
#include "Freehand.h"
#include "App.h"
#include <shobjidl.h> 
#include <windows.h>

void Menu::addItem(const wchar_t* caption, int pos, int cmdId, Menu* subMenu) {
	MENUITEMINFO s;
	s.cbSize = sizeof(s);
	s.fMask = MIIM_TYPE | MIIM_SUBMENU | MIIM_ID;
	s.wID = cmdId;
	s.hSubMenu = subMenu ? subMenu->hMenu : nullptr;
	s.fType = MFT_STRING;
	s.dwTypeData = const_cast<wchar_t*>(caption);
	s.cch = wcslen(caption);

	if (InsertMenuItem(hMenu, pos, true, &s)) {
		_cmds[caption] = cmdId;
	}
	else {
		assert(false);
		return;
	}
}

void Menu::setItemState(int cmdId, int fState, bool checked) {
	MENUITEMINFO s;
	s.cbSize = sizeof(s);
	s.fMask = MIIM_STATE;
	if (checked) {
		s.fState |= fState;
	}
	else {
		s.fState &= ~fState;
	}
	SetMenuItemInfo(hMenu, cmdId, false, &s);
}

void Menu::removeItemByCmd(int cmdId) {
	RemoveMenu(hMenu, cmdId, MF_BYCOMMAND);
}



bool Menu::_onWin32Command(HINSTANCE hInst, HWND hWnd, int cmdId)
{
	switch (cmdId)
	{
	case MCMD_FILE_OPEN: { 
#if 0
		wchar_t filenameBuff[MAX_PATH] = { 0 };
		const wchar_t* defaultFilename = L"saveApp.txt";
		swprintf(filenameBuff, MAX_PATH, defaultFilename);
		auto currentDir = my_getCurrentDirectory();
		
		OPENFILENAME s;
		my_bzero(s);
		s.lStructSize = sizeof(s);
		s.hwndOwner = hWnd;
		s.hInstance = hInst;
		s.lpstrFilter = L"Text File (*.txt)\0*.txt\0"
			L"All Files (*.*)\0*.*\0"
			L"\0";
		s.lpstrFile = filenameBuff;
		s.nMaxFile = MAX_PATH;
		s.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
		s.lpstrInitialDir = currentDir.c_str();

		bool isOpen = GetOpenFileName(&s);
		if (isOpen) {
			App::Instance()->load(s.lpstrFile);
			printf("Loaded from fp: %ws\n", s.lpstrFile);
		}
#else
//#include <shobjidl.h> 
//#include <windows.h>
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
			COINIT_DISABLE_OLE1DDE);
		if (SUCCEEDED(hr))
		{

			IFileOpenDialog* pFileOpen;

			// Create the FileOpenDialog object.
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
				IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

			if (SUCCEEDED(hr))
			{
				// Show the Open dialog box.
				hr = pFileOpen->Show(NULL);

				// Get the file name from the dialog box.
				if (SUCCEEDED(hr))
				{
					IShellItem* pItem;
					hr = pFileOpen->GetResult(&pItem);
					if (SUCCEEDED(hr))
					{
						PWSTR pszFilePath;
						hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

						// Display the file name to the user.
						if (SUCCEEDED(hr))
						{
							MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
							CoTaskMemFree(pszFilePath);
						}
						pItem->Release();
					}
				}
				pFileOpen->Release();
			}
			CoUninitialize();
		}
#endif
	} return true;
	
	case MCMD_FILE_SAVE: { 	
		wchar_t filenameBuff[MAX_PATH] = { 0 };
		const wchar_t* defaultFilename = L"saveApp.txt";
		swprintf(filenameBuff, MAX_PATH, defaultFilename);
		auto currentDir = my_getCurrentDirectory();
		
		OPENFILENAME s;
		my_bzero(s);
		s.lStructSize = sizeof(s);
		s.hwndOwner = hWnd;
		s.hInstance = hInst;
		s.lpstrFilter = L"Text File (*.txt)\0*.txt\0"
			L"All Files (*.*)\0*.*\0"
			L"\0";
		s.lpstrFile = filenameBuff;
		s.nMaxFile = MAX_PATH;
		s.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
		s.lpstrInitialDir = currentDir.c_str();

		bool isOpen = GetSaveFileName(&s);
		if (isOpen) {
			App::Instance()->save(s.lpstrFile);
			printf("Saved at fp: %ws\n", s.lpstrFile);
		}
	} return true;
	
	case MCMD_FILE_EXIT: { SendMessage(hWnd, WM_CLOSE, 0, 0); } return true;
	case MCMD_FILE_ABOUT: { DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, &About); } return true;
		
	
	}
	return false;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}