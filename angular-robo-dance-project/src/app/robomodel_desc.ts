export interface RobomodelDesc {
  id: number;
  name: string;
  num_links: number;
  num_joints: number;
}

export interface RobomodelDescList {
  descriptions: RobomodelDesc[];
}