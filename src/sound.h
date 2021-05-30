/*
 * sound.h
 *
 *  Created on: 28 maj 2021
 *      Author: Kacper Janowski
 */

#ifndef INC_SOUND_H_
#define INC_SOUND_H_

#include "stdint.h"
#include "generator.h"


typedef enum {C = 0, Cb = 1, D = 2, Db = 3, E  = 4, F = 5, Fb = 6, G = 7, Gb = 8, A = 9, Ab = 10, H = 11, N = 12} NoteName_t;

typedef struct {
	NoteName_t note;		// Symbol nuty
	uint32_t duration;		// Odwrotność czasu trwania nuty np. dla ćwierć nuty wynosi 4
//	uint8_t duration;		// Odwrotność czasu trwania nuty np. dla ćwierć nuty wynosi 4
}Note_t;

typedef struct {
	float amplituda;		// Określa poziom maksymalny sygnału w mV
	float bpm;				// Tempo grania nut wyrażona w uderzeniach na minutę - ćwierć nuta trwa 60/bpm np. dla BPM 120 -> (60 [s] / 120) = 0,5 [s]
	float * tone;			// Wskazuje na wybraną oktawę
	uint32_t length;		// Liczba nut w tablicy notes
	Note_t * notes;			// Wskazuje nuty i czasy ich trwania
	uint32_t n;				// Numer nuty

	// Uzupełnić o ewentualnie potrzebne elementy

	uint32_t duration;
	uint16_t octave;

	uint32_t sample;
    float gate;
    uint32_t gatePre;
    uint32_t gatePos;
	OSC_Cfg_t hToneSin;
	//
}SoundCfg_t;

/**
 * @brief Funkcja inicjująca strukturę konfiguracyjną
 * 
 * @param hCfg Struktura z parametrami dzwieku
 * @param notes Struktura z nutami
 * @param length Dlugosc melodii (liczba nut)
 * @param amplituda Amplituda
 * @param bpm Szybkosc (bits per minutes)
 * @param octava Oktawa
 */
void SOUND_Init(SoundCfg_t * hCfg, Note_t * notes, uint32_t length, float amplituda, float bpm, uint8_t octava);

/**
 * @brief Funkcja wyznaczania kolejnej próbki melodi
 * 
 * @param hCfg Struktura z parametrami dzwieku
 * @return int16_t Wartosc probki
 */
int16_t SOUND_GetSample(SoundCfg_t * hCfg);

#endif /* INC_SOUND_H_ */