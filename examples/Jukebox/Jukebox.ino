#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

//Buzzer library
#include "EasyBuzzer.h"

//list of available songs
#include "Songs.h"

//change the name of the song in lines 12, 13, 22 /**/ 
int tempo = happy_birthday_tempo; /**/
const int size = sizeof(happy_birthday) / sizeof(happy_birthday[0]); /**/
int melody[size]; 
int notes;
int wholenote;
int divider = 0; 
int noteDuration = 0;

void setup() 
{
    copyArray(happy_birthday, melody, size); /**/

    //calculate the number of notes in the song
    notes = sizeof(melody) / sizeof(melody[0]) / 2;

    // this calculates the duration of a whole note in ms
    wholenote = (60000 * 4) / tempo;

    divider = 0, noteDuration = 0;

}

void loop() 
{
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
    {
        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) 
        {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
        } 
        else if 
        (divider < 0) 
        {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        buzzer.beep(melody[thisNote]);

        // Wait for the specief duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        buzzer.stopBeep();
    }
    delay(1000);
}