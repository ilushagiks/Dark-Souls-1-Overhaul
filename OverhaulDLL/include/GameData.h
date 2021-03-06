/*
    DARK SOULS OVERHAUL

    Contributors to this file:
        Sean Pesce    -  C++
        Metal-Crow    -  C++
        RavagerChris  -  Reverse engineering of game files, gesture cancelling technique
*/

#pragma once

#ifndef _DS1_OVERHAUL_GAME_DATA_H_
    #define _DS1_OVERHAUL_GAME_DATA_H_



#include <stdint.h>

#include "DarkSoulsOverhaulMod.h"
#include "ModData.h"
#include "SP/main.h"
#include "SP/memory.h"
#include "SP/memory/pointer.h"
#include "SP/memory/aob_scan.h"
#include "Asset/Animation/Tae.h"



enum DS1_PLAYER_STATUS_ENUM {
    DS1_PLAYER_STATUS_LOADING = -1,
    DS1_PLAYER_STATUS_HUMAN = 0,
    DS1_PLAYER_STATUS_COOP = 1,
    DS1_PLAYER_STATUS_INVADER = 2,
    DS1_PLAYER_STATUS_HOLLOW = 8
};

enum TAE_type0_param_values {
    cancel_by_atk = 4,
    lock_rotation = 7,
    activate_iframes = 8,
    cancel_by_moving = 11,
    cancel_by_left_atk = 16,
    cancel_by_left_block = 22,
    cancel_by_rolling_or_backstepping = 26,
    cancel_by_using_consumable = 31,
    cancel_by_two_handing = 32,
    allow_animation_cancel_events = 87,
    cap_movement_to_walk_speed = 90,
    disable_sprinting = 91,
    stop_all_movement = 89,
};

enum AnimationStateTypesEnum {
    Invalid = 31,
    Lower_Action = 24,
    Lower_Attack = 18,
    Lower_Damage_L = 26,
    Lower_Damage_S = 19,
    Lower_Event = 25,
    Lower_Event_HiPrio = 30,
    Lower_ExtraAnim = 27,
    Lower_Guard = 17,
    Lower_SpWait = 16,
    Lower_SpecialAttack = 23,
    Lower_TaeExtraAnim = 28,
    Lower_ThrowAnim = 29,
    Lower_Turn = 22,
    Lower_Wait = 15,
    Lower_WalkFB = 21,
    Lower_WalkLR = 20,
    None = 14,
    Upper_Action = 8,
    Upper_Attack = 6,
    Upper_Damage_L = 11,
    Upper_Damage_S = 9,
    Upper_Event = 10,
    Upper_Event_HiPrio = 13,
    Upper_Guard = 5,
    Upper_SpWait = 1,
    Upper_SpecialAttack = 7,
    Upper_ThrowAnim = 12,
    Upper_Turn = 4,
    Upper_Wait = 0,
    Upper_WalkFB = 3,
    Upper_WalkLR = 2
};

class Game
{
public:

    ////////////////////////////////////////
    ////////////// GAME DATA ///////////////
    ////////////////////////////////////////

    // Base address of Dark Souls game process
    static uint64_t ds1_base;

    // Base address of fmod_event64 dll process
    static uint64_t fmod_event64_base;

    // Base address for player character data
    static uint64_t player_char_base;

    // Base address for world character data
    static const uint64_t world_char_base = 0x141d151b0;

    // Base address for world character data
    static uint64_t char_class_base;

    static uint64_t frpg_net_base;

    static uint64_t game_data_man;

    static uint64_t world_chr_man_imp;

    static const uint64_t player_animation_mediator_loading = 0x3790E2;

    static const uint64_t calculate_attack_damage_offset = 0x2a8ead6;

    static uint64_t player_animation_mediator;

    // Player character status (loading, human, co-op, invader, hollow)
    static sp::mem::pointer<int32_t> player_char_status;

    // Marker for if we're currently in a loading screen
    static sp::mem::pointer<int32_t> is_loading;

    // Flag to determine if any characters have been loaded since the game was launched (useful if player had a character loaded but returned to main menu)
    static bool characters_loaded;

    // Address of lava brightness effect (used for dimming lava)
    static uint8_t *lava_luminosity;

    // Game saving on/off
    static sp::mem::pointer<uint8_t> saves_enabled;

