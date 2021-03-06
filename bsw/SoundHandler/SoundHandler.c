//System includes
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

//User includes
#include "sound.h"

//Plays a tone multiple times and sleeps a given time interval after the tone was played.
void play_multiple_tones(U32 freq, U32 ms, U32 vol, U32 rep, U32 pause) {
	for(int i = 0; i < rep; i++) {
		ecrobot_sound_tone(freq, ms, vol);
		systick_wait_ms(pause);
	}
}

//Plays a wav multiple times and sleeps a given time interval after the wav was played.
void play_multiple_wavs(const CHAR *file, U32 length, S32 freq, U32 vol, U32 rep, U32 pause) {
	for(int i = 0; i < rep; i++) {
		ecrobot_sound_wav(file, length, freq, vol);	
		systick_wait_ms(pause);
	}
}
