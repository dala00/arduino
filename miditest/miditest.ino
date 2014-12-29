#include <MIDI.h>

char notes[] = {36, 38, 40, 41, 43, 45, 47, 48};

void setup()
{
    MIDI.begin();          // Launch MIDI and listen to channel 4
}

void loop()
{
    for (int i = 0; i < 8; i++) {
      MIDI.sendNoteOn(notes[i],127,1);  // Send a Note (pitch 42, velo 127 on channel 1)
      delay(1000);		        // Wait for a second
      MIDI.sendNoteOff(notes[i],0,1);   // Stop the note
      delay(1000);		        // Wait for a second
    }
}
