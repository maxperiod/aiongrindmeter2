##[Click here for Downloads](https://github.com/maxperiod/aiongrindmeter2/releases)

Aion Grind Meter 2 - Aion XP/hr meter and more

##Screenshots

![alt text](images/expexample1.png "EXP - progress to next level")

EXP - progress to next level


![alt text](images/expexample2.png "EXP - cumulative progress to level 65")

EXP - cumulative progress to level 65


![alt text](images/apexample.png "AP")

AP


![alt text](images/gpexample.png "GP")

GP


![alt text](images/gatheringexample49.png "Gathering")

Gathering


![alt text](images/ophidan jerkin 1.png "Crafting")

Crafting


![alt text](images/proflevelingexample.png "Gathering/crafting profession leveling")

Gathering/crafting profession leveling


![alt text](images/theo 19x containers.png "Items from container opens")

Items from container opens


![alt text](images/theo 19x itemsacquired.png "Items acquired (except opened from containers)")

Items acquired (except opened from containers)


![alt text](images/theo 19x mobkills.png "Monster kills")

Monster kills

![alt text](images/pvpexample.png "Player kills and assists")

Player kills and assists

##Overview

Aion Grind Meter contains various grinding meters for Aion: 
* XP (Experience) mode
 * XP gained, in actual numbers and percentage
 * XP/hour (XP gained per hour), in actual amounts and percentage per hour
 * Cumulative progress bar to level 75
* AP (Abyss Points) mode
 * AP gained and lost 
 * AP/hour
 * AP gain from PvP
 * AP value of gained relics
* GP (Glory Points) gained and GP/hour
* Profession (Gathering / crafting) mode
 * List of recipes crafted
 * Number of success/failure/cancellation/procs per recipe
 * Successful attempts per hour
* Profession (Gathering / crafting) leveling mode
 * Profession level ups per hour
 * Estimated XP bar toward next skill level, if two level ups have been attained (not yet supported for aetherforging)
* Monster kills
 * List of XP-granting monsters killed
 * Mobs killed per hour, by monster name
* Item Acquisition
 * List of items acquired
 * Items gained per hour, by item ID
* Items acquired from container openings
* Player kills
 * Number of kills, deaths, and assists in PvP
 * List of players killed (you made last hit) or assisted (you dealt damage to a dead enemy player within 20 seconds)
 * Number of PvP kills per hour
* Item dice rolls


It uses the chat log file (Chat.log) to obtain gameplay information. It does not interact or modify the Aion client in any way.

Aion Grind Meter 2 is written in C++ with wxWidgets library powering the Graphical User Interface (GUI).



##Prerequisites

Aion chat log file (Chat.log) must be enabled and present for Grind Meter 2 to work.

Input strings and item names are currently configured for North American (NCWest) and Europe English (Gameforge) clients, update 5.0

####Enabling Chat Log
You can use Aion RainMeter (ARM) to enable chat log. 
It can be downloaded from http://rainy.ws/

Once you have enabled chat log using ARM, log into Aion with any one of your characters, and the Chat.log file will be created.



##Setup

Extract the folder to anywhere (Recommended: inside your Aion folder). 
You will be prompted to browse for your Aion folder when you run it for the first time.

You do not need to browse for your Aion folder if you extracted it into your Aion folder.
