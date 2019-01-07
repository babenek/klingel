//---------------------------------------------------------------------------
#include <vcl.h>
#include <conio.h>
#include <stdio.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ccalendr"
#pragma link "CurrEdit"
#pragma link "ToolEdit"
#pragma resource "*.dfm"
TKFormSlave *KFormSlave;
//---------------------------------------------------------------------------
__fastcall TKFormSlave::TKFormSlave(TComponent *Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void
__fastcall TKFormSlave::FormActivate(TObject *Sender)
{
	MaskEditTime->Text = TimeToStr(KFormMain->FS.CRTime); //  KFormMain->FS.CRTime;
	MaskEditDate->Date = KFormMain->FS.CRDate;//DateToStr( KFormMain->FS.CRDate );
	ComboBox1->ItemIndex = KFormMain->FS.CRState;
	//EditMessage->Text="Завтра же на работу. Всем спать!";
	EditMessage->Text = "";
	Execute = false;
}
//---------------------------------------------------------------------------

void
__fastcall TKFormSlave::MaskEditKeyPress(TObject *Sender, char &Key)
{
	if (Key==13 || Key==27)
	{
		Execute = (Key==13);
		Close();
	}
}
//---------------------------------------------------------------------------

void
__fastcall TKFormSlave::FormClose(TObject *Sender,
								  TCloseAction &Action)
{
	KFormMain->FS.CRTime = StrToTime(MaskEditTime->Text);//  MaskEditDate->Time;
	KFormMain->FS.CRDate = MaskEditDate->Date;//StrToDate(MaskEditDate->Text);
	KFormMain->FS.CRState = ComboBox1->ItemIndex;
	AnsiString Message = EditMessage->Text;
	if (Message.Length() > (MaxChar - 1))
		Message.SetLength(MaxChar - 1);
	sprintf(KFormMain->FS.CRMessage, "%s", Message.c_str());
}
//---------------------------------------------------------------------------


