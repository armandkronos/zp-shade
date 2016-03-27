/*================================================================================
	
	-------------------------------------------------------
	-*-      Zombie Plague Shade 1.1.2 Includes File    -*-
	-------------------------------------------------------
	
	~~~~~~~~~~
	- How To -
	~~~~~~~~~~
	
	To make use of the Zombie Plague API features in your plugin, just
	add the following line at the beginning of your script:
	
	#include <zombieplague>
	
	~~~~~~~~~~~
	- Natives -
	~~~~~~~~~~~
	
	These work just like any other functions: you may have to pass
	parameters and they usually return values.
	
	Example:
	
	if ( is_user_alive( id ) && zp_get_user_zombie( id ) )
	{
		server_print( "Player %d is alive and a zombie", id )
	}
	
	~~~~~~~~~~~~
	- Forwards -
	~~~~~~~~~~~~
	
	Forwards get called whenever an event happens during the game.
	You need to make a public callback somewhere on your script,
	and it will automatically be triggered when the event occurs.
	
	Example:
	
	public zp_user_infected_post( id, infector, nemesis )
	{
		if ( !infector || nemesis )
			return;
		
		server_print( "Player %d just got infected by %d!", id, infector )
	}
	
	Also, take note of cases when there's a suffix:
	
	* _pre  : means the forward will be called BEFORE the event happens
	* _post : means it will be called AFTER the event takes place
	
=================================================================================*/

#if defined _zombieplague_included
  #endinput
#endif
#define _zombieplague_included

/* Teams for zp_register_extra_item() */
#define ZP_TEAM_ZOMBIE (1<<0)
#define ZP_TEAM_HUMAN (1<<1)
#define ZP_TEAM_NEMESIS (1<<2)
#define ZP_TEAM_SURVIVOR (1<<3)
#define ZP_TEAM_SNIPER (1<<4)
#define ZP_TEAM_ASSASSIN (1<<5)
#define ZP_TEAM_BOMBARDIER (1<<6)

/* Game modes for zp_round_started() */
enum
{
	MODE_NONE = 0,
	MODE_INFECTION,
	MODE_NEMESIS,
	MODE_SURVIVOR,
	MODE_SWARM,
	MODE_MULTI,
	MODE_PLAGUE,
	MODE_SNIPER,
	MODE_ASSASSIN,
	MODE_BOMBARDIER,
	MODE_LNJ
}

/* Winner teams for zp_round_ended() */
enum
{
	WIN_NO_ONE = 0,
	WIN_ZOMBIES,
	WIN_HUMANS
}

/* Restriction types for zp_register_extra_item( ) */
enum
{
	REST_NONE = 0, 		// No restriction
	REST_ROUND, 		// x times per round
	REST_XROUNDS,		// Once in x rounds
	REST_MAP		// x times per map
}

/* Custom forward return values */
#define ZP_PLUGIN_HANDLED 97

/**
 * Returns whether a player is a zombie.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_zombie(id)

/**
 * Returns whether a player is a nemesis.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_nemesis(id)

/**
 * Returns whether a player is a survivor.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_survivor(id)

/**
 * If the user is frozen
 *
 * @param id        Player index.
 */
native zp_get_user_frozen(id)

/**
 * Set if user should be frozen
 *
 * @param id        Player index.
 * @param set        True to set, false for removing it.
 */
native zp_set_user_frozen(id, set)

/**
 * If the user is burning
 *
 * @param id		Player index.
 */
native zp_get_user_burning(id)

/**
 * Set user burning
 *
 * @param id		Player index.
 * @param bool:isburning	True: Set burning | False: Remove burn
 */
native zp_set_user_burning(id, bool:isburning)

/**
 * Returns whether a player is the first zombie.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_first_zombie(id)

/**
 * Returns whether a player is the last zombie.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_last_zombie(id)

/**
 * Returns whether a player is the last human.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_last_human(id)

/**
 * Returns a player's current zombie class ID.
 *
 * @param id		Player index.
 * @return		Internal zombie class ID, or -1 if not yet chosen.
 */
native zp_get_user_zombie_class(id)

