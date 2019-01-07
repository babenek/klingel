//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("KLINGEL.RES");
USEFORM("Unit1.cpp", KFormMain);
USEFORM("Unit2.cpp", KFormSlave);
USEFORM("Unit3.cpp", KFormCfg);
//---------------------------------------------------------------------------
WINAPI
WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TKFormMain), &KFormMain);
		Application->CreateForm(__classid(TKFormSlave), &KFormSlave);
		Application->CreateForm(__classid(TKFormCfg), &KFormCfg);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
