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

interface XYZData {
  x: number[];
  y: number[];
  z: number[];
}

interface XYZLinksData {
  link_groups: XYZData[];
};

// so we want to parse joints, end effectors, and links
// parse joints and end effectors first.
// iterate over joints, and for each joint, push newJoints.x back by joint.x, so on. push newJoints.y back by joint.y.
// similar for end effectors
// for links
// take first link and split by _
// take first_ and thats a group name
// when we dont have that anymore start a new group

function getLinkGroupsXYZ(links: Link[]): XYZLinksData {

  let return_val: XYZLinksData = { link_groups: new Array(5) };
  for (let i = 0; i < 5; i++) {
    return_val.link_groups[i] = { x: [], y: [], z: [] };
  }

  if (links.length == 0) {
    return return_val;
  }
  let group_name: string = links[0].name.split("_")[0];
  let cur_group_index: number = 0;
  for (let i = 0; i < links.length; i++) {
    let split_name: string[] = links[i].name.split("_");
    if (split_name.length == 0) {
      return return_val;
    }
    let this_link_group: string = split_name[0];

    if (this_link_group !== group_name) {
      // add end for previous group
      return_val.link_groups[cur_group_index].x.push(links[i - 1].end_location.x);
      return_val.link_groups[cur_group_index].y.push(links[i - 1].end_location.y);
      return_val.link_groups[cur_group_index].z.push(links[i - 1].end_location.z);

      cur_group_index++;
      group_name = this_link_group;
    }
    return_val.link_groups[cur_group_index].x.push(links[i].start_location.x);
    return_val.link_groups[cur_group_index].y.push(links[i].start_location.y);
    return_val.link_groups[cur_group_index].z.push(links[i].start_location.z);
  }

  // add end for previous group
  return_val.link_groups[cur_group_index].x.push(links[links.length - 1].end_location.x);
  return_val.link_groups[cur_group_index].y.push(links[links.length - 1].end_location.y);
  return_val.link_groups[cur_group_index].z.push(links[links.length - 1].end_location.z);

  return return_val;
}



function getXYZFromJoints(joints: Joint[]): XYZData {
  let parsedData: XYZData = { x: [], y: [], z: [] };
  for (let i = 0; i < joints.length; i++) {
    parsedData.x.push(joints[i].location.x);
    parsedData.y.push(joints[i].location.y);
    parsedData.z.push(joints[i].location.z);
  }
  return parsedData;
}

@Component({
  selector: 'app-roboviewer',
  templateUrl: './roboviewer.component.html',
  styleUrls: ['./roboviewer.component.css']
})
export class RoboviewerComponent implements OnInit {

  robomodel: Robomodel;

  jointXs: number[];
  jointYs: number[];
  jointZs: number[];

  endEffectorXs: number[];
  endEffectorYs: number[];
  endEffectorZs: number[];

  @ViewChild("Graph", { static: false })
  private Graph: ElementRef;

  jointData: Object;
  endEffectorData: Object;
  layoutSetup: Object;
  configSetup: Object;
  graphData: Object[];

  constructor(private robomodelService: RobomodelService) {
    this.jointXs = Array();
    this.jointYs = Array();
    this.jointZs = Array();
    this.endEffectorXs = Array();
    this.endEffectorYs = Array();
    this.endEffectorZs = Array();
    this.robomodel = { id: -1, name: "", links: [], joints: [], end_effectors: [] };
    this.Graph = { nativeElement: {} };

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

    this.endEffectorData = {
      type: 'scatter3d',
      mode: 'markers',
      x: [],
      y: [],
      z: [],
      marker: {
        size: 3.5,
        color: "red"
      },
      showlegend: false
    };

    // we will support up to 5 groups of link data
    this.graphData = new Array(7);
    this.graphData[0] = this.jointData;
    this.graphData[1] = this.endEffectorData;
    for (let i: number = 0; i < 5; i++) {
      this.graphData[i + 2] = {
        type: 'scatter3d',
        mode: 'lines',
        x: [],
        y: [],
        z: [],
        line: {
          width: 6,
          color: "black"
        },
        showlegend: false
      };
    }

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

    let parsedJointsData: XYZData = getXYZFromJoints(this.robomodel.joints);
    let parsedEndEffectorData: XYZData = getXYZFromJoints(this.robomodel.end_effectors);

    let parsedLinkData: XYZLinksData = getLinkGroupsXYZ(this.robomodel.links);
    if (parsedLinkData.link_groups.length < 5) {
      for (let i: number = 0; i < 5; i++) {

        let cur_link_group: XYZData = { x: [], y: [], z: [] };
        parsedLinkData.link_groups.push(cur_link_group);
      }
    }

    let update: plotUpdateData = {
      x: [parsedJointsData.x, parsedEndEffectorData.x, parsedLinkData.link_groups[0].x, parsedLinkData.link_groups[1].x, parsedLinkData.link_groups[2].x, parsedLinkData.link_groups[3].x, parsedLinkData.link_groups[4].x],
      y: [parsedJointsData.y, parsedEndEffectorData.y, parsedLinkData.link_groups[0].y, parsedLinkData.link_groups[1].y, parsedLinkData.link_groups[2].y, parsedLinkData.link_groups[3].y, parsedLinkData.link_groups[4].y],
      z: [parsedJointsData.z, parsedEndEffectorData.z, parsedLinkData.link_groups[0].z, parsedLinkData.link_groups[1].z, parsedLinkData.link_groups[2].z, parsedLinkData.link_groups[3].z, parsedLinkData.link_groups[4].z]
    };

    Plotly.restyle(this.Graph.nativeElement, update, [0, 1, 2, 3, 4, 5, 6]);

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
