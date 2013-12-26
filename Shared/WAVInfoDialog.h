#pragma once

BOOL CALLBACK FileInfoDialogProcedureA(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
    
class CWAVInfoDialog
{
public:

    CWAVInfoDialog();
    ~CWAVInfoDialog();

    long ShowWAVInfoDialog(const str_utfn * pFilename, HINSTANCE hInstance, const str_utfn * lpTemplateName, HWND hWndParent);

private:

    static LRESULT CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
    long InitDialog(HWND hDlg);
    TCHAR m_cFileName[MAX_PATH];
};
