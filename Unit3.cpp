//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TKFormCfg *KFormCfg;
//---------------------------------------------------------------------------
__fastcall TKFormCfg::TKFormCfg(TComponent *Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void
__fastcall TKFormCfg::ButtonWAVClick(TObject *Sender)
{
	OpenDialog->Filter = "AudioFiles (*.*)|*.*";
	if (OpenDialog->Execute())
	{
		((TButton *) Sender)->Caption = OpenDialog->FileName;
	}
}
//---------------------------------------------------------------------------
void
__fastcall TKFormCfg::ButtonOLEClick(TObject *Sender)
{
	OpenDialog->Filter = "All files (*.*)|*.*"; // "Application (*.exe)|*.exe";//
	if (OpenDialog->Execute())
	{
		((TButton *) Sender)->Caption = OpenDialog->FileName;
	}
}
//---------------------------------------------------------------------------

