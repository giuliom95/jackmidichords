#include "chords.h"

#include <string.h>

void populate_everykey() {
	memset(everykey, 0, 128*sizeof(keystatus_t));
}

void chord_midify(char* midi_buf, char key, char midi_status) {
	chord_type_t	type = everykey[key].type;
	char			vel  = everykey[key].velocity;

	// Fill buffer with the Active Sensing message.
	memset(midi_buf, MIDI_STATUS_ACTIVE_SENSING, 12);

	switch(type) {
		case MAJOR:
			midi_buf[0] = midi_status;
			midi_buf[1] = key + 4;
			midi_buf[2] = vel;
			midi_buf[3] = midi_status;
			midi_buf[4] = key + 7;
			midi_buf[5] = vel;
			break;
	}
}