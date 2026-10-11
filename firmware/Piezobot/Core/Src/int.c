#include "tim.h"
#include "dac.h"
#include "usart.h"

#include "int.h"
#include "comm.h"
#include "protocol.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if (htim->Instance == TIM7)
	{
//		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); 
//		HAL_GPIO_TogglePin(IPS_BLK_GPIO_Port, IPS_BLK_Pin);

	}
}


/**
  * @brief  USART3 receive complete callback.
  * @note   The callback lives here with the other HAL callbacks; the byte is
  *         handled by the comm module, which also decides whether to forward it
  *         (see Comm_ProtocolRun) and always re-arms the reception.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART3)
	{
		switch (Comm_ProtocolRun)
		{
			case 0:
			Comm_Usart3RxHandler();
			break;
			
			case 1:
			Protocol_Recieve_UART();
			break;
		}
		
	}
	
}

/**
  * @brief  USART error callback: let the comm module recover USART3.
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART3)
	{
		Comm_Usart3ErrorHandler();
	}
}
