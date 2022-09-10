
// Aray.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CArayApp:
// Сведения о реализации этого класса: Aray.cpp
//

class CArayApp : public CWinApp
{
public:
	CArayApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CArayApp theApp;