/**
 * Returns a player's next zombie class ID (for the next infection).
 *
 * @param id		Player index.
 * @return		Internal zombie class ID, or -1 if not yet chosen.
 */
native zp_get_user_next_class(id)

/**
 * Sets a player's next zombie class ID (for the next infection).
 *
 * @param id		Player index.
 * @param classid	A valid zombie class ID.
 * @return		True on success, false otherwise.
 */
native zp_set_user_zombie_class(id, classid)

/**
 * Returns a player's ammo pack count.
 *
 * @param id		Player index.
 * @return		Number of ammo packs owned.
 */
native zp_get_user_ammo_packs(id)

/**
 * Sets a player's ammo pack count.
 *
 * @param id		Player index.
 * @param amount	New quantity of ammo packs owned.
 */
native zp_set_user_ammo_packs(id, amount)

/**
 * Returns the default maximum health of a zombie.
 *
 * Note: Takes into account first zombie's HP multiplier.
 *
 * @param id		Player index.
 * @return		Maximum amount of health points, or -1 if not a normal zombie.
 */
native zp_get_zombie_maxhealth(id)

/**
 * Returns a player's custom flashlight batteries charge.
 *
 * @param id		Player index.
 * @return		Charge percent (0 to 100).
 */
native zp_get_user_batteries(id)

/**
 * Sets a player's custom flashlight batteries charge.
 *
 * @param id		Player index.
 * @param value		New charge percent (0 to 100).
 */
native zp_set_user_batteries(id, charge)

/**
 * Returns whether a player has night vision.
 *
 * @param id		Player index.
 * @return		True if it has, false otherwise.
 */
native zp_get_user_nightvision(id)

/**
 * Sets whether a player has night vision.
 *
 * @param id		Player index.
 * @param set		True to give, false for removing it.
 */
native zp_set_user_nightvision(id, set)

/**
 * Forces a player to become a zombie.
 *
 * Note: Unavailable for last human/survivor/sniper.
 *
 * @param id		Player index to be infected.
 * @param infector	Player index who infected him (optional).
 * @param silent	If set, there will be no HUD messages or infection sounds.
 * @param rewards	Whether to show DeathMsg and reward frags, hp, and ammo packs to infector.
 * @return		True on success, false otherwise.
 */
native zp_infect_user(id, infector = 0, silent = 0, rewards = 0)

/**
 * Forces a player to become a human.
 *
 * Note: Unavailable for last zombie/nemesis.
 *
 * @param id		Player index to be cured.
 * @param silent	If set, there will be no HUD messages or antidote sounds.
 * @return		True on success, false otherwise.
 */
native zp_disinfect_user(id, silent = 0)

/**
 * Forces a player to become a nemesis.
 *
 * Note: Unavailable for last human/survivor/sniper.
 *
 * @param id		Player index to turn into nemesis.
 * @return		True on success, false otherwise.
 */
native zp_make_user_nemesis(id)

/**
 * Forces a player to become a survivor.
 *
 * Note: Unavailable for last zombie/nemesis.
 *
 * @param id		Player index to turn into survivor.
 * @return		True on success, false otherwise.
 */
native zp_make_user_survivor(id)

/**
 * Respawns a player into a specific team.
 *
 * @param id		Player index to be respawned.
 * @param team		Team to respawn the player into (ZP_TEAM_ZOMBIE or ZP_TEAM_HUMAN).
 * @return		True on success, false otherwise.
 */
native zp_respawn_user(id, team)

/**
 * Forces a player to buy an extra item.
 *
 * @param id		Player index.
 * @param itemid	A valid extra item ID.
 * @param ignorecost	If set, item's cost won't be deduced from player.
 * @param ignorerest	If set, item's restriction will be ignored.
 * @return		True on success, false otherwise.
 */
native zp_force_buy_extra_item(id, itemid, ignorecost = 0, ignorerest = 0)

/**
 * Returns whether a player is a sniper.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_sniper(id)

/**
 * Forces a player to become a sniper.
 *
 * Note: Unavailable for last zombie/nemesis/assassin.
 *
 * @param id		Player index to turn into sniper.
 * @return		True on success, false otherwise.
 */
native zp_make_user_sniper(id)

