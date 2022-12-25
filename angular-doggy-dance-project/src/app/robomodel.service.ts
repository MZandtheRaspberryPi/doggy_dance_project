import { catchError, map, tap } from 'rxjs/operators';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable, of } from 'rxjs';

import { MessageService } from './message.service';

import { RobomodelList } from './robomodel_list';

import { environment } from '../environments/environment';

@Injectable({
  providedIn: 'root'
})
export class RobomodelService {

  constructor(
    private http: HttpClient,
    private messageService: MessageService
  ) { }


  private API_URL: string = environment.API_URL;
  private roboModelsUrl: string = this.API_URL + '/robomodels';

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

  /** Log a HeroService message with the MessageService */
  private log(message: string) {
    this.messageService.add(`HeroService: ${message}`);
  }

  getRobomodels(): Observable<RobomodelList> {
    return this.http.get<RobomodelList>(this.roboModelsUrl)
      .pipe(
        catchError(this.handleError<RobomodelList>('getRobomodels', { robo_models: [] }))
      );
  }
}
