#include "header.h"

/*****************************************************/
//��������� �������� � ������ �� SPI
/*****************************************************/
void start_exchange_via_spi(int index_chip, unsigned int number_bytes_transfer)
{
  //Գ����� ������ ���� �� ����� ���������� (�� ������� �� ������� ���������� ������� - ��� ����� ���� �������� ��������� �� ��������)
  number_bytes_transfer_spi_df = number_bytes_transfer;
  
  //��������� ���� DMA �� ������ ����� ���� �� ���������
  if ((DMA_StreamSPI_DF_Rx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamSPI_DF_Rx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Rx->NDTR = number_bytes_transfer;
  //��������� ���� DMA �� �������� ����� ���� �� ���������
  if ((DMA_StreamSPI_DF_Tx->CR & (uint32_t)DMA_SxCR_EN) !=0) DMA_StreamSPI_DF_Tx->CR &= ~(uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Tx->NDTR = number_bytes_transfer;
  
  //������� ���������, �� �������� ��� ���������� ������/�������� ����� ��� DMA1 �� ������ SPI_DF_Rx � SPI_DF_Tx
  DMA_ClearFlag(DMA_StreamSPI_DF_Rx, DMA_FLAG_TCSPI_DF_Rx | DMA_FLAG_HTSPI_DF_Rx | DMA_FLAG_TEISPI_DF_Rx | DMA_FLAG_DMEISPI_DF_Rx | DMA_FLAG_FEISPI_DF_Rx);
  DMA_ClearFlag(DMA_StreamSPI_DF_Tx, DMA_FLAG_TCSPI_DF_Tx | DMA_FLAG_HTSPI_DF_Tx | DMA_FLAG_TEISPI_DF_Tx | DMA_FLAG_DMEISPI_DF_Tx | DMA_FLAG_FEISPI_DF_Tx);
  
  //���������� �������� ����� DMA
  if ((SPI_DF->CR2 & SPI_I2S_DMAReq_Tx) == 0) SPI_DF->CR2 |= SPI_I2S_DMAReq_Tx;
  //���������� ������ ����� DMA
  if ((SPI_DF->CR2 & SPI_I2S_DMAReq_Rx) == 0) SPI_DF->CR2 |= SPI_I2S_DMAReq_Rx;

  //����������� chip_select  � ������������� � ������� �����������, �� ��� ����
  if (index_chip == INDEX_DATAFLASH_1) GPIO_SPI_DF_TOGGLE->BSRRH = GPIO_SPI_DF_TOGGLE_Pin;//DF_TOGGLE - �� ���������� � 0 
  else if (index_chip == INDEX_DATAFLASH_2)GPIO_SPI_DF_TOGGLE->BSRRL = GPIO_SPI_DF_TOGGLE_Pin;//DF_TOGGLE - �� ���������� � 1
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(6);
  }
  driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING;
  GPIO_SPI_DF->BSRRH = GPIO_NSSPin_DF; //����������� Chip_select ��������� NSS  � 0

  //���������� ��������� ���������� �� ������ DMA_StreamSPI_DF_Rx
  DMA_StreamSPI_DF_Rx->CR |= DMA_IT_TC;
  
  //������� ������ ��������
  SPI_DF->DR;
  SPI_DF->SR;

  //��������� ������-�������� 
  DMA_StreamSPI_DF_Rx->CR |= (uint32_t)DMA_SxCR_EN;
  DMA_StreamSPI_DF_Tx->CR |= (uint32_t)DMA_SxCR_EN;
}
/*****************************************************/

/*****************************************************/
//������ ���������� ������� � ��������� dataFlash
/*****************************************************/
void dataflash_status_read(int index_chip)
{
  if ((index_chip == INDEX_DATAFLASH_1) || (index_chip == INDEX_DATAFLASH_2))
  {
    driver_spi_df[index_chip].code_operation = CODE_OPERATION_STATUS_READ;
    TxBuffer_SPI_DF[0] = 0xD7;
    start_exchange_via_spi(index_chip, 2);
  }
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(7);
  }
  
}
/*****************************************************/

/*****************************************************/
//������ ������� �� ���������������� DataFlash �� ����� ������� 256�
/*****************************************************/
void dataflash_set_pagesize_256(int index_chip)
{
  if ((index_chip == INDEX_DATAFLASH_1) || (index_chip == INDEX_DATAFLASH_2))
  {
    driver_spi_df[index_chip].code_operation = CODE_OPERATION_PAGESIZE_256;
    TxBuffer_SPI_DF[0] = 0x3D;
    TxBuffer_SPI_DF[1] = 0x2A;
    TxBuffer_SPI_DF[2] = 0x80;
    TxBuffer_SPI_DF[3] = 0xA6;
    start_exchange_via_spi(index_chip, 4);
  }
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(8);
  }
  
}
/*****************************************************/

/*****************************************************/
//������ ������� ������� �������� ���������
/*****************************************************/
void dataflash_erase(int index_chip)
{
  if ((index_chip == INDEX_DATAFLASH_1) || (index_chip == INDEX_DATAFLASH_2))
  {
    driver_spi_df[index_chip].code_operation = CODE_OPERATION_ERASE;
    TxBuffer_SPI_DF[0] = 0xC7;
    TxBuffer_SPI_DF[1] = 0x94;
    TxBuffer_SPI_DF[2] = 0x80;
    TxBuffer_SPI_DF[3] = 0x9A;
    start_exchange_via_spi(index_chip, 4);
  }
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(9);
  }
  
}
/*****************************************************/

/*****************************************************/
//����� ����� � ����� � ��������� ��������� � ������������������
/*****************************************************/
void dataflash_mamory_page_program_through_buffer(int index_chip)
{
  unsigned int size_page;
  driver_spi_df[index_chip].code_operation = CODE_OPERATION_WRITE_PAGE_THROUGH_BUFFER;
  TxBuffer_SPI_DF[0] = 0x82;
  
  if (index_chip == INDEX_DATAFLASH_1)
  {
    size_page = SIZE_PAGE_DATAFLASH_1;

    //����� ����� ����������� ����������
      
    //������� ����� ��� ������
    if(part_writing_dr_into_dataflash < NUMBER_PAGES_IN_ONE_DR_RECORD)
    {
      //������� ������ ��� ������
      unsigned int address_for_program_dataflash = info_rejestrator_dr.next_address + part_writing_dr_into_dataflash*size_page;
        
      TxBuffer_SPI_DF[1] = (address_for_program_dataflash >> 16) & 0x0f; 
      TxBuffer_SPI_DF[2] = (address_for_program_dataflash >> 8 ) & 0xff; 
      TxBuffer_SPI_DF[3] = 0; 
        
      //���������� ������ ����� ������, �� ����� �������� 
      unsigned int offset_from_start = part_writing_dr_into_dataflash*size_page;
      for (unsigned int i = 0; i < size_page; i++ )
        TxBuffer_SPI_DF[4 + i] = buffer_for_save_dr_record_level_2[offset_from_start + i];
    }
    else
    {
      //³������� ����������� �������, ���� ����� ��� �� ����������������
      total_error_sw_fixed(10);
    }
  }
  else if (index_chip == INDEX_DATAFLASH_2)
  {
    size_page = SIZE_PAGE_DATAFLASH_2;

    //����� ����� ����������� ���������� (���� ������� �������)

    //������� ������ ��� ������
    TxBuffer_SPI_DF[1] = (temporary_address_ar >> 16) & 0x1f; 
    TxBuffer_SPI_DF[2] = (temporary_address_ar >> 8 ) & 0xfe; 
    TxBuffer_SPI_DF[3] = 0; 
        
    //���������� ������ ����� ������, �� ����� �������� 
    for (unsigned int i = 0; i < size_page; i++ )
    TxBuffer_SPI_DF[4 + i] = buffer_for_save_ar_record[i];
    
    /*
    ������� ������� ���� ��� ������ � ����� count_to_save 
    �� ������, �� �� ��� ��� ������ "������" � ������� buffer_for_save_ar_record
    � ���� ����� ����� ����������� ������ ������, ���� �������� ����������� � DataFlash
    ���� ���������� ����-���� ���������� ��������� � ����� permit_copy_new_data ����� �� ��������� ����� �����
    
    ����� ��� ��������� �������� ������ ��� ������
    */
    temporary_address_ar += size_page;
    count_to_save = 0;
    permit_copy_new_data = 0xff;
  }
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(11);
  }
  
  //��������� ������ ������
  start_exchange_via_spi(index_chip, (4 + size_page));
}
/*****************************************************/

