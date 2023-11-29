#pragma once
#include "Config.h"

//--------------------------------------------------------------------------------------------------------------
enum EBrick_Type: char
{                                               
   EBT_None,                                      
   EBT_Blue,
   EBT_Red
};
//--------------------------------------------------------------------------------------------------------------
class AActive_Brick
{
public:
   AActive_Brick(EBrick_Type Brick_Type);

   void Act(HWND hwnd);
   void Draw(HDC hdc, RECT &paint_area);
   
   static void Setup_Color();

   static const int Max_Fade_step = 80;

   static HPEN Fading_Blue_Brick_Pens[Max_Fade_step];
   static HBRUSH Fading_Blue_Brick_Brushes[Max_Fade_step];

   static HPEN Fading_Red_Brick_Pens[Max_Fade_step];
   static HBRUSH Fading_Red_Brick_Brushes[Max_Fade_step];

   RECT Brick_Rect;
   EBrick_Type Brick_Type;
   int Fade_Step;
};
//--------------------------------------------------------------------------------------------------------------