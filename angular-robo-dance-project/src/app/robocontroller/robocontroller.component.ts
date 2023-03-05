import { Component, OnInit } from '@angular/core';
import { MatSliderChange } from '@angular/material/slider'

import { ForwardKinematics } from '../forward_kinematics_interfaces';
import { JointId } from '../joint';
import { Robomodel } from '../robomodel';
import { RobomodelService } from '../robomodel.service';


interface SliderDetails {
  name: string,
  joint_id: number,
  min: number,
  max: number,
  cur: number,
  step: number
}

@Component({
  selector: 'app-robocontroller',
  templateUrl: './robocontroller.component.html',
  styleUrls: ['./robocontroller.component.css']
})
export class RobocontrollerComponent implements OnInit {

  robomodel: Robomodel;
  new_sliders: SliderDetails[];
  sliders: SliderDetails[];
  kinematics: ForwardKinematics;
  prevRoboModel: number;

  constructor(private robomodelService: RobomodelService) {
    this.robomodel = { id: -1, name: "", links: [], joints: [], end_effectors: [] };
    this.prevRoboModel = -1;
    this.sliders = [];
    let new_sliders: SliderDetails[] = new Array();

    this.kinematics = {
      body_x_meters: 0,
      body_y_meters: 0,
      body_z_meters: 0,
      body_roll_rad: 0,
      body_pitch_rad: 0,
      body_yaw_rad: 0,
      joints: []
    };

    let body_meter_sliders: string[] = new Array("body_x_meters", "body_y_meters", "body_z_meters");
    let body_radian_sliders: string[] = new Array("body_roll_rad", "body_pitch_rad", "body_yaw_rad");
    for (let i: number = 0; i < body_meter_sliders.length; i++) {
      let new_slider: SliderDetails = {
        name: body_meter_sliders[i],
        joint_id: -1,
        min: -3,
        max: 3,
        cur: 0,
        step: 0.1
      };
      new_sliders.push(new_slider);
    }

    for (let i: number = 0; i < body_radian_sliders.length; i++) {
      let new_slider: SliderDetails = {
        name: body_radian_sliders[i],
        joint_id: -1,
        min: 0,
        max: 2 * 3.141,
        cur: 0,
        step: 2 * 3.141 / 360
      };
      new_sliders.push(new_slider);
    }
    this.new_sliders = new_sliders;

  }

  ngOnInit(): void {
    this.robomodelService.subject.subscribe({
      next: robomodel => { this.robomodel = robomodel; this.updateSliders(); },
      error: err => console.error('An error occurred', err)
    });

    this.robomodelService.getForwardKinematics(0, this.kinematics);
  }

  sliderInput(event: MatSliderChange, slider: SliderDetails): void {
    if (event.value == null) {
      return;
    }
    if (slider.name == "body_x_meters") {
      this.kinematics.body_x_meters = event.value;
    }
    else if (slider.name == "body_y_meters") {
      this.kinematics.body_y_meters = event.value;
    }
    else if (slider.name == "body_z_meters") {

      this.kinematics.body_z_meters = event.value;
    }
    else if (slider.name == "body_roll_rad") {

      this.kinematics.body_roll_rad = event.value;
    }
    else if (slider.name == "body_pitch_rad") {

      this.kinematics.body_pitch_rad = event.value;
    }
    else if (slider.name == "body_yaw_rad") {

      this.kinematics.body_yaw_rad = event.value;
    }
    else {
      this.kinematics.joints[slider.joint_id - 1].current_angle_radians = event.value;
    }

    this.getRobomodel(this.kinematics);
  }

  updateSliders(): void {
    if (this.prevRoboModel !== this.robomodel.id) {
      this.prevRoboModel = this.robomodel.id;
      this.kinematics.joints = new Array(this.robomodel.joints.length);
      for (let i: number = 0; i < this.robomodel.joints.length; i++) {
        let new_slider: SliderDetails = {
          name: this.robomodel.joints[i].name,
          joint_id: this.robomodel.joints[i].number,
          min: 0,
          max: 2 * 3.141,
          cur: 0,
          step: 2 * 3.141 / 360
        };
        this.new_sliders.push(new_slider);
        let new_joint: JointId = { number: this.robomodel.joints[i].number, current_angle_radians: this.robomodel.joints[i].current_angle_radians };
        this.kinematics.joints[this.robomodel.joints[i].number - 1] = new_joint;
      }
      this.sliders = this.new_sliders;
    }
  }

  getRobomodel(kinematics: ForwardKinematics): void {
    this.robomodelService.getForwardKinematics(0, kinematics);
  }

}