/*****************************************************/
//���������� ����� �� �������� �� 66���
/*****************************************************/
void dataflash_mamory_read(int index_chip)
{
  unsigned int size_page;

  driver_spi_df[index_chip].code_operation = CODE_OPERATION_READ_HIGH_FREQ;
  TxBuffer_SPI_DF[0] = 0x0B;

  int temp_value_for_address;
    
  if (index_chip == INDEX_DATAFLASH_1)
  {
    size_page = SIZE_PAGE_DATAFLASH_1;

    if(
       (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_MENU ) ||
       (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_USB  ) ||
       (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_RS485)
      )
    {
      //������� ����� ����������� ����������
      unsigned int part_reading;
      unsigned int number_record;
      if (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_MENU)
      {
        part_reading = part_reading_dr_from_dataflash_for_menu;
        number_record = number_record_of_dr_for_menu;
      }
      else if (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_USB)
      {
        part_reading = part_reading_dr_from_dataflash_for_USB;
        number_record = number_record_of_dr_for_USB;
      }
      else
      {
        part_reading = part_reading_dr_from_dataflash_for_RS485;
        number_record = number_record_of_dr_for_RS485;
      }

      //������� ����� ��� ����������� � ��������� DataFlash
      if(part_reading < NUMBER_PAGES_IN_ONE_DR_RECORD)
      {
        //������� ������ ��� ������� ������� ������ ���������� ����������
        temp_value_for_address = info_rejestrator_dr.next_address - (((number_record + 1)*NUMBER_PAGES_IN_ONE_DR_RECORD - part_reading)<<VAGA_SIZE_PAGE_DATAFLASH_1);
        while (temp_value_for_address < MIN_ADDRESS_DR_AREA) temp_value_for_address = temp_value_for_address + SIZE_DR_AREA; 
      
        TxBuffer_SPI_DF[1] = (temp_value_for_address >> 16) & 0x0f; 
        TxBuffer_SPI_DF[2] = (temp_value_for_address >> 8 ) & 0xff; 
        TxBuffer_SPI_DF[3] = (temp_value_for_address      ) & 0xff; 
        
        //ϳ��� ������ �� ��� ���� ��������� ���� �� ����� ����� �������� ����������� �������� �����
        
        //�������� ������� �� �� ��������

        //��������� ������ ������
        start_exchange_via_spi(index_chip, (5 + size_page));
      }
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(12);
      }
    }
    else if (
             (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU ) ||
             (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB  ) ||
             (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_RS485)
            )   
    {
      //������� ����� ���������� ���������� �������
      unsigned int number_record;
      if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU)
      {
        number_record = number_record_of_pr_err_into_menu;
      }
      else if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB)
      {
        number_record = number_record_of_pr_err_into_USB;
      }
      else
      {
        number_record = number_record_of_pr_err_into_RS485;
      }

      //��������� ��������� ������ ������, ��� ����� �������
      temp_value_for_address = info_rejestrator_pr_err.next_address - ((number_record + 1)<<VAGA_SIZE_ONE_RECORD_PR_ERR);
      while (temp_value_for_address < MIN_ADDRESS_PR_ERR_AREA) temp_value_for_address = temp_value_for_address + SIZE_PR_ERR_AREA; 
        
      TxBuffer_SPI_DF[1] = (temp_value_for_address >> 16) & 0x0f; 
      TxBuffer_SPI_DF[2] = (temp_value_for_address >> 8 ) & 0xff; 
      TxBuffer_SPI_DF[3] = (temp_value_for_address      ) & 0xff; 

      //ϳ��� ������ �� ��� ���� ��������� ���� �� ����� ����� �������� ����������� �������� �����
        
      //�������� ������� �� �� ��������

      //��������� ������ ������
      start_exchange_via_spi(index_chip, (5 + SIZE_ONE_RECORD_PR_ERR));
    }
    else
    {
      //³������� ����������� �������, ���� ����� ��� �� ����������������
      total_error_sw_fixed(13);
    }
  }
  else if (index_chip == INDEX_DATAFLASH_2)
  {
    size_page = SIZE_PAGE_DATAFLASH_2;

    if(
       (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_MENU ) ||
       (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_USB  ) ||
       (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_RS485)
      )
    {
      //������� ����� ����������� ����������
      unsigned int number_bytes;
      unsigned int size_one_ar_record_tmp = size_one_ar_record, max_number_records_ar_tmp = max_number_records_ar;
      if (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_MENU)
      {
        temp_value_for_address = info_rejestrator_ar.next_address - (number_record_of_ar_for_menu + 1)*size_one_ar_record_tmp;
        while (temp_value_for_address < MIN_ADDRESS_AR_AREA) temp_value_for_address = temp_value_for_address + size_one_ar_record_tmp*max_number_records_ar_tmp; 
        number_bytes = sizeof(__HEADER_AR);
      }
      else 
      {
        unsigned int number_record_of_ar;
        int first_number_time_sample, last_number_time_sample;
        
        if (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_USB)
        {
          number_record_of_ar = number_record_of_ar_for_USB;
          first_number_time_sample = first_number_time_sample_for_USB;
          last_number_time_sample = last_number_time_sample_for_USB;
        }
        else
        {
          number_record_of_ar = number_record_of_ar_for_RS485;
          first_number_time_sample = first_number_time_sample_for_RS485;
          last_number_time_sample = last_number_time_sample_for_RS485;
        }

        //��������� ����� ������ ��������� ������
        /*
        ������������ �������, �� ��� �������� �� ���������, �� ����� ���� �������� � ���� ��������� ��������� 
        DataFlash, � �������� - ��� �� ������� ���������. ������ � �� ����������, ���� ���� � ��� �������� ������ ������, 
        �� ������ ����� ������ ��� �������� ��� �������� �� ���������� "��������� ��������" ��� �������� �������� (�����������
        � ������������� ������)
        */
        temp_value_for_address = info_rejestrator_ar.next_address - (number_record_of_ar + 1)*size_one_ar_record_tmp;
        while (temp_value_for_address < MIN_ADDRESS_AR_AREA) temp_value_for_address = temp_value_for_address + size_one_ar_record_tmp*max_number_records_ar_tmp; 

        if (first_number_time_sample == -1)
        {
          //������� ������� ���� ����� � ���������� ����������� ����������
          number_bytes = sizeof(__HEADER_AR) + (last_number_time_sample + 1)*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int);
          //������ ������� ��� ���������, �� ���� ������� � ������� �������
        }
        else
        {
          //������� ������� ���� ����� ��� ��������� ����������� ����������
          number_bytes = (last_number_time_sample + 1 - first_number_time_sample)*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int);
          temp_value_for_address += (sizeof(__HEADER_AR) + first_number_time_sample*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int));
        }
      }

      //������� ����� ��� ����������� � ��������� DataFlash
      if(number_bytes <= size_page)
      {
        TxBuffer_SPI_DF[1] = (temp_value_for_address >> 16) & 0x1f; 
        TxBuffer_SPI_DF[2] = (temp_value_for_address >> 8 ) & 0xff; 
        TxBuffer_SPI_DF[3] = (temp_value_for_address      ) & 0xff; 
        
        //ϳ��� ������ �� ��� ���� ��������� ���� �� ����� ����� �������� ����������� �������� �����
        
        //�������� ������� �� �� ��������

        //��������� ������ ������
        start_exchange_via_spi(index_chip, (5 + number_bytes));
      }
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(31);
      }
    }
    else
    {
      //³������� ����������� �������, ���� ����� ��� �� ����������������
      total_error_sw_fixed(32);
    }
  }
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(14);
  }
}
/*****************************************************/

