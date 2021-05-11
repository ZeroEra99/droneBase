

void safeLanding(){
  //Richiede input altezza
  /* Sfrutta due informazioni: altezza attuale e altezza al ciclo precedente.
  Conoscendo il tempo passato fra le due rilevazioni calcola la velocità verticale.
  Se la velocità verticale è maggiore di quella di discesa allora aumenta la potenza.
  Se la velocità verticale è minore di quella di discesa allora diminuisce la potenza.
  Di quanto deve aumentare/diminuire???? --> Dividi et impera*/
  return;
}

void normalFlight(){
  throttleCompensation();
  offsetGeneration();
  offsetLimitation();
  //updateGPSpos();
  //updateAltitude():
}

void altitudeHold(){
  //throttleCalculation();
  offsetGeneration();
  offsetLimitation();
}

void gpsHold(){
  //Calculate heading and distance
  //Calculate drone's orientation with the north
    //If distance<2m translate to point
    //If distance>2m head to target and point forward
  //throttleCalculation();
  offsetGeneration();
  offsetLimitation();
}