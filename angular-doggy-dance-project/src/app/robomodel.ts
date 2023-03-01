import { Link } from './link';
import { Joint } from './joint';

export interface Robomodel {
  id: number;
  name: string;
  links: Link[];
  joints: Joint[];
  end_effectors: Joint[];
}