/*****************************************************/
//���������� ������� ���'�� DataFlash � �����
/*****************************************************/
void dataflash_mamory_page_into_buffer(int index_chip)
{
  unsigned int address_into_dataflash;
  driver_spi_df[index_chip].code_operation = CODE_OPERATION_READ_PAGE_INTO_BUFFER;
  TxBuffer_SPI_DF[0] = 0x53;
  
  if (index_chip == INDEX_DATAFLASH_1)
  {
    //������� ������ ������� ��� ���������� � ����� DataFlash
    address_into_dataflash = info_rejestrator_pr_err.next_address;

    TxBuffer_SPI_DF[1] = (address_into_dataflash >> 16) & 0x0f; 
    TxBuffer_SPI_DF[2] = (address_into_dataflash >> 8 ) & 0xff; 
    TxBuffer_SPI_DF[3] = 0; 
  }
  else if (index_chip == INDEX_DATAFLASH_2)
  {
    //������� ������ ������� ��� ���������� � ����� DataFlash
    address_into_dataflash = temporary_address_ar;

    TxBuffer_SPI_DF[1] = (address_into_dataflash >> 16) & 0x1f; 
    TxBuffer_SPI_DF[2] = (address_into_dataflash >> 8 ) & 0xfe; 
    TxBuffer_SPI_DF[3] = 0; 
  }
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(15);
  }

  //��������� ������ ������
  start_exchange_via_spi(index_chip, 4);
}
/*****************************************************/

/*****************************************************/
//����� ����� ����� � ����� �������� DataFlash
/*****************************************************/
void dataflash_mamory_write_buffer(int index_chip)
{
  unsigned int size_page;

  driver_spi_df[index_chip].code_operation = CODE_OPERATION_WRITE_BUFFER;
  TxBuffer_SPI_DF[0] = 0x84;

  if (index_chip == INDEX_DATAFLASH_1)
  {
    size_page = SIZE_PAGE_DATAFLASH_1;

    //����� ����� ���������� ���������� ���� � ���������� ��������� ���� � ��� �� ���, ��� ������ ������ ���� ��������� �� ���� �������
      
    //������� ������ ��� ������
    unsigned int next_address_into_buffer = info_rejestrator_pr_err.next_address & 0xff;
        
    TxBuffer_SPI_DF[1] = 0; 
    TxBuffer_SPI_DF[2] = 0; 
    TxBuffer_SPI_DF[3] = next_address_into_buffer; 
    
    //�������� ����������� ����� ��� �������� � ����� ��������� DataFlash ������ ��� ������
    number_recods_writing_into_dataflash_now = 0;
    unsigned int head = head_fifo_buffer_pr_err_records, tail = tail_fifo_buffer_pr_err_records;
    while(
          ((next_address_into_buffer + SIZE_ONE_RECORD_PR_ERR - 1) < size_page) &&
          (tail != head)
         )
    {
      //���������� ������ ����� ������, �� ����� �������� 
      for (unsigned int i = 0; i < SIZE_ONE_RECORD_PR_ERR; i++ )
        TxBuffer_SPI_DF[4 + number_recods_writing_into_dataflash_now*SIZE_ONE_RECORD_PR_ERR + i] =
          buffer_pr_err_records[tail*SIZE_ONE_RECORD_PR_ERR + i];
      
      //������� ����������� ����
      number_recods_writing_into_dataflash_now++;
      next_address_into_buffer += SIZE_ONE_RECORD_PR_ERR;
      tail++;
      if(tail >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) tail = 0;
    }

    //��������� ������ ������
    start_exchange_via_spi(index_chip, (4 + number_recods_writing_into_dataflash_now*SIZE_ONE_RECORD_PR_ERR));
  }
  else if (index_chip == INDEX_DATAFLASH_2)
  {
    size_page = SIZE_PAGE_DATAFLASH_2;

    //����� ������� ������� ��� ����������� ����������

    //������� ������ ��� ������
    TxBuffer_SPI_DF[1] = 0; 
    TxBuffer_SPI_DF[2] = (temporary_address_ar >>  8) & 0x01; 
    TxBuffer_SPI_DF[3] =  temporary_address_ar        & 0xff; 
    
    //���������� ������ ����� ������, �� ����� �������� 
    for (unsigned int i = 0; i < count_to_save; i++ )
      TxBuffer_SPI_DF[4 + i] = buffer_for_save_ar_record[i];

    //��������� ������ ������
    start_exchange_via_spi(index_chip, (4 + count_to_save));

    /*
    �� ������� ������� ���� ��� ������ � ����� count_to_save ���, �� ��������
    �� ���������� ������ �� �������, ���� �� ���������� �������� (��� ��������������� �� �� ��������)
    ��������� ������� "��������� ������ � �������� �����_1 DataFlash" - "����������� ����� ����������� ������" -
    "����� ����� ������ � DataFlash"
    ���� �������� �� ������� ���� ����, ���� ������ �������, �� �������� �� ��� ����� ��� �� �����������.
    
    ���, ���� ��� ��������� ���� � ���������, �� ��� � ����� ���� ������� ������� ������ buffer_for_save_ar_record �� ������� 
    */
  }
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(16);
  }
}
/*****************************************************/

