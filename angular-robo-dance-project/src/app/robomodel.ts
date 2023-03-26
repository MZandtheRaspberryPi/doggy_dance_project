import { Link } from './link';
import { Joint, EndEffector } from './joint';

export interface Robomodel {
  id: number;
  name: string;
  links: Link[];
  joints: Joint[];
  end_effectors: EndEffector[];
}