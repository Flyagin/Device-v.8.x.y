/* Includes ------------------------------------------------------------------*/
 #include "stm32f2xx_it.h"
 
#include "hw_config.h"
#include "platform_config.h"
#include "header.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Extern variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : Set_System
* Description    : Configures Main system clocks & power
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_System(void)
{
  //��������� ������ ����� �� ��������
 
  //AHB3

  //AHB1
  RCC_AHB1PeriphClockCmd(
                         RCC_AHB1Periph_DMA1                    |
                         RCC_AHB1Periph_DMA2                    |
                         RCC_AHB1Periph_GPIO_LCD_RW             |
                         RCC_AHB1Periph_GPIO_LCD_RS             |
                         RCC_AHB1Periph_GPIO_LCD_BL             |
                         RCC_AHB1Periph_GPIO_CON_L              |
                         RCC_AHB1Periph_GPIO_KEYBOARD           |
                         RCC_AHB1Periph_GPIO_SELECT_ADC         |
                         RCC_AHB1Periph_GPIO_SPI_ADC            |
                         RCC_AHB1Periph_GPIO_I2C                |
                         RCC_AHB1Periph_GPIO_SPI_DF             |
                         RCC_AHB1Periph_GPIO_SPI_DF_TOGGLE      |
                         RCC_AHB1Periph_GPIO_CON_OUTPUTS        |
                         RCC_AHB1Periph_GPIO_USART_RS485        |
                         RCC_AHB1Periph_GPIO_485DE              |
                         RCC_AHB1Periph_GPIO_EXTERNAL_WATCHDOG  |
                         RCC_AHB1Periph_GPIO_POWER_CTRL,
                         
                         ENABLE);

  //APB2
  RCC_APB2PeriphClockCmd(
                         RCC_APB2Periph_SYSCFG  |
                         RCC_APB2Periph_SPI_DF/*  |
                         RCC_USARTRS_485*/,
                         ENABLE);
  
  //APB1
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C     |
                         RCC_APB1Periph_TIM2    |
                         RCC_APB1Periph_TIM5    |
                         RCC_APB1Periph_TIM4    |
                         RCC_APB1Periph_SPI_ADC |
                         RCC_USARTRS_485,
                         
                         ENABLE);

}

/*******************************************************************************
* Function Name  : Interrupts_Config
* Description    : Configures the USB interrupts
* Input          : None.
* Return         : None.
*******************************************************************************/
void Interrupts_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
//#ifdef  VECT_TAB_RAM
//  /* Set the Vector Table base location at 0x20000000 */
//  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
//#else  /* VECT_TAB_FLASH */
//  /* Set the Vector Table base location at 0x08000000 */
//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
//#endif

  /*******************************/
  //��������� ���������� ����������
  /*
  �������� ����
  4-�� �� Pre-emption ����: 4 ��� [0-3] Pre-emption ���������. 0 - �������� Pre-emption ��������
  
  �������� �������� �����
  4-�� �� Subpriority ����: 4 ��� [0-3] Subpriority ���������. 0 - �������� Subpriority ��������
  */
  /*******************************/
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /*******************************/

  /*******************************/
  /* Enable the I2C global events Interrupt */
  /*
  //�� ������������� ST �� ���� �������� ��������
  Pre-emption �������� = 0 
  Subpriority �������� = 0 
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = I2C_EV_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/

  /*******************************/
  /* Enable the I2C global errors Interrupt */
  /*
  Pre-emption �������� = 0 
  Subpriority �������� = 0 
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = I2C_ER_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/

  /*******************************/
  /* ����������� �� TIM5, ���� ����������� ���� 0,625�� ��� ������� ������ ����� � ���*/
  /*
  Pre-emption �������� = 0 
  Subpriority �������� = 1 
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/

  /*******************************/
  /* ���������� ����������� �� SPI ����������� ������� */
  /*
  Pre-emption �������� = 0 
  Subpriority �������� = 2
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = SPI_ADC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/
  
  /*******************************/
  /* ����������� �� TIM2, ���� ����������� ���� 1�� ��� ������ ������ �������*/
  /*
  Pre-emption �������� = 1 
  Subpriority �������� = 1
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/

  /*******************************/
  /* ���������� ����������� �� SPI_DF - ������� Dataflash */
  /*
  Pre-emption �������� = 2 
  Subpriority �������� = 0  (�������� � ���� ����)
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = SPI_DF_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/

  /*******************************/
  /* ���������� ����������� �� DMA_SPI_DF ������ - ������� Dataflash */
  /*
  Pre-emption �������� = 2 
  Subpriority �������� = 1
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = DMA_StreamSPI_DF_Rx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/

  /*******************************/
  /* ����������� �� USART2 ��� RS-485*/
  /*
  Pre-emption �������� = 2 
  Subpriority �������� = 2
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = USARTRS485_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/
  
  /*******************************/
  /* ����������� �� DMA1_ChannelRS485_TX*/
  /*
  Pre-emption �������� = 2 
  Subpriority �������� = 2
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = DMA_StreamRS485_Tx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/

  /*******************************/
  /* ���������� ����������� �� ������ ������� ���������/���������� �������� �� ���� ������� �������� */
  /*
  Pre-emption �������� = 2 
  Subpriority �������� = 3
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = EXITI_POWER_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/
  
  /*******************************/
  /* ���������� ����������� �� DMA_StreamI2C_Tx �������� ����� ����� I2C */
  /*
  Pre-emption �������� = 3 (��������� ����� ����)
  Subpriority �������� = 1 
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = DMA_StreamI2C_Tx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/
  
  /*******************************/
  /* ���������� ����������� �� DMA_ChannelI2C_Rx ������ ����� � I2C */
  /*
  Pre-emption �������� = 3 (��������� ����� ����)
  Subpriority �������� = 1 
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = DMA_StreamI2C_Rx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/

  /*******************************/
  /* ����������� �� TIM4, ������� ��������� � ���� ��������������� ������*/
  /*
  Pre-emption �������� = 3 (��������� ����� ����)
  Subpriority �������� = 2 
  */
  /*******************************/
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /*******************************/
}