/*****************************************************/
//����� ����� DataFlash � ���'��� ��������� DataFlash
/*****************************************************/
void dataflash_mamory_buffer_into_memory(int index_chip)
{
  //����� ������������ ������ (������ 1) ���'��� DataFlash
  driver_spi_df[index_chip].code_operation = CODE_OPERATION_WRITE_BUFFER_INTO_MEMORY_WITH_ERASE;
  TxBuffer_SPI_DF[0] = 0x83;

  if (index_chip == INDEX_DATAFLASH_1)
  {
    //� �������� �� ���������� ����� ���������� ����������� �����������, �� ������� ����� � �� �� ���������
    _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
    info_rejestrator_pr_err.saving_execution = 1;
    
    //������� ������ ��� ������
    unsigned int address_into_dataflash = info_rejestrator_pr_err.next_address;
        
    TxBuffer_SPI_DF[1] = (address_into_dataflash >> 16) & 0x0f; 
    TxBuffer_SPI_DF[2] = (address_into_dataflash >> 8 ) & 0xff; 
    TxBuffer_SPI_DF[3] = 0; 
  }
  else if (index_chip == INDEX_DATAFLASH_2)
  {
    //������� ������ ��� ������
    TxBuffer_SPI_DF[1] = (temporary_address_ar >> 16) & 0x1f; 
    TxBuffer_SPI_DF[2] = (temporary_address_ar >> 8 ) & 0xfe; 
    TxBuffer_SPI_DF[3] = 0; 
  }
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(17);
  }

  //��������� ������ ������
  start_exchange_via_spi(index_chip, 4);
}
/*****************************************************/


