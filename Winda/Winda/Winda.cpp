// Project1.cpp : definiuje punkt wejścia dla aplikacji
//
#include "stdafx.h"
#include <vector>
#include "Winda.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <objidl.h>
#include <gdiplus.h>
#include <iomanip>
#include <queue>
#pragma comment (lib,"Gdiplus.lib")
#define MAX_LOADSTRING 100
using namespace Gdiplus;
int liczenie_23;
// Zmienne globalne:
HINSTANCE hInst;                                // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];            // nazwa klasy okna głównego
												// Przekaż dalej deklaracje funkcji dołączonych w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//guziki
int ilosc_linijek_w_pliku;

#define ID_P12 102
#define ID_P13 103
#define ID_P14 107


#define ID_P21 201
#define ID_P23 202
#define ID_P24 203

#define ID_P31 301
#define ID_P32 302
#define ID_P34 303

#define ID_P41 401
#define ID_P42 403
#define ID_P43 402

#define TMR_ruch_ludzika 500
#define TMR_ruch_windy 503

int masa_MAX_windy =500;
int wartosci_przesuniecia;

int ilosc_linijek;  //ilosc linijek w tekscie    //robie na zmiennych globalnych bo nie wiem jak dac przez referencje
float obroty_roll;
float obroty_pitch;
float obroty_yaw;
int opoznienie_licznika = 2;
int value;
int value1;

int masa_calkowita;            //wszystkie te zmienne sa potrzebe do priorytezacji 
int masa_czlowieka;
int pietro_terazniejsze;  //to pietro na ktore teraz jedzie winda
int pietro_na_ktorym_kliknal_guzik;
std::vector<int> dokad;
int oczekuje_1;
int oczekuje_2;
int oczekuje_3;
int oczekuje_4;
int kierunek;

int licznik;


RECT drawArea = { 100, 0, 400, 1000 };
RECT drawArea_1pietro = { 49, 578, 250, 620 };
RECT drawArea_2pietro = { 49, 478, 250, 520 };
RECT drawArea_3pietro = { 49, 378, 250, 420 };
RECT drawArea_4pietro = { 49, 278, 250, 320 };






void rysuj_linie(HDC hdc, HWND hWnd)
{

	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 25, 0, 255));


	Point pietro11 = Point(0, 621);
	Point pietro12 = Point(200, 621);
	Point pietro21 = Point(0, 521);
	Point pietro22 = Point(200, 521);
	Point pietro31 = Point(0, 421);
	Point pietro32 = Point(200, 421);
	Point pietro41 = Point(0, 321);
	Point pietro42 = Point(200, 321);

	graphics.DrawLine(&pen2, pietro11, pietro12);
	graphics.DrawLine(&pen2, pietro21, pietro22);
	graphics.DrawLine(&pen2, pietro31, pietro32);
	graphics.DrawLine(&pen2, pietro41, pietro42);

	


}

