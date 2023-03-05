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