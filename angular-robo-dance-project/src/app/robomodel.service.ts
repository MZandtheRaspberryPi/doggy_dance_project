import { catchError, tap } from 'rxjs/operators';
import { HttpClient, HttpParams } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable, of, BehaviorSubject } from 'rxjs';

import { MessageService } from './message.service';

import { Robomodel } from './robomodel';

import { RobomodelDescList } from './robomodel_desc';

import { ForwardKinematics, InverseKinematics } from './kinematics_interfaces';

import { environment } from '../environments/environment';


var ROBODOG_ID: number = 0;
var AXIS_NEGATIVE_LIMIT: number = -2;
var AXIS_POSITIVE_LIMIT: number = 2;

@Injectable({
  providedIn: 'root'
})
export class RobomodelService {

  private API_URL: string;
  private roboModelsUrl: string;
  private currentRobomodel: Robomodel;
  public subject: BehaviorSubject<Robomodel>;
  public ROBODOG_ID: number = 0;
  public AXIS_NEGATIVE_LIMIT: number;
  public AXIS_POSITIVE_LIMIT: number;
  public END_EFFECTOR_STR: string;
  constructor(
    private http: HttpClient,
    private messageService: MessageService
  ) {
    this.API_URL = environment.API_URL;
    this.roboModelsUrl = this.API_URL + '/v1';
    this.ROBODOG_ID = 0;
    this.AXIS_NEGATIVE_LIMIT = -1;
    this.AXIS_POSITIVE_LIMIT = 1;
    this.END_EFFECTOR_STR = "end_effector";
    this.currentRobomodel = { id: -1, name: "", joints: [], links: [], end_effectors: [] };
    this.subject = new BehaviorSubject<Robomodel>({ id: -1, name: "", links: [], joints: [], end_effectors: [] });
  }


  /**
 * Handle Http operation that failed.
 * Let the app continue.
 *
 * @param operation - name of the operation that failed
 * @param result - optional value to return as the observable result
 */
  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {

      // TODO: send the error to remote logging infrastructure
      console.error(error); // log to console instead

      // TODO: better job of transforming error for user consumption
      this.log(`${operation} failed: ${error.message}`);

      // Let the app keep running by returning an empty result.
      return of(result as T);
    };
  }

  private log(message: string) {
    this.messageService.add(`HeroService: ${message}`);
  }

  getForwardKinematics(kinematics: ForwardKinematics): void {

    let params_obj: HttpParams = new HttpParams();
    params_obj = params_obj.set('robo_model_id', ROBODOG_ID);
    params_obj = params_obj.set('body_x_meters', kinematics.body_x_meters);
    params_obj = params_obj.set('body_y_meters', kinematics.body_y_meters);
    params_obj = params_obj.set('body_z_meters', kinematics.body_z_meters);
    params_obj = params_obj.set('body_roll_rad', kinematics.body_roll_rad);
    params_obj = params_obj.set('body_pitch_rad', kinematics.body_pitch_rad);
    params_obj = params_obj.set('body_yaw_rad', kinematics.body_yaw_rad);

    for (let i: number = 0; i < kinematics.joints.length; i++) {
      params_obj = params_obj.set(kinematics.joints[i].number.toString(), kinematics.joints[i].current_angle_radians);
    }

    let my_observable: Observable<Robomodel> = this.http.get<Robomodel>(this.roboModelsUrl + `/forward_kinematics`, { params: params_obj })
      .pipe(
        catchError(this.handleError<Robomodel>('getRoboModel', { id: -1, name: "", links: [], joints: [], end_effectors: [] }))
      );

    my_observable.subscribe({
      next: model => { this.subject.next(model); },
      error: err => this.subject.error(err)
    });

    return;
  }

  getInverseKinematics(kinematics: InverseKinematics): void {

    let params_obj: HttpParams = new HttpParams();
    params_obj = params_obj.set('robo_model_id', ROBODOG_ID);
    params_obj = params_obj.set('body_x_meters', kinematics.body_x_meters);
    params_obj = params_obj.set('body_y_meters', kinematics.body_y_meters);
    params_obj = params_obj.set('body_z_meters', kinematics.body_z_meters);
    params_obj = params_obj.set('body_roll_rad', kinematics.body_roll_rad);
    params_obj = params_obj.set('body_pitch_rad', kinematics.body_pitch_rad);
    params_obj = params_obj.set('body_yaw_rad', kinematics.body_yaw_rad);

    for (let i: number = 0; i < kinematics.end_effectors.length; i++) {
      params_obj = params_obj.set(kinematics.end_effectors[i].id.toString() + '_x', kinematics.end_effectors[i].location.x);
      params_obj = params_obj.set(kinematics.end_effectors[i].id.toString() + '_y', kinematics.end_effectors[i].location.y);
      params_obj = params_obj.set(kinematics.end_effectors[i].id.toString() + '_z', kinematics.end_effectors[i].location.z);
    }

    let my_observable: Observable<Robomodel> = this.http.get<Robomodel>(this.roboModelsUrl + `/inverse_kinematics`, { params: params_obj })
      .pipe(
        catchError(this.handleError<Robomodel>('getRoboModel', { id: -1, name: "", links: [], joints: [], end_effectors: [] }))
      );

    my_observable.subscribe({
      next: model => { this.subject.next(model); },
      error: err => this.subject.error(err)
    });

    return;
  }

  getRobomodelDescriptions(): Observable<RobomodelDescList> {
    return this.http.get<RobomodelDescList>(this.roboModelsUrl + '/descriptions')
      .pipe(
        catchError(this.handleError<RobomodelDescList>('getRobomodelDescriptions', { descriptions: [] }))
      );
  }

  getCurrentRobomodel(): Robomodel {
    return this.currentRobomodel;
  }
}
