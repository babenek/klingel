//---------------------------------------------------------------------------
#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TKFormMsg : public TForm
{
	__published:    // IDE-managed Components
		TBitBtn*BitBtn1;
	TBitBtn *BitBtn2;
	TBitBtn *BitBtn3;
	TStaticText *StaticText1;
private:    // User declarations
public:        // User declarations
	__fastcall TKFormMsg(TComponent *Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKFormMsg
*
KFormMsg;
//---------------------------------------------------------------------------
#endif