/*****************************************************/
//����� ��������� ����� ���� ������
/*****************************************************/
inline void analize_received_data_dataflash(int index_chip)
{
  switch (driver_spi_df[index_chip].code_operation)
  {
  case CODE_OPERATION_STATUS_READ:
    {
      if ((index_chip == INDEX_DATAFLASH_1) || (index_chip == INDEX_DATAFLASH_2))
      {
        //������������ �������� ���������� ������� ��������� DataFlash
        if ((RxBuffer_SPI_DF[1] & (1<< 7)) != 0) dataflash_not_busy |= (1 << index_chip);
        else dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
        
        driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
        driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      }
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(26);
      }
      break;
    }
  case CODE_OPERATION_ERASE:
    {
      //������ ������� ������� �������� ���������
     
      //������ � ����� ������ ������� ��������
      if (index_chip == INDEX_DATAFLASH_1) control_tasks_dataflash &= (unsigned int)(~TASK_ERASE_DATAFLASH_1);
      else if (index_chip == INDEX_DATAFLASH_2) control_tasks_dataflash &= (unsigned int)(~TASK_ERASE_DATAFLASH_2);
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(18);
      }

      //����� ��� ��������, ��� ����� ������ ������� ����, ���� �������, �� ��������� � �������� � �������� ������� ���������, ���� �� �������� ������� ����������
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  case CODE_OPERATION_WRITE_PAGE_THROUGH_BUFFER:
    {
      if (index_chip == INDEX_DATAFLASH_1)
      {
        if(part_writing_dr_into_dataflash < (NUMBER_PAGES_IN_ONE_DR_RECORD - 1)) part_writing_dr_into_dataflash++;
        else
        {
          //��������� ���� ������ ���������� ������, ���� ������� ������ � ������ �����������, �� ����� ��� �����
          unsigned int temp_value_for_address = (info_rejestrator_dr.next_address + SIZE_BUFFER_FOR_DR_RECORD);
          while (temp_value_for_address > MAX_ADDRESS_DR_AREA) temp_value_for_address = temp_value_for_address - SIZE_DR_AREA; 

          //����������� ������� ������ ���� ��������� � EEPROM
          /*
          ������� ����������� ������, � ���� ������ ���� � �����, �� ����� ������,
          �� �� ����� ��������������� ����������� ����� ���������� �� ����������
          ���������� ���������� ��������� � ������� ������� ���������
          info_rejestrator_adr � �������� ����. �� ��������� ��������� � ������� 
          "������� �"/"������ �" EEPROM ���� ����������. ���� ����������� �������� �������
          ������ ������� ���������.
          � ����� ������� �� �������, ��� ������� ����� �� �����������, 
          �� ����� ���������� �������� main_routines_for_i2c - ��� ���������� �������
          ��� ������������, �� � ������� analize_received_data_dataflash.
          ����� �������� ����� ���� �� ������� ������� - ����� � ���� ������� � ���� 
          �� ������� ������� main_routines_for_i2c, � �� ��� ������� ��������� �������,
          ��� �� ��������� ����� ����� �����, ��� �� ����� ����������� ������� 
          (�� ������� ������� main_routines_for_i2c)
          */
          _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_DR_EEPROM_BIT);
          
          info_rejestrator_dr.next_address = temp_value_for_address;
          info_rejestrator_dr.saving_execution = 0;
          if (info_rejestrator_dr.number_records < MAX_NUMBER_RECORDS_INTO_DR) info_rejestrator_dr.number_records += 1;

          //������ � ����� ������ ������ ����������� ����������
          /*
          ������� ������ ����� ����� ������� �������, � ���� ������� routine_for_queue_dr 
          (���� ���������� �� ���� ������� analize_received_data_dataflash,
          ��� ����������� � ������� �������������� DataFlash) , ����� ���, ����
          �� �� ������ TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR ���������
          � ���������� ���� control_tasks_dataflash. 
          ������ �������� � �������� ���������� ���������� ���� - ������� �������
          ����� ����� ������, ���� ����� TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR
          �������, ��� � �������� ������� ���������� ��������� ���������.
          ���� ��� �� ������� ���� ����, �� �� ������� ����������� � ������������ �������� ���������� ����������
          */
          control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR);
        }
      }
      else if (index_chip == INDEX_DATAFLASH_2)
      {
        /*
        ���������� ����� ���� ������� ��� ����������� ����������
        ������ � ����� ������ ������ ���� ������� � DataFlash ��� ����������� ����������
        */
        control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR);
      }
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(27);
      }
       
      //����� ��� ������ ������, ���� ����� ������ ������� ����, ���� �������, �� ��������� � �������� � �������� ������� ���������, ���� �� �������� ������� ����������
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  case CODE_OPERATION_READ_HIGH_FREQ:
    {
      //������� �������� ��� � �����
      unsigned char *point_buffer;
      unsigned int number_byte_copy_into_target_buffer;
      unsigned int size_page;

      if (index_chip == INDEX_DATAFLASH_1)
      {
        size_page = SIZE_PAGE_DATAFLASH_1;
        unsigned int *point_part_reading;

        if (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_MENU)
        {
          point_buffer = (unsigned char *)(buffer_for_manu_read_record + part_reading_dr_from_dataflash_for_menu*size_page);
          number_byte_copy_into_target_buffer = size_page;
          point_part_reading = &part_reading_dr_from_dataflash_for_menu;
        }
        else if (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_USB)
        {
          point_buffer = (unsigned char *)(buffer_for_USB_read_record_dr + part_reading_dr_from_dataflash_for_USB*size_page);
          number_byte_copy_into_target_buffer = size_page;
          point_part_reading = &part_reading_dr_from_dataflash_for_USB;
        }
        else if (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_RS485)
        {
          point_buffer = (unsigned char *)(buffer_for_RS485_read_record_dr + part_reading_dr_from_dataflash_for_RS485*size_page);
          number_byte_copy_into_target_buffer = size_page;
          point_part_reading = &part_reading_dr_from_dataflash_for_RS485;
        }
        else if (
                 (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU )||
                 (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB  )||
                 (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_RS485)
                )   
        {
          if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU)
            point_buffer = (unsigned char *)(buffer_for_manu_read_record);
          else if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB)
            point_buffer = (unsigned char *)(buffer_for_USB_read_record_pr_err);
          else
            point_buffer = (unsigned char *)(buffer_for_RS485_read_record_pr_err);
          
          number_byte_copy_into_target_buffer = SIZE_ONE_RECORD_PR_ERR;
        }
        
        if (
            (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_MENU     ) ||
            (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_USB      ) ||  
            (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_RS485    ) ||  
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU ) ||
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB  ) ||  
            (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_RS485)  
           )
        {
          //�� ��� �� ����� ������ �� ������������
          for (unsigned int i = 0; i < number_byte_copy_into_target_buffer; i++ )
            *(point_buffer + i) = RxBuffer_SPI_DF[5 + i];
        }
        else
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(46);
        }

        if (
            (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_MENU ) ||
            (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_USB  ) ||  
            (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_RS485)  
           )
        {
          //³��������� ���������� ����������� ����������
          if((*point_part_reading) < (NUMBER_PAGES_IN_ONE_DR_RECORD - 1)) (*point_part_reading)++;
          else
          {
            //������ � ����� ������ ���������� ������ ����������� ����������
            if (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_MENU)
            {
              control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU);
              
              //��������� ������������ ��� ���� ���� �������� ���������� ���������
              unsigned char *point_unsigned_char = (unsigned char*)(buffer_for_manu_read_record + FIRST_INDEX_EXTRA_SETTINGS_DR);
              unsigned int *point_unsigned_int  = (unsigned int*)point_unsigned_char;
              control_extra_settings_1_dr_for_manu = *point_unsigned_int;
            
              /*������ ������� �� ���������� ������ �� LCD, ��� �� ���� �� 
              ��� <= 1c ���������� �����������, �� ������� ���� ����, ����
              ���� ������� �����
              */
              new_state_keyboard |= (1<<BIT_REWRITE);
            }
            else if (what_we_are_reading_from_dataflash_1 == READING_DR_FOR_USB)
              control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB);
            else
              control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485);
          
            *point_part_reading = 0;
          }
        }
        else if (
                 (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU ) ||
                 (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB  ) ||  
                 (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_RS485)  
                )
        {
          //³��������� ���������� ���������� ���������� ����
          //������ � ����� ������ ���������� ������ ���������� ���������� ����
          if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_MENU)
          {
            control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU);

            /*������ ������� �� ���������� ������ �� LCD, ��� �� ���� �� 
            ��� <= 1c ���������� �����������, �� ������� ���� ����, ����
            ���� ������� �����
            */
            new_state_keyboard |= (1<<BIT_REWRITE);
          }
          else if (what_we_are_reading_from_dataflash_1 == READING_PR_ERR_FOR_USB)
            control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB);
          else
            control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485);
        }
      }
      else if (index_chip == INDEX_DATAFLASH_2)
      {
        size_page = SIZE_PAGE_DATAFLASH_2;
        
        if (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_MENU)
        {
          point_buffer = (unsigned char *)(buffer_for_manu_read_record);
          number_byte_copy_into_target_buffer = sizeof(__HEADER_AR);
        }
        else if (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_USB)
        {
          point_buffer = (unsigned char *)(buffer_for_USB_read_record_ar);
          number_byte_copy_into_target_buffer = size_page; /*�������� ���� ���� � �����, ��� ����� �� �����, ��� ��� �� ������� � ���������� ����� ������� ����� ����� �������. ��� ����� �� ��� ��������� ������ ������ ������ ����, ��� ���� ����������� ��������� ��� ��'��*/
        }
        else if (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_RS485)
        {
          point_buffer = (unsigned char *)(buffer_for_RS485_read_record_ar);
          number_byte_copy_into_target_buffer = size_page; /*�������� ���� ���� � �����, ��� ����� �� �����, ��� ��� �� ������� � ���������� ����� ������� ����� ����� �������. ��� ����� �� ��� ��������� ������ ������ ������ ����, ��� ���� ����������� ��������� ��� ��'��*/
        }

        if (
            (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_MENU ) ||
            (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_USB  ) ||  
            (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_RS485)  
           )
        {
          for (unsigned int i = 0; i < number_byte_copy_into_target_buffer; i++ )
            *(point_buffer + i) = RxBuffer_SPI_DF[5 + i];
        }
        else
        {
          //���������� ����� ����� �� ���� � ����
          total_error_sw_fixed(47);
        }

        //������ � ����� ������ ���������� ������ ����������� ����������
        if (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_MENU)
        {
          control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU);
              
          /*������ ������� �� ���������� ������ �� LCD, ��� �� ���� �� 
          ��� <= 1c ���������� �����������, �� ������� ���� ����, ����
          ���� ������� �����
          */
          new_state_keyboard |= (1<<BIT_REWRITE);
        }
        else if (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_USB)
          control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB);
        else if (what_we_are_reading_from_dataflash_2 == READING_AR_FOR_RS485)
          control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485);
      }
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(33);
      }
          
       
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  case CODE_OPERATION_READ_PAGE_INTO_BUFFER:
    {
      //����������� ������ ������� ���������� ���'�� ������� � ����� ��������� DataFlash
      unsigned int *label_to_etap_writing;
      if (index_chip == INDEX_DATAFLASH_1) label_to_etap_writing = &etap_writing_pr_err_into_dataflash;
      else if (index_chip == INDEX_DATAFLASH_2) label_to_etap_writing = &etap_writing_part_page_ar_into_dataflash;
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(28);
      }
      
      //���������� ����� ������ ���������� ���������� � ����� ����� �������
      if (*label_to_etap_writing == ETAP_READ_MEMORY_INTO_BUFFER)
        *label_to_etap_writing = ETAP_HAVE_READ_MEMORY_INTO_BUFFER;
      else 
        *label_to_etap_writing = ETAP_ERROR_BEFALLEN;
      
      //����� ��� ������ ���������� � �����, ���� ����� ������ ������� ����, ���� �������, �� ��������� � �������� � �������� ������� ���������, ���� �� �������� ������� ����������
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  case CODE_OPERATION_WRITE_BUFFER:
    {
      //����������� �������� ����� � ����� ��������� DataFlash
      unsigned int *label_to_etap_writing;
      if (index_chip == INDEX_DATAFLASH_1) label_to_etap_writing = &etap_writing_pr_err_into_dataflash;
      else if (index_chip == INDEX_DATAFLASH_2) label_to_etap_writing = &etap_writing_part_page_ar_into_dataflash;
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(29);
      }
      
      //���������� ����� ������ � ���������� ����������� ������ DataFlah
      if (*label_to_etap_writing == ETAP_MODIFY_AND_WRITE_BUFFER)
        *label_to_etap_writing = ETAP_MODIFIED_AND_WRITTEN_BUFFER;
      else 
        *label_to_etap_writing = ETAP_ERROR_BEFALLEN;
      
      //�������, �� ��������� � �������� � �������� ������� ���������, ���� �� �������� ������� ����������
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  case CODE_OPERATION_WRITE_BUFFER_INTO_MEMORY_WITH_ERASE:
    {
      if (index_chip == INDEX_DATAFLASH_1)
      {
        if (etap_writing_pr_err_into_dataflash == ETAP_WRITE_BUFFER_INTO_MEMORY)
        {
          //����������� ������� ������ ��������� ���������� ���������� ���� � EEPROM
          _SET_BIT(control_i2c_taskes, TASK_START_WRITE_INFO_REJESTRATOR_PR_ERR_EEPROM_BIT);
          //��������� ���� ������ ���������� ������, ���� ������� ������ � ������ �����������, �� ����� ��� �����
          unsigned int temp_value_for_address = (info_rejestrator_pr_err.next_address + number_recods_writing_into_dataflash_now*SIZE_ONE_RECORD_PR_ERR);
          while (temp_value_for_address > MAX_ADDRESS_PR_ERR_AREA) temp_value_for_address = temp_value_for_address - SIZE_PR_ERR_AREA; 
          info_rejestrator_pr_err.next_address = temp_value_for_address;
          info_rejestrator_pr_err.saving_execution = 0;
          if ((info_rejestrator_pr_err.number_records + number_recods_writing_into_dataflash_now) <= MAX_NUMBER_RECORDS_INTO_PR_ERR) info_rejestrator_pr_err.number_records += number_recods_writing_into_dataflash_now;
          else info_rejestrator_pr_err.number_records = MAX_NUMBER_RECORDS_INTO_PR_ERR;
        
          //������� ������� ������ ���� FIFO 
          tail_fifo_buffer_pr_err_records += number_recods_writing_into_dataflash_now;
          while(tail_fifo_buffer_pr_err_records >= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER) tail_fifo_buffer_pr_err_records -= MAX_NUMBER_RECORDS_PR_ERR_INTO_BUFFER;
          number_recods_writing_into_dataflash_now = 0;
        
          if (_CHECK_SET_BIT(diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT) != 0)
          {
            //����� ���������� ����� ����������� ��� ������������ ������ FIFO ���������� ����
            _SET_BIT(clear_diagnostyka, ERROR_PR_ERR_OVERLOAD_BIT);
          }

          //������ � ����� ������ ������ � ��������� ���������� ����
          etap_writing_pr_err_into_dataflash = ETAP_NONE;
          control_tasks_dataflash &= (unsigned int)(~TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH);
        }
        else 
          etap_writing_pr_err_into_dataflash = ETAP_ERROR_BEFALLEN;
      }
      else if (index_chip == INDEX_DATAFLASH_2)
      {
        if (etap_writing_part_page_ar_into_dataflash == ETAP_WRITE_BUFFER_INTO_MEMORY)
        {
          /*
          ������� ������� ���� ��� ������ � ����� count_to_save
          ���� �� ����������� � ����� ����, �� ��� ��� ����� ������� � ������ DataFlash
          � ������� ������� ������ buffer_for_save_ar_record ��� ����� �� �������.
          ��� �������� ���� ��� �� ���� ������� � �������, ���� �� �� ������� �������� � ��������
          ����� ��������� DataFlash.
          ��� ����� ������� �������� �� ��������� ������� �� ���������� ���������� �����
          buffer_for_save_ar_record ������ ���������� ����� ���.

          ���� ���������� ����-���� ���������� ��������� � ����� permit_copy_new_data ����� �� ��������� ����� �����
          ����� ��� ��������� �������� ������ ��� ������
          */
          temporary_address_ar += count_to_save;
          count_to_save = 0;
          permit_copy_new_data = 0xff;
           
          //������ � ����� ������ ������ ������� ������� ��� ����������� ����������
          etap_writing_part_page_ar_into_dataflash = ETAP_NONE;
          control_tasks_dataflash &= (unsigned int)(~TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR);
        }
        else 
          etap_writing_part_page_ar_into_dataflash = ETAP_ERROR_BEFALLEN;
      }
      else
      {
        //³������� ����������� �������, ���� ����� ��� �� ����������������
        total_error_sw_fixed(30);
      }
       
      //����� ��� ������ ������, ���� ����� ������ ������� ����, ���� �������, �� ��������� � �������� � �������� ������� ���������, ���� �� �������� ������� ����������
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  default:
    {
      //�� ���, ���� �������� ����� �� ���� � ��������. 
      //���� �� ���� ������, �� ����� ��������� �����������, �� �� ���� �� ��������� � ������ � ������� �� ��������
      dataflash_not_busy &= (unsigned int)(~(1 << index_chip));
      driver_spi_df[index_chip].state_execution = TRANSACTION_EXECUTING_NONE;
      driver_spi_df[index_chip].code_operation = CODE_OPERATION_NONE;
      break;
    }
  }
}
/*****************************************************/

