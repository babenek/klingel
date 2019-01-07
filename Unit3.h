//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include <OleCtnrs.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TKFormCfg : public TForm
{
	__published:    // IDE-managed Components
		TRadioGroup*RadioGroupSignal;
	TButton *ButtonOLE;
	TButton *ButtonWAV;
	TMaskEdit *MaskEditSpeaker;
	TUpDown *UpDownSpeaker;
	TOpenDialog *OpenDialog;
	TLabel *Label1;
	TCheckBox *CheckBoxMessage;
	void
	__fastcall ButtonWAVClick(TObject *Sender);
	void
	__fastcall ButtonOLEClick(TObject *Sender);
private:    // User declarations
public:        // User declarations
	__fastcall TKFormCfg(TComponent *Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKFormCfg
*
KFormCfg;
//---------------------------------------------------------------------------
#endif
