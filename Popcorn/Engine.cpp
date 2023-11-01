#include "Engine.h"

const int Global_Scale = 3;                     // Глобальный масштаб
const int Brick_Width = 15;                     // Ширина кирпича
const int Brick_Height = 7;                     // Высота кирпича
const int Cell_Width = Brick_Width + 1;         // Ширина ячейки (16 px)
const int Cell_Height = Brick_Height + 1;       // Высота ячейки (17 px)
const int Lelvel_X_Offset = 8;                  // Смещение поле по Х 
const int Lelvel_Y_Offset = 6;                  // Смещение поле по Y 
const int Circle_Size = 7;                      // Размер круга платформы

int Inner_Width = 21;                           // Ширина платформы

HPEN Brick_Red_Pen, Brick_Blue_Pen;             // Создаем карандаш
HBRUSH Brick_Red_Brush, Brick_Blue_Brush;       // Создаем кисть

char Level_01[14][12] =                         // Отрисовка расположение кирпича и тип кирпича
{
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

enum EBrick_Type: char
{                                               // None - 0, Blue - 1, Red - 2
   EBT_None,                                      
   EBT_Blue,
   EBT_Red
};
//--------------------------------------------------------------------------------------------------------------
void Init()
{// Настройка игры при старте                                                                                                                      
   Brick_Blue_Pen = CreatePen(PS_SOLID, 0, RGB(85, 255, 255));             // Создал карандаш для окраски кирпича
   Brick_Blue_Brush = CreateSolidBrush(RGB(85, 255, 255));                 // Создал кисть для окраски кирпича

   Brick_Red_Pen = CreatePen(PS_SOLID, 0, RGB(255, 85, 85)); 
   Brick_Red_Brush = CreateSolidBrush(RGB(255, 85, 85));
}
//--------------------------------------------------------------------------------------------------------------
void Draw_Brick(HDC hdc, int x, int y , char brick_type)
{// Вывод кирпича                                                    
   HPEN pen;
   HBRUSH brush;

   switch (brick_type)
   {
   case EBT_None:
      return;

   case EBT_Blue:
      pen = Brick_Blue_Pen; 
      brush = Brick_Blue_Brush;  
      break;

   case EBT_Red:
      pen = Brick_Red_Pen;
      brush = Brick_Red_Brush;
      break;

   default:
      return;
   }
   SelectObject(hdc, pen);    // Окрашиваем карандашом(pen) наш объект(кирпич - рамка)
   SelectObject(hdc, brush);  // Окрашиваем кистью(brush) наш объект(кирпич - тело)

   RoundRect(hdc, x * Global_Scale, y * Global_Scale, (x + Brick_Width) * Global_Scale, 
      (y + Brick_Height) * Global_Scale, 2 * Global_Scale, 2 * Global_Scale);      // Отрисовка прямоугольника  c закругленными углами
}
//--------------------------------------------------------------------------------------------------------------
void Draw_Level(HDC hdc)
{ // Вывод всех кирпичей
   int i, j;

   for (i = 0; i < 14; i++) 
      for (j = 0; j < 12; j++) 
         Draw_Brick(hdc, Lelvel_X_Offset + j * Cell_Width, Lelvel_Y_Offset + i * Cell_Height, Level_01[i][j]);
}
//--------------------------------------------------------------------------------------------------------------
void Draw_Platform(HDC hdc, int x, int y)                                          
{// Рисую платформу
   SelectObject(hdc, Brick_Red_Pen);    
   SelectObject(hdc, Brick_Red_Brush);

   Ellipse(hdc, x * Global_Scale, y * Global_Scale, (x + Circle_Size) * Global_Scale, (y + Circle_Size) * Global_Scale);
   Ellipse(hdc, (x + Inner_Width) * Global_Scale, y * Global_Scale, (x + Circle_Size + Inner_Width) * Global_Scale, (y + Circle_Size) * Global_Scale);

   SelectObject(hdc, Brick_Blue_Pen);    
   SelectObject(hdc, Brick_Blue_Brush); 

   RoundRect(hdc, (x + 4) * Global_Scale, (y + 1) * Global_Scale, (x + 4 + Inner_Width - 1) * Global_Scale, (y + 1 + 5) * Global_Scale, 3 * Global_Scale, 3 * Global_Scale);
}
//--------------------------------------------------------------------------------------------------------------
void Draw_Frame(HDC hdc)                                          
{// Отрисовка экрана игры                                                                 
   Draw_Level(hdc);
   Draw_Platform(hdc, 50, 150);
}
//--------------------------------------------------------------------------------------------------------------
