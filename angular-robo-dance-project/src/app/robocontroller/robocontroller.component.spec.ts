import { ComponentFixture, TestBed } from '@angular/core/testing';

import { RobocontrollerComponent } from './robocontroller.component';

describe('RobocontrollerComponent', () => {
  let component: RobocontrollerComponent;
  let fixture: ComponentFixture<RobocontrollerComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ RobocontrollerComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(RobocontrollerComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
