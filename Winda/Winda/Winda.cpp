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

#define ID_P1G 102
#define ID_P1 103


#define ID_P2D 201
#define ID_P2G 202
#define ID_P2 203

#define ID_P3D 301
#define ID_P3G 302
#define ID_P3 303

#define ID_P4D 401

#define ID_P4 403

#define TMR_12 500
#define TMR_13 501
#define TMR_14 502
#define TMR_21 503
#define TMR_23 504
#define TMR_24 505
#define TMR_31 506
#define TMR_32 507
#define TMR_34 508
#define TMR_41 509
#define TMR_42 510
#define TMR_43 511

std::vector<Point>oczekiwania;

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

//RECT drawArea = { 201, 0, 621, 421 };
RECT drawArea = { 100, 0, 400, 1000 };





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

	

//	std::wostringstream licznik1;
//	licznik1 << value << "/" << ilosc_linijek;
//	HWND textLicznik = CreateWindow(L"Static", licznik1.str().c_str(), WS_VISIBLE | WS_CHILD, 250, 300, 53, 18, hWnd, NULL, NULL, NULL);
}

void rysuj_poziom( HWND hWnd, HINSTANCE hInstance) {

	// Rectangle(hdc, 440, 60, 460, 100); //prostokat pod roll
	// Rectangle(hdc, 590, 60, 610, 100); //prostokat pod pitch
	// Rectangle(hdc, 740, 60, 760, 100); //prostokat pod yaw
	
	

	HWND   pietro1G = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"G", WS_CHILD | WS_VISIBLE | ///pierwsze pietro
		WS_BORDER, 0, 570, 30, 30, hWnd, (HMENU)ID_P1G, hInstance, NULL);
	HWND   pietro14 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"1", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 400, 540, 30, 30, hWnd, (HMENU)ID_P1, hInstance, NULL);

	HWND pietro2D = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"D", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 490, 30, 30, hWnd, (HMENU)ID_P2D, hInstance, NULL);
	HWND   pietro2G = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"G", WS_CHILD | WS_VISIBLE | ///drugie pietro
		WS_BORDER, 0, 460, 30, 30, hWnd, (HMENU)ID_P2G, hInstance, NULL);
	HWND   pietro24 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"2", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 400, 430, 30, 30, hWnd, (HMENU)ID_P2, hInstance, NULL);

	HWND pietro3D = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"D", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 380, 30, 30, hWnd, (HMENU)ID_P3D, hInstance, NULL);
	HWND   pietro3G = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"G", WS_CHILD | WS_VISIBLE | ///trzecie pietro
		WS_BORDER, 0, 350, 30, 30, hWnd, (HMENU)ID_P3G, hInstance, NULL);
	HWND   pietro34 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"3", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 400, 320, 30, 30, hWnd, (HMENU)ID_P3, hInstance, NULL);

	HWND pietro4D = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"D", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 0, 270, 30, 30, hWnd, (HMENU)ID_P4D, hInstance, NULL);
	HWND   pietro43 = CreateWindowEx(WS_EX_CLIENTEDGE, L"BUTTON", L"4", WS_CHILD | WS_VISIBLE |
		WS_BORDER, 400, 210, 30, 30, hWnd, (HMENU)ID_P4, hInstance, NULL);
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

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea, int przesuniecie)
{
	if (drawArea == NULL )
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	rysuj_linie(hdc, hWnd);
	rysuj_winde(hdc, hWnd, przesuniecie);
	std::wostringstream licznik1;
	licznik1 << masa_calkowita;   //tutaj wyswietlimy nasza mase
	HWND textLicznik = CreateWindow(L"Static", licznik1.str().c_str(), WS_VISIBLE | WS_CHILD, 450, 150,53, 18, hWnd, NULL, NULL, NULL);
	EndPaint(hWnd, &ps);
}



