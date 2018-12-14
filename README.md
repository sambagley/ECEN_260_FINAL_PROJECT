# msp432-ws2812-POV-display-project

ccs project using an msp432 Launchpad at 48 MHZ to drive a string of 50 ws2812b RGB LEDs for a persistence of vision display. 
Inspired by the many bicycle POV display projects that have been made before. 

ws2812 addressing is based somewhat off of user efess's WS2812_CCS implimentation(https://github.com/fmilburn3/WS2812), although we opted to bit-bang our addressing signal instead of going the more elegant and probably efficient route of using SPI. 
