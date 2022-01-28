# Arduino-Roulette-like-game
Code for the Roulette-like game I designed and built.

There are 60 LEDs arranged in circle (1m of adressable LED strip is used), from which one that represents goal has fixed index and lights up red all the time. 
Other LEDs are all off but one which is yellow, and that yellow dot moves around the circle. The goal of the game is to press a button at the exact time when
yellow dot comes on the red one. If that happens, the player moves on to the next level, and the current level is displayed on sevensegment. 
Each level is a bit harder, because the yellow dot moves a bit faster. There are 9 levels in total, and if the player passes all 9 levels, the game returns to
level 1. Additionally, the yellow dot starts its moving randomly somwhere between the first 30 LEDs.
After the successful stopping, whole LED circle blinks yellow as an indication of a level upgrade. In contrast, after an error, the circle blinks red, and the
player returns to level 1.

You can see the final look of the game on YT: https://www.youtube.com/watch?v=ZWWBeHa98_0
