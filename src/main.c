/**
 * @file main.c
 * @author Kacper Janowski
 * @brief 
 * @version 0.1
 * @date 2021-05-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "stdio.h"
#include "sound.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define     TICK_START()        tickStart = SysTick->VAL
#define     TICK_TIME()     {   tickStop = SysTick->VAL;      \
                                tickDelay = tickStart - tickStop;   \
                                processingTime = (tickDelay - 3) * (1.0f / 80.0f);  }

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// Wyznaczanie czasu realizacji
uint32_t tickStart, tickStop,tickDelay;
float processingTime;

SoundCfg_t sound;

int16_t val;

// Utwór do tesotwania
Note_t notes[] = {{G,4},{E,4},{E,4}, {F,4},{D,4},{D,4}, {C,8},{E,8},{G,2}, {G,4},{E,4},{E,4}, {F,4},{D,4},{D,4}, {C,8},{E,8},{C,2},	{N,1},{N,1},{N,1}};

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

int main(void) {

    SOUND_Init(&sound, &notes, 18, 100, 120, 4);

	while (1) {
		AD_On(DEBUG_MAIN_LOOP_IO);
		if (PDSP_MODE == PDSP_MODE_POLL) {
			DataIn = CODEC_GetSample();  	// Odczytanie nowej próbki od kodeka
			CODEC_SetSample(DataOut);  		// Wysłanie próbki do kodeka
			DataOut = DataIn;               // Przetwarzanie
		} else {
			if (DataNew == true) {
				DataNew = false;
				AD_On(DEBUG_PROCESSING_IO);
				DataOut = DataIn;		// Przetwarzanie
				val =  SOUND_GetSample(&sound);
				DataOut.channel[0] = (int8_t)((1000 * val ) / ((PDSP_CODEC_Vres) * 1000.0f) );
				AD_Off(DEBUG_PROCESSING_IO);
			}
		}
		AD_Off(DEBUG_MAIN_LOOP_IO);
	}
}

void CODEC_IRQHandler(void){
	DataIn = CODEC_GetSample();   		// Odczytanie nowej próbki od kodeka
//	DataOut = DataIn;			        // Przetwarzanie - opcjonalnie
	CODEC_SetSample(DataOut);     		// Wysłanie próbki do kodeka
	DataNew = true;             		// Ustawienie flagi obecności nowych danych
	SampleNumber++;
}
