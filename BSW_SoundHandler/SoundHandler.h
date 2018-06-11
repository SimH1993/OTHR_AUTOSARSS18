SINT play_single_tone(U32 freq, U32 ms, U32 vol);

SINT play_single_wav(const CHAR *file, U32 length, S32 freq, U32 vol);

void play_multiple_tones(U32 freq, U32 ms, U32 vol, U32 rep, U32 pause);

void play_multiple_wavs(const CHAR *file, U32 length, S32 freq, U32 vol, U32 rep, U32 pause);