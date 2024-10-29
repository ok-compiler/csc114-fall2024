im making a jrpg game where you attack enemies with hp and have items, powerups, etc

## im kinda going over the top with this for the sake of learning, decided to add:
- progress saving (possibly, im gonna try saving in a .txt file cuz im dumb)
- story cuz why not 
- different protags with different stats/traits 
- bosses 
- different chapters 
- pokemon style menu for jrpg stuff, with fight/run/item options 
- multiple files for ease of reading 
- movement possibly, im not sure how to implement

also i know this is a md file but im too lazy to format it at the moment, so its kinda a mess

## files include:
- engine.h - game engine with all shared function from each file 
- main.cpp - main file with the bulk of logic (i think for now) 
- title.cpp - self explanatory, title screen function 
- monologue.cpp - runs story monologue when new game is started

## future files to most likely be included:
- save.txt - all save data (its in a txt instead of using something like sql cuz im dumb and dont feel like it) 
- save_load.cpp - loads save data from save.txt file 
- interface.cpp - player interface (hoping to have player use wasd to move using 2d arrays)

## other things i havent planned fully:
- maps/layouts (they'll be split in sections kinda like zelda on the nes) 
- enemy types 
- combat

i would like to give proper credit to chatgpt (my best friend) for coming up with the story for this game, elsewise everything here has been written by me and me only

