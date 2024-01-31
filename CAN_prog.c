 /****************************************************************************
 *
 * Module: CAN
 *
 * File Name: CAN_program.c
 *
 * Description: source file for the CAN driver program
 *
 * Author: Ahmed Hesham 
 *
 * Created on: Sep 25, 2023
 *
 *****************************************************************************/

 #include "CAN_interface.h"
 #include "CAN_config.h"
 #include "CAN_private.h"
/********************************************************************/
void CAN_Init(CAN_ConfigType* config)
{
  
  for(uint8 i=0;i<NO_CAN_USED;i++)
  {
  
    uint32 Msg;
    

    //
    // Check the arguments.
    //
    
    if(/*config->Num*/ config[i].Num >= MAX_NO_CAN)
    {
    }
    else
    {
      SET_BIT(RCGC0, 24);
      while(GET_BIT( RCGC0, config->Num<<24) == 1);
      
        
      switch(config[i].Num)
      {
      case CAN0:
        SET_BIT(CAN0_CTL, CAN_CTL_INIT);
        //CAN0_CTL_R = 0x01;
        
        while( GET_BIT(CAN0_IF1CRQ, CAN_IF1CRQ_BUSY) );
        
        SET_BIT(CAN0_IF1CMSK, CAN_IF1CMSK_WRNRD);
        SET_BIT(CAN0_IF1CMSK, CAN_IF1CMSK_ARB);
        SET_BIT(CAN0_IF1CMSK, CAN_IF1CMSK_CONTROL);
        //CAN0_IF1CMSK_R = 0xB0;
        CAN0_IF1ARB2 = 0x00;
        CAN0_IF1MCTL = 0x00;
        
        for(Msg = 1; Msg <= 32; Msg++)
        {
          while( GET_BIT(CAN0_IF1CRQ, CAN_IF1CRQ_BUSY) );
          
          CAN0_IF1CRQ = Msg;
          
        }
        
        SET_BIT(CAN0_IF1CMSK, CAN_IF1CMSK_CLRINTPND);
        SET_BIT(CAN0_IF1CMSK, CAN_IF1CMSK_NEWDAT);
        //CAN0_IF1CMSK_R = 0x0C;
        
        for(Msg = 1; Msg <= 32; Msg++)
        {
          while( GET_BIT(CAN0_IF1CRQ, CAN_IF1CRQ_BUSY) );
          
          CAN0_IF1CRQ = Msg;
          
        }
        
        CAN0_STS;
        
        ///////////
        ///*
        uint32 DesiredRatio;
        uint32 CANBits;
        uint32 PreDivide;
        uint32 RegValue;
        uint16 CAN_CTL;
        uint8 flag = 0;
        
        //
        // Calculate the desired clock rate.
        //
        DesiredRatio = sourceClock / config[i].BitRate;
        
        //
        // Make sure that the Desired Ratio is not too large.  This enforces the
        // requirement that the bit rate is larger than requested.
        //
        if((sourceClock / DesiredRatio) > config[i].BitRate)
        {
            DesiredRatio++;
        }
        //
        // Check all possible values to find a matching value not more than 14 bytes.
        //
        while(DesiredRatio <= (CAN_MAX_PRE_DIVISOR * CAN_MAX_BIT_DIVISOR))
        {
            //
            // Loop through all possible CAN bit divisors.
            //
            for(CANBits = CAN_MAX_BIT_DIVISOR; CANBits >= CAN_MIN_BIT_DIVISOR; CANBits--)
            {
                //
                // For a given CAN bit divisor save the pre divisor.
                //
                PreDivide = DesiredRatio / CANBits;

                //
                // If the calculated divisors match the desired clock ratio then
                // return these bit rate and set the CAN bit timing.
                //
                if((PreDivide * CANBits) == DesiredRatio)
                {
                    //
                    // Start building the bit timing value by adding the bit timing
                    // in time quanta.
                    //
                    RegValue = CAN_BitValues[CANBits - CAN_MIN_BIT_DIVISOR];

                    //
                    // To set the bit timing register, the controller must be
                    // placed in init mode (if not already), and also configuration
                    // change bit enabled.  The state of the register must be
                    // saved so it can be restored.
                    //
                    CAN_CTL = CAN0_CTL;
                    CAN0_CTL = CAN_CTL | (1 << CAN_CTL_INIT) | (1 << CAN_CTL_CCE);

                    //
                    // Now add in the pre-scalar on the bit rate.
                    //
                    RegValue |= ((PreDivide - 1) & CAN_BIT_BRP_M);

                    //
                    // Set the clock bits in the and the lower bits of the
                    // pre-scalar.
                    //
                    CAN0_BIT = RegValue;

                    //
                    // Set the divider upper bits in the extension register.
                    //
                    CAN0_BRPE = ((PreDivide - 1) >> 6) & CAN_BRPE_BRPE_M;

                    //
                    // Restore the saved CAN Control register.
                    //
                    CAN0_CTL = CAN_CTL;
                    
                    flag = 1;
                    
                    break;
                }
                
                
                        
            }
            //
            // Move the divisor up one and look again.  Only in rare cases are
            // more than 2 loops required to find the value.
            //
            if(flag)
            {
              break;
            }
            DesiredRatio++;
                
        }
        SET_BIT(CAN0_CTL, CAN_CTL_IE);
        CLEAR_BIT(CAN0_CTL, CAN_CTL_INIT);//*/

        
        
        break;
        
      case CAN1:
        
        CAN1_CTL = 0x01;
        
        while(GET_BIT(CAN1_IF1CRQ,CAN_IF1CRQ_BUSY));
        
        CAN1_IF1CMSK = 0xB0;
        CAN1_IF1ARB2 = 0x00;
        CAN1_IF1MCTL = 0x00;
        
        for(Msg = 1; Msg <= 32; Msg++)
        {
          while(GET_BIT(CAN1_IF1CRQ,CAN_IF1CRQ_BUSY));
          
          CAN1_IF1CRQ = Msg;
          
        }
        
        CAN1_IF1CMSK = 0xC0;
        
        for(Msg = 1; Msg <= 32; Msg++)
        {
          while(GET_BIT(CAN1_IF1CRQ,CAN_IF1CRQ_BUSY));
          
          CAN1_IF1CRQ = Msg;
          
        }
        
        CAN1_STS;
        
        break;
        
      default:
        break;
      }
    }
  }
}
void CAN_Transmit(CAN_Num Num, CAN_MessageConfig* Message)
{
  /* INITIALIZATION */
  uint8 ExtendedID = 0, TransferData = 0;
  uint16 CMSK = 0, MSK1 = 0 , MSK2 = 0, ARB1 = 0, ARB2 = 0, MCTL = 0;
  
  switch(Num)
  {
  case CAN0:
    while( GET_BIT(CAN0_IF1CRQ, CAN_IF1CRQ_BUSY) );
    
    if( ( Message->ID > CAN_MAX_STD_MSG_ID ) || ( Message->Flags & CAN_MSG_EXTENDED_ID) )
       ExtendedID = STD_TRUE;
    else
      ExtendedID = STD_FALSE;
    SET_BIT(CMSK, CAN_IF1CMSK_WRNRD);
    SET_BIT(CMSK, CAN_IF1CMSK_CONTROL);
    SET_BIT(CMSK, CAN_IF1CMSK_DATAA);
    SET_BIT(CMSK, CAN_IF1CMSK_DATAB);
    //CMSK = 0x93;
    
    switch(Message ->Type)
    {
    case TX:
      SET_BIT(MCTL, CAN_IF1MCTL_TXRQST);
      SET_BIT(ARB2, CAN_IF1ARB2_DIR);
      //ARB2 = 0x2000;
      TransferData = STD_TRUE;
      
      break;
    case TX_REMOTE:
      SET_BIT(MCTL, CAN_IF1MCTL_TXRQST);
      ARB2 = 0;
      
      break;
    case RX:
      ARB2 = 0;
      
      break;
    case RX_REMOTE:
      SET_BIT(ARB2, CAN_IF1ARB2_DIR);
      //ARB2 = 0x2000;
      SET_BIT(MCTL, CAN_IF1MCTL_UMASK);
      //MCTL = 0x1000;
      MSK1 = CAN_IF1MSK1_MSK_MASK;
      MSK2 = CAN_IF1MSK2_MSK_MASK;
      SET_BIT(CMSK, CAN_IF1CMSK_MASK);
      
      break;
    case RXTX_REMOTE:
      SET_BIT(ARB2, CAN_IF1ARB2_DIR);
      //ARB2 = 0x2000;
      SET_BIT(MCTL, CAN_IF1MCTL_UMASK);
      SET_BIT(MCTL, CAN_IF1MCTL_RMTEN);
      //MCTL = 0x1200;
      TransferData = STD_TRUE;
      
      break;
    default:
      break;
    }
    
    if( Message->Flags & MSG_OBJ_USE_ID_FILTER )
    {
      if( ExtendedID )
      {
        MSK1 = Message -> Mask & CAN_IF1MSK1_MSK_MASK;
        MSK2 = ( ( Message->Mask >> 16) & CAN_IF1MSK2_MSK_MASK);
        
      }
      else
      {
        MSK1 = 0;
        MSK2 = ( ( Message ->Mask <<2) & CAN_IF1MSK2_MSK_MASK);
      }
    }
  
  if ( (Message ->Flags & MSG_OBJ_USE_EXT_FILTER) == MSG_OBJ_USE_EXT_FILTER)
  {
    SET_BIT(MSK2, CAN_IF1MSK2_MXTD); 
  }
  
  if( ( Message->Flags & MSG_OBJ_USE_DIR_FILTER) == MSG_OBJ_USE_DIR_FILTER)
  {
    SET_BIT(MSK2, CAN_IF1MSK2_MDIR);
  }
  
  if( Message -> Flags &  MSG_OBJ_USE_EXT_DIR_FILTER)
  {
    SET_BIT(MCTL,CAN_IF1MCTL_UMASK);
    SET_BIT(CMSK,CAN_IF1CMSK_MASK);
  }
  
  SET_BIT(CMSK,CAN_IF1CMSK_ARB);
  
  if( ExtendedID)
  {
    ARB1 |= Message ->ID & CAN_IF1ARB1_ID_MASK;
    ARB2 |= ( Message->ID >> 16) & CAN_IF1ARB2_ID_MASK;
    
    SET_BIT(ARB2, CAN_IF1ARB2_MSGVAL);
    SET_BIT(ARB2, CAN_IF1ARB2_XTD);
    //ARB2 |= 0xC0;
  }
  else
  {
    ARB2 |= ( Message->ID <<2) & CAN_IF1ARB2_ID_MASK;
    
    SET_BIT(ARB2, CAN_IF1ARB2_MSGVAL); 
  }
  
  MCTL |= (Message->Length & CAN_IF1MCTL_DLC_M);
  
  if( (Message->Flags & MSG_OBJ_FIFO) == 0)
  {
    SET_BIT(MCTL,CAN_IF1MCTL_EOB); 
  }
  
  if( (Message->Flags & MSG_OBJ_TX_INT_ENABLE))
  {
    SET_BIT(MCTL,CAN_IF1MCTL_TXIE); 
  }
  
  if( (Message->Flags & MSG_OBJ_RX_INT_ENABLE))
  {
    SET_BIT(MCTL,CAN_IF1MCTL_RXIE); 
  }
  
  if( TransferData)
  {
    CAN0_IF1DA1 = *(Message->Data);
    //_CANDataRegWrite(Message->Data, CAN0, Message->Length);
  }
  
  CAN0_IF1CMSK = CMSK;
  CAN0_IF1MSK1 = MSK1;
  CAN0_IF1MSK2 = MSK2;
  CAN0_IF1ARB1 = ARB1;
  CAN0_IF1ARB2 = ARB2;
  CAN0_IF1MCTL = MCTL;
  
  /* Message is ent as soon as ID is written in MNUM bits */
  CAN0_IF1CRQ = /*Message-> ID*/Message->MsgObj & CAN_IF1CRQ_MNUM_M;
  
  
    
    
    
    break;
  case CAN1:
    break;
  default:
    break;
  }
}

