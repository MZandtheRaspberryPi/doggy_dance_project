import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HttpClientModule } from '@angular/common/http';
import { RoboviewerComponent } from './roboviewer/roboviewer.component';

import { PlotlyViaWindowModule } from 'angular-plotly.js';
import { RobomodelComponent } from './robomodel/robomodel.component';
import { JointComponent } from './joint/joint.component';
import { LinkComponent } from './link/link.component';
import { MessagesComponent } from './messages/messages.component';

@NgModule({
  declarations: [
    AppComponent,
    RoboviewerComponent,
    RobomodelComponent,
    JointComponent,
    LinkComponent,
    MessagesComponent
  ],
  imports: [
    AppRoutingModule,
    BrowserModule,
    HttpClientModule,
    PlotlyViaWindowModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
