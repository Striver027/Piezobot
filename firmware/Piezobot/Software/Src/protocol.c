#include "stm32g4xx_hal.h"
#include <string.h>

#include "usart.h"
#include "protocol.h"
#include "comm.h"


uint8_t rx_index = 0;
uint8_t frame_rx_buf[FRAME_BUF_SIZE];
uint8_t frame_data_buf[FRAME_BUF_SIZE];

#ifdef PROTOCOL_MODE_RX
/* Protocol initialisation: stop the USART3 interrupt handler from consuming
   the bytes, so that the parsing code below owns the port. */
void Protocol_Init(void)
{
    Comm_ProtocolRun = 1;
#ifdef PROTOCOL_MODE_RX
		
		HAL_UART_Receive_IT(&PROTOCOL_UART_PORT, frame_rx_buf, 1);

#endif
	
}
#endif

#ifdef PROTOCOL_MODE_TX
    Protocol_DataStruct_TypeDef transmitted_data[PROTOCOL_ID_NUM];
	Protocol_Transmission_StateTypeDef tramsmit_state = IDLE;
#endif
#ifdef PROTOCOL_MODE_RX
  Protocol_DataStruct_TypeDef received_data[PROTOCOL_ID_NUM];
	Protocol_Transmission_StateTypeDef receive_state = IDLE;
#endif




#ifdef PROTOCOL_MODE_TX
void Protocol_Send_UART(Protocol_DataStruct_TypeDef* data) {
	uint8_t packet[PROTOCOL_DATA_LEN];
	static uint8_t tx_buf[FRAME_BUF_SIZE];

	Protocol_Encode_Packet(data, packet);
	Protocol_Build_Frame (tx_buf, packet, PROTOCOL_DATA_LEN);
	HAL_UART_Transmit(&PROTOCOL_UART_PORT, tx_buf, PROTOCOL_DATA_LEN + 4, 100);


}
#endif

#ifdef PROTOCOL_MODE_RX
void Protocol_Recieve_UART(void){
	Protocol_Parse_Frame();
	HAL_UART_Receive_IT(&PROTOCOL_UART_PORT, frame_rx_buf, 1);


}
#endif
#ifdef PROTOCOL_MODE_TX
void Protocol_Encode_Packet(Protocol_DataStruct_TypeDef* data, uint8_t* packet) {
		
    memcpy(&packet[0], &data->ID, 1);
    memcpy(&packet[1], &data->speed, 4);
    memcpy(&packet[5], &data->angle, 4);
    memcpy(&packet[9], &data->voltage, 4);
	// uint8_t i;
	
	// for (i = 0; i < 14; i++)
	// {
	// 	packet[i] = i	;
	// }
	// HAL_UART_Transmit_IT(&huart1, packet, i);
	
}
#endif
#ifdef PROTOCOL_MODE_RX
void Protocol_Decode_Packet(Protocol_DataStruct_TypeDef* data, uint8_t* packet, uint8_t len) {
    if (len != PROTOCOL_DATA_LEN) return; // 防呆

    memcpy(&data->ID, &packet[0], 1);
    memcpy(&data->speed, &packet[1], 4);
    memcpy(&data->angle, &packet[5], 4);
    memcpy(&data->voltage, &packet[9], 4);


    // 你可以打印或处理这些变量
//    printf("ID: %d, Speed: %.2f, Angle: %.2f, Voltage: %.2f\n",
// 		data->ID, data->speed, data->angle, data->voltage);
}
#endif
#ifdef PROTOCOL_MODE_TX

void Protocol_Build_Frame (uint8_t* tx_buf, uint8_t* packet, uint8_t len) {
	uint8_t i, checksum = 0;

	tx_buf[0] = FRAME_HEADER;       // 帧头
	tx_buf[1] = len;        // 数据长度
  
	for (i = 0; i < len; i++) {
		tx_buf[2 + i] = packet[i];
		checksum ^= packet[i];  // XOR校验
	}


	tx_buf[2 + len] = checksum;
	tx_buf[3 + len] = FRAME_TAIL;   // 帧尾

// 	for (uint8_t i = 0; i < 17; i++)
//   {
//     frame_rx_buf[0] = tx_buf[i];
//		Protocol_Recieve_UART();
//   }

  }
  #endif

  #ifdef PROTOCOL_MODE_RX
void Protocol_Parse_Frame(void) {
	static uint8_t current_byte;
	static Protocol_Parse_StateTypeDef state = WAIT_HEAD;
	static uint8_t data_len = 0, data_index = 0, checksum = 0;

	current_byte = frame_rx_buf[0];  // 每次收一个字�?

//	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

	switch (state) {
		case WAIT_HEAD:
			if (current_byte == FRAME_HEADER) {
				state = WAIT_LEN;
//				receive_state = BUSY;

			}
			break;

		case WAIT_LEN:
			data_len = current_byte;
			data_index = 0;
			checksum = 0;
			state = WAIT_DATA;
			break;

		case WAIT_DATA:
			frame_data_buf[data_index++] = current_byte;
			checksum ^= current_byte;
			if (data_index >= data_len) {
				state = WAIT_CHECK;
			}
			break;

		case WAIT_CHECK:
		
			if (current_byte == checksum) {

				state = WAIT_TAIL;
			} else {
				state = WAIT_HEAD; // 校验失败，丢�?
				receive_state = IDLE;
				
			}
			break;

		case WAIT_TAIL:
			if (current_byte == FRAME_TAIL && receive_state == IDLE) {// �?成功接收完整�?
				Handle_Received_Packet(frame_data_buf, data_len);
				state = WAIT_HEAD;	
				receive_state = DONE;
			}
			break;
	}

}
#endif
#ifdef PROTOCOL_MODE_RX
void Handle_Received_Packet(uint8_t* data, uint8_t len) {
	// receive_state = BUSY;
	Protocol_Decode_Packet(&(received_data[data[0] - 1]), data, len);
	// receive_state = DONE;

}
#endif

