import { Robomodel } from './robomodel';
import { XYZ } from './xyz';

const L1: number = 0.25;
const L2: number = 0.20;
const L3: number = 0.80;
const L4: number = 0.80;

const BODYLENGTH: number = 1.20;
const BODYWIDTH: number = 0.9;

const STARTING_XYZ: XYZ = { x: 1, y: 1, z: 1 };

function shiftPositive(xs: number[], shift_x: number): number[] {
  let xs_return: Array<number> = Array(xs.length);
  for (let i = 0; i < xs.length; i++) {
    xs_return[i] = xs[i] + shift_x;
  }
  return xs_return;
}

function shiftNegative(xs: number[], shift_x: number): number[] {
  let xs_return: Array<number> = Array(xs.length);
  for (let i = 0; i < xs.length; i++) {
    xs_return[i] = xs[i] - shift_x;
  }
  return xs_return;
}

export const ROBOMODELS: Robomodel[] = [
  {
    id: 1, name: 'Dog',
    links: [{
      id: 1, name: "front_body", start_x: STARTING_XYZ.x + BODYLENGTH / 2,
      start_y: STARTING_XYZ.y + BODYWIDTH / 2, start_z: STARTING_XYZ.z,
      end_x: STARTING_XYZ.x + BODYLENGTH / 2, end_y: STARTING_XYZ.y - BODYWIDTH / 2, end_z: STARTING_XYZ.z
    },
    {
      id: 2, name: "right_body", start_x: STARTING_XYZ.x + BODYLENGTH / 2,
      start_y: STARTING_XYZ.y - BODYWIDTH / 2, start_z: STARTING_XYZ.z,
      end_x: STARTING_XYZ.x - BODYLENGTH / 2, end_y: STARTING_XYZ.y - BODYWIDTH / 2, end_z: STARTING_XYZ.z
    },
    {
      id: 3, name: "back_body", start_x: STARTING_XYZ.x - BODYLENGTH / 2,
      start_y: STARTING_XYZ.y - BODYWIDTH / 2, start_z: STARTING_XYZ.z,
      end_x: STARTING_XYZ.x - BODYLENGTH / 2, end_y: STARTING_XYZ.y + BODYWIDTH / 2, end_z: STARTING_XYZ.z
    },
    {
      id: 4, name: "left_body", start_x: STARTING_XYZ.x - BODYLENGTH / 2,
      start_y: STARTING_XYZ.y + BODYWIDTH / 2, start_z: STARTING_XYZ.z,
      end_x: STARTING_XYZ.x + BODYLENGTH / 2, end_y: STARTING_XYZ.y + BODYWIDTH / 2, end_z: STARTING_XYZ.z
    }],
    joints: [{
      id: 1, name: "front_left_shoulder", axis: "y", x: STARTING_XYZ.x + BODYLENGTH / 2,
      y: STARTING_XYZ.y - BODYWIDTH / 2, z: STARTING_XYZ.z
    },
    {
      id: 2, name: "front_right_shoulder", axis: "y", x: STARTING_XYZ.x + BODYLENGTH / 2,
      y: STARTING_XYZ.y + BODYWIDTH / 2, z: STARTING_XYZ.z
    },
    {
      id: 3, name: "back_left_shoulder", axis: "y", x: STARTING_XYZ.x - BODYLENGTH / 2,
      y: STARTING_XYZ.y - BODYWIDTH / 2, z: STARTING_XYZ.z
    },
    {
      id: 4, name: "back_right_shoulder", axis: "y", x: STARTING_XYZ.x - BODYLENGTH / 2,
      y: STARTING_XYZ.y + BODYWIDTH / 2, z: STARTING_XYZ.z
    }]
  },
  {
    id: 2, name: 'HandWave',
    links: [{ id: 1, name: "upper_arm", start_x: 0, start_y: 0.0, start_z: 0, end_x: 0.1, end_y: 0.0, end_z: 1 },
    { id: 2, name: "lower_arm", start_x: 0.1, start_y: 0.0, start_z: 1, end_x: 0.2, end_y: 0.0, end_z: 1.6 },
    { id: 3, name: "hand", start_x: 0.2, start_y: 0.0, start_z: 1.6, end_x: 0.3, end_y: 0.0, end_z: 2.0 }],
    joints: [{ id: 1, name: "shoulder", axis: "x", x: 0, y: 0, z: 0 },
    { id: 2, name: "elbow", axis: "x", x: 0.1, y: 0, z: 1 },
    { id: 3, name: "wrist", axis: "x", x: 0.2, y: 0, z: 1.6 }]
  }
];