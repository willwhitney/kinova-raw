import kinova_raw as raw
import time

import ipdb

raw.InitAPI()
raw.InitCommunication()
raw.InitFingers()
# raw.MoveHome()

# traj = raw.TrajectoryPoint()
# traj.InitStruct()
# traj.Position.Type = raw.ANGULAR_VELOCITY
# traj.Position.Actuators.Actuator6 = 48

# raw.SendBasicTrajectory(traj)
# for i in range(300):
#     raw.SendBasicTrajectory(traj)
#     time.sleep(0.005)


# limit_array = raw.FloatArray(70)
# for i in range(70):
#     limit_array[i] = 10
# raw.SetActuatorMaxVelocity(limit_array)
# ipdb.set_trace()

position = raw.AngularPosition()
position.InitStruct()
raw.GetAngularPosition(position)

print("Current position: ")
print(position.Actuators)

traj2 = raw.TrajectoryPoint()
traj2.InitStruct()
traj2.Position.Type = raw.ANGULAR_POSITION
traj2.Position.HAND_MODE = raw.POSITION_MODE
traj2.Position.Actuators = position.Actuators
# traj2.Position.Actuators.Actuator1 = traj2.Position.Actuators.Actuator1 + 20.0
# traj2.Position.CartesianPosition.X = 0.0

traj2.Position.Actuators.Actuator6 += 20.0

traj2.Position.Fingers.Finger1 = 0.0
traj2.Position.Fingers.Finger2 = 5000.0
traj2.Position.Fingers.Finger3 = 6700.0

print(traj2.Position.Actuators)
raw.SendBasicTrajectory(traj2)

# position = raw.CartesianPosition()
# position.InitStruct()
# raw.GetCartesianPosition(position)
#
# print("Current position: ")
# print(position.Coordinates)
#
# traj2 = raw.TrajectoryPoint()
# traj2.InitStruct()
# traj2.Position.Type = raw.CARTESIAN_POSITION
#
# print(traj2.Position.CartesianPosition)
# traj2.Position.CartesianPosition = position.Coordinates
# print(traj2.Position.CartesianPosition)
#
# traj2.Position.CartesianPosition.Z = traj2.Position.CartesianPosition.Z + -0.2
# # traj2.Position.CartesianPosition.X = 0.0
# raw.SendBasicTrajectory(traj2)

raw.CloseCommunication()
raw.CloseAPI()
