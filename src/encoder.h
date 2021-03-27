#ifndef ENCODER_H
#define ENCODER_H

#include <string>

struct message
{
    float dust;
    float turbidity;
    float temperature;
    struct
    {
        float humidity;
        float pressure;
        float temperature;
    } meteo_station;
};

std::string to_json(const message& data);

#endif
