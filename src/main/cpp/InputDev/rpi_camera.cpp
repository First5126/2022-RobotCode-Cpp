#include "rpi_camera.h"

#include <iostream>

using namespace InputDev;

rpi_camera::rpi_camera(Layer *layer) {
    m_layer = layer;

    m_table = nt::NetworkTableInstance::GetDefault();

    assert(m_layer != NULL);

    std::cout << "[INPUTDEV]: RPI_CAMERA NETWORK INIT" << std::endl;
}

rpi_camera::~rpi_camera() { }

void rpi_camera::OutputIntoLayer() {
    double latency = m_table.GetEntry("/photonvision/Microsoft_LifeCam_HD-3000/latencyMillis").GetDouble(0);
    
    m_layer->pi_yaw = m_table.GetEntry("/photonvision/Microsoft_LifeCam_HD-3000/targetYaw").GetDouble(0);
    m_layer->pi_pitch = m_table.GetEntry("/photonvision/Microsoft_LifeCam_HD-3000/targetPitch").GetDouble(0);
    m_layer->pi_mode = (int)m_table.GetEntry("/photonvision/Microsoft_LifeCam_HD-3000/pipelineIndex").GetDouble(0);
    m_layer->pi_active = latency > 0;
    m_layer->pi_driver_mode = m_layer->pi_mode == -1;

}
