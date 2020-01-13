import { Injectable } from "@angular/core";
import { HttpClient } from "@angular/common/http";
import { HttpHeaders } from "@angular/common/http";

const httpOptions = {
  headers: new HttpHeaders({
    "Content-Type": "application/json",
    Authorization: "Basic ZGl0dG86ZGl0dG8="
  })
};

@Injectable()
export class DittoServiceService {
  dittoURL: string = "http://localhost/api/2/";
  ledToggleEndPoint: string = "things/open.iot%3AUDMIduino-000";
  toggleBody: any = {
    version: 1,
    timestamp: "0",
    points: {
      lux_level: {
        present_value: 0
      },
      lum_value: {
        present_value: 0
      },
      dimmer_value: {
        present_value: 0
      }
    }
  };

  constructor(private http: HttpClient) {}

  toggleLED() {
    return this.http.put(
      this.dittoURL + this.ledToggleEndPoint,
      this.toggleBody,
      httpOptions
    );
  }
}
