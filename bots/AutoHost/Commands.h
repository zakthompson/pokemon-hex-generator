#include "../Joystick.h"
#include <avr/pgmspace.h>

static const Command m_command[] PROGMEM = {
	//----------Setup [0,2]----------
	// Press B once to connect
	{NOTHING, 30},
	{B, 1},
	{NOTHING, 1},

	//----------Connect internet and talk to den [3,14]----------
	{Y, 50},
	{PLUS, 9999},		// OVERWRITTEN, refer to m_internetTime in Config.h
	{B, 1},
	{NOTHING, 6},
	{B, 1},
	{NOTHING, 240},		// Allow time to load other players

	{A, 20},			// Interact with den
	{NOTHING, 1},
	{A, 6},				// (Optional) There's energy pouring out from the den!
	{NOTHING, 1},
	{A, 30},			// (Optional) You gained 2,000W!
	{NOTHING, 200},		// Communicating... standing by

	//----------Start raid [15,26]----------
	{A, 2660},			// (2660 ~= until 2 min)
	{NOTHING, 1},
	{A, 5200},			// (5200 ~= until 1 min)
	{NOTHING, 1},

	{UP, 1},
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 30},
	{A, 50},
	{NOTHING, 1},

	// This A will be repeated 40 times
	{A, 1},
	{NOTHING, 19},	// Wait until raid starts (between standing up to show abilities)

	//----------Set Link Code [27,56]----------
	// Init
	{PLUS, 40},
	{NOTHING, 1},

	// Reset to 0
	{DOWN, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},
	{DOWN, 1},
	{NOTHING, 1},

	// Press A
	{A, 1},
	{NOTHING, 1},

	// 1,4,7,2,5,8 [37-44]
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{LEFT, 1},
	{NOTHING, 1},

	// 3,6,9 [45-52]
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{UP, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},

	// Confirm link code
	{PLUS, 51},
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 30},

	//----------Soft-reset [57,68]----------
	{HOME, 1},
	{NOTHING, 40},
	{X, 1},			// Close game
	{NOTHING, 8},
	{A, 1},			// Comfirm close game
	{NOTHING, 120},
	{A, 1},			// Choose game
	{NOTHING, 50},
	{A, 1},			// Pick User
	{NOTHING, 800},
	{A, 1},			// Enter game
	{NOTHING, 460},

	//----------Unsafe invite local friend [69,92]----------
	{HOME, 1},
	{NOTHING, 40},
	{UP, 1},
	{NOTHING, 1},
	{A, 1},				// To profile
	{NOTHING, 1},
	{DOWN, 90},			// Scroll to bottom
	{NOTHING, 1},
	{UP, 1},			// Add friend
	{NOTHING, 8},
	{A, 1},
	{NOTHING, 1},
	{DOWN, 1},			// Search for local friend
	{NOTHING, 1},
	{A, 1},
	{NOTHING, 20},
	{A, 1},				// DC
	{NOTHING, 90},

	// Back to game
	{HOME, 1},
	{NOTHING, 30},
	{HOME, 1},
	{NOTHING, 60},
	{A, 1},				// Error message
	{NOTHING, 900},		// Wait until exit raid

	// COPY FROM Auto3DaySkipper
	//----------Sync and unsync time, goto change date [93,124][93,127]----------
	// To System Settings
	{HOME, 1},
	{NOTHING, 30},
	{DOWN, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{RRIGHT, 1},
	{RIGHT, 1},
	{RRIGHT, 1},
	{A, 40},

	// To Date and Time
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{A, 8},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{RDOWN, 1},
	{DOWN, 1},
	{A, 1},
	{NOTHING, 8},

	// Sync and unsync time
	{A, 1},
	{NOTHING, 4},
	{A, 1},
	{NOTHING, 8},

	//----------Plus 1 year [125,148][125,138][128][139]----------
	// To actually Date and Time
	{DOWN, 1},
	{RDOWN, 1},
	{A, 1},
	{NOTHING, 7},

	// Plus 1 year
	{RIGHT_A, 1},		// EU/US start
	{NOTHING, 1},
	{UP_A, 1},		// JP start
	{RRIGHT, 1},
  {RIGHT_A, 1},
  {RRIGHT, 1},
	{A, 1},
	{NOTHING, 4},

	//----------Back to game [149,152][139,142][140,143]----------
	{HOME, 1},
	{NOTHING, 30},
	{HOME, 1},
	{NOTHING, 30},

	//----------Quit the raid [153,156][143,146][144,147]----------
	{B, 32},
	{NOTHING, 1},
	{A, 200},		// WAITING on local communication
	{NOTHING, 1},

	//----------Collect Watts [157,164][147,154][148,155]----------
	{A, 20},		// Talk
	{NOTHING, 1},
	{A, 6},			// There's energy pouring out from the den!
	{NOTHING, 1},
	{A, 30},		// You gained 2,000W!
	{NOTHING, 1},
	{A, 120},		// WAITING on local communication
	{NOTHING, 1},

	//----------Goto profile [165,194][155,184][156,185]----------
	{A, 400},			// Start raid, wait 4-5 seconds
	{NOTHING, 1},
	{HOME, 1},
	{NOTHING, 40},
	{UP, 1},
	{NOTHING, 1},

	// 10 profiles maximum [171,188][161,178][162,179]
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},
	{RIGHT, 1},
	{NOTHING, 1},

	{A, 1},				// To profile
	{NOTHING, 1},
	{DOWN, 90},			// Scroll to bottom
	{NOTHING, 1},
	{UP, 1},			// Add friend
	{NOTHING, 8},

	//----------A Spam [195,196][185,186][186,187]----------
	{A, 1},
	{NOTHING, 9},

	//----------Back to game [197,200][187,190][188,191]----------
	{HOME, 1},
	{NOTHING, 30},
	{HOME, 1},
	{NOTHING, 50},
};
