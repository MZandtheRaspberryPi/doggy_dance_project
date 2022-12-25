import { Coordinate } from './coordinate';

export interface Link {
  id: number;
  name: string;
  start_location: Coordinate;
  end_location: Coordinate;
}