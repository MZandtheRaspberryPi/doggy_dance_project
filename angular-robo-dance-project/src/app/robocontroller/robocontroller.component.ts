import { Component, OnInit } from '@angular/core';
import { MatSliderChange } from '@angular/material/slider'

import { EndEffectorTrimmed, ForwardKinematics, InverseKinematics } from '../kinematics_interfaces';
import { JointId, Joint } from '../joint';
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
  body_sliders: SliderDetails[];
  forward_sliders: SliderDetails[];
  inverse_sliders: SliderDetails[];
  forward_kinematics: ForwardKinematics;
  inverse_kinematics: InverseKinematics;
  prevRoboModel: number;
  num_slider_steps: number;

  constructor(private robomodelService: RobomodelService) {
    this.robomodel = { id: -1, name: "", links: [], joints: [], end_effectors: [] };
    this.prevRoboModel = -1;
    this.num_slider_steps = 36;

    this.forward_kinematics = {
      body_x_meters: 0,
      body_y_meters: 0,
      body_z_meters: 0,
      body_roll_rad: 0,
      body_pitch_rad: 0,
      body_yaw_rad: 0,
      joints: []
    };

    this.inverse_kinematics = {
      body_x_meters: 0,
      body_y_meters: 0,
      body_z_meters: 0,
      body_roll_rad: 0,
      body_pitch_rad: 0,
      body_yaw_rad: 0,
      end_effectors: []
    };


    this.forward_sliders = [];
    this.inverse_sliders = [];
    this.body_sliders = [];

    let new_body_sliders: SliderDetails[] = new Array();

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
      new_body_sliders.push(new_slider);
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
      new_body_sliders.push(new_slider);
    }
    this.body_sliders = new_body_sliders;

  }

  ngOnInit(): void {
    this.robomodelService.subject.subscribe({
      next: robomodel => {
        this.robomodel = robomodel;
        this.updateForwardJointsAndSliders(robomodel);
        this.updateInverseEndEffectorsAndSliders(robomodel);
      },
      error: err => console.error('An error occurred', err)
    });

    this.robomodelService.getForwardKinematics(this.forward_kinematics);
  }

  sliderInput(event: MatSliderChange, slider: SliderDetails): void {
    if (event.value == null) {
      return;
    }
    let inverse_kinematic_flag: boolean = false;
    if (slider.name == "body_x_meters") {
      this.forward_kinematics.body_x_meters = event.value;
      this.inverse_kinematics.body_x_meters = event.value;
    }
    else if (slider.name == "body_y_meters") {
      this.forward_kinematics.body_y_meters = event.value;
      this.inverse_kinematics.body_y_meters = event.value;
    }
    else if (slider.name == "body_z_meters") {

      this.forward_kinematics.body_z_meters = event.value;
      this.inverse_kinematics.body_z_meters = event.value;
    }
    else if (slider.name == "body_roll_rad") {

      this.forward_kinematics.body_roll_rad = event.value;
      this.inverse_kinematics.body_roll_rad = event.value;
    }
    else if (slider.name == "body_pitch_rad") {

      this.forward_kinematics.body_pitch_rad = event.value;
      this.inverse_kinematics.body_pitch_rad = event.value;
    }
    else if (slider.name == "body_yaw_rad") {

      this.forward_kinematics.body_yaw_rad = event.value;
      this.inverse_kinematics.body_yaw_rad = event.value;
    }

    else if (slider.name.endsWith(this.robomodelService.END_EFFECTOR_STR + "_x")) {
      inverse_kinematic_flag = true;
      this.inverse_kinematics.end_effectors[slider.joint_id - 1].location_shoulder.x = event.value;
    }

    else if (slider.name.endsWith(this.robomodelService.END_EFFECTOR_STR + "_y")) {
      inverse_kinematic_flag = true;
      this.inverse_kinematics.end_effectors[slider.joint_id - 1].location_shoulder.y = event.value;
    }

    else if (slider.name.endsWith(this.robomodelService.END_EFFECTOR_STR + "_z")) {
      inverse_kinematic_flag = true;
      this.inverse_kinematics.end_effectors[slider.joint_id - 1].location_shoulder.z = event.value;
    }

    else {
      this.forward_kinematics.joints[slider.joint_id - 1].current_angle_radians = event.value;
    }

    if (slider.name.startsWith("body_")) {
      this.updateBodySlider(slider.name, event.value);
    }

    if (inverse_kinematic_flag) {
      this.robomodelService.getInverseKinematics(this.inverse_kinematics);
    }
    else {
      this.robomodelService.getForwardKinematics(this.forward_kinematics);
    }

  }

  updateInverseEndEffectorsAndSliders(model: Robomodel): void {

    this.inverse_kinematics.end_effectors = new Array(model.end_effectors.length);

    this.inverse_sliders = new Array();
    this.inverse_sliders = this.inverse_sliders.concat(this.body_sliders);

    let axis_letters: string[] = new Array("x", "y", "z");

    let slider_end_effectors: SliderDetails[] = new Array(model.end_effectors.length * axis_letters.length);
    this.inverse_sliders = this.inverse_sliders.concat(slider_end_effectors);

    for (let i: number = 0; i < model.end_effectors.length; i++) {
      for (let j: number = 0; j < axis_letters.length; j++) {
        let new_slider: SliderDetails = {
          name: model.end_effectors[i].name + "_" + axis_letters[j],
          joint_id: model.end_effectors[i].number,
          min: 0,
          max: 0,
          cur: 0,
          step: 0
        };

        if (axis_letters[j] == "x") {
          new_slider.cur = model.end_effectors[i].location_shoulder.x;
          new_slider.min = model.end_effectors[i].min_x;
          new_slider.max = model.end_effectors[i].max_x;
        }
        else if (axis_letters[j] == "y") {
          new_slider.cur = model.end_effectors[i].location_shoulder.y;
          new_slider.min = model.end_effectors[i].min_y;
          new_slider.max = model.end_effectors[i].max_y;
        }
        else if (axis_letters[j] == "z") {
          new_slider.min = model.end_effectors[i].min_z;
          new_slider.max = model.end_effectors[i].max_z;
          new_slider.cur = model.end_effectors[i].location_shoulder.z;
        }

        new_slider.step = (new_slider.max - new_slider.min) / this.num_slider_steps;

        this.inverse_sliders[this.body_sliders.length + (i * 3) + j] = new_slider;

      }

      let new_end_effector: EndEffectorTrimmed = {
        id: model.end_effectors[i].number,
        location_shoulder: {
          x: model.end_effectors[i].location_shoulder.x,
          y: model.end_effectors[i].location_shoulder.y,
          z: model.end_effectors[i].location_shoulder.z
        }
      };

      this.inverse_kinematics.end_effectors[model.end_effectors[i].number - 1] = new_end_effector;

    }

  }

  updateForwardJointsAndSliders(model: Robomodel): void {
    this.forward_kinematics.joints = new Array(model.joints.length);

    this.forward_sliders = new Array();
    this.forward_sliders = this.forward_sliders.concat(this.body_sliders);
    let slider_joints: SliderDetails[] = new Array(model.joints.length);
    this.forward_sliders = this.forward_sliders.concat(slider_joints);
    for (let i: number = 0; i < model.joints.length; i++) {
      let new_slider: SliderDetails = {
        name: model.joints[i].name,
        joint_id: model.joints[i].number,
        min: model.joints[i].min_angle_radians,
        max: model.joints[i].max_angle_radians,
        cur: model.joints[i].current_angle_radians,
        step: 0
      };
      new_slider.step = (new_slider.max - new_slider.min) / this.num_slider_steps;
      this.forward_sliders[this.body_sliders.length + model.joints[i].number - 1] = new_slider;
      let new_joint: JointId = { number: model.joints[i].number, current_angle_radians: model.joints[i].current_angle_radians };
      this.forward_kinematics.joints[model.joints[i].number - 1] = new_joint;
    }
  }


  updateBodySlider(slider_name: string, cur_val: number): void {

    for (let i: number = 0; i < this.body_sliders.length; i++) {
      if (this.body_sliders[i].name == slider_name) {
        this.body_sliders[i].cur = cur_val;
        break;
      }
    }
  }

  formatLabel(value: number) {
    return Math.round(value * 100) / 100;
  }

}