/**
 * Returns whether a player is an assassin.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_assassin(id)

/**
 * Returns whether a player is a bombardier.
 *
 * @param id		Player index.
 * @return		True if it is, false otherwise.
 */
native zp_get_user_bombardier(id)

/**
 * Forces a player to become a assassin.
 *
 * Note: Unavailable for last human/survivor/sniper.
 *
 * @param id		Player index to turn into assassin.
 * @return		True on success, false otherwise.
 */
native zp_make_user_assassin(id)

/**
 * Forces a player to become a bombardier.
 *
 * Note: Unavailable for last human/survivor/sniper.
 *
 * @param id		Player index to turn into bombardier.
 * @return		True on success, false otherwise.
 */
native zp_make_user_bombardier(id)

/**
 * Overrides ZP player model with a different custom model.
 *
 * Note: This will last until player's next infection/humanization/respawn.
 *
 * Note: Don't call more often than absolutely needed.
 *
 * @param id		Player index.
 * @param newmodel	Model name.
 * @param modelindex	Modelindex (optional).
 */
native zp_override_user_model(id, const newmodel[], modelindex = 0)

/**
 * Returns whether the ZP round has started, i.e. first zombie
 * has been chosen or a game mode has begun.
 *
 * @return		0 - Round not started
 *			1 - Round started
 *			2 - Round starting
 */
native zp_has_round_started()

/**
 * Returns whether the current round is a nemesis round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_nemesis_round()

/**
 * Returns whether the current round is a survivor round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_survivor_round()

/**
 * Returns whether the current round is a swarm round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_swarm_round()

/**
 * Returns whether the current round is a plague round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_plague_round()

/**
 * Returns whether the current round is a Armageddon round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_lnj_round()

/**
 * Returns the last played mode.
 *
 * @return		Last played mode.
 */
native zp_get_last_mode( )

/**
 * Returns the current mode.
 * 
 * @return		Current mode.
 */
native zp_get_current_mode( )

/**
 * Returns the number of consecutive normal rounds played since the last special mode.
 *
 * @return		Number of consecutive normal rounds played since the last special mode.
 */
native zp_consecutive_normal_rounds( )

/**
 * Returns number of alive zombies.
 *
 * @return		Zombie count.
 */
native zp_get_zombie_count()

/**
 * Returns number of alive humans.
 *
 * @return		Human count.
 */
native zp_get_human_count()

/**
 * Returns number of alive nemesis.
 *
 * @return		Nemesis count.
 */
native zp_get_nemesis_count()

/**
 * Returns number of alive survivors.
 *
 * @return		Survivor count.
 */
native zp_get_survivor_count()

/**
 * Returns whether the current round is a sniper round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_sniper_round()

/**
 * Returns whether the current round is a assassin round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_assassin_round()

/**
 * Returns whether the current round is a bombardier round.
 *
 * @return		True if it is, false otherwise.
 */
native zp_is_bombardier_round()

/**
 * Returns number of alive snipers.
 *
 * @return		Sniper count.
 */
native zp_get_sniper_count()

/**
 * Returns number of alive assassins.
 *
 * @return		Assassin count.
 */
native zp_get_assassin_count()

/**
 * Returns number of alive bombardiers.
 *
 * @return		Bombardier count.
 */
native zp_get_bombardier_count()

/**
 * Registers a custom item which will be added to the extra items menu of ZP.
 *
 * Note: The returned extra item ID can be later used to catch item
 * purchase events for the zp_extra_item_selected() forward.
 *
 * Note: ZP_TEAM_NEMESIS, ZP_TEAM_SURVIVOR, ZP_TEAM_ASSASSIN, ZP_TEAM_SNIPER
 * and ZP_TEAM_BOMBARDIER can be used to make an item available to Nemesis,
 * Survivors, Assassins, Snipers and Bombardiers.
 *
 * @param name		Caption to display on the menu.
 * @param cost		Ammo packs to be deducted on purchase.
 * @param teams		Bitsum of teams it should be available for.
 * @param restriction	Type of restriction
 * @param limit		Limit of the restriction
 * @return		An internal extra item ID, or -1 on failure.
 */
native zp_register_extra_item(const name[], cost, teams, restriction = 0, limit = 0)

