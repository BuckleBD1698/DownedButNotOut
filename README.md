# BBD_VignettesDownedButNotOut

This adds a server configurable mechanic that intercepts the bit of damage that would kill a player and instead knocks them into a new DOWNED state.

DOWNED players can still interact with the world, their inventory, fire their guns, etc. However, they can only crawl around and their hearing is decreased.
After a set amount of time, if another player does not help them back up, the DOWNED player dies.
DOWNED players have 5 hitpoints, so any additional damage will likely kill them. Being DOWNED does not cure bleeds or any other status effect injuries, such as broken legs.
If a player has greater than 3001 blood, they are reduced to 3001 in the DOWNED state.
A DOWNED player who is revived is not healed in any way. They retain all status effects, bleeds, health, blood and shock values they had in the DOWNED state.

Non-downed players have the option to help up fallen players, or finish them off, each with an animation.

Server onwers can configure the following settings:
* Enabled: true/false toggle to turn the feature on and off
* downedTime: the number of seconds a downed player has to be revived before dying, default 120
* reviveTime: the number of seconds the Revive action requires, default 5
* finishTime: the number of seconds the Execute action requires, default 5

TODO in no particular order:
* Possibly require an item, like the debfibrillator, to revive a player.
* Possibly add more RP friendly mechanics to support more realistic medical RP.
* Possibly add a server toggle to clear status conditions on revive to allow for more flexibility in event style servers.
