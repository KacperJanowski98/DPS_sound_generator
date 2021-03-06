/*
 * sound.c
 *
 *  Created on: 28 maj 2021
 *      Author: Kacper Janowski
 */

#include "sound.h"

// Skala chromatyczna durowa (majorowa)

const float tone[9][13] = {
		/* C		 C#			  D			 D#			  E			  F			 F#			  G			 G#			  A			 A#			  H */
/* 0 */{ 16.35f, 	17.32f, 	18.35f,   19.45f, 		20.60f,   21.83f, 		23.12f, 	24.50f, 	25.96f, 	27.50f, 	29.14f, 	30.87f, 0.0f },
/* 1 */{ 32.70f, 	34.65f, 	36.71f,   38.89f, 		41.20f,   43.65f, 		46.25f, 	49.00f, 	51.91f, 	55.00f, 	58.27f, 	61.74f, 0.0f },
/* 2 */{ 65.41f, 	69.30f, 	73.42f,   77.78f, 		82.41f,   87.31f, 		92.50f, 	98.00f,    103.83f,    110.00f,    116.54f,    123.47f, 0.0f },
/* 3 */{ 130.81f, 	138.59f,   146.83f,  155.56f, 	   164.81f,  174.61f,  	   185.00f,    196.00f,    207.65f,    220.00f,    233.08f,    246.94f, 0.0f },
/* 4 */{ 261.63f, 	277.18f,   293.66f,  311.13f, 	   329.63f,  349.23f, 	   369.99f,    392.00f,    415.30f,    440.00f,    466.16f,    493.88f, 0.0f },
/* 5 */{ 523.25f, 	554.37f,   587.33f,  622.25f, 	   659.26f,  698.46f, 	   739.99f,    783.99f,    830.61f,    880.00f,    932.33f,    987.77f, 0.0f },
/* 6 */{ 1046.50f, 1108.73f,  1174.66f, 1244.51f,     1318.51f, 1396.91f, 	  1479.98f,   1567.98f,   1661.22f,   1760.00f,   1864.66f,   1975.53f, 0.0f },
/* 7 */{ 2093.00f, 2217.46f,  2349.32f, 2489.02f, 	  2637.02f, 2793.83f, 	  2959.96f,   3135.96f,   3322.44f,   3520.00f,   3729.31f,   3951.07f, 0.0f },
/* 8 */{ 4186.01f, 4434.92f,  4698.64f, 4978.03f, 	  5274.04f, 5587.65f, 	  5919.91f,   6271.93f,   6644.88f,   7040.00f,   7458.62f,   7902.13f, 0.0f }, };


// Utwór do tesotwania
//Note_t notes[] = {{G,4},{E,4},{E,4}, {F,4},{D,4},{D,4}, {C,8},{E,8},{G,2}, {G,4},{E,4},{E,4}, {F,4},{D,4},{D,4}, {C,8},{E,8},{C,2},	{N,1},{N,1},{N,1}};


void SOUND_Init(SoundCfg_t * hCfg, Note_t * notes, uint32_t length, float amplituda, float bpm, uint8_t octava){
    hCfg->amplituda = amplituda;
	hCfg->notes = notes;
    hCfg->bpm = bpm = (60.0f/bpm) ;
    hCfg->length = length;
//    hCfg->gate = 0.1;
	hCfg->bpm = (60.0f / bpm);
	hCfg->octave = octava;
	hCfg->n = 0;
    hCfg->sample = 0;
    hCfg->tone = (float*)notes->duration;

    hCfg->notes[hCfg->n].duration = (uint32_t)(((1.0f/(hCfg->notes[hCfg->n].duration)) * hCfg->bpm) * PDSP_CODEC_Fs);

//     hCfg->gatePre = (uint32_t)(hCfg->notes[hCfg->n].duration * hCfg->gate);
//     hCfg->gatePos = (uint32_t)(hCfg->notes[hCfg->n].duration - (hCfg->notes[hCfg->n].duration * hCfg->gate));

	OSC_Init(&hCfg->hToneSin, OSC_Sinusoid, hCfg->amplituda, tone[hCfg->octave][hCfg->notes[hCfg->n].note], 0.0f);

}

int16_t SOUND_GetSample(SoundCfg_t * hCfg){
    float wynik;
//    float gateValue;
//
//     if(hCfg->sample < hCfg->gatePre){
//         gateValue = cosf(((float)hCfg->sample / (float)hCfg->gatePre) * PDSP_2PI_DIV_FS);
//         gateValue *= gateValue;
//         gateValue = (1.0f - gateValue);
//     } else if (hCfg->sample > hCfg->gatePos){
//         gateValue =cosf(((hCfg->notes[hCfg->n].duration - hCfg->sample) * PDSP_2PI_DIV_FS ) / (hCfg->gatePre ));
//         gateValue *= gateValue;
//     } else {
//         gateValue = 1.0f;
//     }

	wynik = ((hCfg->amplituda) * OSC_GetValuePeriodF(&hCfg->hToneSin));

    hCfg->sample++;
    if(hCfg->sample == hCfg->notes[hCfg->n].duration){
        hCfg->sample = 0;
        hCfg->n++;
        if(hCfg->n == hCfg->length) {
            hCfg->n = 0;
        }
//        hCfg->notes->duration = (uint32_t)(((1.0f / (hCfg->notes->duration[&hCfg->n]))* hCfg->bpm) * PDSP_FS);
        hCfg->notes[hCfg->n].duration = (uint32_t)(((1.0f/(hCfg->notes[hCfg->n].duration)) * hCfg->bpm) * PDSP_CODEC_Fs);

//        hCfg->gatePre = (uint32_t)(hCfg->notes[hCfg->n].duration * hCfg->gate);
//        hCfg->gatePos = (uint32_t)(hCfg->notes[hCfg->n].duration - (hCfg->notes[hCfg->n].duration * hCfg->gate));

		OSC_SetFreq(&hCfg->hToneSin, tone[hCfg->octave][hCfg->notes[hCfg->n].note]);
    }
    return (int16_t)wynik;
}
