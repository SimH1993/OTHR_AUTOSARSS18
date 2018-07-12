#ifndef SOUNDHANDLER_H_
#define SOUNDHANDLER_H_

#define play_single_tone(freq, ms, vol) ecrobot_sound_tone(freq, ms, vol)
#define play_single_wav(file, length, freq, vol) ecrobot_sound_wav(file, length, freq, vol)

void play_multiple_tones(U32 freq, U32 ms, U32 vol, U32 rep, U32 pause);
void play_multiple_wavs(const CHAR *file, U32 length, S32 freq, U32 vol, U32 rep, U32 pause);

#endif /* SOUNDHANDLER_H_ */
