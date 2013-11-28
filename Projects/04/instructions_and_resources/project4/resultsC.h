//
//  resultsC.h
//  Project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#ifndef resultsC_h
#define resultsC_h

class resultsC {
  protected:
   int totalPacketCount;

  public:
   resultsC();
   void incrementPacketCount() { totalPacketCount++; };
   void displayResults();
};

#endif
