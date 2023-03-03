import { Component, OnInit } from '@angular/core';

import { RobomodelDesc, RobomodelDescList } from '../robomodel_desc';
import { RobomodelService } from '../robomodel.service';

@Component({
  selector: 'app-robomodel',
  templateUrl: './robomodel.component.html',
  styleUrls: ['./robomodel.component.css']
})
export class RobomodelComponent implements OnInit {

  robomodel_descs: RobomodelDescList;
  selected_desc?: RobomodelDesc;

  constructor(private robomodelService: RobomodelService) {
    this.robomodel_descs = { descriptions: [] };
  }

  ngOnInit(): void {
    this.getRobomodels();
  }

  onSelect(robomodel: RobomodelDesc): void {
    if (this.selected_desc === robomodel) {
      this.selected_desc = undefined;
    }
    else {
      this.selected_desc = robomodel;
    }
  }


  getRobomodels(): void {
    this.robomodelService.getRobomodels().subscribe(robomodel_descs => this.robomodel_descs = robomodel_descs);
  }

}
