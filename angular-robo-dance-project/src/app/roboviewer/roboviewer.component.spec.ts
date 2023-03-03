import { ComponentFixture, TestBed } from '@angular/core/testing';

import { RoboviewerComponent } from './roboviewer.component';

describe('RoboviewerComponent', () => {
  let component: RoboviewerComponent;
  let fixture: ComponentFixture<RoboviewerComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ RoboviewerComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(RoboviewerComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