/*****************************************************/
//������� ������� ������� ����� �� ��������� DataFlash (������� ��������� �����)
/*****************************************************/
void main_function_for_dataflash_resp(int index_chip)
{
  if ((index_chip >= INDEX_DATAFLASH_1) && (index_chip <= INDEX_DATAFLASH_2))
  {
    if(driver_spi_df[index_chip].state_execution == TRANSACTION_EXECUTED_WAIT_ANALIZE)
    {
      //�������� ������� ������� ����� �� ���������� ����������
      analize_received_data_dataflash(index_chip);
    }
  }
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(19);
  }
}
/*****************************************************/

/*****************************************************/
//������� ������� ������� ����� �� ��������� DataFlash (������ ���� ������� �����)
/*****************************************************/
void main_function_for_dataflash_req(int index_chip)
{
  if ((index_chip >= INDEX_DATAFLASH_1) && (index_chip <= INDEX_DATAFLASH_2))
  {
    if (driver_spi_df[index_chip].state_execution == TRANSACTION_EXECUTING_NONE)
    {
      //���� ����� �� �������� ����� ��������, �� ����� ��� ������ ���� ����������
      if((dataflash_not_busy & (1 << index_chip)) == 0)
      {
        //��������� ��� ������� ����������� ��� ��, �� ��������� � �������, ���� ����� �������� ��������� ������ ���� ���� �� ����� ���������
        dataflash_status_read(index_chip);
      }
      else
      {
        //��������� ����� � ������. ���� ����� ��������� ��� ����������� ��� ����������
        unsigned int tasks_register;
        if (index_chip == INDEX_DATAFLASH_1) tasks_register = control_tasks_dataflash & 0xffff;
        else tasks_register = control_tasks_dataflash & 0xffff0000;
        
        if (tasks_register !=0)
        {
          //����� ������ � ������ ��������, �� ����� ��������
          if (
              ((tasks_register & TASK_ERASE_DATAFLASH_1) !=0) ||
              ((tasks_register & TASK_ERASE_DATAFLASH_2) !=0)
             )
          {
            //����� �������� ������� ������� �������� ���������
            dataflash_erase(index_chip);
          }
          else if ((tasks_register & TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH) !=0 )
          {
            //����� �������� �������: ���������� � �����, ���� ������, ����� ������ ���������� ���� ��������� ��� ���������� ���������� ����
            if (etap_writing_pr_err_into_dataflash > ETAP_ERROR_BEFALLEN)
              etap_writing_pr_err_into_dataflash = ETAP_ERROR_BEFALLEN;
            
            switch (etap_writing_pr_err_into_dataflash)
            {
            case ETAP_NONE:
              {
                etap_writing_pr_err_into_dataflash = ETAP_READ_MEMORY_INTO_BUFFER;
                dataflash_mamory_page_into_buffer(index_chip);
                break;
              }
            case ETAP_HAVE_READ_MEMORY_INTO_BUFFER:
              {
                //���������� � ����� ������ ����� � �����
                etap_writing_pr_err_into_dataflash = ETAP_MODIFY_AND_WRITE_BUFFER;
                //����� �������� ������� ������ ����� ���������� ���������� ���� � ����� ����������
                dataflash_mamory_write_buffer(index_chip);
                break;
              }
            case ETAP_MODIFIED_AND_WRITTEN_BUFFER:
              {
                //���������� � ����� ������ ����� � ������ � ���'��� ��������� DataFlash
                etap_writing_pr_err_into_dataflash = ETAP_WRITE_BUFFER_INTO_MEMORY;
                //����� �������� ������� ������ ����� ���������� ���������� ���� � ����� ����������
                dataflash_mamory_buffer_into_memory(index_chip);
                break;
              }
            default:
              {
                /*
                ���� ���� ����� ��������, ���� ����� ������� �������, 
                ��� ������ ����� ������ ���������� ���������� ������� � ���������� ��� � ��������� ����
                ����� �� �������� � ���������� ����  
                */
                etap_writing_pr_err_into_dataflash = ETAP_NONE;
                //������ � ����� ������ ������ � ��������� ���������� ����
                control_tasks_dataflash &= (unsigned int)(~TASK_WRITE_PR_ERR_RECORDS_INTO_DATAFLASH);
                
                break;
              }
            }   
          }   
          else if ((tasks_register & TASK_MAMORY_PART_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR) !=0 )
          {
            //����� �������� �������: ���������� � �����, ���� ������, ����� ������ ���������� ���� ��������� ��� ����������� ����������
            if (etap_writing_part_page_ar_into_dataflash > ETAP_ERROR_BEFALLEN)
              etap_writing_part_page_ar_into_dataflash = ETAP_ERROR_BEFALLEN;
            
            switch (etap_writing_part_page_ar_into_dataflash)
            {
            case ETAP_NONE:
              {
                etap_writing_part_page_ar_into_dataflash = ETAP_READ_MEMORY_INTO_BUFFER;
                dataflash_mamory_page_into_buffer(index_chip);
                break;
              }
            case ETAP_HAVE_READ_MEMORY_INTO_BUFFER:
              {
                //���������� � ����� ������ ����� � �����
                etap_writing_part_page_ar_into_dataflash = ETAP_MODIFY_AND_WRITE_BUFFER;
                //����� �������� ������� ������ ����� ���������� ���������� ���� � ����� ����������
                dataflash_mamory_write_buffer(index_chip);
                break;
              }
            case ETAP_MODIFIED_AND_WRITTEN_BUFFER:
              {
                //���������� � ����� ������ ����� � ������ � ���'��� ��������� DataFlash
                etap_writing_part_page_ar_into_dataflash = ETAP_WRITE_BUFFER_INTO_MEMORY;
                //����� �������� ������� ������ ����� ���������� ���������� ���� � ����� ����������
                dataflash_mamory_buffer_into_memory(index_chip);
                break;
              }
            default:
              {
                /*
                ���� ���� ����� ��������, ���� ����� ������� �������, 
                ��� ������������� �� �������� � �������  
                */
                etap_writing_part_page_ar_into_dataflash = ETAP_NONE;
                break;
              }
            }   
          }   
          else if (
                   ((tasks_register & TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_DR) !=0) ||
                   ((tasks_register & TASK_MAMORY_PAGE_PROGRAM_THROUGH_BUFFER_DATAFLASH_FOR_AR) !=0)
                  )
          {
            //����� �������� ������� ������ ����� � ������� ����� ����� � ��������� ���������
            dataflash_mamory_page_program_through_buffer(index_chip);
          }
          else if (
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU     ) !=0 ) ||
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB      ) !=0 ) ||
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485    ) !=0 ) ||
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU     ) !=0 ) ||
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB      ) !=0 ) ||
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485    ) !=0 ) ||
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU ) !=0 ) ||
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB  ) !=0 ) ||
                   ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485) !=0 )
                  )   
          {
            
            //���� ������������ ����� ���� �������� ��� ���� ��������� DataFlash(������� ���i ���������� ���� ���������� ���� ����������, ���� ������ ���������� � ������� �����)
            //DataFlash1
            if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_DR_USB) !=0 )
              what_we_are_reading_from_dataflash_1 = READING_DR_FOR_USB; //������� ��� USB ������ �� ������ �������� �������� � �������� ��� RS-485 � ����
            else if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_USB) !=0 )
              what_we_are_reading_from_dataflash_1 = READING_PR_ERR_FOR_USB;//������� ��� USB ������ �� ������ �������� �������� � �������� ��� RS-485 � ����
            else if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_DR_RS485) !=0 )
              what_we_are_reading_from_dataflash_1 = READING_DR_FOR_RS485; //������� ��� RS-485 ������ �� ������ �������� �������� � �������� ��� ����
            else if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_RS485) !=0 )
              what_we_are_reading_from_dataflash_1 = READING_PR_ERR_FOR_RS485;//������� ��� RS-485 ������ �� ������ �������� �������� � �������� ��� ����
            else if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_DR_MENU) !=0 )
              what_we_are_reading_from_dataflash_1 = READING_DR_FOR_MENU;
            else if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_PR_ERR_MENU) !=0 )
              what_we_are_reading_from_dataflash_1 = READING_PR_ERR_FOR_MENU;
            
            //DataFlash2
            if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_AR_USB) !=0 )
              what_we_are_reading_from_dataflash_2 = READING_AR_FOR_USB; //������� ��� USB ������ �� ������ �������� �������� � �������� ��� RS-485 � ����
            else if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_AR_RS485) !=0 )
              what_we_are_reading_from_dataflash_2 = READING_AR_FOR_RS485; //������� ��� RS485 ������ �� ������ �������� �������� � �������� ��� ����
            else if ((tasks_register & TASK_MAMORY_READ_DATAFLASH_FOR_AR_MENU) !=0 )
              what_we_are_reading_from_dataflash_2 = READING_AR_FOR_MENU;
            //����� �������� ������� ������� �����
            dataflash_mamory_read(index_chip);
          }
        }
      }
    }
  }
  else
  {
    //³������� ����������� �������, ���� ����� ��� �� ����������������
    total_error_sw_fixed(24);
  }
}
/*****************************************************/

