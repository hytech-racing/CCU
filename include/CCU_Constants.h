#ifndef CCU_CONSTANTS
#define CCU_CONSTANTS

/* Watchdog constants */
constexpr int WATCHDOG_PIN = 26;
constexpr int SOFTWARE_OK_PIN = 27; // Watchdog's !RESET pin
constexpr unsigned long WATCHDOG_KICK_INTERVAL_MS = 10UL;
constexpr unsigned long VCF_PEDALS_MAX_HEARTBEAT_MS = 50UL;         // 20ms at 60mph is about 0.5 meters

#endif