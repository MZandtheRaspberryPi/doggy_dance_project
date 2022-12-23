import { ComponentFixture, TestBed } from '@angular/core/testing';

import { RobomodelComponent } from './robomodel.component';

describe('RobomodelComponent', () => {
  let component: RobomodelComponent;
  let fixture: ComponentFixture<RobomodelComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ RobomodelComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(RobomodelComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
