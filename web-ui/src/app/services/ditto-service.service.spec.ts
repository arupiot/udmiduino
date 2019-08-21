import { TestBed, inject } from '@angular/core/testing';

import { DittoServiceService } from './ditto-service.service';

describe('DittoServiceService', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [DittoServiceService]
    });
  });

  it('should be created', inject([DittoServiceService], (service: DittoServiceService) => {
    expect(service).toBeTruthy();
  }));
});
