#include "color_sensor.h"

using namespace InputDev;

ColorSensor::ColorSensor(Layer *layer) {
    m_layer = layer;
    //m_sensor = rev::ColorSensorV3(frc::I2C::Port::kOnboard);

    assert(m_layer != NULL);
}

ColorSensor::~ColorSensor() {
}

void ColorSensor::OutputIntoLayer() {
    m_layer->cs_r = m_sensor.GetColor().red;
    m_layer->cs_g = m_sensor.GetColor().green;
    m_layer->cs_b = m_sensor.GetColor().blue;
}