void rysuj_poziom( HWND hWnd, HINSTANCE hInstance) {


	
	

	HWND   pietro12 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"2", WS_CHILD | WS_VISIBLE | ///pierwsze pietro
		WS_BORDER, 0, 590, 30, 30, hWnd, (HMENU)ID_P12, hInstance, NULL);
	HWND   pietro13 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"3", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 560, 30, 30, hWnd, (HMENU)ID_P13, hInstance, NULL);
	HWND   pietro14 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"4", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 530, 30, 30, hWnd, (HMENU)ID_P14, hInstance, NULL);

	HWND pietro21 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"1", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 490, 30, 30, hWnd, (HMENU)ID_P21, hInstance, NULL);
	HWND   pietro23 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"3", WS_CHILD | WS_VISIBLE | ///drugie pietro
		WS_BORDER, 0, 460, 30, 30, hWnd, (HMENU)ID_P23, hInstance, NULL);
	HWND   pietro24 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"4", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 430, 30, 30, hWnd, (HMENU)ID_P24, hInstance, NULL);

	HWND pietro31 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"1", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 390, 30, 30, hWnd, (HMENU)ID_P31, hInstance, NULL);
	HWND   pietro32 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"2", WS_CHILD | WS_VISIBLE | ///trzecie pietro
		WS_BORDER, 0, 360, 30, 30, hWnd, (HMENU)ID_P32, hInstance, NULL);
	HWND   pietro34 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"4", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 330, 30, 30, hWnd, (HMENU)ID_P34, hInstance, NULL);

	HWND pietro41 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"1", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 290, 30, 30, hWnd, (HMENU)ID_P41, hInstance, NULL);
	HWND   pietro42 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"2", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 260, 30, 30, hWnd, (HMENU)ID_P42, hInstance, NULL);
	HWND   pietro43 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"3", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 230, 30, 30, hWnd, (HMENU)ID_P43, hInstance, NULL);
	HWND text_P1 = CreateWindow(L"Static", L"   1", WS_VISIBLE | WS_CHILD, 100, 550, 30 ,30, hWnd, NULL, NULL, NULL);
	HWND text_P2 = CreateWindow(L"Static", L"   2", WS_VISIBLE | WS_CHILD, 100, 450, 30, 30, hWnd, NULL, NULL, NULL);
	HWND text_P3 = CreateWindow(L"Static", L"   3", WS_VISIBLE | WS_CHILD, 100, 350, 30, 30, hWnd, NULL, NULL, NULL);
	HWND text_P4 = CreateWindow(L"Static", L"   4", WS_VISIBLE | WS_CHILD, 100, 250, 30, 30, hWnd, NULL, NULL, NULL);
	HWND text_MASA = CreateWindow(L"Static", L"   Masa Całkowita", WS_VISIBLE | WS_CHILD, 425, 100, 80, 30, hWnd, NULL, NULL, NULL);
	
}

void rysuj_winde(HDC hdc, HWND hWnd,int przesuniecie_y) {

	Graphics graphics(hdc);
	Pen pen(Color(255, 25, 100, 100));


	Point punktDOL_LEWO = Point(201, 621+przesuniecie_y);
	Point punktDOL_PRAWO = Point(301, 621+przesuniecie_y);
	Point punktGORA_LEWO = Point(201, 521+ przesuniecie_y);
	Point punktGORA_PRAWO = Point(301, 521+ przesuniecie_y);

	graphics.DrawLine(&pen, punktDOL_LEWO, punktDOL_PRAWO);
	graphics.DrawLine(&pen, punktDOL_LEWO, punktGORA_LEWO);
	graphics.DrawLine(&pen, punktGORA_LEWO, punktGORA_PRAWO);
	graphics.DrawLine(&pen, punktDOL_PRAWO, punktGORA_PRAWO);

}
void rysuj_ludzika(HDC hdc, HWND hWnd, int przesuniecie_x,int pietro) {

	Graphics graphics(hdc);
	Pen pen(Color(255, 25, 86, 67));


	Point punktDOL_LEWO = Point(50+ przesuniecie_x, 619-((pietro-1)*100));    //20x40 ludzik
	Point punktDOL_PRAWO = Point(70+przesuniecie_x, 619 - ((pietro - 1) * 100));
	Point punktGORA_LEWO = Point(50+przesuniecie_x, 579 - ((pietro - 1) * 100));
	Point punktGORA_PRAWO = Point(70+przesuniecie_x, 579 - ((pietro - 1) * 100));

	graphics.DrawLine(&pen, punktDOL_LEWO, punktDOL_PRAWO);
	graphics.DrawLine(&pen, punktDOL_LEWO, punktGORA_LEWO);
	graphics.DrawLine(&pen, punktGORA_LEWO, punktGORA_PRAWO);
	graphics.DrawLine(&pen, punktDOL_PRAWO, punktGORA_PRAWO);

}


