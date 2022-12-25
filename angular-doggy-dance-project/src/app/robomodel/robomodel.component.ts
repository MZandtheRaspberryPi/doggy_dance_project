import { Component, OnInit } from '@angular/core';


import { Robomodel } from '../robomodel';
import { RobomodelList } from '../robomodel_list';
import { RobomodelService } from '../robomodel.service';

@Component({
  selector: 'app-robomodel',
  templateUrl: './robomodel.component.html',
  styleUrls: ['./robomodel.component.css']
})
export class RobomodelComponent implements OnInit {

  robomodels: Robomodel[] = [];
  selectedRobomodel?: Robomodel;

  onSelect(robomodel: Robomodel): void {
    if (this.selectedRobomodel === robomodel) {
      this.selectedRobomodel = undefined;
    }
    else {
      this.selectedRobomodel = robomodel;
    }
  }

  constructor(private robomodelService: RobomodelService) { }

  ngOnInit(): void {
    this.getRobomodels();
  }

  getRobomodels(): void {
    this.robomodelService.getRobomodels().subscribe(robomodels => this.robomodels = robomodels.robo_models);
  }

}