/*****************************************************/
//ĳ� ��� ��� �������� ��� ������������ ����������
/*****************************************************/
void actions_after_changing_tiomouts_ar(void)
{
  //���������� ��������� ���������� ��� ������ ����������� ���������� � ���������� (��������� ����)
  
  //ϳ��������� ����� ������ ������ � ����������� ������� ������ � ����������� ��������� ��� ����� ��������
  calc_size_and_max_number_records_ar(current_settings.prefault_number_periods, current_settings.postfault_number_periods);
  
  //�������, �� ����� �������� ���������� ���������
  clean_rejestrators |= CLEAN_AR;

  //�������, �� ����� ������ �� ��������
  number_record_of_ar_for_menu = 0xffff;
  number_record_of_ar_for_USB = 0xffff;
  number_record_of_ar_for_RS485 = 0xffff;
}
/*****************************************************/

/*****************************************************/
//���������� ������ ������ ������ � ����������� ������ ������ � ����������� ��������� ��� ����� ��������
/*****************************************************/
void calc_size_and_max_number_records_ar(unsigned int prefault_number_periods, unsigned int postfault_number_periods)
{
  size_one_ar_record = sizeof(__HEADER_AR) + ((prefault_number_periods + postfault_number_periods) << VAGA_NUMBER_POINT_AR)*(NUMBER_ANALOG_CANALES + number_word_digital_part_ar)*sizeof(short int);
  max_number_records_ar = (NUMBER_PAGES_INTO_DATAFLASH_2 << VAGA_SIZE_PAGE_DATAFLASH_2) / size_one_ar_record;
}
/*****************************************************/

