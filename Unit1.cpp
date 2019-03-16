//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = -10;
int y = -10;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rightUpTimerTimer(TObject *Sender)
{
       if(rightPaddle -> Top > 1) rightPaddle -> Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::rightDownTimerTimer(TObject *Sender)
{
        if(rightPaddle -> Top + 110 < background -> Height)
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
        if(leftPaddle -> Top + 110 <= background -> Height)
                leftPaddle -> Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leftUpTimer(TObject *Sender)
{
        if(leftPaddle -> Top >= 10) leftPaddle -> Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ballTimerTimer(TObject *Sender)
{
        ball -> Left += x;
        ball -> Top += y;

        // top
        if (ball -> Top <= background -> Top) y = -y;

        //bottom
        if (ball -> Top + ball -> Height + 10 >=  background -> Height) y = -y;

        //fail

        if (ball -> Left <= background -> Left ||
        ball -> Left + ball -> Width >= background -> Left + background -> Width)
        {
                ballTimer -> Enabled = false;
                ball -> Visible = false;
                
        } else if (ball->Top > leftPaddle->Top - ball->Top + 5 &&
                ball->Top + ball->Height < leftPaddle->Top + leftPaddle->Height &&
                ball->Left < leftPaddle->Left + leftPaddle->Width )
        {
               if( x<0) x = -x;
        } else if (ball->Top > rightPaddle->Top - ball->Top + 5 &&
                ball->Top + ball->Height < rightPaddle->Top + rightPaddle->Height &&
                ball->Left + ball->Width > rightPaddle->Left )
        {
               if( x>0) x = -x;
        }
}
//---------------------------------------------------------------------------


