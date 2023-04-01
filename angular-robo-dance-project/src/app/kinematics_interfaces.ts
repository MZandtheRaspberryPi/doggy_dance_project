import { Coordinate } from "./coordinate";
import { JointId } from "./joint";


export interface ForwardKinematics {
    body_x_meters: number,
    body_y_meters: number,
    body_z_meters: number,
    body_roll_rad: number,
    body_pitch_rad: number,
    body_yaw_rad: number,
    joints: JointId[]
}

export interface EndEffectorTrimmed {
    id: number,
    location_shoulder: Coordinate
}

export interface InverseKinematics {
    body_x_meters: number,
    body_y_meters: number,
    body_z_meters: number,
    body_roll_rad: number,
    body_pitch_rad: number,
    body_yaw_rad: number,
    end_effectors: EndEffectorTrimmed[]
}