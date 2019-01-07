#define CSNumWaitDefValue 8
#define CSToneWaitDefValue 200
#define CSBeepWaitDefValue 2000
#define CSLoopWaitDefValue 16383
//#define CSdTime 0.0007
#define CSdTime 0.0014

#define PB  61H
#define COMREG 43H
#define CHAN_2 42H

//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <winbase.h>
#include <mmsystem.hpp>
#include <vcl/dstring.h>

#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
//#include "Signal.cpp"





//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RXShell"
#pragma link "RXShell"
#pragma resource "*.dfm"
TKFormMain *KFormMain;
//---------------------------------------------------------------------------
__fastcall TKFormMain::TKFormMain(TComponent *Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void
Signal(short int NUMBEEP)
{
//Beep();

	asm{
	cli
	mov BX, NUMBEEP
	BEGIN:
	push BX
	in AL, PB
	or AL, 3
	out PB, AL
	mov AL, 10110110B
	out COMREG, AL
	mov AX, 500
	out CHAN_2, AL
	mov AL, AH
	out CHAN_2, AL
	mov AH, 0
	int 26
	add DX, 1
	mov BX, DX
	REPEAT:
	int 26
	cmp DX, BX
	jne REPEAT
	in AL, PB
	and AL, 252
	out PB, AL
	mov AH, 0
	int 26
	add DX, 1
	mov BX, DX
	REP1:
	int 26
	cmp DX, BX
	jne REP1
	pop BX
	dec BX
	jnz BEGIN
	sti
	};

}

//---------------------------------------------------------------------------
void
__fastcall TKFormMain::RefreshListBox1(void)
{

	char *Stat[4] = {"Включен", "Выключен", "Пропущен", "Ежедневно"};

	ListBoxRecords->Items->Clear();

	for (int x = 0; x < MengeCrank; x++)
	{

		ListBoxRecords->Items->Add(
			Format("%8s  %8s   %s   %s",
				   OPENARRAY(TVarRec, (
					   TimeToStr(CR[x].CRTime),
						   DateToStr(CR[x].CRDate),
						   Stat[CR[x].CRState],
						   CR[x].CRMessage
				   ))));

	}
	ListBoxRecords->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void
__fastcall TKFormMain::TimerTimer(TObject *Sender)
{
	StatusBarDateTime->Panels->Items[0]->Text = "Time: " + TimeToStr(Time());
	StatusBarDateTime->Panels->Items[1]->Text = "Date: " + DateToStr(Date());

	Timer->Enabled = false;
	char *KeyEnter, ASCIIEnter = 13;
	KeyEnter = &ASCIIEnter;

	for (int x = 0; x < MengeCrank; x++)
		if (CR[x].CRState!=DISABLE && (CR[x].CRDate==Date() || CR[x].CRState==DAILY && CR[x].CRDate < Date()))
		{
			double Tmp = Time() - CR[x].CRTime;
			if (Tmp > 0 && Tmp < dTime)
			{

				Show();
				WindowState = wsNormal;

				switch (KFormCfg->RadioGroupSignal->ItemIndex)
				{
					case 0: // открыть файло
						if (FileExists(KFormCfg->ButtonOLE->Caption))
						{
							OleContainer->CreateObjectFromFile(KFormCfg->ButtonOLE->Caption, true);
							OleContainer->DoVerb(0);
							//CR[x].CRState = DISABLE;
							ListBoxRecordsKeyPress(Sender, *KeyEnter);
						}
						break;
					case 1: // проиграть вавку
						if (FileExists(KFormCfg->ButtonWAV->Caption))
						{
							for (int n = 0; n < KFormCfg->UpDownSpeaker->Position; n++)
								sndPlaySound((KFormCfg->ButtonWAV->Caption).c_str(), SND_SYNC);
							//CR[x].CRState = DISABLE;
							ListBoxRecordsKeyPress(Sender, *KeyEnter);
						}
						break;
					case 2: // попищать спикером
						Signal(KFormCfg->UpDownSpeaker->Position);
						break;
				};

				AnsiString Message(CR[x].CRMessage);
				if (Message.Length() && KFormCfg->CheckBoxMessage->Checked)
					// показать сообщение
					MessageDlg(Message, mtConfirmation, TMsgDlgButtons() << mbYes << mrNo, 0);

				if (CR[x].CRState==ENABLE)
				{
					CR[x].CRState = SKIP;
				}
				RefreshListBox1();
				ListBoxRecords->ItemIndex = x;
			}
		}

	Timer->Enabled = true;
}
//---------------------------------------------------------------------------
void
__fastcall TKFormMain::Clearall1Click(TObject *Sender)
{
	if (MessageDlg("Удалить все записи?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0)==mrYes)
		MengeCrank = 0;

	RefreshListBox1();
}
//---------------------------------------------------------------------------

void
__fastcall TKFormMain::Delete1Click(TObject *Sender)
{
	int x = ListBoxRecords->ItemIndex;
	if (x < 0 || x > MengeCrank)
		return;
	MengeCrank--;
	for (; x < MengeCrank; x++)
		CR[x] = CR[x + 1];
	RefreshListBox1();
}
//---------------------------------------------------------------------------



void
__fastcall TKFormMain::Add1Click(TObject *Sender)
{
	if (MengeCrank < MaxRec)
	{
		Timer->Enabled = false;
		FS.CRTime = Time();
		FS.CRDate = Date();
		FS.CRState = ENABLE;
		FS.CRMessage[0] = '\0';
		KFormSlave->Caption = "Добавить";
		KFormSlave->ShowModal();
		if (KFormSlave->Execute)
		{
			CR[MengeCrank] = FS;
			MengeCrank++;
		}
		RefreshListBox1();
		Timer->Enabled = true;
	}
	else
		ShowMessage("Больше нельзя!");
}
//---------------------------------------------------------------------------

void
__fastcall TKFormMain::Change1Click(TObject *Sender)
{

	int x = ListBoxRecords->ItemIndex;

	if (x < 0 || x > MengeCrank)
		return;

	Timer->Enabled = false;
	FS = CR[x];
	KFormSlave->Caption = "Изменить";
	KFormSlave->ShowModal();
	if (KFormSlave->Execute)
		CR[x] = FS;
	RefreshListBox1();
	Timer->Enabled = true;
}
//---------------------------------------------------------------------------




void
__fastcall TKFormMain::ListBoxRecordsKeyPress(TObject *Sender, char &Key)
{

	switch (Key)
	{
		case 43:  // +
			Add1Click(Sender);
			break;
		case 46:  // .
			RxTrayIconDblClick(Sender);
			break;
	};

	int x = ListBoxRecords->ItemIndex;
	if (x < 0 || x > MengeCrank)
		return;

	switch (Key)
	{
		case 13:  // Enter
			if (CR[x].CRState==DAILY)
				CR[x].CRDate += 1;
			else
				CR[x].CRState = DISABLE;
			break;
		case 42:  // *
			Change1Click(Sender);
			break;
		case 45:   // -
			Delete1Click(Sender);
			break;
	};

	RefreshListBox1();
}
//---------------------------------------------------------------------------



void
__fastcall TKFormMain::AboutClick(TObject *Sender)
{
	ShowMessage("babenek\nМариуполь 1999г ПГТУ ВТ-97");
}
//---------------------------------------------------------------------------



void
__fastcall TKFormMain::FormShow(TObject *Sender)
{


	HomeDir = ParamStr(0);
	HomeDir = ExtractFilePath(HomeDir);

	FILE *Stream;
	if ((Stream = fopen((HomeDir + "Klingel.rec").c_str(), "r"))==NULL)
	{
		MengeCrank = 0;
		RefreshListBox1();
		return;
	}

	fread(&MengeCrank, sizeof(MengeCrank), 1, Stream);
	fread(&CR, sizeof(CR), 1, Stream);
	fclose(Stream);

	if (MengeCrank < 0 || MengeCrank > MaxRec)
		MengeCrank = 0;

	RefreshListBox1();

	NumBeep = CSNumWaitDefValue;
	dTime = CSdTime;

}
//---------------------------------------------------------------------------

void
__fastcall TKFormMain::RxTrayIconDblClick(TObject *Sender)
{
	if (KFormMain->Visible)
		KFormMain->Hide();
	else
		KFormMain->Show();
}
//---------------------------------------------------------------------------

void
__fastcall TKFormMain::FormHide(TObject *Sender)
{
	FILE *Stream;
	if ((Stream = fopen((HomeDir + "Klingel.rec").c_str(), "w"))==NULL)
	{
		ShowMessage("Insert yuor HDD\nat previons locations\nand try again");
		return;
	}

	fwrite(&MengeCrank, sizeof(MengeCrank), 1, Stream);
	fwrite(&CR, sizeof(CR), 1, Stream);
	fclose(Stream);
}
//---------------------------------------------------------------------------



void
__fastcall TKFormMain::CloseKlingelClick(TObject *Sender)
{
	FormHide(Sender);
	Close();
}
//---------------------------------------------------------------------------

void
__fastcall TKFormMain::PopupMenuTrayIconPopup(TObject *Sender)
{
	if (KFormMain->Visible)
		HideShow->Caption = "Спрятать";
	else
		HideShow->Caption = "Показать";
}
//---------------------------------------------------------------------------

void
__fastcall TKFormMain::ConfigClick(TObject *Sender)
{
	Timer->Enabled = false;
	KFormCfg->ShowModal();
	Timer->Enabled = true;
}
//---------------------------------------------------------------------------




void
__fastcall TKFormMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if (MessageDlg("Выйти из программы?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0)!=mrYes)
		CanClose = false;
}
//---------------------------------------------------------------------------

