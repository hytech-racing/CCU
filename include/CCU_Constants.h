#ifndef CCU_CONSTANTS
#define CCU_CONSTANTS

/* External Dependencies */
#include <stddef.h>


namespace CCUSystems
{

}

namespace CCUInterfaces
{
    /* Interface Constants */
    const size_t ANALOG_READ_RESOLUTION = 12;
    const size_t SERIAL_BAUDRATE = 115200;


    /* ACU Interface Constants */


    /* ADC Interface Constants */
    constexpr const size_t SHDN_A_PIN = 9;
    constexpr const size_t SHDN_B_PIN = 8;
    constexpr const size_t SHDN_C_PIN = 7;
    constexpr const size_t SHDN_D_PIN = 6;
    constexpr const size_t SHDN_E_PIN = 5;
    constexpr const size_t SHDN_F_PIN = 4;
    constexpr const size_t SHDN_G_PIN = 3;

    constexpr const size_t SCALED_24V_PIN = 33;
    constexpr const size_t CONTROL_PILOT_PIN = 27;
    constexpr const size_t PROXIMITY_PILOT_PIN = 15;
    constexpr const size_t TEENSY_240_ENABLED_PIN = 29;
    constexpr const size_t TEENSY_240_OK_PIN = 36;
    constexpr const size_t JUMPER_OUT_PIN = 26;

    constexpr const float GLV_CONV_FACTOR = 0.106699751861F; // 4.3K / (4.3K + 36K)
    constexpr const float CONTROL_PILOT_CONV_FACTOR = 0.358695652174; // 3.3K / (3.3K + 5.9K)
    constexpr const float PROXIMITY_PILOT_CONV_FACTOR = 0.62962962963F; // 5.1K / (5.1K + 3K)
    constexpr const float JUMPER_OUT_CONV_FACTOR = 0.106699751861F; // 4.3K / (4.3K + 36K)


    /* Display Interface Constants */
    constexpr const size_t LCD_CS_PIN = 39;
    constexpr const size_t LCD_SCK_PIN = 13;
    constexpr const size_t LCD_MISO_PIN = 12;
    constexpr const size_t LCD_MOSI_PIN = 11;
    constexpr const size_t LCD_RESET_PIN = 40;
    constexpr const size_t LCD_DC_PIN = 41;


    /* Level2 Interface Constants */
    constexpr const size_t CONTROL_PWM_SENSE_PIN = 10;
    constexpr const size_t START_CHARGE_PIN = 32;


    /* Watchdog Interface Constants */
    constexpr const size_t SOFTWARE_NOT_OK_PIN = 34; // Watchdog's !RESET pin
    constexpr const size_t WATCHDOG_KICK_PIN = 35;
    constexpr const unsigned long WATCHDOG_KICK_INTERVAL_MS = 10UL; // why define this here and in the interface itslef isnt that useless?

}
namespace CCUConstants
{
    /* General Information */
    constexpr const float MIN_PACK_VOLTAGE = 403; // need to double check this number
    constexpr const float MAX_PACK_VOLTAGE = 530;
    constexpr const float MAX_ALLOWABLE_CELL_TEMP = 40; // need data for this
    constexpr const float CUTOFF_VOLTAGE = 4.2; // max voltage that cells can be at - if high = this, stop charging
    constexpr const float CHARGER_CURRENT_MAX = 120; // 120 = 3.4 amps
    constexpr const float SAFE_CHARGING_CURRENT = 15;

    /* Task Times */
    constexpr unsigned long KICK_WATCHDOG_PERIOD = 1000; // 1 000 us = 1kHz
    constexpr unsigned long KICK_WATCHDOG_PRIORITY = 1;

    constexpr unsigned long LEVEL2_ENABLED_SAMPLE_PERIOD = 90000; // 90 000 us = 11.11 hz
    constexpr unsigned long LEVEL2_ENABLED_PRIORITY = 10;

    constexpr unsigned long TICK_STATE_MACHINE_PERIOD = 2000; // 2 000 us = 500 Hz
    constexpr unsigned long TICK_STATE_MACHINE_PRIORITY = 12;

    constexpr unsigned long SAMPLE_CAN_DATA_PRIORITY = 3; //0?
    constexpr unsigned long SAMPLE_CAN_DATA_PERIOD = 2000; // 2 000 us = 500 Hz

    constexpr unsigned long ENQUEUE_ACU_CAN_DATA_PRIORITY = 4;
    constexpr unsigned long ENQUEUE_ACU_CAN_DATA_PERIOD = 4000; // 4 000 us = 250 Hz

    constexpr unsigned long ENQUEUE_CHARGER_CAN_DATA_PRIORITY = 5;
    constexpr unsigned long ENQUEUE_CHARGER_CAN_DATA_PERIOD = 4000; // 4 000 us = 250 Hz

    constexpr unsigned long DIAL_PERIOD_US = 20000; // 20 000 us = 50 Hz
    constexpr unsigned long ETHERNET_PERIOD_US = 20000; // 20 000 us = 50 Hz

    constexpr unsigned long UPDATE_DISPLAY_PRIORITY = 11;
    constexpr unsigned long UPDATE_DISPLAY_PERIOD = 100000;

    constexpr unsigned long REFRESH_DISPLAY_PRIORITY = 13;
    constexpr unsigned long READ_DIAL_PRIORITY = 10;
    constexpr unsigned long SEND_ETHERNET_PRIORITY = 8;
    constexpr unsigned long RECIEVE_ETHERNET_PRIORITY = 7;

    constexpr unsigned long SEND_ALL_DATA_PRIORITY = 6;
    constexpr unsigned long SEND_ALL_DATA_PERIOD = 4000; // 4 000 us = 250 Hz

    constexpr unsigned long HT_SCHED_CAN_PERIOD = 100000;

    /* CAN Constants */
    const uint32_t CAN_BAUDRATE = 1000000; //CAN for ACU
    const uint32_t CHARGER_CAN_BAUDRATE = 500000; //CAN for charger
};


#endif