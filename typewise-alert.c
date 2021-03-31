#include "typewise-alert.h"
#include <stdio.h>


BreachLimits BreachLimitArr[]={{0,35, PASSIVE_COOLING},{0,45,HI_ACTIVE_COOLING},{0,40,MED_ACTIVE_COOLING}};

void (*AlertTargetFunc[])(BreachType breachType)={	sendToController,sendToEmail};

void (*EmailMessage[])(const char* recepient)={NormalMessage,TooLowmessage,Toohighmessage};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {

  return inferBreach(temperatureInC, BreachLimitArr[coolingType].lowerLimit, BreachLimitArr[coolingType].upperLimit);
}

BreachType checkAndAlert(AlertTarget alertTarget, CoolingType coolingType, double temperatureInC) 
{ 
  BatteryCharacter batteryChar;
  batteryChar.coolingTypeIdentifier = coolingType ;	
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingTypeIdentifier, temperatureInC);
   (*AlertTargetFunc[alertTarget])(breachType);
   return breachType;
}


void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void TooLowmessage (const char* recepient)
{
	printf("To: %s\n", recepient);
    printf("!! ALERT !! temperature is too low\n");
}

void Toohighmessage (const char* recepient)
{
	printf("To: %s\n", recepient);
    printf("!! ALERT !! temperature is too high\n");
}

void NormalMessage (const char* recepient)
{
	printf("To: %s\n", recepient);
    printf(" ! OKAY ! temperature is normal\n");
}
	

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  (*EmailMessage[breachType])(recepient);
}
