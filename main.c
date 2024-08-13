#include "DSP28x_Project.h"
#include "sci.h"
#include "SPI.h"
#include "FLASH.h"
#include "Protocole.h"
/*Defines-------------------------------------------------------*/
#define         PROG_MODE   0
int             line                                                 = 0;
int             coun                                                 = 0;
int             flag                                                 = 0;
int             flag_Write                                           = 0;
int             flag_Read                                            = 0;
int             flag_Erase                                           = 0;
int             flag_BLock_Erase                                     = 0;
int             flag_Write2                                          = 0;
int             flag_Chip_Erase                                      = 0;
int     offset2              = 0;

char            f[32];
extern          char                FIFO[672];
extern          int                 Data_index;
extern          int                 Flag_Write_Flash;
extern          int                 Flag_Read_Flash;
Uint16          Ram[640];
Uint16          Data[640];
Uint32          Address_Flash                                        = 0x000000;
Uint64          Counter_Time                                         = 0;

typedef enum
{
    STATE_FUN1_0,
    STATE_FUN1_1,
    STATE_FUN2,
    STATE_FUN3,
    STATE_FUN4,
    STATE_FUN5
}state;
char d[20] = {0x01,0x01,0x01,0x02,0x02,0x02,0x07,0x02,0x09,0x99,0x88,0x77,0x66,0x55,0x44,0xCC,0xBB,0xAA};
/*---------------------------------------------------------------*/

#if PROG_MODE == 1
    #pragma CODE_SECTION(timer0_isr, ".TI.ramfunc");
#endif

/*Loop_Timer-------------------------------------------------------*/

__interrupt void timer0_isr(void);


/*Private_Functions-----------------------------------------------*/
void write_Array();

void value_Data(Uint16 *Data)
{
    int i;

    for(i = 0; i < 640; i++)
    {
        Data[i] = i;

    }
}

volatile int State_Machine = STATE_FUN1_0;
void ziro();
int main(void)
{
    int i;
    InitSysCtrl();
    InitPieCtrl();
    Init_Sci();
    SPI_GPIO();
    SPI_Init();






    Chip_Erase();
    for(i = 0; i < 25000;i++)
    {
        DELAY_US(1000);
    }




    Read_From_Flash_Init(Address_Flash, Ram, 640);
    #if PROG_MODE == 1
        MemCopy(RamfuncsLoadStart,RamfuncsLoadEnd,RamfuncsRunStart);
        InitFlash();
    #endif
// Initialize PIE control registers to their default state
    InitPieVectTable();
            DINT;
            IER = 0x0000;
            IFR = 0x0000;
// Configure CPU timer 0
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 150, 1000); // 150MHz CPU, 500us period


// Set up interrupt handling for CPU timer 0
    EALLOW;
      PieVectTable.TINT0 = &timer0_isr;
    EDIS;
// Enable CPU timer 0 interrupt
            PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
// Enable global interrupts
    IER |= M_INT1;
    EINT;
// Start CPU tiemr 0
    value_Data(Data);
   StartCpuTimer0();
   while(1){}
}

char Array[10]= {0xAA,0x55,0x33};

__interrupt void timer0_isr(void)
{

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

        if(Counter_Time >= 1 && Counter_Time <= 250 )
        {
            if(Counter_Time <= 4)                             Send_CommandLine(0,line);
            if(Counter_Time >= 4)                             RxReader();
            if(Data_index == 672)                             Write_In_Flash_Init(Address_Flash, frame.Data, 640);
            if(Counter_Time == 250 && Data_index != 672)      Counter_Time = 0;
        }

        if(Flag_Write_Flash != 1)
        {
           Write_In_Flash();
        }

        if(Flag_Read_Flash == 0 && Flag_Write_Flash == 1  )
        {
            Read_From_Flash();
        }
        if(Flag_Read_Flash == 1 && Flag_Write_Flash == 1   )
        {
            if(line <= 255)
            {
                  frame.crc1 = 0;
                  frame.crc2 = 0;

                  if(Check_CRC(Ram))
                  {
                      Clear(Ram);
                      flag_Read =0;
                      Address_Flash += 768;
                      Counter_Time = 0;
                      Read_From_Flash_Init(Address_Flash,   Ram, 640);

                      line++;

                  }
                  else
                  {
                      line = EraseFlashData(&Address_Flash);
                      Read_From_Flash_Init(Address_Flash,   Ram, 640);
                      Counter_Time = 0;
                      flag_Read =0;
                      Clear(Ram);

                  }
            }

        }

        /*if(100 != 1000)
        {
            if(10000 == 10000)
            {
                int i;
              for(i = 0; i< 1000;i++)
                  asm("NOP");


            }
        }*/

                        Counter_Time++;

}




