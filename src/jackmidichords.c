#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <jack/jack.h>
#include <jack/midiport.h>


#define MIDI_STATUS_CC		0b1011
#define MIDI_STATUS_NOTEON	0b1001
#define MIDI_STATUS_NOTEOFF	0b1000


jack_port_t *midi_in_port;
jack_port_t *midi_out_port;

int process(jack_nframes_t nframes, void *data) {

	void *midi_in;
	void *midi_out;
	
	midi_in		= jack_port_get_buffer(midi_in_port,	nframes);
	midi_out	= jack_port_get_buffer(midi_out_port,	nframes);

	jack_midi_event_t in_event;
	jack_nframes_t event_count = jack_midi_get_event_count(midi_in);
	for(int i = 0; i < event_count; ++i) {
		jack_midi_event_get(&in_event, midi_in, i);
		jack_midi_data_t status = in_event.buffer[0];
		if(status >> 4 == MIDI_STATUS_NOTEON) {
			jack_midi_data_t ctrl_key = in_event.buffer[1];
			jack_midi_data_t ctrl_val = in_event.buffer[2];


		}
	}

	return 0;
}

void jack_shutdown(void *arg)
{
	exit(1);
}


int main(int argc, char *argv[])
{
	jack_client_t *client;

			char *client_name = "jackmidichords";
	const	char *server_name = NULL;
	
	jack_options_t options = JackNoStartServer;
	jack_status_t status;

	client = jack_client_open(client_name, options, &status, server_name);
	if(client == NULL) 
	{
		fprintf(stderr, "Jack client open failed, "
						"status = 0x%2.0x\n", status);
		if(status & JackServerFailed) 
		{
			fprintf (stderr, "Unable to connect to JACK server\n");
		}
		exit(1);
	}

	if(status & JackNameNotUnique) 
	{
		char *actual_client_name = jack_get_client_name(client);
		fprintf(stderr, "Unique name `%s' assigned\n", actual_client_name);
		strcpy(client_name, actual_client_name);
	}

	midi_in_port = jack_port_register(
		client, "MIDI IN",
		JACK_DEFAULT_MIDI_TYPE,
		JackPortIsInput, 0
	);
	midi_out_port = jack_port_register(
		client, "MIDI OUT",
		JACK_DEFAULT_MIDI_TYPE,
		JackPortIsOutput, 0
	);

	jack_set_process_callback(client, process, NULL);
	jack_on_shutdown(client, jack_shutdown, NULL);

	if(jack_activate(client))
	{
		fprintf(stderr, "Cannot activate client.\n");
		exit(1);
	}

	sleep(-1);

	jack_client_close(client);
	exit (0);
}
