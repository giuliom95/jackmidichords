#include "chords.h"

#include <string.h>

void chord_midify(char* midi_buf, chord_t chord, char midi_status) {
	switch(chord.type) {
		case MAJOR:
			midi_buf[0] = midi_status;
			midi_buf[1] = chord.key + 4;
			midi_buf[2] = chord.velocity;
			midi_buf[3] = midi_status;
			midi_buf[4] = chord.key + 7;
			midi_buf[5] = chord.velocity;
			memset(&midi_buf[6], 0b11111110, 6);
			break;
	}
}