/**
 * Registers a custom class which will be added to the zombie classes menu of ZP.
 *
 * Note: The returned zombie class ID can be later used to identify
 * the class when calling the zp_get_user_zombie_class() natives.
 *
 * @param name		Caption to display on the menu.
 * @param info		Brief description of the class.
 * @param model		Player model to be used.
 * @param clawmodel	Claws model to be used.
 * @param hp		Initial health points.
 * @param speed		Maximum speed.
 * @param gravity	Gravity multiplier.
 * @param knockback	Knockback multiplier.
 * @return		An internal zombie class ID, or -1 on failure.
 */
native zp_register_zombie_class(const name[], const info[], const model[], const clawmodel[], hp, speed, Float:gravity, Float:knockback)

/**
 * Returns an extra item's ID.
 *
 * @param name		Item name to look for.
 * @return		Internal extra item ID, or -1 if not found.
 */
native zp_get_extra_item_id(const name[])

/**
 * Returns a zombie class' ID.
 *
 * @param name		Class name to look for.
 * @return		Internal zombie class ID, or -1 if not found.
 */
native zp_get_zombie_class_id(const name[])

/**
 * Returns a zombie class' description (passed by reference).
 *
 * @param classid		Internal zombie class ID.
 * @param info			The buffer to store the string in.
 * @param len			Character size of the output buffer.
 * @return			True on success, false otherwise.
 */
native zp_get_zombie_class_info(classid, info[], len)

/**
 * Called when the ZP round starts, i.e. first zombie
 * is chosen or a game mode begins.
 *
 * @param gamemode	Mode which has started.
 * @param id		Affected player's index (if applicable).
 */
forward zp_round_started(gamemode, id)

/**
 * Called when the round ends.
 *
 * @param winteam	Team which has won the round.
 */
forward zp_round_ended(winteam)

/**
 * Called when a player gets infected.
 *
 * @param id		Player index who was infected.
 * @param infector	Player index who infected him (if applicable).
 * @param nemesis	Whether the player was turned into a nemesis.
 */
forward zp_user_infected_pre(id, infector, nemesis)
forward zp_user_infected_post(id, infector, nemesis)

/**
 * Called when a player turns back to human.
 *
 * @param id		Player index who was cured.
 * @param survivor	Whether the player was turned into a survivor.
 */
forward zp_user_humanized_pre(id, survivor)
forward zp_user_humanized_post(id, survivor)
forward zp_user_humanized_pre(id, sniper)
forward zp_user_humanized_post(id, sniper)

/**
 * Called on a player infect/cure attempt. You can use this to block
 * an infection/humanization by returning ZP_PLUGIN_HANDLED in your plugin.
 *
 * Note: Right now this is only available after the ZP round starts, since some
 * situations (like blocking a first zombie's infection) are not yet handled.
 */
forward zp_user_infect_attempt(id, infector, nemesis)
forward zp_user_humanize_attempt(id, survivor)
forward zp_user_humanize_attempt(id, sniper)

/**
 * Called when a player buys an extra item from the ZP menu.
 *
 * Note: You can now return ZP_PLUGIN_HANDLED in your plugin to block
 * the purchase and the player will be automatically refunded.
 *
 * @param id		Player index of purchaser.
 * @param itemid	Internal extra item ID.
 */
forward zp_extra_item_selected(id, itemid)

/**
 * Called when a player gets unfrozen (frostnades).
 *
 * @param id		Player index.
 */
forward zp_user_unfrozen(id)

/**
 * Called when a player becomes the last zombie.
 *
 * Note: This is called for the first zombie too.
 *
 * @param id		Player index.
 */
forward zp_user_last_zombie(id)

/**
 * Called when a player becomes the last human.
 *
 * @param id		Player index.
 */
forward zp_user_last_human(id)

/**
 * Called when a player spawns. This is also called for CZ bots 
 * which are spawning.
 *
 * Note: You should use this, instead of other spawn forwards,
 * for changing a player's class after the player's spawn.
 *
 * @param id		Player index who has spawned
 */
forward zp_player_spawn_post(id, resp_zombie)

/**
 * @deprecated - Do not use!
 * For backwards compatibility only.
 */
#define ZP_TEAM_ANY 0
