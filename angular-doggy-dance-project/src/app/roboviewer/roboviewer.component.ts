import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-roboviewer',
  template: `
  <plotly-plot [data]="graph.data" [layout]="graph.layout"
     [useResizeHandler]="true" [style]="{width: '100%', height: '100%'}">
  </plotly-plot>`,
})
export class RoboviewerComponent implements OnInit {

  constructor() { }

  ngOnInit(): void {
  }

  public graph = {
    data: [
      {type: 'scatter3d',
      mode: 'lines',
      x: [1, 2, 3],
      y: [2, 3, 3],
      z: [4, 4, 5],
      line: {
        width: 6,
        color: [1, 1, 1],
        colorscale: "Viridis"},
      },
      {type: 'scatter3d',
      mode: 'markers',
      x: [1, 2, 3],
      y: [2, 3, 3],
      z: [4, 4, 5],
      marker: {
        size: 3.5,
        color: [2, 2, 2],
        colorscale: "Greens",
        cmin: -20,
        cmax: 50
      }},                 
    ],
    layout: {autosize: true, title: 'Robo Viewer Graph'}
};

}