void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea, RECT *drawArea_1pietro, RECT *drawArea_2pietro, RECT *drawArea_3pietro, RECT *drawArea_4pietro,int przesuniecie,int pietro)
{
	if(wartosci_przesuniecia!=600){///animujemy tylko winde 
		if (drawArea == NULL)
			InvalidateRect(hWnd, NULL, TRUE); // repaint all
		else
			InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
		InvalidateRect(hWnd, drawArea_1pietro, TRUE);
		InvalidateRect(hWnd, drawArea_2pietro, TRUE);
		InvalidateRect(hWnd, drawArea_3pietro, TRUE);
		InvalidateRect(hWnd, drawArea_4pietro, TRUE);
		hdc = BeginPaint(hWnd, &ps);
		rysuj_linie(hdc, hWnd);
		rysuj_winde(hdc, hWnd, przesuniecie);
		rysuj_ludzika(hdc, hWnd, wartosci_przesuniecia, pietro);
		std::wostringstream licznik1;
		licznik1 << masa_calkowita;   //tutaj wyswietlimy nasza mase
		HWND textLicznik = CreateWindow(L"Static", licznik1.str().c_str(), WS_VISIBLE | WS_CHILD, 450, 150, 53, 18, hWnd, NULL, NULL, NULL);
		EndPaint(hWnd, &ps);
	}
	else {
		if (drawArea == NULL)
			InvalidateRect(hWnd, NULL, TRUE); // repaint all
		else
			InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea

		hdc = BeginPaint(hWnd, &ps);
		rysuj_linie(hdc, hWnd);
		rysuj_winde(hdc, hWnd, przesuniecie);
		rysuj_ludzika(hdc, hWnd, wartosci_przesuniecia, pietro);
		std::wostringstream licznik1;
		licznik1 << masa_calkowita;   //tutaj wyswietlimy nasza mase
		HWND textLicznik = CreateWindow(L"Static", licznik1.str().c_str(), WS_VISIBLE | WS_CHILD, 450, 150, 53, 18, hWnd, NULL, NULL, NULL);
		EndPaint(hWnd, &ps);
	}

}


int pietro;
void jedz_winda(int dokad, int zwrot, HWND hWnd, HDC &hdc, PAINTSTRUCT &ps) {
	if (masa_calkowita < masa_MAX_windy) {
		int wart_doc;
		wart_doc = (dokad - 1)*(-1) * 100 - zwrot;
		wartosci_przesuniecia = 600;
		SetTimer(hWnd, TMR_ruch_windy, 1000, 0);
		while (licznik != wart_doc) {
			if (licznik % opoznienie_licznika == 0) {
				repaintWindow(hWnd, hdc, ps, &drawArea, &drawArea_1pietro, &drawArea_2pietro, &drawArea_3pietro, &drawArea_4pietro, licznik, pietro);
				if (zwrot == 1) { licznik--; }
				else { licznik++; }
			}
			else {
				if (zwrot == 1) { licznik--; }
				else { licznik++; }
			}
		}
		KillTimer(hWnd, TMR_ruch_windy);
	}
	
}

void animuj_ludzika(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps,int pietro,int kierunek) {  // kierunek=1 prawo   kierunek=-1 lewo
	////nadajemy mase ludzikowi
	
	if (masa_calkowita < masa_MAX_windy) {
		SetTimer(hWnd, TMR_ruch_ludzika, 1000, 0);

		 wartosci_przesuniecia = 0;
		if (kierunek == 1) {
			while (wartosci_przesuniecia != 200) {
				if (wartosci_przesuniecia % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, &drawArea_1pietro, &drawArea_2pietro, &drawArea_3pietro, &drawArea_4pietro, licznik, pietro);
					wartosci_przesuniecia++;
				}
				else {
					wartosci_przesuniecia++;
				}

			}
		}
		else {
			while (wartosci_przesuniecia != -200) {
				if (wartosci_przesuniecia % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, &drawArea_1pietro, &drawArea_2pietro, &drawArea_3pietro, &drawArea_4pietro, licznik, pietro);
					wartosci_przesuniecia--;
				}
				else {
					wartosci_przesuniecia--;
				}

			}
			
		}
		KillTimer(hWnd, TMR_ruch_ludzika);
	}

}

