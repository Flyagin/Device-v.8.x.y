#include "header.h"

/*****************************************************/
//Формуємо екран відображення заголовків настройок
/*****************************************************/
void make_ekran_chose_settings(void)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CHOSE_SETTINGS][MAX_COL_LCD] = 
  {
    {
      " Версия ПО и КП ",
      " Метка настроек ",
      " Входы          ",
      " Выходы         ",
      " Светоиндикаторы",
      " Выключатель    ",
      " Трансформаторы ",
      " УВВ            ",
      " Коммуникация   ",
      " Регистраторы   ",
      " О-функции      ",
      " О-триггеры     ",
      " Ф-кнопки       ",
      " Группа уставок ",
      " Доп.настройки  ",
      " Пароли         "
    },
    {
      " Версія ПЗ і КП ",
      " Мітка налашт.  ",
      " Входи          ",
      " Виходи         ",
      " Світлоіндикат. ",
      " Вимикач        ",
      " Трансформатори ",
      " УВВ            ",
      " Комунікація    ",
      " Реєстратори    ",
      " В-функції      ",
      " В-триґери      ",
      " Ф-кнопки       ",
      " Група уставок  ",
      " Дод.налашт.    ",
      " Паролі         "
    },
    {
      " VER.of F/W & MM",
      " Settings Mark  ",
      " Inputs         ",
      " Outputs        ",
      " LED            ",
      " Circuit-Breaker",
      " Transformers   ",
      " BIOS           ",
      " Communication  ",
      " Recorders      ",
      " UD Functions   ",
      " UD Flip-Flops  ",
      " F-Keys         ",
      " Pick-up Set    ",
      " Addit.Settings ",
      " Passwords      "
    },
    {
      " Версия ПО и КП ",
      " Метка настроек ",
      " Входы          ",
      " Выходы         ",
      " Светоиндикаторы",
      " Выключатель    ",
      " Трансформаторы ",
      " УВВ            ",
      " Коммуникация   ",
      " Регистраторы   ",
      " О-функции      ",
      " О-триггеры     ",
      " Ф-кнопки       ",
      " Группа уставок ",
      " Доп.настройки  ",
      " Пароли         "
    }
  };

  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  
  index_of_ekran = (position_temp >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  //Копіюємо  рядки у робочий екран
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    //Наступні рядки треба перевірити, чи їх требе відображати у текучій коффігурації
    if (index_of_ekran < MAX_ROW_FOR_CHOSE_SETTINGS)
    {
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran][j];
    } 
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Курсор по горизонталі відображається на першій позиції
  current_ekran.position_cursor_x = 0;
  //Відображення курору по вертикалі
  current_ekran.position_cursor_y = position_temp & (MAX_ROW_LCD - 1);
  //Курсор видимий
  current_ekran.cursor_on = 1;
  //Курсор не мигає
  current_ekran.cursor_blinking_on = 0;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
