
// ArayDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Aray.h"
#include "ArayDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define MAX_NAME_LENGTH 255
#define MAX_KEY	2048
#define MAX_VALUE_NAME 16383
#endif



// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CArayDlg



CArayDlg::CArayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ARAY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CArayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, panel);
}

BEGIN_MESSAGE_MAP(CArayDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CArayDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CArayDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CArayDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CArayDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// Обработчики сообщений CArayDlg

BOOL CArayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CArayDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CArayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CArayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CArayDlg::OnBnClickedButton1()
{
    // TODO: добавьте свой код обработчика уведомлений    
	panel.DeleteAllItems(); // Clear the panel 
	panel.InsertColumn(0, TEXT("Name"));
	panel.InsertColumn(1, TEXT("ImagePath"));
	for (int i = 0; i < panel.GetHeaderCtrl()->GetItemCount(); ++i) panel.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	CString  paths[5] = { TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 
		TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"),
		TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
		TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce"),
		TEXT("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run") };
	for (int k = 0; k < 5; k++) 
	{
		HKEY root, hKEY;
		if (k == 0 || k == 1) root = HKEY_CURRENT_USER;
		else root = HKEY_LOCAL_MACHINE;
		long ret0 = (::RegOpenKeyEx(root, paths[k], 0, KEY_READ, &hKEY)); // 打开注册表位置 
		if (ret0 != ERROR_SUCCESS) 	return;
		TCHAR    lpachClass[MAX_PATH] = TEXT("");     
		DWORD    lpcbMaxSubKey, lpcchMaxClass, lpcValues, lpcchMaxValue, lpcbMaxValueData, lpcbSecurityDescriptor, i;                       
		DWORD    lpcchClassName = MAX_PATH, lpcSubKeys = 0;  
		FILETIME ftLastWriteTime;      
		long ret1 = RegQueryInfoKey(hKEY, lpachClass, &lpcchClassName, NULL, &lpcSubKeys, &lpcbMaxSubKey, &lpcchMaxClass,
				&lpcValues, &lpcchMaxValue, &lpcbMaxValueData, &lpcbSecurityDescriptor, & ftLastWriteTime);
		if (lpcValues) // in case of key values 
			for (i = 0, ret1 = ERROR_SUCCESS; i < lpcValues; i++) 
			{
				DWORD type = REG_SZ, datasize = 1000, lpcchValue = MAX_VALUE_NAME;
				BYTE data[1000];                  
				memset(data, 0x00, sizeof(data));
				CString value;
				TCHAR achValue[MAX_VALUE_NAME];
				achValue[0] = '\0';
				ret1 = RegEnumValue(hKEY, i, achValue, &lpcchValue, 0, & type, data, & datasize);
				if (ret1 == ERROR_SUCCESS) 
				{
					value.Format(TEXT("%s"), achValue);
					panel.InsertItem(i, value);
					value.Format(TEXT("%s"), data);
					panel.SetItemText(i, 1, value);
				}
			}
	}
	// 自启动文件夹  
	CString path[2] = {TEXT("C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\StartUp\\*.*"), 
			TEXT("C:\\Users\\Admin\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\*.*")};
	for (int j = 0; j < 2; j++) 
	{
		CFileFind finder;
		BOOL bWorking = finder.FindFile(path[j]);
		int index = 0;      
		CString fontName, lastType, filepath, filename, filesize; // storing cutting results  
		while (bWorking)
		{    
			bWorking = finder.FindNextFile();
			filename = finder.GetFileName();
			if (filename != _T(".") && filename != _T(".."))
				if (filename != L"desktop.ini") 
				{
					filepath = finder.GetFilePath();
					panel.InsertItem(index, filename);
					panel.SetItemText(index, 1, filepath);
					index++;
				}
		}
		finder.Close();
	}
}


	void CArayDlg::OnBnClickedButton2()
	{
		// TODO: добавьте свой код обработчика уведомлений	  
		panel.DeleteAllItems(); // Clear the panel
		// Fill in the data
		HKEY hKEY;
		long ret0 = (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &hKEY));
		if (ret0 != ERROR_SUCCESS) return;
		TCHAR    lpachClass[MAX_PATH] = TEXT("");     
		DWORD    lpcbMaxSubKey, lpcchMaxClass, lpcValues, lpcchMaxValue, lpcbMaxValueData, lpcbSecurityDescriptor;                      
		DWORD    lpcchClassName = MAX_PATH, lpcSubKeys = 0;                           
		FILETIME ftLastWriteTime;         
		long ret1 = RegQueryInfoKey(hKEY, lpachClass, &lpcchClassName, NULL, &lpcSubKeys, &lpcbMaxSubKey, &lpcchMaxClass,
			&lpcValues, &lpcchMaxValue, &lpcbMaxValueData, &lpcbSecurityDescriptor, & ftLastWriteTime);
		 
		if (lpcSubKeys) // search subkeys
		{
			int index = 0;
			for (DWORD i = 0; i < lpcSubKeys; i++)
			{  
				TCHAR  lpachKey[MAX_NAME_LENGTH];
				DWORD cbName = MAX_NAME_LENGTH;
				long retCode = RegEnumKeyEx(hKEY, i, lpachKey, & cbName, NULL, NULL, NULL, & ftLastWriteTime);
				if (retCode == ERROR_SUCCESS)
				{
					HKEY hKey;
					CString path;
					path.Format(TEXT("SYSTEM\\CurrentControlSet\\Services\\%s"), lpachKey);
					long ret0 = (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &hKey));
					if (ret0 != ERROR_SUCCESS)  return;
					DWORD dwType = REG_EXPAND_SZ, dwValue = MAX_VALUE_NAME;
					BYTE dwData[MAX_VALUE_NAME];  
					long ret2 = RegQueryValueEx(hKey, TEXT("ImagePath"), 0, & dwType, dwData, & dwValue);
					if (ret2 == ERROR_SUCCESS) 
					{
						CString data, driver = _T("drivers");
						data.Format(TEXT("%s"), dwData);
						if (data.Find(driver) == -1) //is driver or not
						{ 
							panel.InsertItem(index, lpachKey);
							panel.SetItemText(index, 1, data);
							index++;
						}
					}
				}
			}
		}
	}


	void CArayDlg::OnBnClickedButton3()
	{
		// TODO: добавьте свой код обработчика уведомлений
		panel.DeleteAllItems(); // Clear the panel
		// Fill in the data
		HKEY hKEY;
		long ret0 = (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &hKEY));
		if (ret0 != ERROR_SUCCESS) return;
		DWORD    lpcbMaxSubKey, lpcchMaxClass, lpcValues, lpcchMaxValue, lpcbMaxValueData, lpcbSecurityDescriptor;                  
		DWORD    lpcchClassName = MAX_PATH, lpcSubKeys = 0;          
		TCHAR    achKey[MAX_NAME_LENGTH], achClass[MAX_PATH] = TEXT(""); 
		FILETIME ftLastWriteTime;      
		long ret1 = RegQueryInfoKey(hKEY, achClass, &lpcchClassName, NULL, &lpcSubKeys, &lpcbMaxSubKey, &lpcchMaxClass,
			&lpcValues, &lpcchMaxValue, &lpcbMaxValueData, &lpcbSecurityDescriptor, & ftLastWriteTime);
		if (lpcSubKeys) // search subkeys  
		{
			int index = 0;
			for (int i = 0; i < lpcSubKeys; i++)
			{    
				DWORD lpcbName = MAX_NAME_LENGTH;
				long retCode = RegEnumKeyEx(hKEY, i, achKey, & lpcbName, NULL, NULL, NULL, & ftLastWriteTime);
				if (retCode == ERROR_SUCCESS)
				{
					HKEY hKey;
					CString path;
					path.Format(TEXT("SYSTEM\\CurrentControlSet\\Services\\%s"), achKey);
					long ret0 = (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, path, 0, KEY_READ, &hKey));
					if (ret0 != ERROR_SUCCESS) return;
					DWORD dwTpye = REG_EXPAND_SZ, dwValue = MAX_VALUE_NAME;
					BYTE dwData[MAX_VALUE_NAME]; 
					long ret2 = RegQueryValueEx(hKey, TEXT("ImagePath"), 0, & dwTpye, dwData, & dwValue); 
					if (ret2 == ERROR_SUCCESS)
					{
						CString data, driver=_T("drivers");
						data.Format(TEXT("%s"), dwData);
						if (data.Find (driver)!=-1) //is driver or not
						{
							panel.InsertItem(index, achKey);
							panel.SetItemText(index, 1, data);
							index++;
						}
					}
				}
			}
		}
	}


	void CArayDlg::OnBnClickedButton4()
	{
		// TODO: добавьте свой код обработчика уведомлений
		panel.DeleteAllItems(); // Clear the panel
		// Fill in the data
		CString strWildcard = TEXT("C:\\Windows\\System32\\Tasks\\*.*");
		CFileFind finder;
		BOOL bWorking = finder.FindFile(strWildcard);
		if (!bWorking) MessageBox(L"Run as administrator");
		int index = 0;  
		CString fontName, lastType, filepath, filename, filesize;	// Storing cutting results
		while (bWorking)
		{   // Internal file retrieval 
			bWorking = finder.FindNextFileW();
			filename = finder.GetFileName();
			if (filename != _T(".") && filename != _T(".."))
				if (filename != L"desktop.ini") 
				{
					filepath = finder.GetFilePath();
					panel.InsertItem(index, filename);
					panel.SetItemText(index, 1, filepath);
					index++;
				}
		}
		finder.Close();
	}