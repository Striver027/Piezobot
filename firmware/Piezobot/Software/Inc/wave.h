/**
  ******************************************************************************
  * @file           : wave.h
  * @brief          : 
  ******************************************************************************
  * @attention

  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WAVE_H
#define __WAVE_H		

/* Includes ------------------------------------------------------------------*/


/* Private includes ----------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/

extern uint32_t toothsheet_fullwave[];
extern uint32_t toothsheet_runwave_left[];
extern uint32_t toothsheet_runwave_right[];


/* Exported macro ------------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

void RunWave_Gen(uint32_t *fullwave, float rate, uint32_t *genwave);

/* Private defines -----------------------------------------------------------*/

#define WAVE_LENTH 100

/* Local robot ID: picks received_data[LOCAL_ID - 1] (speed / angle). */
/* Wire IDs start at 1 and array indices at 0, as in protocol.c. */
#define LOCAL_ID 1





#endif
