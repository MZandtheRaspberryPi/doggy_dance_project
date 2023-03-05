import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { MatSliderModule } from '@angular/material/slider';
import { MatTabsModule } from '@angular/material/tabs';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HttpClientModule } from '@angular/common/http';
import { RoboviewerComponent } from './roboviewer/roboviewer.component';

import { PlotlyViaWindowModule } from 'angular-plotly.js';
import { RobomodelComponent } from './robomodel/robomodel.component';
import { JointComponent } from './joint/joint.component';
import { LinkComponent } from './link/link.component';
import { MessagesComponent } from './messages/messages.component';
import { RobocontrollerComponent } from './robocontroller/robocontroller.component';

@NgModule({
  declarations: [
    AppComponent,
    RoboviewerComponent,
    RobomodelComponent,
    JointComponent,
    LinkComponent,
    MessagesComponent,
    RobocontrollerComponent
  ],
  imports: [
    AppRoutingModule,
    BrowserAnimationsModule,
    BrowserModule,
    HttpClientModule,
    MatSliderModule,
    MatTabsModule,
    PlotlyViaWindowModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
