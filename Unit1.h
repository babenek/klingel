//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Db.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ToolWin.hpp>
#include <OleCtnrs.hpp>
#include "Trayicon.h"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
#define MaxRec 365
#define MaxChar 64

#define ENABLE 0
#define DISABLE 1
#define SKIP 2
#define DAILY 3
//#define TEMP 4
// цифры - для комбобокса

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
class TKFormMain : public TForm
{
	__published:    // IDE-managed Components
		TListBox*ListBoxRecords;
	TTimer *Timer;
	TPopupMenu *PopupMenuMain;
	TMenuItem *Delete1;
	TStatusBar *StatusBarDateTime;
	TMenuItem *Change1;
	TMenuItem *Add1;
	THeaderControl *HeaderControl;
	TMainMenu *MainMenu;
	TMenuItem *RemoveAll;
	TPopupMenu *PopupMenuTrayIcon;
	TMenuItem *HideShow;
	TMenuItem *Exit1;
	TMenuItem *Config;
	TOleContainer *OleContainer;
	TMenuItem *About;
	TTrayIcon *TrayIconKlingel;
	TImageList *ImageListKlingel;
	void
	__fastcall TimerTimer(TObject *Sender);
	void
	__fastcall RefreshListBox1(void);
	void
	__fastcall Clearall1Click(TObject *Sender);
	void
	__fastcall Delete1Click(TObject *Sender);
	void
	__fastcall Add1Click(TObject *Sender);
	void
	__fastcall Change1Click(TObject *Sender);

	void
	__fastcall ListBoxRecordsKeyPress(TObject *Sender, char &Key);

	void
	__fastcall AboutClick(TObject *Sender);
	void
	__fastcall FormShow(TObject *Sender);
	void
	__fastcall FormHide(TObject *Sender);

	void
	__fastcall CloseKlingelClick(TObject *Sender);
	void
	__fastcall PopupMenuTrayIconPopup(TObject *Sender);

	void
	__fastcall ConfigClick(TObject *Sender);
	void
	__fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void
	__fastcall HideShowClick(TObject *Sender);
private:    // User declarations

	int MengeCrank;    //     кол-тво записей()заводов
	AnsiString HomeDir;  //   домашняя директория
	short int NumBeep;   //   количество бикалок за одну секунду
	double dTime;        //   протяженность времени сигнализации

public:        // User declarations
	struct CrankRec
	{     //  структура записей(заводов)
		double CRTime;//[MaxRec];
		double CRDate;//[MaxRec];
		int CRState;//[MaxRec];
		char CRMessage[MaxChar];
	};
	CrankRec CR[MaxRec]; // сами записи в листбоксе
	CrankRec FS;   // для обмена между формами

	__fastcall TKFormMain(TComponent *Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKFormMain
*
KFormMain;
//---------------------------------------------------------------------------
#endif
