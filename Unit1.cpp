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
int leftPoints = 0;
int rightPoints = 0;
int bounces = 0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Application->MessageBox(    "Witaj w PingPong.\n"
                        "\n"
                        "Lewy gracz steruje wciskaj¹c klawisze A oraz Z.\n"
                        "Prawy gracz steruje wciskaj¹c strza³ki do góry i w dó³.\n"
                        "\n"
                        "Dla urozmaicenia zabawy:\n"
                        "Kiedy odbijesz pi³kê na srodku paletki, wówczas zmienisz jej k¹t odbicia i pi³ka przyspieszy.\n"
                        "Im d³u¿ej odbijasz, tym pi³ka szybciej przemieszcza siê.\n"
                        "Mo¿esz dowolnie zmieniac pole gry.\n"
                        "\n"
                        "Mi³ej zabawy!", "PingPong", MB_OK);

        leftPaddle -> Top = 150;
        leftPaddle -> Left = 16;
        rightPaddle -> Top = 150;
        rightPaddle -> Left = Form1 -> Width - 52;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::rightUpTimerTimer(TObject *Sender)
{
       if(rightPaddle -> Top > 1) rightPaddle -> Top -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::rightDownTimerTimer(TObject *Sender)
{
        if(rightPaddle -> Top + 99 < background -> Height)
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

        ball->Visible = true;
        ballTimer->Enabled = false;
        ball->Top = background->Height / 2 - ball->Height / 2;
        ball->Left = background->Width / 2 - ball->Width / 2;

        welcome->Caption = " Zagrajmy w Ping Ponga! ";
        welcome->Top = background->Height *0.15;
        welcome->Left = background->Width / 2 - welcome->Width / 2;

        Points->Visible = false;

        nextGame->Top = background->Height *0.75;
        nextGame->Left = background->Width / 2 - nextGame->Width / 2;
        nextGame->Visible = false;

        newGame->Top = background->Height *0.6;
        newGame->Left = background->Width / 2 - nextGame->Width / 2;
        newGame->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
        Form1->FormCreate(Form1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leftDownTimer(TObject *Sender)
{
        if(leftPaddle -> Top + 99 < background -> Height)
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
                if(ball -> Left < background -> Left)
                {
                        rightPoints++;
                        welcome->Caption = " Punkt dla gracza Prawego >>> ";

                        Points->Visible = true;
                        Points->Left =  welcome->Left;
                        Points->Width = welcome->Width;
                        Points->Caption = IntToStr(leftPoints) + " : " + IntToStr(rightPoints);

                        Bounces->Visible = true;
                        Bounces->Left =  welcome->Left;
                        Bounces->Width = welcome->Width;
                        Bounces->Caption = "Ilosc odbic pilka: " + IntToStr(bounces);

                }
                if(ball -> Left + ball -> Width > background -> Left + background -> Width)
                {
                        leftPoints++;
                        welcome->Caption = " <<< Punkt dla gracza Lewego ";

                        Points->Visible = true;
                        Points->Left =  welcome->Left;
                        Points->Width = welcome->Width;
                        Points->Caption = IntToStr(leftPoints) + " : " + IntToStr(rightPoints);

                        Bounces->Visible = true;
                        Bounces->Left =  welcome->Left;
                        Bounces->Width = welcome->Width;
                        Bounces->Caption = "Ilosc odbic pilka: " + IntToStr(bounces);
                }
                ballTimer -> Enabled = false;
                ball -> Visible = false;
                welcome->Visible = true;
                nextGame->Visible = true;
                newGame->Visible = true;

        } else if (ball->Top > leftPaddle->Top &&
                ball->Top + ball->Height < leftPaddle->Top + leftPaddle->Height &&
                ball->Left <= leftPaddle->Left + leftPaddle->Width )
        {
               if( x<0)
               {

                        x = -x;
                        bounces++;
               }

        } else if (ball->Top > rightPaddle->Top &&
                ball->Top + ball->Height < rightPaddle->Top + rightPaddle->Height &&
                ball->Left + ball->Width >= rightPaddle->Left )
        {
               if( x>0) x = -x;
               bounces++;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::nextGameClick(TObject *Sender)
{
        bounces = 0;
        newGame->Visible = false;
        ball->Top = background->Height / 2 - ball->Height / 2;
        ball->Left = background->Width / 2 - ball->Width / 2;

        ball->Visible = true;
        welcome->Visible = false;

        ballTimer->Enabled = true;
        nextGame->Visible = false;

        Points->Visible = false;
        Bounces->Visible = false;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::newGameClick(TObject *Sender)
{
        if(Application->MessageBox("Czy napewno rozpoczac od pocz¹tku?", "PotwierdŸ...", MB_YESNO) == IDYES)
        {
                leftPoints = 0;
                rightPoints = 0;
                bounces = 0;
                ball->Top = background->Height / 2 - ball->Height / 2;
                ball->Left = background->Width / 2 - ball->Width / 2;

                ball->Visible = true;
                welcome->Visible = false;

                ballTimer->Enabled = true;
                newGame->Visible = false;
                nextGame->Visible = false;

                Points->Visible = false;
                Bounces->Visible = false;
        }
}
//---------------------------------------------------------------------------



