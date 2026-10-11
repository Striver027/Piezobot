#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "stm32g4xx_hal.h"

//Protocol mode select
// #define PROTOCOL_MODE_TX
#define PROTOCOL_MODE_RX

#define PROTOCOL_UART_PORT huart3
#define PROTOCOL_ID_NUM 50

#define PROTOCOL_DATA_LEN 13
#define FRAME_BUF_SIZE 128
#define FRAME_HEADER 0xAA
#define FRAME_TAIL 0x55


typedef enum
{
	IDLE, BUSY, DONE

} Protocol_Transmission_StateTypeDef;

typedef enum
{
	WAIT_HEAD, WAIT_LEN, WAIT_DATA, WAIT_CHECK, WAIT_TAIL 

} Protocol_Parse_StateTypeDef;

typedef struct {
    uint8_t ID;
    float speed;
    float angle;
    float voltage;
} Protocol_DataStruct_TypeDef;

#ifdef PROTOCOL_MODE_RX
    // extern uint8_t rx_index = 0;
extern uint8_t frame_rx_buf[FRAME_BUF_SIZE];
    // extern uint8_t frame_data_buf[FRAME_BUF_SIZE];
#endif



#ifdef PROTOCOL_MODE_TX
    extern Protocol_DataStruct_TypeDef transmitted_data[PROTOCOL_ID_NUM];
    extern Protocol_Transmission_StateTypeDef transmit_state;

#endif
#ifdef PROTOCOL_MODE_RX
    extern Protocol_DataStruct_TypeDef received_data[PROTOCOL_ID_NUM];
    extern Protocol_Transmission_StateTypeDef receive_state;

#endif


#ifdef PROTOCOL_MODE_TX
    void Protocol_Send_UART(Protocol_DataStruct_TypeDef *packet);
#endif
#ifdef PROTOCOL_MODE_RX
    void Protocol_Recieve_UART(void);
#endif
#ifdef PROTOCOL_MODE_TX
    void Protocol_Encode_Packet(Protocol_DataStruct_TypeDef *packet, uint8_t *data);
#endif
#ifdef PROTOCOL_MODE_RX
    void Protocol_Decode_Packet(Protocol_DataStruct_TypeDef *data, uint8_t *packet, uint8_t len);
#endif
#ifdef PROTOCOL_MODE_TX
    void Protocol_Build_Frame(uint8_t *tx_buf, uint8_t *packet, uint8_t len);
#endif
#ifdef PROTOCOL_MODE_RX
    void Protocol_Parse_Frame(void);

    void Handle_Received_Packet(uint8_t *data, uint8_t len);

    /* Takes USART3 over for the parsing code (sets Comm_ProtocolRun) */
    void Protocol_Init(void);
#endif




#endif
