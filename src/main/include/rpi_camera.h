#pragma once

#include "Layer.h"
#include <stdint.h>

#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"

namespace InputDev {
    class rpi_camera {
        private:
            Layer* m_layer;
            nt::NetworkTableInstance m_table;            

        public:

            rpi_camera(Layer *layer);
            ~rpi_camera();

            void OutputIntoLayer();

    };
}