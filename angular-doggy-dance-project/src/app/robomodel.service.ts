import { Injectable } from '@angular/core';
import { Observable, of } from 'rxjs';

import { Robomodel } from './robomodel';
import { ROBOMODELS } from './mock-robomodels';

@Injectable({
  providedIn: 'root'
})
export class RobomodelService {

  constructor() { }

  getRobomodels(): Observable<Robomodel[]> {
    const robomodels = of(ROBOMODELS);
    return robomodels;
  }
}
