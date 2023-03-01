import { Component, ElementRef, OnInit, ViewChild } from '@angular/core';

import { Joint } from '../joint';
import { Link } from '../link';
import { RobomodelService } from '../robomodel.service';
import { Robomodel } from '../robomodel';

declare var Plotly: any;

interface plotUpdateData {
  x: number[][];
  y: number[][];
  z: number[][];
};

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
  templateUrl: './roboviewer.component.html',
  styleUrls: ['./roboviewer.component.css']
})
export class RoboviewerComponent implements OnInit {

  robomodel: Robomodel;

  linkXs: number[];
  linkYs: number[];
  linkZs: number[];

  jointXs: number[];
  jointYs: number[];
  jointZs: number[];

  @ViewChild("Graph", { static: false })
  private Graph: ElementRef;

  jointData: Object;
  linkData: Object;
  layoutSetup: Object;
  configSetup: Object;
  graphData: Object[];

  constructor(private robomodelService: RobomodelService) {
    this.linkXs = Array();
    this.linkYs = Array();
    this.linkZs = Array();
    this.jointXs = Array();
    this.jointYs = Array();
    this.jointZs = Array();
    this.robomodel = { id: -1, name: "", links: [], joints: [] };
    this.Graph = { nativeElement: {} };

    this.linkData = {
      type: 'scatter3d',
      mode: 'lines',
      x: [],
      y: [],
      z: [],
      line: {
        width: 6,
        color: [1, 1, 1],
        colorscale: "Viridis"
      },
      showlegend: false
    };

    this.jointData = {
      type: 'scatter3d',
      mode: 'markers',
      x: [],
      y: [],
      z: [],
      marker: {
        size: 3.5,
        color: [2, 2, 2],
        colorscale: "Greens",
        cmin: -20,
        cmax: 50
      },
      showlegend: false
    };

    this.graphData = [this.linkData, this.jointData];

    this.layoutSetup = {
      autosize: true, title: 'Robo Viewer Graph',
      scene: {
        camera: { up: { x: 0, y: 1, z: 0 } },
        aspectmode: "manual",
        aspectratio: {
          x: 1, y: 1, z: 1,
        },
        xaxis: {
          nticks: 4,
          range: [-1, 1],
        },
        yaxis: {
          nticks: 4,
          range: [-1, 1],
        },
        zaxis: {
          nticks: 4,
          range: [-1, 1],
        }
      },
    };

    this.configSetup = { responsive: true };

  }

  ngOnInit(): void {
  }

  ngAfterViewInit() {
    Plotly.newPlot(
      this.Graph.nativeElement,
      this.graphData,
      this.layoutSetup,
      this.configSetup
    );

    this.getRobomodels();
  }

  updateGraphOnRobotLoad(): void {
    if (this.robomodel.id != -1) {
      this.linkXs = getXFromLinks(this.robomodel.links);
      this.linkYs = getYFromLinks(this.robomodel.links);
      this.linkZs = getZFromLinks(this.robomodel.links);

      this.jointXs = getXFromJoint(this.robomodel.joints);
      this.jointYs = getYFromJoint(this.robomodel.joints);
      this.jointZs = getZFromJoint(this.robomodel.joints);
    }

    let update: plotUpdateData = { x: [this.linkXs, this.jointXs], y: [this.linkYs, this.jointYs], z: [this.linkZs, this.jointZs] };
    Plotly.restyle(this.Graph.nativeElement, update, [0, 1]);

  }

  getRobomodels(): void {
    this.robomodelService.getRobomodel(0).subscribe(
      {
        next: robomodel => this.robomodel = robomodel,
        error: err => console.error('An error occurred', err),
        complete: () => this.updateGraphOnRobotLoad()
      });
  }
}
