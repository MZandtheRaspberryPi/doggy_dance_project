import { Coordinate } from './coordinate';

enum JointType {
  FIXED,
  ROTATING,
  PRISMATIC
}

export interface Joint {
  id: number;
  name: string;
  axis: string;
  location: Coordinate;
  joint_type: JointType;
  min: number;
  max: number;
}