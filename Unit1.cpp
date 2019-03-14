//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int positionOfLeftPaddleX;
int positionOfLeftPaddleY;
int positionOfRightPaddleX;
int positionOfRightPaddleY;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rightUpTimerTimer(TObject *Sender)
{
       if(rightPaddle -> Top > 10) rightPaddle -> Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::rightDownTimerTimer(TObject *Sender)
{
        if(rightPaddle -> Top + 100 < background -> Height - 10)
                rightPaddle -> Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_UP) rightUp -> Enabled = true;
        if(Key == VK_DOWN) rightDown -> Enabled = true;

        if(Key == 'A') leftUp -> Enabled = true;
        if(Key == 'Z') leftDown -> Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == VK_UP) rightUp -> Enabled = false;
        if(Key == VK_DOWN) rightDown -> Enabled = false;
        if(Key == 'A') leftUp -> Enabled = false;
        if(Key == 'Z') leftDown -> Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        leftPaddle -> Top = 150;
        leftPaddle -> Left = 16;
        rightPaddle -> Top = 150;
        rightPaddle -> Left = Form1 -> Width - 52;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
        leftPaddle -> Top = 150;
        leftPaddle -> Left = 16;
        rightPaddle -> Top = 150;
        rightPaddle -> Left = Form1 -> Width - 52;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leftDownTimer(TObject *Sender)
{
        if(leftPaddle -> Top + 100 < background -> Height - 10)
                leftPaddle -> Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leftUpTimer(TObject *Sender)
{
        if(leftPaddle -> Top > 10) leftPaddle -> Top -= 10;
}
//---------------------------------------------------------------------------

