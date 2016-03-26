/*
	----------------------
	-*- Licensing Info -*-
	----------------------

	[ZPS] Bot Support
	Copyright (C) abdul-rehman

	This is an edited version by ROKronoS

	Website: http://zpshade.esy.es/
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
	In addition, as a special exception, the author gives permission to
	link the code of this program with the Half-Life Game Engine ("HL
	Engine") and Modified Game Libraries ("MODs") developed by Valve,
	L.L.C ("Valve"). You must obey the GNU General Public License in all
	respects for all of the code used other than the HL Engine and MODs
	from Valve. If you modify this file, you may extend this exception
	to your version of the file, but you are not obligated to do so. If
	you do not wish to do so, delete this exception statement from your
	version.

	---------------
	-*- Credits -*-
	---------------

	* MeRcyLeZZ: for developing Zombie Plague
	* abdul-rehman: for developing the plugin
	* Sn!ff3R: for providing a useful forward to detect whether the bot is aiming at a player or not
	* Bugsy: for helping me with forcing the bots to press the attack button

	----------------------
	-*-   Changelog    -*
	----------------------

	* v1.0 - 17.09.2015
	- Initial release
	- Added support for bombardiers

*/

#include < amxmodx >
#include < hamsandwich >
#include < zombieplague >

// Offsets
new const OFFSET_ACTIVE_ITEM = 373;
new const OFFSET_LINUX = 5;

// CVAR's
new cvar_throw_chance

public plugin_init( )
{
	register_plugin( "[ZPS] Bot Support", "1.0", "WiLS, abdul-rehman & ROKronoS" );
	
	register_event( "StatusValue", "Event_Nade_Throw", "be", "1=2", "2!0" );
	
	cvar_throw_chance = register_cvar( "zp_nade_throw_chance", "1" );
}

// Thanks to Sn!ff3R
public Event_Nade_Throw( index )
{
	// Get the index of the player at which the bot is aiming
	new pindex = read_data( 2 );

	if ( is_user_bot( index ) && is_user_alive( index ) && is_user_alive( pindex ) )
	{
		// Support for bots - Humans
		if ( !zp_get_user_zombie( index ) && zp_get_user_zombie( pindex ) )
		{
			if ( !get_pcvar_num( cvar_throw_chance ) )
			{
				switch ( random_num( 0, 3 ) )
				{
					case 0:
					{
						// Throw flare
						Func_Throw_Flare( index );
					}
					case 1:
					{
						// Throw napalm nade
						Func_Throw_NapalmInfect( index );
					}
					case 2:
					{
						// Throw frost nade
						Func_Throw_Frost( index );
					}
					case 3:
					{
						// Throw frost nade
						Func_Throw_Frost( index );

						// Throw napalm nade after a time
						set_task( 0.8, "Func_Throw_NapalmInfect", index );
					}
				}
			}
			else
			{
				new cvar_value = get_pcvar_num( cvar_throw_chance );
				new chance = random_num( 0, cvar_value + 3);

				if ( chance == cvar_value )
				{
					// Throw flare
					Func_Throw_Flare( index )
				}
				else if ( chance == cvar_value + 1 )
				{
					// Throw napalm nade
					Func_Throw_NapalmInfect( index );
				}
				else if ( chance == cvar_value + 2 )
				{
					// Throw frost nade
					Func_Throw_Frost( index );
				}
				else if ( chance == cvar_value + 3 )
				{
					// Throw frost nade
					Func_Throw_Frost( index );

					// Throw napalm nade after a time
					set_task( 0.8, "Func_Throw_NapalmInfect", index );
				}
				else
					return;
			}
		}
		// Support for bots - Bombardier
		else if ( zp_get_user_bombardier( index ) && !zp_get_user_zombie( pindex ) )
		{
			Func_Throw_NapalmInfect( index );
		}
	}
}

public Func_Throw_NapalmInfect( index )
{
	// Check whether the bot has napalm/infection nade
	if ( user_has_weapon( index, CSW_HEGRENADE ) )
	{
		// Switch to nade
		engclient_cmd( index, "weapon_hegrenade" );
		
		// Forced throw [Thanks to Bugsy]
		ExecuteHam( Ham_Weapon_PrimaryAttack, get_pdata_cbase( index, OFFSET_ACTIVE_ITEM, OFFSET_LINUX ) );
	}
}

public Func_Throw_Frost( index )
{
	// Check whether the bot has frost nade
	if ( user_has_weapon( index, CSW_FLASHBANG ) )
	{
		// Switch to nade
		engclient_cmd( index, "weapon_flashbang" );
		
		// Forced throw [Thanks to Bugsy]
		ExecuteHam( Ham_Weapon_PrimaryAttack, get_pdata_cbase( index, OFFSET_ACTIVE_ITEM, OFFSET_LINUX ) );
	}
}

public Func_Throw_Flare( index )
{
	// Check whether the user haves Frost Nade
	if ( user_has_weapon( index, CSW_SMOKEGRENADE ) )
	{
		// Switch to nade
		engclient_cmd( index, "weapon_smokegrenade" );
		
		// Forced throw [Thanks to Bugsy]
		ExecuteHam( Ham_Weapon_PrimaryAttack, get_pdata_cbase( index, OFFSET_ACTIVE_ITEM, OFFSET_LINUX ) );
	}
}