#include "header.h"

/*****************************************************/
//Формуємо екран відображення уставок "Контроль напруги О/Р живлення"
/*****************************************************/
void make_ekran_setpoint_control_U(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_SETPOINT_CONTROL_U][MAX_COL_LCD] = 
  {
    {
      "   Уст. U ОЛ    ",
      "   Уст. U РЛ    "
    },
    {
      "   Уст. U ОЛ    ",
      "   Уст. U РЛ    "
    },
    {
      "   Уст. U ОЛ    ",
      "   Уст. U РЛ    "
    },
    {
      "   Уст. U ОЛ    ",
      "   Уст. U РЛ    "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //Множення на два величини position_temp потрібне для того, бо наодн позицію ми використовуємо два рядки (назва + значення)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;
  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_SETPOINT_CONTROL_U<<1))//Множення на два константи MAX_ROW_FOR_SETPOINT_CONTROL_U потрібне для того, бо наодн позицію ми використовуємо два рядки (назва + значення)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_STPCONTROL_U_OL)
        {
          vaga = 100000; //максимальний ваговий коефіцієнт для вилілення старшого розряду
          if (current_ekran.edition == 0) value = current_settings.setpoint_U_ol[group]; //у змінну value поміщаємо значення уставки
          else value = edition_settings.setpoint_U_ol[group];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений
        }
        else if ((index_of_ekran>>1) == INDEX_ML_STPCONTROL_U_RL)
        {
          vaga = 100000; //максимальний ваговий коефіцієнт для вилілення старшого розряду
          if (current_ekran.edition == 0) value = current_settings.setpoint_U_rl[group]; //у змінну value поміщаємо значення уставки
          else value = edition_settings.setpoint_U_rl[group];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений
        }
      }
      else
      {
        //У парному номері рядку виводимо значення уставки
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_STPCONTROL_U_OL)
          {
            if (
                ((j < COL_SETPOINT_CONTROL_U_OL_BEGIN) ||  (j > COL_SETPOINT_CONTROL_U_OL_END ))  &&
                (j != (COL_SETPOINT_CONTROL_U_OL_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_CONTROL_U_OL_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_CONTROL_U_OL_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_CONTROL_U_OL_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_STPCONTROL_U_RL)
          {
            if (
                ((j < COL_SETPOINT_CONTROL_U_RL_BEGIN) ||  (j > COL_SETPOINT_CONTROL_U_RL_END )) &&
                (j != (COL_SETPOINT_CONTROL_U_RL_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_SETPOINT_CONTROL_U_RL_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_SETPOINT_CONTROL_U_RL_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_V];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_SETPOINT_CONTROL_U_RL_COMMA, 0);
          }
        }
      }
        
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //Курсор по горизонталі відображається на першому символі у випадку, коли ми не в режимі редагування, інакше позиція буде визначена у функцї main_manu_function
  if (current_ekran.edition == 0)
  {
    int last_position_cursor_x = MAX_COL_LCD;
    if (current_ekran.index_position == INDEX_ML_STPCONTROL_U_OL)
    {
      current_ekran.position_cursor_x = COL_SETPOINT_CONTROL_U_OL_BEGIN;
      last_position_cursor_x = COL_SETPOINT_CONTROL_U_OL_END;
    }
    else if (current_ekran.index_position == INDEX_ML_STPCONTROL_U_RL) 
    {
      current_ekran.position_cursor_x = COL_SETPOINT_CONTROL_U_RL_BEGIN;
      last_position_cursor_x = COL_SETPOINT_CONTROL_U_RL_END;
    }
    
    //Підтягуємо курсор до першого символу
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;
    
    //Курсор ставимо так, щоб він був перед числом
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //Курсор видимий
  current_ekran.cursor_on = 1;
  //Курсор не мигає
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення витримок "Контроль напруги О/Р живлення"
/*****************************************************/
void make_ekran_timeout_control_U(unsigned int group)
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_TIMEOUT_CONTROL_U][MAX_COL_LCD] = 
  {
    { 
      "     T U ОЛ     ",
      "     T U РЛ     "
    },
    {
      "     T U ОЛ     ",
      "     T U РЛ     "
    },
    {
      "     T U ОЛ     ",
      "     T U РЛ     "
    },
    {
      "     T U ОЛ     ",
      "     T U РЛ     "
    }
  };
  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;
  unsigned int vaga, value, first_symbol;
  
  //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_TIMEOUT_CONTROL_U<<1))//Множення на два константи MAX_ROW_FOR_TIMEOUT_CONTROL_U потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
        if ((index_of_ekran>>1) == INDEX_ML_TMOCONTROL_U_OL)
        {
          vaga = 10000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для витримки
          if (current_ekran.edition == 0) value = current_settings.timeout_U_ol[group]; //у змінну value поміщаємо значення витримки
          else value = edition_settings.timeout_U_ol[group];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений
        }
        else if ((index_of_ekran>>1) == INDEX_ML_TMOCONTROL_U_RT)
        {
          vaga = 10000; //максимальний ваговий коефіцієнт для вилілення старшого розряду для витримки 2 Ступені "Контроль напруги О/Р живлення"
          if (current_ekran.edition == 0) value = current_settings.timeout_U_rl[group]; //у змінну value поміщаємо значення витримки 2 Ступені "Контроль напруги О/Р живлення"
          else value = edition_settings.timeout_U_rl[group];
          first_symbol = 0; //помічаємо, що ще ніодин значущий символ не виведений
        }
      }
      else
      {
        //У парному номері рядку виводимо значення уставки
        for (unsigned int j = 0; j<MAX_COL_LCD; j++)
        {
          if ((index_of_ekran>>1) == INDEX_ML_TMOCONTROL_U_OL)
          {
            if (
                ((j < COL_TMO_CONTROL_U_OL_BEGIN) ||  (j > COL_TMO_CONTROL_U_OL_END )) &&
                (j != (COL_TMO_CONTROL_U_OL_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_CONTROL_U_OL_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_CONTROL_U_OL_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_CONTROL_U_OL_COMMA, 0);
          }
          else if ((index_of_ekran>>1) == INDEX_ML_TMOCONTROL_U_RT)
          {
            if (
                ((j < COL_TMO_CONTROL_U_RL_BEGIN) ||  (j > COL_TMO_CONTROL_U_RL_END )) &&
                (j != (COL_TMO_CONTROL_U_RL_END + 2))  
               )working_ekran[i][j] = ' ';
            else if (j == COL_TMO_CONTROL_U_RL_COMMA )working_ekran[i][j] = ',';
            else if (j == (COL_TMO_CONTROL_U_RL_END + 2)) working_ekran[i][j] = odynyci_vymirjuvannja[index_language][INDEX_SECOND];
            else
              calc_symbol_and_put_into_working_ekran((working_ekran[i] + j), &value, &vaga, &first_symbol, j, COL_TMO_CONTROL_U_RL_COMMA, 0);
          }
        }
      }
        
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //Курсор по горизонталі відображається на першому символі у випадку, коли ми не в режимі редагування, інакше позиція буде визначена у функцї main_manu_function
  if (current_ekran.edition == 0)
  {
    int last_position_cursor_x = MAX_COL_LCD;
    if (current_ekran.index_position == INDEX_ML_TMOCONTROL_U_OL)
    {
      current_ekran.position_cursor_x = COL_TMO_CONTROL_U_OL_BEGIN;
      last_position_cursor_x = COL_TMO_CONTROL_U_OL_END;
    }
    else if (current_ekran.index_position == INDEX_ML_TMOCONTROL_U_RT)
    {
      current_ekran.position_cursor_x = COL_TMO_CONTROL_U_RL_BEGIN;
      last_position_cursor_x = COL_TMO_CONTROL_U_RL_END;
    }

    //Підтягуємо курсор до першого символу
    while (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x + 1]) == ' ') && 
           (current_ekran.position_cursor_x < (last_position_cursor_x -1))) current_ekran.position_cursor_x++;

    //Курсор ставимо так, щоб він був перед числом
    if (((working_ekran[current_ekran.position_cursor_y][current_ekran.position_cursor_x]) != ' ') && 
        (current_ekran.position_cursor_x > 0)) current_ekran.position_cursor_x--;
  }
  //Курсор видимий
  current_ekran.cursor_on = 1;
  //Курсор не мигає
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//Формуємо екран відображення значення управлінської інформації для "Контроль напруги О/Р живлення"
/*****************************************************/
void make_ekran_control_control_U()
{
  const unsigned char name_string[MAX_NAMBER_LANGUAGE][MAX_ROW_FOR_CONTROL_CONTROL_U][MAX_COL_LCD] = 
  {
    {
      "   Контр.U ОЛ   ",
      "   Контр.U РЛ   "
    },
    {
      "   Контр.U ОЛ   ",
      "   Контр.U РЛ   "
    },
    {
      "   Контр.U ОЛ   ",
      "   Контр.U РЛ   "
    },
    {
      "   Контр.U ОЛ   ",
      "   Контр.U РЛ   "
    }
  };

  int index_language = index_language_in_array(current_settings.language);
  
  unsigned int position_temp = current_ekran.index_position;
  unsigned int index_of_ekran;

  //Множення на два величини position_temp потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
  index_of_ekran = ((position_temp<<1) >> POWER_MAX_ROW_LCD) << POWER_MAX_ROW_LCD;

  
  for (unsigned int i=0; i< MAX_ROW_LCD; i++)
  {
    if (index_of_ekran < (MAX_ROW_FOR_CONTROL_CONTROL_U<<1))//Множення на два константи MAX_ROW_FOR_CONTROL_CONTROL_U потрібне для того, бо на одну позицію ми використовуємо два рядки (назва + значення)
    {
      if ((i & 0x1) == 0)
      {
        //У непарному номері рядку виводимо заголовок
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = name_string[index_language][index_of_ekran>>1][j];
      }
      else
      {
        //У парному номері рядку виводимо значення уставки
        const unsigned char information[MAX_NAMBER_LANGUAGE][2][MAX_COL_LCD] = 
        {
          {"     Откл.      ", "      Вкл.      "},
          {"     Вимк.      ", "     Ввімк.     "},
          {"      Off       ", "       On       "},
          {"     Сљнд.      ", "     Косу.      "}
        };
        const unsigned int cursor_x[MAX_NAMBER_LANGUAGE][2] = 
        {
         {4, 5},
         {4, 4},
         {5, 6},
         {4, 4}
        };
        
        unsigned int index_ctr = (index_of_ekran>>1);

        unsigned int temp_data;
        if(current_ekran.edition == 0) temp_data = current_settings.control_control_U;
        else temp_data = edition_settings.control_control_U;
        
        for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = information[index_language][(temp_data >> index_ctr) & 0x1][j];
        current_ekran.position_cursor_x = cursor_x[index_language][(temp_data >> index_ctr) & 0x1];
      }
    }
    else
      for (unsigned int j = 0; j<MAX_COL_LCD; j++) working_ekran[i][j] = ' ';

    index_of_ekran++;
  }

  //Відображення курору по вертикалі і курсор завжди має бути у полі із значенням устаки
  current_ekran.position_cursor_y = ((position_temp<<1) + 1) & (MAX_ROW_LCD - 1);
  //Курсор видимий
  current_ekran.cursor_on = 1;
  //Курсор не мигає
  if(current_ekran.edition == 0)current_ekran.cursor_blinking_on = 0;
  else current_ekran.cursor_blinking_on = 1;
  //Обновити повністю весь екран
  current_ekran.current_action = ACTION_WITH_CARRENT_EKRANE_FULL_UPDATE;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
