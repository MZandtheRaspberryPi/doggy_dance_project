import { Coordinate } from './coordinate';

enum JointType {
  FIXED,
  ROTATING,
  PRISMATIC
}

export interface Joint {
  number: number;
  name: string;
  axis: string;
  location: Coordinate;
  joint_type: JointType;
  current_angle_radians: number;
  min_angle_radians: number;
  max_angle_radians: number;
}

export interface JointId {
  number: number;
  current_angle_radians: number;
}

export interface EndEffector {
  number: number,
  name: string,
  location_global: Coordinate,
  location_shoulder: Coordinate,
  min_x: number,
  min_y: number,
  min_z: number,
  max_x: number,
  max_y: number,
  max_z: number
};
