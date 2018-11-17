
#include "music.h"
#include "buzzer.h"

#include "global_defines.h"

#include "util/delay.h"


void firstSection()
{
  buzzer_set_tone(a, 500);
  buzzer_set_tone(a, 500);
  buzzer_set_tone(a, 500);
  buzzer_set_tone(f, 350);
  buzzer_set_tone(cH, 150);
  buzzer_set_tone(a, 500);
  buzzer_set_tone(f, 350);
  buzzer_set_tone(cH, 150);
  buzzer_set_tone(a, 650);

  _delay_ms(500);

  buzzer_set_tone(eH, 500);
  buzzer_set_tone(eH, 500);
  buzzer_set_tone(eH, 500);
  buzzer_set_tone(fH, 350);
  buzzer_set_tone(cH, 150);
  buzzer_set_tone(gS, 500);
  buzzer_set_tone(f, 350);
  buzzer_set_tone(cH, 150);
  buzzer_set_tone(a, 650);

  _delay_ms(500);
}

void secondSection()
{
  buzzer_set_tone(aH, 500);
  buzzer_set_tone(a, 300);
  buzzer_set_tone(a, 150);
  buzzer_set_tone(aH, 500);
  buzzer_set_tone(gSH, 325);
  buzzer_set_tone(gH, 175);
  buzzer_set_tone(fSH, 125);
  buzzer_set_tone(fH, 125);
  buzzer_set_tone(fSH, 250);

  _delay_ms(325);

  buzzer_set_tone(aS, 250);
  buzzer_set_tone(dSH, 500);
  buzzer_set_tone(dH, 325);
  buzzer_set_tone(cSH, 175);
  buzzer_set_tone(cH, 125);
  buzzer_set_tone(b, 125);
  buzzer_set_tone(cH, 250);

  _delay_ms(350);
}