uint8 CAN_Receive(CAN_Num Num, CAN_MessageConfig* Message)
{
  /* INITIALIZATION */
  uint16 CMSK, MSK1 = 0 , MSK2 = 0, ARB1 = 0, ARB2 = 0, MCTL = 0;
  uint8 state = STD_FALSE;
  
  CMSK = ((1 << CAN_IF1CMSK_DATAA) | (1 << CAN_IF1CMSK_DATAB) |
          (1 << CAN_IF1CMSK_CONTROL) | (1 << CAN_IF1CMSK_MASK) |
          (1 << CAN_IF1CMSK_ARB));
  
  CMSK |= (1 << CAN_IF1CMSK_CLRINTPND);

  switch(Num)
  {
    case CAN0:
    CAN0_IF2CMSK = CMSK;
    CAN0_IF2CRQ = Message->MsgObj & CAN_IF1CRQ_MNUM_M;

    while(GET_BIT(CAN0_IF1CRQ, CAN_IF1CRQ_BUSY));

    MSK1 = CAN0_IF2MSK1;
    MSK2 = CAN0_IF2MSK2;
    ARB1 = CAN0_IF2ARB1;
    ARB2 = CAN0_IF2ARB2;
    MCTL = CAN0_IF2MCTL;

    Message->Flags = MSG_OBJ_NO_FLAGS;

    if((!(MCTL & (1 << CAN_IF1MCTL_TXRQST)) && (ARB2 & (1 << CAN_IF1ARB2_DIR))) || 
        ((MCTL & (1 << CAN_IF1MCTL_TXRQST))  && (!(ARB2 & (1 << CAN_IF1ARB2_DIR)))))
    {
      Message->Flags |= MSG_OBJ_REMOTE_FRAME;
    }

    if(ARB2 & (1 << CAN_IF1ARB2_XTD))
    {
      //
      // Set the 29 bit version of the Identifier for this message object.
      //
      Message->ID = (((ARB2 & CAN_IF1ARB2_ID_M) << 16) | ARB1);
      Message->Flags |= MSG_OBJ_EXTENDED_ID;
    }
    else
    {
      //
      // The Identifier is an 11 bit value.
      //
      Message->ID = (ARB2 & CAN_IF1ARB2_ID_M) >> 2;
    }

    //
    // Indicate that we lost some data.
    //
    if(MCTL & (1 << CAN_IF1MCTL_MSGLST))
    {
      Message->Flags |= MSG_OBJ_DATA_LOST;
    }
    
    //
    // Set the flag to indicate if ID masking was used.
    //
    if(MCTL & (1 << CAN_IF1MCTL_UMASK))
    {
      if(ARB2 & (1 << CAN_IF1ARB2_XTD))
      {
        //
        // The Identifier Mask is assumed to also be a 29 bit value.
        //
        Message->ID = ((ARB2 & CAN_IF1MSK2_IDMSK_M) << 16) | ARB1;

        //
        // If this is a fully specified Mask and a remote frame then don't
        // set the MSG_OBJ_USE_ID_FILTER because the ID was not really
        // filtered.
        //
        if((Message->ID != 0x1fffffff) || ((Message->Flags & MSG_OBJ_REMOTE_FRAME) == 0))
        {
          Message->Flags |= MSG_OBJ_USE_ID_FILTER;
        }
      }
      else
      {
        //
        // The Identifier Mask is assumed to also be an 11 bit value.
        //
        Message->ID = (ARB2 & CAN_IF1MSK2_IDMSK_M) >> 2;

        //
        // If this is a fully specified Mask and a remote frame then don't
        // set the MSG_OBJ_USE_ID_FILTER because the ID was not really
        // filtered.
        //
        if((Message->ID != 0x7ff) || ((Message->Flags & MSG_OBJ_REMOTE_FRAME) == 0))
        {
          Message->Flags |= MSG_OBJ_USE_ID_FILTER;
        }
      }

      //
      // Indicate if the extended bit was used in filtering.
      //
      if(ARB2 & (1 << CAN_IF1MSK2_MXTD))
      {
        Message->Flags |= MSG_OBJ_USE_EXT_FILTER;
      }

      //
      // Indicate if direction filtering was enabled.
      //
      if(ARB2 & (1 << CAN_IF1MSK2_MDIR))
      {
        Message->Flags |= MSG_OBJ_USE_DIR_FILTER;
      }
    }
    
    //
    // Set the interrupt flags.
    //
    if(MCTL & (1 << CAN_IF1MCTL_TXIE))
    {
        Message->Flags |= MSG_OBJ_TX_INT_ENABLE;
    }
    if(MCTL & (1 << CAN_IF1MCTL_RXIE))
    {
        Message->Flags |= MSG_OBJ_RX_INT_ENABLE;
    }

    //
    // See if there is new data available.
    //
    if(MCTL & 0x00008000)
    {
      state = STD_TRUE;
      //
      // Get the amount of data needed to be read.
      //
      Message->Length = (MCTL & CAN_IF1MCTL_DLC_M);

      //
      // Don't read any data for a remote frame, there is nothing valid in
      // that buffer anyway.
      //
      if((Message->Flags & MSG_OBJ_REMOTE_FRAME) == 0)
      {
        //
        // Read out the data from the CAN registers.
        //
        *(Message->Data) = CAN0_IF2DA1;
      }

      //
      // Now clear out the new data flag.
      //
      CAN0_IF2CMSK = (1 << CAN_IF1CMSK_NEWDAT);

      //
      // Transfer the message object to the message object specified by
      // ui32ObjID.
      //
      CAN0_IF2CRQ = Message->MsgObj & CAN_IF1CRQ_MNUM_M;

      //
      // Wait for busy bit to clear
      //
      while(GET_BIT(CAN0_IF2CRQ, CAN_IF2CRQ_BUSY));

      //
      // Indicate that there is new data in this message.
      //
      Message->Flags |= MSG_OBJ_NEW_DATA;
    }
    else
    {
      //
      // Along with the MSG_OBJ_NEW_DATA not being set the amount of data
      // needs to be set to zero if none was available.
      //
      Message->Length = 0;
    }
    break;
  case CAN1:
    break;
  default:
    break;
  
  }
  
  
  return state;
}

