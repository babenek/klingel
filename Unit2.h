//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include "ccalendr.h"
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TKFormSlave : public TForm
{
	__published:    // IDE-managed Components
		///
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *ComboBox1;
	TLabel *Label3;
	TEdit *EditMessage;
	TDateTimePicker *MaskEditDate;
	TMaskEdit *MaskEditTime;
	void
	__fastcall FormActivate(TObject *Sender);

	void
	__fastcall MaskEditKeyPress(TObject *Sender, char &Key);
	void
	__fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:    // User declarations
public:        // User declarations
	bool Execute;
	__fastcall TKFormSlave(TComponent *Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKFormSlave
*
KFormSlave;
//---------------------------------------------------------------------------
#endif
