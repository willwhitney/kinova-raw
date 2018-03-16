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
#
# for i in range(100):
#     position = raw.AngularPosition()
#     position.InitStruct()
#     raw.GetAngularPosition(position)
#
#     traj2 = raw.TrajectoryPoint()
#     traj2.InitStruct()
#     traj2.Position.Type = raw.ANGULAR_POSITION
#     traj2.Position.HAND_MODE = raw.POSITION_MODE
#     traj2.Position.Actuators = position.Actuators
#     traj2.Position.Fingers = position.Fingers
#
#     print(traj2.Position.Actuators)
#     raw.SendBasicTrajectory(traj2)
#     time.sleep(0.05)

# for i in range(100):
#     position = raw.CartesianPosition()
#     position.InitStruct()
#     raw.GetCartesianPosition(position)
#
#     # print("Current position: ")
#     # print(position.Coordinates)
#
#     traj2 = raw.TrajectoryPoint()
#     traj2.InitStruct()
#     traj2.Position.Type = raw.CARTESIAN_POSITION
#
#     traj2.Position.CartesianPosition = position.Coordinates
#     traj2.Position.Fingers = position.Fingers
#     print(traj2.Position.CartesianPosition)
#
#     raw.SendBasicTrajectory(traj2)
#     time.sleep(0.05)



zone_shape = raw.ZoneShape()
zone_shape.shapeType = raw.PrismSquareBase_Z

points = raw.CartesianInfoArray(8)

points[0].X =  0.1
points[0].Y = -0.52
points[0].Z =  0.23
points[0].ThetaX =  0.0
points[0].ThetaY =  0.0
points[0].ThetaZ =  0.0
points[1].X =  0.1
points[1].Y = -0.32
points[1].Z =  0.23
points[2].X =  0.3
points[2].Y = -0.32
points[2].Z =  0.23
points[3].X =  0.3
points[3].Y = -0.54
points[3].Z =  0.23
points[4].Z =  0.63

zone_shape.Points = points

limitation = raw.ZoneLimitation()
limitation.speedParameter1 = 0.0
limitation.speedParameter2 = 0.0
limitation.speedParameter3 = 0.0

zone = raw.Zone()
zone.zoneShape = zone_shape
zone.zoneLimitation = limitation

zone_array = raw.ZoneArray(1)
zone_array[0] = zone

zone_list = raw.ZoneList()
zone_list.NbZones = 1
zone_list.Zones = zone_array

# zones = raw.ZoneList()
# zones.NbZones = 1
# ipdb.set_trace()
# zones.Zones[0].zoneShape.shapeType = raw.PrismSquareBase_Z
# zones.Zones[0].zoneShape.Points[0].X = -1
# zones.Zones[0].zoneShape.Points[0].Y = -1
# zones.Zones[0].zoneShape.Points[0].Z = 0.1
# zones.Zones[0].zoneShape.Points[0].ThetaX = 0.0
# zones.Zones[0].zoneShape.Points[0].ThetaY = 0.0
# zones.Zones[0].zoneShape.Points[0].ThetaZ = 0.0
# zones.Zones[0].zoneShape.Points[1].X = -1
# zones.Zones[0].zoneShape.Points[1].Y = 1
# zones.Zones[0].zoneShape.Points[1].Z = 0.1
# zones.Zones[0].zoneShape.Points[2].X = 1
# zones.Zones[0].zoneShape.Points[2].Y = 1
# zones.Zones[0].zoneShape.Points[2].Z = 0.1
# zones.Zones[0].zoneShape.Points[3].X = 1
# zones.Zones[0].zoneShape.Points[3].Y = -1
# zones.Zones[0].zoneShape.Points[3].Z = 0.1
# zones.Zones[0].zoneShape.Points[4].Z = 2
# zones.Zones[0].zoneLimitation.speedParameter1 = 0.0
# zones.Zones[0].zoneLimitation.speedParameter2 = 0.0
# zones.Zones[0].zoneLimitation.speedParameter3 = 0.0

# zones.Zones[0].zoneShape.Points[0].X = 0.1
# zones.Zones[0].zoneShape.Points[0].Y = -0.52
# zones.Zones[0].zoneShape.Points[0].Z = 0.23
# zones.Zones[0].zoneShape.Points[0].ThetaX = 0.0
# zones.Zones[0].zoneShape.Points[0].ThetaY = 0.0
# zones.Zones[0].zoneShape.Points[0].ThetaZ = 0.0
# zones.Zones[0].zoneShape.Points[1].X = 0.1
# zones.Zones[0].zoneShape.Points[1].Y = -0.32
# zones.Zones[0].zoneShape.Points[1].Z = 0.23
# zones.Zones[0].zoneShape.Points[2].X = 0.3
# zones.Zones[0].zoneShape.Points[2].Y = -0.32
# zones.Zones[0].zoneShape.Points[2].Z = 0.23
# zones.Zones[0].zoneShape.Points[3].X = 0.3
# zones.Zones[0].zoneShape.Points[3].Y = -0.54
# zones.Zones[0].zoneShape.Points[3].Z = 0.23
# zones.Zones[0].zoneShape.Points[4].Z = 0.63



import kinova
kinova.maybe_err(raw.SetProtectionZone(zone_list))
info = raw.GeneralInformations()

kinova.move_cartesian([0.1, -0.52, 0.23])
time.sleep(5)
raw.GetGeneralInformations(info)
print("Speed param 1: ", info.ActualLimitations.speedParameter1)
kinova.move_cartesian_delta([0.1, 0.1, -0.1])
time.sleep(5)
raw.GetGeneralInformations(info)
print("Speed param 1: ", info.ActualLimitations.speedParameter1)
kinova.move_cartesian_delta([0, 0, 0.1])
time.sleep(5)


recovered_zone = raw.ZoneList()
raw.GetProtectionZone(recovered_zone)
# print(recovered_zone.Zones.zoneLimitation.speedParameter1)

raw.GetGeneralInformations(info)
print("Speed param 1: ", info.ActualLimitations.speedParameter1)

ipdb.set_trace()

raw.CloseCommunication()
raw.CloseAPI()
