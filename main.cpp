#include "stdafx.h"
#include <Project64-core/AppInit.h>
#include "Multilanguage\LanguageSelector.h"
#include "Settings/UISettings.h"

#include <windows.h>
#include <string>

using namespace std;;

//#include <Project64-core/Plugins/PluginClass.h>

int WINAPI WinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpszArgs*/, int /*nWinMode*/)
{
	CoInitialize(NULL);
	AppInit(&Notify(), CPath(CPath::MODULE_DIRECTORY), __argc, __argv);
	CLanguageSelector().Set("English");
	WriteTrace(TraceUserInterface, TraceDebug, "Create Main Window");
	CMainGui MainWindow(true, stdstr_f("Project64 %s", "SM64AI").c_str()), HiddenWindow(false);
	CMainMenu MainMenu(&MainWindow);
	CDebuggerUI Debugger;
	g_Debugger = &Debugger;
	g_Plugins->SetRenderWindows(&MainWindow, &HiddenWindow);
	Notify().SetMainWindow(&MainWindow);
	WriteTrace(TraceUserInterface, TraceDebug, "Show Main Window");
	MainWindow.Show(true);
	try
	{
		string path;
		TCHAR dir[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, dir);
		path = dir;
		path = path + "/Super Mario 64 (USA).z64";	
		CN64System::RunFileImage(path.c_str());
	}
	catch (...)
	{
		WriteTrace(TraceUserInterface, TraceError, "Exception caught (File: \"%s\" Line: %d)", __FILE__, __LINE__);
		MessageBox(NULL, stdstr_f("Exception caught\nFile: %s\nLine: %d", __FILE__, __LINE__).c_str(), "Exception", MB_OK);
	}

	/*
	try
	{
	CoInitialize(NULL);
	AppInit(&Notify(), CPath(CPath::MODULE_DIRECTORY), __argc, __argv);
	CLanguageSelector().Set("English");

	// if (!g_Lang->IsLanguageLoaded())
	//  {
	//  CLanguageSelector().Select();
	// }

	//Create the main window with Menu
	WriteTrace(TraceUserInterface, TraceDebug, "Create Main Window");
	CMainGui MainWindow(true, stdstr_f("Project64 %s", "test").c_str()), HiddenWindow(false);
	CMainMenu MainMenu(&MainWindow);
	CDebuggerUI Debugger;
	g_Debugger = &Debugger;
	g_Plugins->SetRenderWindows(&MainWindow, &HiddenWindow);
	Notify().SetMainWindow(&MainWindow);
	// CSupportWindow SupportWindow;

	if (g_Settings->LoadStringVal(Cmd_RomFile).length() > 0)
	{
	MainWindow.Show(true);	//Show the main window
	//N64 ROM or 64DD Disk
	stdstr ext = CPath(g_Settings->LoadStringVal(Cmd_RomFile)).GetExtension();
	if (!(_stricmp(ext.c_str(), "ndd") == 0))
	{
	//File Extension is not *.ndd so it should be a N64 ROM
	CN64System::RunFileImage(g_Settings->LoadStringVal(Cmd_RomFile).c_str());
	}
	else
	{
	//Ext is *.ndd, so it should be a disk file.
	if (CN64System::RunDiskImage(g_Settings->LoadStringVal(Cmd_RomFile).c_str()))
	{
	stdstr IPLROM = g_Settings->LoadStringVal(File_DiskIPLPath);
	if ((IPLROM.length() <= 0) || (!CN64System::RunFileImage(IPLROM.c_str())))
	{
	CPath FileName;
	const char * Filter = "64DD IPL ROM Image (*.zip, *.7z, *.?64, *.rom, *.usa, *.jap, *.pal, *.bin)\0*.?64;*.zip;*.7z;*.bin;*.rom;*.usa;*.jap;*.pal\0All files (*.*)\0*.*\0";
	if (FileName.SelectFile(NULL, g_Settings->LoadStringVal(RomList_GameDir).c_str(), Filter, true))
	{
	CN64System::RunFileImage(FileName);
	}
	}
	}
	}
	}
	else
	{
	//CN64System::RunFileImage("C:/Users/justi/Desktop/Class files repo/Class-files-repo/C463 AI/Mario64AI/Super Mario 64 (USA).z64");
	//  SupportWindow.Show(reinterpret_cast<HWND>(MainWindow.GetWindowHandle()));
	if (UISettingsLoadBool(RomBrowser_Enabled))
	{
	WriteTrace(TraceUserInterface, TraceDebug, "Show Rom Browser");
	//Display the rom browser
	MainWindow.ShowRomList();
	MainWindow.Show(true);	//Show the main window
	MainWindow.HighLightLastRom();
	}
	else
	{
	WriteTrace(TraceUserInterface, TraceDebug, "Show Main Window");
	MainWindow.Show(true);	//Show the main window
	}
	}

	//Process Messages till program is closed
	WriteTrace(TraceUserInterface, TraceDebug, "Entering Message Loop");
	MainWindow.ProcessAllMessages();
	WriteTrace(TraceUserInterface, TraceDebug, "Message Loop Finished");

	if (g_BaseSystem)
	{
	g_BaseSystem->CloseCpu();
	delete g_BaseSystem;
	g_BaseSystem = NULL;
	}
	WriteTrace(TraceUserInterface, TraceDebug, "System Closed");
	}
	catch (...)
	{
	WriteTrace(TraceUserInterface, TraceError, "Exception caught (File: \"%s\" Line: %d)", __FILE__, __LINE__);
	MessageBox(NULL, stdstr_f("Exception caught\nFile: %s\nLine: %d", __FILE__, __LINE__).c_str(), "Exception", MB_OK);
	}
	*/
	//Process Messages till program is closed
	WriteTrace(TraceUserInterface, TraceDebug, "Entering Message Loop");
	MainWindow.ProcessAllMessages();
	WriteTrace(TraceUserInterface, TraceDebug, "Message Loop Finished");

	if (g_BaseSystem)
	{
		g_BaseSystem->CloseCpu();
		delete g_BaseSystem;
		g_BaseSystem = NULL;
	}
	WriteTrace(TraceUserInterface, TraceDebug, "System Closed");

	AppCleanup();
	CoUninitialize();

	return true;
}