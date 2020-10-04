# Cookie Synthesizer firmware

The Cookie Synth uses YAM0.05 alternative firmware for Shruthi-1 written by bjoeri.
I changed the splash screen to show "Cookie Synth" and removed "Mutable Instruments" because this is a registered trademark of Émilie Gillet.
To adapt for inverting opamps at the CV inputs the method "Ui::ScanPotentiometers()" in file "ui.cc" has been modified by adding the following line: 
```
    adc_.StartConversion(pots_multiplexer_address_);
    if (address >= 4) {
      value = 1023 - value;   // ### Cookie: invert external CV inputs CV1..4
      part.mutable_voice()->set_modulation_source(
          MOD_SRC_CV_1 + address - 4, value >> 2);
      address = 0xff;
    }
```


### User Manual
Have a look at the [user manual of the original Shruthi-1](https://mutable-instruments.net/archive/shruthi/manual/).


### YAM0.05 Differences / Improvements
Here's a short summary of changes compared to official Shruthi-1 firmware 1.02:

* PolyBlep implementations replace the original band-limited 'saw' and 'square' oscillators for higher fidelity and less memory footprint (Polyblep implementations inspired by, but less general than, Oliviers prototype for STM).
* 'square' is now a Polyblep oscillator with a more proper sounding PWM, i.e. more edginess, and no loudness drop for PWM modulation parameter above 0. (The original aliasing pwm is still available as 'dpwm'.)
* 'saw' is now a Polyblep oscillator (withuot any high pass pre-filtering and the modulation is different). The parameter for saw now add mix of a 2nd saw edge, resulting in a saw with sub oscillator (actually super oscillator) sound. 
* 'triangle' is no longer band-limited (to reduce memory footprint) and is folded (instead of clipped) upon modulation. This also means that the 'crush' oscillator is slightly different sounding.
* Added a 'csaw' Polyblep oscillator very similar to the CS-80 inspired saw oscillator for Braids. Without modulation it's a plain saw (identical to 'saw'). Modulation adds a 'notch' discontinuity before the ramp.
* Added a quad PWM oscillator ('qpwm') very similar to the quad saw ('pad'). The modulation parameter simultaneously affect both detuning of the four pwm oscillators, and the pulse width.
* Added an alternative FM oscillator ('fmfb') with feedback modulation. Just as for the regular FM oscillator, the modulation parameter defines the FM amount, but for modulation values above 64 increasing amount of feedback is added. At moderate levels the feedback adds 'grit'. At higher settings it adds digital distortion (deliberately left in).
* Added filter variations of CZ resonance saw and pulse waveforms ported from Ambika ('lpzsaw', 'pkzsaw', 'hpzsaw', 'lpzpulse', 'pkzpulse', 'hpzpulse'). In this new naming conventionm, the old 'zreso' is now named 'lpzsaw', and the old 'zpulse' is now named 'pkzpulse'.
* Added 'wavquence' oscillator (simply ported from the official Ambika firmware).
* Duo mode voice allocation reverted to 0.96 behaviour (because I subjectively think it's more enjoyable):
  - Press and hold C -> Osc1 plays C; then 
  - Press and hold E -> Osc2 plays C, Osc1 plays E 
  - (Sub is always assigned to lowest note)

Some tips on patch compatibility with official Shruthi-1 firmware:
Due to qualitative differences of the 'saw' and 'square' oscillators etc, levels may have to be adjusted somewhat to mimic original patches. If you really miss the original saw oscillator from the official firmware, this one is still available as 'oldsaw' (it's high-pass sampled and have a different character).


### How to make
- On a Mac install CrossPack-AVR with GCC Version 4.3.3: https://www.obdev.at/downloads/crosspack/CrossPack-AVR-20100115.dmg
- Connect an avrdude compatible programmer (e. g. AVRISP mkII) to the ISP connector on the Cookie and to a USB port on your computer.
Check the avrdude parameters in avrlib/makefile.mk.
- Use the terminal and go to the Cookie firmware directory.
- Make the bootloader first: make -f bootloader/makefile
- Then make the rest: make bake_all


### Authors
* Author of the original Shruthi-1 firmware is Émilie Gillet.
See https://github.com/pichenettes/shruthi-1
* Author of the alternative firmware YAM is bjoeri.
See https://github.com/bjoeri/shruthi-1


### License
The firmware is released under a GPL3.0 license. It includes a
reimplementation of the formant synthesis algorithm used in Peter Knight's
Cantarino speech synthesizer.

