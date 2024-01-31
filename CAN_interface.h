 /****************************************************************************
 *
 * Module: CAN
 *
 * File Name: CAN_interface.h
 *
 * Description: Header file for the CAN driver interface
 *
 * Author: Ahmed Hesham
 *
 * Created on: Sep 25, 2023
 *
 *****************************************************************************/
#ifndef _CAN_INTERFACE_H
#define _CAN_INTERFACE_H

#include "Common_Macros.h"
#include "Std_Types.h"
#include "CAN_config.h"
#include "CAN_private.h"

//
// Converts a set of CAN bit timing values into the value that needs to be
// programmed into the CAN_BIT register to achieve those timings.
//
//*****************************************************************************
#define CAN_BIT_VALUE(TSEG1, TSEG2, SJW)                                      \
                    ((((TSEG1 - 1) << CAN_BIT_TSEG1_S) & CAN_BIT_TSEG1_M) |   \
                     (((TSEG2 - 1) << CAN_BIT_TSEG2_S) & CAN_BIT_TSEG2_M) |   \
                       (((SJW - 1) << CAN_BIT_SJW_S) & CAN_BIT_SJW_M))        \

//*****************************************************************************
//
// This table is used by the CANBitRateSet() API as the register defaults for
// the bit timing values.
//
//*****************************************************************************
static const uint16 CAN_BitValues[] =
{
    CAN_BIT_VALUE(2, 1, 1),     // 4 clocks/bit
    CAN_BIT_VALUE(3, 1, 1),     // 5 clocks/bit
    CAN_BIT_VALUE(3, 2, 2),     // 6 clocks/bit
    CAN_BIT_VALUE(4, 2, 2),     // 7 clocks/bit
    CAN_BIT_VALUE(4, 3, 3),     // 8 clocks/bit
    CAN_BIT_VALUE(5, 3, 3),     // 9 clocks/bit
    CAN_BIT_VALUE(5, 4, 4),     // 10 clocks/bit
    CAN_BIT_VALUE(6, 4, 4),     // 11 clocks/bit
    CAN_BIT_VALUE(6, 5, 4),     // 12 clocks/bit
    CAN_BIT_VALUE(7, 5, 4),     // 13 clocks/bit
    CAN_BIT_VALUE(7, 6, 4),     // 14 clocks/bit
    CAN_BIT_VALUE(8, 6, 4),     // 15 clocks/bit
    CAN_BIT_VALUE(8, 7, 4),     // 16 clocks/bit
    CAN_BIT_VALUE(9, 7, 4),     // 17 clocks/bit
    CAN_BIT_VALUE(9, 8, 4),     // 18 clocks/bit
    CAN_BIT_VALUE(10, 8, 4)     // 19 clocks/bit
};

#define MAX_NO_CAN 2
#define NO_CAN_USED 1
typedef enum {
  CAN0,CAN1
}CAN_Num;

typedef enum {
  TX, TX_REMOTE, RX, RX_REMOTE, RXTX_REMOTE
}CAN_MessageType;


typedef struct{
  CAN_Num Num;
  uint32 BitRate;
  
}CAN_ConfigType;

typedef struct {
  
  uint32              ID;
  uint32              Mask;
  uint32              Flags;
  uint32              Length;
  uint8*              Data;
  CAN_MessageType       Type;
  uint8               MsgObj;
  
}CAN_MessageConfig;


void CAN_Init(CAN_ConfigType* config);

void CAN_Transmit(CAN_Num Num, CAN_MessageConfig* Message);

uint8 CAN_Receive(CAN_Num Num, CAN_MessageConfig* Message);

uint8 CAN_NewMessage(CAN_Num Num, CAN_MessageConfig *Message, uint32 ID);

extern CAN_ConfigType can_config[];

extern CAN_MessageConfig msg_config[];

#endif