    // Multiplayer node count
    static int node_count;

    //Const handle for the PC
    static const uint32_t PC_Handle = 0x10044000;

    /////////////////////////////////////////
    /////////////// FUNCTIONS ///////////////
    /////////////////////////////////////////

    // Initializes pointers and base addresses required for most other functions
    static void init();

    // Runs tasks that were deferred until a character was loaded
    static void on_first_character_loaded();

    // Performs tasks that must be rerun after any loading screen
    static void on_reloaded();

    // Check if dim lava mod is currently active
    static bool dim_lava_enabled();

    // Dim lava effects or restore default lava visuals
    static void enable_dim_lava(bool dim);

    // Returns multiplayer node count as an int (or -1 if player is not online)
    static int get_node_count();

    // Enables/Disables automatic game disconnection when low framerate is detected
    static void disable_low_fps_disconnect(bool enable);

    // Set the current animation speed for the player character
    static void set_current_player_animation_speed(float speed);

    // Returns current player character body animation ID (attacking, rolling, gestures, etc)
    static int32_t get_player_body_anim_id();

    static int32_t get_player_upper_body_anim_id();

    static int32_t get_player_lower_body_anim_id();

    static int32_t get_animation_mediator_state_animation(void* animationMediator, AnimationStateTypesEnum state_id);

    static void set_animation_mediator_state_entry(void* animationMediator, AnimationStateTypesEnum state_id, int32_t new_aid, float new_progressTime);

    // Return pointer to current game time in milliseconds since the game has started
    static uint32_t* get_game_time_ms();

	static uint64_t get_pc_entity_pointer();

	static float * get_pc_position();


                    /////////////////////////////////////////
                    //////////////// PATCHES ////////////////
                    /////////////////////////////////////////

    // Set available pool of memory that Dark Souls allocates for itself
    static void set_memory_limit();

    // Allow effect IDs to be transferred between clients without bounds restrictions
    static void unrestrict_network_synced_effectids();

    static float new_hpbar_max;

    // Fix the bug where the player HP could be greater than the displayed GUI bar
    static void increase_gui_hpbar_max();

    // Gets currently equipped L hand weapon
	static uint32_t left_hand_weapon();

    // Gets currently equipped R hand weapon
    static uint32_t right_hand_weapon();

	static int32_t get_player_char_status();

	static uint32_t get_player_char_max_hp();

	static float get_entity_rotation(void * entity_ptr);

	static int32_t get_area_id();

    static int32_t* get_mp_id_ptr();

    static int32_t* get_saved_chars_menu_flag();

    static uint8_t* get_saved_chars_preview_data();

    static uint32_t get_pc_playernum();

    static uint64_t get_connected_player(uint32_t i);

    static int32_t convert_handle_to_playernum(uint32_t handle);

    static uint32_t convert_playernum_to_handle(uint32_t playernum);

    static uint32_t get_last_attack_weapon_id();

	static void* get_pc_EzStateMachineImpl();

	static uint64_t get_EzStateMachineImpl_curstate_id(void * EzStateMachineImpl);

    /*
     * Help speedup some functions by, whenever we're loaded into an area,
     * preload/preresolve some pointers and values so they can be much more quickly read when we need them
     * This function should be called whenever an area is loaded (after player status changes from loading)
    */
	static void preload_function_caches();

    // Two-part patch to increase the multiplayer phantom limit:
    static void increase_phantom_limit1(); // Called from on_process_attach()
    static void increase_phantom_limit2(); // Called from initialize_plugin()




                    /////////////////////////////////////////
                    ////////////// HUD-RELATED //////////////
                    /////////////////////////////////////////

    class Hud {
    public:

        // Additional HUD elements
        static bool get_show_compass_radial();
        static void set_show_compass_radial(bool enable);
        static bool get_show_compass_bar();
        static void set_show_compass_bar(bool enable);
        static bool get_show_elevation_meter();
        static void set_show_elevation_meter(bool enable);
        static bool get_show_node_graph();
        static void set_show_node_graph(bool enable, bool game_flag_only = true);
    };



                    /////////////////////////////////////////
                    ////////////// FILE-RELATED /////////////
                    /////////////////////////////////////////
};
typedef Game::Hud Hud;



#endif // _DS1_OVERHAUL_GAME_DATA_H_
