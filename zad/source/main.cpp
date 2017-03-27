#include<Windows.h>
#include<stdio.h>
#include "res.h"
#include <cstdlib>

bool isGameOnn = true;
bool isFirstPlayer = true;
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];


INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_COMMAND:
    
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:
      case IDC_BUTTON2:
      case IDC_BUTTON3:
      case IDC_BUTTON4:
      case IDC_BUTTON5:
      case IDC_BUTTON6:
      case IDC_BUTTON7:
      case IDC_BUTTON8:
      case IDC_BUTTON9:
      { 
        if (isGameOnn == true) 
      {
       if (isFirstPlayer == true)
       {
        HWND hwndButton = (HWND)lParam;
        if (GetWindowTextLength(hwndButton) == 0)
        {
          CHAR szText[500];
          wsprintf(szText, "X");
          SetWindowText(hwndButton, szText);
          isFirstPlayer = false;
          CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
        }
      }
      else
      {
        HWND hwndButton = (HWND)lParam;
        if (GetWindowTextLength(hwndButton) == 0)
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton, szText);
          isFirstPlayer = true;
          CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
        }
      }
      
      }
        return TRUE;
      }
      case IDC_BUTTON10:
        isGameOnn = true;
        CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
        isFirstPlayer = true;
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 4; j++) {
            isFieldOccupiedByFirstPlayer[i][j] = false;
            isFieldOccupiedBySecondPlayer[i][j] = false;
          }
        }
        CHAR szText[500];
        HDC hdc = GetDC(hwndDlg);
        //LineTo
        //MoveToEx
        //Rectangle
        //TextOut
        //GetPixel
        //SetPixel
        HPEN hMyPen=CreatePen(PS_SOLID,2,RGB(255,255,0));
        SelectObject(hdc,hMyPen);
        MoveToEx(hdc, 80, 100, NULL);
        LineTo(hdc,300,100);
        MoveToEx(hdc, 80, 160, NULL);
        LineTo(hdc, 300, 160);
        MoveToEx(hdc, 160, 40, NULL);
        LineTo(hdc, 160, 220);
        MoveToEx(hdc, 220, 40, NULL);
        LineTo(hdc, 220, 220);
        //DeleteObject(hMyPen);
        TextOut(hdc,0,0,szText,strlen(szText));
        ReleaseDC(hwndDlg, hdc);
        for (int i = 0; i < 9; i++) 
        {
          HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1 + i);
          CHAR szText[500];
          wsprintf(szText, "");
          SetWindowText(hwndButton, szText);



        }
        return TRUE;
      }
        /*
      case IDC_BUTTON1:
        liczba_prob++;
        CHAR Text[30];

        HWND hwndEditBox = GetDlgItem(hwndDig, IDC_EDIT1), hwndStatic1 = GetDlgItem(hwndDig, IDC_STATIC1), hwndStatic2 = GetDlgItem(hwndDig, IDC_STATIC2);
        int iTextLength = GetWindowTextLength(hwndEditBox);
        liczba_podana = atoi(szText);
        if (iTextLength > 0 && iTextLength < 3 && liczba_podana > 0 && liczba_podana < 41)
        {
          if (liczba_wylosowana == liczba_podana)
          {
            wsprintf(Text, "Wygra³eœ w %d kroku", liczba_prob);
            SetWindowText(hwndStatic1, Text);
            SetWindowText(hwndStatic2, "Gratulacje !!!!! Aby zagraæ ponownie wpisz liczbê i wciœnij Zagraj");
            liczba_wylosowana = (std::rand() % 40) + 1;
            liczba_prob = 0;
          }
          else
          {
            if (liczba_podana > liczba_wylosowana) {
              SetWindowText(hwndStatic1, "Wylosowana liczba jest mniejsza");
              wsprintf(Text, "Krok: %d ", liczba_prob);
              SetWindowText(hwndStatic2, Text);
            }
            else {
              SetWindowText(hwndStatic1, "Wylosowana liczba jest wiêksza");
              wsprintf(Text, "Krok: %d", liczba_prob);
              SetWindowText(hwndStatic2, Text);
            }
          }
        }
        else 
        {
          SetWindowText(hwndStatic1, "Niepoprawne dane wpisz liczbê z zakresu 1-40");
          liczba_prob--;
        }
        return TRUE;
      } */
      return FALSE;

    }


    return FALSE;

    case WM_LBUTTONDOWN:

      if (isGameOnn == true)
      {
        HDC hdc = GetDC(hwndDlg);
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        if ((x > 80 && x < 300) && (y > 40 && y < 220)) {
          int FieldX = ((x - 80) / 60);
          int FieldY = ((y - 40) / 60);

          if (isFieldOccupiedByFirstPlayer[FieldX][FieldY] == false && isFieldOccupiedBySecondPlayer[FieldX][FieldY] == false)
          {

            x = ((x - 80) / 60) * 60 + 110;
            y = ((y - 40) / 60) * 60 + 110;

            if (isFirstPlayer == true)
            {
              MoveToEx(hdc, x - 10, y - 10, NULL);
              LineTo(hdc, x + 10, y + 10);
              MoveToEx(hdc, x - 10, y + 10, NULL);
              LineTo(hdc, x + 10, y - 10);
              isFieldOccupiedByFirstPlayer[FieldX][FieldY] = true;
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);

            }
            else
            {
              MoveToEx(hdc, x - 10, y - 10, NULL);
              LineTo(hdc, x - 10, y + 10);
              LineTo(hdc, x - 10, y - 10);
              LineTo(hdc, x + 10, y - 10);
              LineTo(hdc, x + 10, y + 10);
              isFieldOccupiedBySecondPlayer[FieldX][FieldY] = true;
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
            }
            ReleaseDC(hwndDlg, hdc);
            isFirstPlayer = !isFirstPlayer;
          }
        }
      }
      return TRUE;
  //  case WM_PAINT:
  //    HDC hdc = GetDC(hwndDlg);

   //   ReleaseDC(hwndDlg, hdc);
   //   return TRUE;


  case WM_CLOSE:
    DestroyWindow(hwndDlg);
    PostQuitMessage(0);
    return TRUE;
  }
  return FALSE;
}


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, PSTR szCmdLIne, int iCmdShow)
{

  HWND hwndMainWindow = CreateDialog(hinstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  MSG msg = {};
  CheckRadioButton(hwndMainWindow, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
