#ifndef CCU_CONSTANTS
#define CCU_CONSTANTS

/* Watchdog constants */
constexpr int WATCHDOG_PIN = 35;
constexpr int SOFTWARE_OK_PIN = 34; // Watchdog's !RESET pin
constexpr unsigned long WATCHDOG_KICK_INTERVAL_MS = 10UL;

#endif