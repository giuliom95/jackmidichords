#ifndef _CHORDS_H_
#define _CHORDS_H_

#define MIDI_STATUS_ACTIVE_SENSING 0b11111110

typedef enum _chord_type {
	NONE,
	MAJOR,
	MINOR
} chord_type_t;

typedef struct {
	char			velocity;
	chord_type_t	type;
} keystatus_t;

/**
 * \brief Contains chord info for every key.
 */
keystatus_t everykey[128];

/**
 * \brief Populates the `everykey` array with blank data.
 */
void populate_everykey();

/**
 * \brief Converts chord notes into midi commands. 
 * 
 * \param midi_buf		Buffer where to write MIDI commands. It has to be 12(3*4) bytes long.
 * \param key			Key of the chord to convert. Data will be fetched from `everykey`.
 * \param midi_status	MIDI status -- note on or off with channel -- to prepone on each command.
 */
void chord_midify(char* midi_buf, char key, char midi_status);

#endif
