import { Coordinate } from './coordinate';

export interface Joint {
  id: number;
  name: string;
  axis: string;
  location: Coordinate;
}