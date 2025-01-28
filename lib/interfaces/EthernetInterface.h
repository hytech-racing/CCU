/* Template message
{
    std::array<std::array<std::optional<volt>, 12>, num_chips> voltages;
    std::array<celcius, 4 * num_chips> cell_temperatures;
    std::array<float, num_humidity_sensors> humidity;
    std::array<float, num_board_thermistors> board_temperatures;
    float min_voltage;
    float max_voltage;
    size_t min_voltage_cell_id;              // 0 - 125
    size_t max_voltage_cell_id;              // 0 - 125
    size_t max_board_temperature_segment_id; // 0 - 5
    size_t max_humidity_segment_id;          // 0 - 5
    size_t max_cell_temperature_cell_id;     // 0 - 47
    float total_voltage;
    float average_cell_temperature;
};
*/
struct EthernetInterface
{
    float maxCellTemp = 70; //in degress C
    float maxCellV = 2.3; //in Volts
};