void funkcja_guzika(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps,int pieterko_start,int pieterko_stop ) {
	masa_calkowita = rand() % 300 + 30;
	int kieruneczek;
	int kieruneczek_wynikowy;
	kieruneczek = pieterko_stop - pieterko_start;
	if (kieruneczek > 0) {
		kieruneczek_wynikowy = 1;
	}
	else { kieruneczek_wynikowy = -1; }
	if (masa_calkowita < masa_MAX_windy) {
		animuj_ludzika(hWnd, hdc, ps, pieterko_start, 1);
		jedz_winda(pieterko_stop, kieruneczek_wynikowy, hWnd, hdc, ps);
		animuj_ludzika(hWnd, hdc, ps, pieterko_stop, -1);
	}
	else {
		std::wostringstream masa_raz;
		masa_raz << masa_calkowita;
		MessageBox(hWnd, masa_raz.str().c_str(), L"UWAGA", MB_ICONINFORMATION | MB_OKCANCEL);
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	// TODO: W tym miejscu umieść kod.
	value = 0;
	value1 = 0;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	// Zainicjuj ciągi globalne
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// Wykonaj inicjacje aplikacji:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDA));
	MSG msg;
	// Główna pętla wiadomości:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;
}

//
//  FUNKCJA: MyRegisterClass()
//
//  CEL: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDA));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDA);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}
//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   CEL: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Przechowuj dojście wystąpienia w zmiennej globalnej
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	rysuj_poziom(hWnd,hInstance);
	licznik = 0;
	






	//HWND editctl = CreateWindow(L"EDIT", L"hduahda", WS_CHILD | WS_BORDER |WS_VISIBLE | 
	//ES_LEFT | ES_AUTOHSCROLL | ES_WANTRETURN, 350, 470, 100, 50, hWnd, (HMENU)IDC_WINDOWSPROJECT1, hInst, 0); // by mozna bylo wpisywac tekst

	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  CEL: Przetwarza wiadomości dla okna głównego.
//
//  WM_COMMAND — przetwarzaj menu aplikacji
//  WM_PAINT — pomaluj okno główne
//  WM_DESTROY — opublikuj komunikat o rezygnacji i wróć
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Analizuj zaznaczenia menu:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_P12: {
			funkcja_guzika(hWnd, hdc, ps, 1, 2);
			break;
		}
					
		case ID_P13: {
			funkcja_guzika(hWnd, hdc, ps, 1, 3);
			break;
		}
		case ID_P14: {
			
			funkcja_guzika(hWnd, hdc, ps, 1, 4);
			break;
		}
					 
		case ID_P21: {
			funkcja_guzika(hWnd, hdc, ps, 2, 1);
			break;
		}
					
		case ID_P23: {
			funkcja_guzika(hWnd, hdc, ps, 2, 3);
			break;
		}
					
		case ID_P24: {
			funkcja_guzika(hWnd, hdc, ps, 2, 4);
			break;
		}
					 
		case ID_P31: {
			funkcja_guzika(hWnd, hdc, ps,3 , 1);
			break;
		}
		case ID_P32: {
			funkcja_guzika(hWnd, hdc, ps, 3, 2);
			break;
		}
					  
		case ID_P34: {
			funkcja_guzika(hWnd, hdc, ps, 3, 4);
			break;
		}
			
		case ID_P41: {
			funkcja_guzika(hWnd, hdc, ps, 4, 1);
			break;
		}
					
					  
		case ID_P42: {
			funkcja_guzika(hWnd, hdc, ps, 4, 2);
			break;
		}
		case ID_P43: {
			funkcja_guzika(hWnd, hdc, ps, 4, 3);
			break;
		}
					  

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		rysuj_linie(hdc, hWnd);
		rysuj_winde(hdc, hWnd, 0);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		switch (wParam)
		{


		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//Procedura obsługi wiadomości dla okna informacji o programie.
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
