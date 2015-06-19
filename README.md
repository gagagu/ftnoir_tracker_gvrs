# ftnoir_tracker_gvrs
VR Streamer Plugin for opentrack to use in combination with my VR Streamer Server and VR Streamer iOS App.
It is a combination of the acuro tracker and udp tracker. The Sensor data will transmit from iPhone to opentrack per UDP.
The aruco tracker is used for positional tracking (position of iPhone in space). My plugin will miy this inportmations
to give you a poweful VR Headtracking system for my VR Streaming Server.

# Installation
Copy the dll into the opentrack main directory.

# Setup

1) Print out the aruco tracking image found in clientfiles/aruco on opentrack install directory

2) Apply this image in front of your vr glasses

3) Connect a Webcam to your system and install/configure it.

4) Start opentrack

5) Select aruco tracker on Tracker Drop-Down-List

6) Configure aruco by selecting the "..." button (specially camera name, resolution and frames per second)

7) Select GVRS sender on Tracker Drop-Down-List

8) Configure GVRS sender by selecting the "..." button

9) Make other necessary settings for the game you want to play (Filter, Mapping, Keys)

10) Save the Profile

11) Start tracking

# Credits
Special thanks to all who helped me to realize this plugin !!!!

# Licence
see opentrack main page http://github.com/opentrack/opentrack
