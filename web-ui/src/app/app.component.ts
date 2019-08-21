import { Component } from '@angular/core';
import { DittoServiceService } from './services/ditto-service.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {

  constructor(private dittoService: DittoServiceService) {}

  toggleLED() {
    console.log('toggle!');
    this.dittoService.toggleLED()
    // clone the data object, using its known Config shape
    .subscribe((data: any) => console.log(data)
    );
  }

}
