# Spherebot
Assembly guide:
https://www.jjrobots.com/sphere-o-bot-assembly-and-user-guide/

servoUpPose and servoDownPose are changed during runtime:
In intiHardware function the pen poses are read from EEProm - When they where NEVER written before RANDOM values are loaded and used!!! THis can crash servo!