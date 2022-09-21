import { Robomodel } from './robomodel';

export const ROBOMODELS: Robomodel[] = [
    { id: 1, name: 'Dog',
  links: [{id: 1, name: "front_body", start_x: 1, start_y: 1, start_z: 1, end_x: 1, end_y: 2, end_z: 1}],
  joints: [{id: 1, name: "front_left_shoulder", axis: "y", x: 1, y: 1, z: 1},
          {id: 2, name: "front_right_shoulder", axis: "y", x: 1, y: 2, z: 1},
          {id: 3, name: "back_left_shoulder", axis: "y", x: 0, y: 1, z: 1},
          {id: 4, name: "back_right_shoulder", axis: "y", x: 0, y: 2, z: 1}]
        }
  ];