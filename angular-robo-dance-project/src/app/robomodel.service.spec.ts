import { TestBed } from '@angular/core/testing';

import { RobomodelService } from './robomodel.service';

describe('RobomodelService', () => {
  let service: RobomodelService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(RobomodelService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