/*****************************************************/
//���������� ������ (������) ��� ������ � � ������� ��������� DataFlash ������� ����������� ����������
/*****************************************************/
unsigned int making_buffer_for_save_ar_record(unsigned int *point_unsaved_bytes_of_header_ar)
{
  unsigned int error = 0; //�� ����������� �������, �� ������� �� ����������� .�� ���� � ���� ��� ��������� ������, �� ������ � ������� �� ������� �� ����� ���������

  //��������� ������ ����� � ������ ������ �� �������� � ������ ������� DataFlash
  unsigned int free_space_in_page_df = SIZE_PAGE_DATAFLASH_2 - (temporary_address_ar & 0x1ff);
  
  if (*point_unsaved_bytes_of_header_ar > 0)
  {
    //�������� ����� ������������ ��������� ����������� ����������, ���� �� �� �� ��������������
    if (*point_unsaved_bytes_of_header_ar <= sizeof(__HEADER_AR))
    {
      unsigned char  *point = (unsigned char*)(&header_ar);
      point += (sizeof(__HEADER_AR) - *point_unsaved_bytes_of_header_ar);
      
      while (
             ((count_to_save + 1) <= free_space_in_page_df) &&
             (*point_unsaved_bytes_of_header_ar > 0)  
            )
      {
        //������ �� ������ �����, ���� � ����� ���� ��� ����������
        buffer_for_save_ar_record[count_to_save++] = *point;
        point++;
        *point_unsaved_bytes_of_header_ar -= 1;
      }
    }
    else
    {
      //���������� ���� �������� ����� �� �� ���� � ��������
      error = 1;
    }
  }
  
  if (
      (state_ar_record == STATE_AR_SAVE_SRAM_AND_SAVE_FLASH) ||
      (state_ar_record == STATE_AR_ONLY_SAVE_FLASH         )
     )  
  {
    //������ ����� �������, ���� � ��� � ���� � ����� ���� ��� ���������
    unsigned int index_array_ar_heat_tmp = index_array_ar_heat;/*�� ����� ��� ����, �� ��������� ���� ����������� ��� �������� ������ � ��������� volatile*/
    unsigned int index_array_ar_tail_tmp = index_array_ar_tail;/*�� ����� ��� ����, �� ��������� ���� ����������� ��� �������� ������ � ��������� volatile*/
    while (
           ((count_to_save + 2) <= free_space_in_page_df)           /*� ����� ���� � ���������� ������� �� ��� ����� �������� ��������*/
           &&  
           (
            (index_array_ar_tail_tmp != index_array_ar_heat_tmp) || /* "����" ������ FIFO �� "������" �� "������"*/
            (state_ar_record == STATE_AR_ONLY_SAVE_FLASH)           /*��� ���������� ���������� ��� ������*/ 
           )
           &&  
           (copied_number_samples < total_number_samples)           /*�� �� ���� ���������� ��� ������� ������� �������, ��� �� ���� � ������ ����� ����������� ���������� ��� ������� ����� ����������� � ������������� ������*/
          )
    {
    
      //������ �� ��� ����� (������ ������� ���������� � ���� ����), ���� � ����� ���� ��� ����������
      unsigned int sample;
      if (index_array_ar_tail_tmp != index_array_ar_heat_tmp)
      {
        /*�������� � ���������� ������ index_array_ar_tail, � �� � �� ��쳺� index_array_ar_tail_tmp, �� ��� ��������� �� ���� ����������*/
        sample = array_ar[index_array_ar_tail++];
        if (index_array_ar_tail >= SIZE_BUFFER_FOR_AR) index_array_ar_tail = 0; /*����� ��� �� ���� ==, ��� ��� ��������������� �� ����������� ������� � �������� >=*/
        index_array_ar_heat_tmp = index_array_ar_heat;/*�� ����� ��� ����, �� ��������� ���� ����������� ��� �������� ������ � ��������� volatile*/
        index_array_ar_tail_tmp = index_array_ar_tail;/*�� ����� ��� ����, �� ��������� ���� ����������� ��� �������� ������ � ��������� volatile*/
      }
      else
      {
        /*
        ���� �������� ���� ����� ����� � ���� ������� ���������� ����� ��� ������, 
        (���� ����� state_ar_record ���� STATE_AR_ONLY_SAVE_FLASH) � ���� ����������
        �������� ������������, ����� ������� ����� � ���������, ���� ���������� �����
        ������� ���������� ������ � ���� ������
        */
        sample = 0;
      }

      //������� � Little Endian mode (�������� ������ ������)
      buffer_for_save_ar_record[count_to_save++] = sample        & 0xff;
      buffer_for_save_ar_record[count_to_save++] = (sample >> 8) & 0xff;
      copied_number_samples++; //�������� ������� "��������" ������� �������
    }
  
    if (
        (count_to_save > free_space_in_page_df) ||
        (copied_number_samples > total_number_samples)  
       )
    {
      //���������� ���� �������� ����� �� �� ���� � ��������
      error = 2;
    }
    else if (
             (
              (*point_unsaved_bytes_of_header_ar > 0      ) &&
              ((count_to_save + 1) > free_space_in_page_df)  
             )
             ||
             (
              (*point_unsaved_bytes_of_header_ar == 0     ) &&
              ((count_to_save + 2) > free_space_in_page_df)  
             )
             ||
             (copied_number_samples == total_number_samples)
            )   
    {
      //����� ������� ���������� ��������� ����� ����� � ����� ������ ������ �� ����� � DataFlash
      permit_copy_new_data = 0;
    }
  }
  
  return error;
}
/*****************************************************/

/*****************************************************/
//
/*****************************************************/
/*****************************************************/
