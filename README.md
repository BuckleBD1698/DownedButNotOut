# Downed But Not Out - Vignettes RP

This adds a server configurable mechanic that intercepts the bit of damage that would kill a player and instead knocks them into a new DOWNED state.
It is inspired by games with similar mechanics, such as PUBG and ARC Raiders.
The goal of the mod is to give new mechanical flexibility to event based servers, and to support and improve medical RP on roleplay servers.

When entering the new DOWNED state:
* A new DOWNED status icon appears above the health/blood indicators.
* A red warning message is displayed to the player in the lower left, informing them of how long they have before dying.
* The player's health is 'restored' to 5 hitpoints. Any additional damage once entering this state may still kill the player.
* If the player's blood is greater than 3001, it is reduced to 3001, preventing the player from immediately going unconscious.
* The player is forced a prone, crawling state. Limited emotes can bring the player into a sitting position, but all movement will be limited to crawling.
* The player's hearing is reduced to 25% of the normal volume.
* The player can still interact with the world, their inventory, fire a gun, etc.
* No status effects are healed; the player maintains all bleeds, broken limbs, illnesses, etc.
* The player can only be revived by another player, which similarily does not restore any health, blood, shock or cure any status effects.

Non-DOWNED players have two new options when looking at a DOWNED player:
* REVIVE: a continuous action that will return the player to full control of their injured character.
* FINISH OFF: a continuous action that kills the DOWNED player, primarily for brutal bragging rights.

Server onwers can configure the following settings:
* Enabled: true/false toggle to turn the feature on and off
* downedTime: the number of seconds a downed player has to be revived before dying, default 120
* reviveTime: the number of seconds the Revive action requires, default 5
* finishTime: the number of seconds the Execute action requires, default 5

TODO in no particular order:
* Possibly require an item, like the debfibrillator, to revive a player.
* Possibly add more RP friendly mechanics to better support realistic medical RP.
* Possibly add a server toggle to clear status conditions on revive to allow for more flexibility in event style servers.
