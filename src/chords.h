#ifndef _CHORDS_H_
#define _CHORDS_H_

typedef enum _chord_type {
	MAJOR,
	MINOR
} chord_type_t;

typedef struct {
	char			key;
	char			velocity;
	chord_type_t	type;
} chord_t;

/**
 * \brief Converts chord notes into midi commands. 
 * 
 * \param midi_buf		Buffer where to write MIDI commands. It has to be 12(3*4) bytes long.
 * \param chord			Chord to convert.
 * \param midi_status	MIDI status -- typically note on or off -- to prepone on each command.
 */
void chord_midify(char* midi_buf, chord_t chord, char midi_status);

#endif
