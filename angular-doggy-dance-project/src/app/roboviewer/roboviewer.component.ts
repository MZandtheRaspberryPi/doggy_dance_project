import { Component, OnInit } from '@angular/core';

import { Joint } from '../joint';
import { Link } from '../link';
import { RobomodelService } from '../robomodel.service';
import { Robomodel } from '../robomodel';


function getXFromLinks(links: Link[]): number[] {
  let xs: Array<number> = Array(links.length + 1);
  for (let i = 0; i < links.length; i++) {
    xs[i] = links[i].start_location.x;
  }
  xs[links.length] = links[links.length - 1].end_location.x;
  return xs;
}

function getYFromLinks(links: Link[]): number[] {
  let ys: Array<number> = Array(links.length + 1);
  for (let i = 0; i < links.length; i++) {
    ys[i] = links[i].start_location.y;
  }
  ys[links.length] = links[links.length - 1].end_location.y;
  return ys;
}

function getZFromLinks(links: Link[]): number[] {
  let zs: Array<number> = Array(links.length + 1);
  for (let i = 0; i < links.length; i++) {
    zs[i] = links[i].start_location.z;
  }
  zs[links.length] = links[links.length - 1].end_location.z;
  return zs;
}

function getXFromJoint(joints: Joint[]): number[] {
  let xs: Array<number> = Array(joints.length);
  for (let i = 0; i < joints.length; i++) {
    xs[i] = joints[i].location.x;
  }
  return xs;
}

function getYFromJoint(joints: Joint[]): number[] {
  let ys: Array<number> = Array(joints.length);
  for (let i = 0; i < joints.length; i++) {
    ys[i] = joints[i].location.y;
  }
  return ys;
}

function getZFromJoint(joints: Joint[]): number[] {
  let zs: Array<number> = Array(joints.length);
  for (let i = 0; i < joints.length; i++) {
    zs[i] = joints[i].location.z;
  }
  return zs;
}

@Component({
  selector: 'app-roboviewer',
  template: `
  <plotly-plot [data]="graph.data" [layout]="graph.layout"
       [useResizeHandler]="true" [style]="{position: 'relative', width: '100%', height: '100%'}">
  </plotly-plot>`,
})
export class RoboviewerComponent implements OnInit {

  robomodel?: Robomodel;

  linkXs: number[] = Array();
  linkYs: number[] = Array();
  linkZs: number[] = Array();

  jointXs: number[] = Array();
  jointYs: number[] = Array();
  jointZs: number[] = Array();

  constructor(private robomodelService: RobomodelService) { }

  ngOnInit(): void {
    this.getRobomodels();
  }

  updateGraphOnRobotLoad(): void {
    if (typeof this.robomodel !== 'undefined') {
      this.linkXs = getXFromLinks(this.robomodel!.links);
      this.linkYs = getYFromLinks(this.robomodel!.links);
      this.linkZs = getZFromLinks(this.robomodel!.links);

      this.jointXs = getXFromJoint(this.robomodel!.joints);
      this.jointYs = getYFromJoint(this.robomodel!.joints);
      this.jointZs = getZFromJoint(this.robomodel!.joints);
    }

    this.graph.data[0].x = this.linkXs;
    this.graph.data[0].y = this.linkYs;
    this.graph.data[0].z = this.linkZs;

    this.graph.data[1].x = this.jointXs;
    this.graph.data[1].y = this.jointYs;
    this.graph.data[1].z = this.jointZs;

  }

  getRobomodels(): void {
    this.robomodelService.getRobomodels().subscribe(
      {
        next: robomodels => this.robomodel = robomodels.robo_models[0],
        error: err => console.error('An error occurred', err),
        complete: () => this.updateGraphOnRobotLoad()
      });
  }

  public graph = {
    data: [
      {
        type: 'scatter3d',
        mode: 'lines',
        x: this.linkXs,
        y: this.linkYs,
        z: this.linkZs,
        line: {
          width: 6,
          color: [1, 1, 1],
          colorscale: "Viridis"
        },
        showlegend: false
      },
      {
        type: 'scatter3d',
        mode: 'markers',
        x: this.jointXs,
        y: this.jointYs,
        z: this.jointZs,
        marker: {
          size: 3.5,
          color: [2, 2, 2],
          colorscale: "Greens",
          cmin: -20,
          cmax: 50
        },
        showlegend: false
      }
    ],
    layout: { autosize: true, title: 'Robo Viewer Graph' }
  };



}
