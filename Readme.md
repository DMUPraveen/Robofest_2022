# Codebase for Robofest 2022 Micromouse Challenge for team Megatrons


## Todo List and RoadMap

### Software
Software will consist of four main components
1. Maze solving Algorithm
2. PID controller
3. Sensor Fusion and Pose Estimator
4. Main Controller (that cordinates the previous three)

The todo list for the previous components are as follows

- [x] Developing the maze solving algorithm
- [ ] Converting the maze solving algorithm in to c++ source code (in progress)
- [ ] Code to process raw data from the Ultrasonic Sensors and calculate distance
- [ ] Code to process raw data from the Magentometer and calculate the angle relatice to north
- [ ] Code to process raw data from the wheel encoders and the control vector to calculate speed
- [ ] Code to use the distance measurements obtained by distance sensors over a period of time of a specific wall and use it estimate the current orientation of the robot
- [ ] Code to use the distance from two walls (if two are avilable) to estimate the position of the robot relative to current cell) 
- [ ] Code to use the moment a wall disapears to update the position estimate of the robot (?)
- [ ] Sensor Fusion and Pose Estimation
    - Using the data from different sensors to estimate the pose of the robot (orientation position and velocity) the sensor data may include.
        - [ ] Speed data calculted from wheel encoders
            - [ ] Angular velocity 
            - [ ] and Linear velocity needs to be calcualted and stored
            - [ ] Velcoities from intergrated accelerometer and gyroscopic data (?)
        - [ ] Orientation from intergration of angular velcoity
        - [ ] Orientation from the magnetometer
        - [ ] Orientation relatice to the wall using wall distance data over a period (?)
        - [ ] Position from intergration of velocity
        - [ ] Position from distancce measurements to the walls 
        - [ ] Fusing all the data with approporiate filters to get the best estimation
- [ ] PID control to provide the control vector to drive the robot given the current pose and target
    - [ ] Getting the motor Controller working
    - [ ] Writing the PID control logic
- [ ] Main event handler that communicate between the differnet components 
    - activating and deactivating the PID contoller and giving it the current position (from Pose detection) and providing it with a target (provided by the maze solver algorithm)
    - handing control over to the maze solver algorithm and comunicating the current posse and wall details (provided by the Pose Estimation and Snesor Fusion)
    - Calling Pose Estimation and Sensor Fusion to make sure the data is uptodate
- [ ] Initial Orientation Code
    - Code to orient the robot so that it travels parallel and perpendicular to the maze walls, and measuring the intial readings of the magentometer to get a reference for future measurements
- [ ] Building a Webots enviornment for testing sensor fusion and etc.
- [ ] Finally  use the already solved path to get back to the beginning and go back and forth from the starting point to the center using the same path until the robot is stopped
### Hardware
As of now the hardware will consist of the following
1. Body od the robot (material and shape unsure as of yet)
2. Micro Controller (Insitially and Esp32(or8266) and later probably a Pico) 
3. Distance sensors (Ultrasonic Sensor x4)
4. Motors with encoder wheels and wheels
5. Sensors to detect encoder signals
6. Motor Controller (L293D)
7. Magetometer (GY-271 HMC5883L)
8. Power componets
   1. Battery (probably a single LiFe)
   2. Booster circuit -- boost the voltage for the motors
   3. Voltage regulators(?)
8. (?) Gyroscope (MPU-6050)

Todo list is as follows
- [ ] Plannging the basic shape and dimensions of the robot
- [ ] Building the structure of the robot
- [ ] Testing the range and accuracy of the ultrasonic Sensor
- [ ] Testing the magenotometer accuracy
- [ ] Testing the encoders
- [ ] Tuning the PID controller -- finding the control paramters
- [ ] Tuning the Sensor Fusion algorithm
- [ ] Finally testing the robot on a real maze