#pragma once


#include <frc/trajectory/constraint/DifferentialDriveKinematicsConstraint.h>
#include "pathplanner/lib/PathPlanner.h"
#include <units/acceleration.h>
#include <units/angle.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/area.h>
#include <units/capacitance.h>
#include <units/charge.h>
#include <units/concentration.h>
#include <units/conductance.h>
#include <units/current.h>
#include <units/curvature.h>
#include <units/data.h>
#include <units/data_transfer_rate.h>
#include <units/density.h>
#include <units/dimensionless.h>
#include <units/energy.h>
#include <units/force.h>
#include <units/frequency.h>
#include <units/illuminance.h>
#include <units/impedance.h>
#include <units/inductance.h>
#include <units/length.h>
#include <units/luminous_flux.h>
#include <units/luminous_intensity.h>
#include <units/magnetic_field_strength.h>
#include <units/magnetic_flux.h>
#include <units/mass.h>
#include <units/moment_of_inertia.h>
#include <units/power.h>
#include <units/pressure.h>
#include <units/radiation.h>
#include <units/solid_angle.h>
#include <units/substance.h>
#include <units/temperature.h>
#include <units/time.h>
#include <units/torque.h>
#include <units/velocity.h>
#include <units/voltage.h>
#include <units/volume.h>

namespace Const {
    // values found from the tool
    constexpr auto ks = 0.22_V;
    constexpr auto kv = 1.98 * 1_V * 1_s / 1_m;
    constexpr auto ka = 0.2 * 1_V * 1_s * 1_s / 1_m;

    constexpr double kPDriveVel = 8.5;

    constexpr auto kTrackwidth = 0.69_m;
    extern const frc::DifferentialDriveKinematics kDriveKinematics;

    constexpr auto kMaxSpeed = 3_mps;
    constexpr auto kMaxAcceleration = 3_mps_sq;

    constexpr double kRamseteB = 2;
    constexpr double kRamseteZeta = 0.7;

}
    