void jedz_winda(int dokad, int zwrot, HWND hWnd, HDC &hdc, PAINTSTRUCT &ps) {
	int wart_doc;
	wart_doc = (dokad - 1)*(-1) * 100-zwrot;

	while (licznik != wart_doc) {
		if (licznik % opoznienie_licznika == 0) {
			repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
			if (zwrot == 1) { licznik--; }
			else { licznik++; }
		}
		else {
			if (zwrot == 1) { licznik--; }
			else { licznik++; }
		}
	}

	KillTimer(hWnd, TMR_13);
	

}
//void wybor(std::vector<Point>oczekuj) {
//
//}



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
		case ID_P1G: {
			oczekiwania.push_back(Point(1, 1));
			
		}
					   break;
		case ID_P1: {
			SetTimer(hWnd, TMR_14, 25, 0);
		}
					 break;
		case ID_P2D: {
			SetTimer(hWnd, TMR_21, 25, 0);
		}
					  break;
		case ID_P2G: {
			SetTimer(hWnd, TMR_23, 25, 0);
		}
					  break;
		case ID_P2: {
			SetTimer(hWnd, TMR_24, 25, 0);
		}
					  break;
		case ID_P3D: {
			SetTimer(hWnd, TMR_31, 25, 0);
		}
					  break;
		case ID_P3G: {
			SetTimer(hWnd, TMR_32, 25, 0);
		}
					  break;
		case ID_P3: {
			SetTimer(hWnd, TMR_34, 25, 0);
		}
					  break;
		case ID_P4D: {
			SetTimer(hWnd, TMR_41, 25, 0);
		}
					  break;
					  
		case ID_P4: {
			SetTimer(hWnd, TMR_43, 25, 0);
		}
					  break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		// Rectangle(hdc, 440, 60, 460, 100); //prostokat pod roll
		// Rectangle(hdc, 590, 60, 610, 100); //prostokat pod pitch
		// Rectangle(hdc, 740, 60, 760, 100); //prostokat pod yaw
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
		case TMR_12: {

			while (licznik > -101) {
				if (licznik % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
					licznik--;
				}
				else {
					licznik--;
				}
			}
				KillTimer(hWnd, TMR_12);
				break;
			}
		case TMR_13: {

			jedz_winda(3, 1, hWnd, hdc, ps);
			break;

		}
		case TMR_14: {
			//force window to repaint udaje sie tutaj wejsc
			while (licznik > -301) {
				if (licznik % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
					licznik--;
				}
				else {
					licznik--;
				}
			}
			KillTimer(hWnd, TMR_14);
			break;
		}
		case TMR_21: {
			while (licznik <1) {
				if (licznik % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
					licznik++;
				}
				else {
					licznik++;
				}
			}
			KillTimer(hWnd, TMR_21);
			break;
		}
		case TMR_23: {
			//force window to repaint udaje sie tutaj wejsc
			
			while (licznik >-201) {
				if (licznik % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
					licznik--;
				}
				else {
					licznik--;
				}
			}
			KillTimer(hWnd, TMR_23);
			break;
		}
		case TMR_24: {
			//force window to repaint udaje sie tutaj wejsc

			while (licznik >-301) {
				if (licznik % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
					licznik--;
				}
				else {
					licznik--;
				}
			}
			KillTimer(hWnd, TMR_24);
			break;
		}

		case TMR_31: {

			while (licznik < 1) {
				if (licznik % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
					licznik++;
				}
				else {
					licznik++;
				}
			}
			KillTimer(hWnd, TMR_31);
			break;
		}

		case TMR_32: {


			while (licznik < -99) {
				if (licznik % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
					licznik++;
				}
				else {
					licznik++;
				}
			}
			KillTimer(hWnd, TMR_32);
			break;

		}
		case TMR_34: {
			//force window to repaint udaje sie tutaj wejsc

			while (licznik >-301) {
				if (licznik % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
					licznik--;
				}
				else {
					licznik--;
				}
			}
			KillTimer(hWnd, TMR_34);
			break;
		}
		case TMR_41: {
			//force window to repaint udaje sie tutaj wejsc

			while (licznik <1) {
				if (licznik % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
					licznik++;
				}
				else {
					licznik++;
				}
			}
			KillTimer(hWnd, TMR_41);
			break;
		}
		case TMR_42: {
			//force window to repaint udaje sie tutaj wejsc

			while (licznik < -99) {
				if (licznik % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
					licznik++;
				}
				else {
					licznik++;
				}
			}
			KillTimer(hWnd, TMR_42);
			break;
		}
		case TMR_43: {
			while (licznik < -199) {
				if (licznik % opoznienie_licznika == 0) {
					repaintWindow(hWnd, hdc, ps, &drawArea, licznik);
					licznik++;
				}
				else {
					licznik++;
				}
			}
			KillTimer(hWnd, TMR_43);
			break;


					}
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