# Spherebot
Assembly guide:
https://www.jjrobots.com/sphere-o-bot-assembly-and-user-guide/

servoUpPose and servoDownPose are changed during runtime:
In intiHardware function the pen poses are read from EEProm - When they where NEVER written before RANDOM values are loaded and used!!! THis can crash servo!

Servo on 3.3V and GPIO 13

CMDs (serial port 9600)
http://evil-mad.github.io/EggBot/ebb.html (other version)
eggduino https://github.com/cocktailyogi/EggDuino
not eggbot as it uses PIC code!
eg.
SC,4,2000

void makeComInterface(){
	SCmd.addCommand("v",sendVersion);
	SCmd.addCommand("EM",enableMotors);
	SCmd.addCommand("SC",stepperModeConfigure);
	SCmd.addCommand("SP",setPen);
	SCmd.addCommand("SM",stepperMove);
	SCmd.addCommand("SE",ignore);
	SCmd.addCommand("TP",togglePen);
	SCmd.addCommand("PO",ignore);    //Engraver command, not implemented, gives fake answer
	SCmd.addCommand("NI",nodeCountIncrement);
	SCmd.addCommand("ND",nodeCountDecrement);
	SCmd.addCommand("SN",setNodeCount);
	SCmd.addCommand("QN",queryNodeCount);
	SCmd.addCommand("SL",setLayer);
	SCmd.addCommand("QL",queryLayer);
	SCmd.addCommand("QP",queryPen);
	SCmd.addCommand("QB",queryButton);  //"PRG" Button,
	SCmd.setDefaultHandler(unrecognized); // Handler for command that isn't matched (says "What?")
}