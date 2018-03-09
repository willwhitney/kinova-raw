import kinova_raw
import time

kinova_raw.InitAPI()
kinova_raw.InitCommunication()
# kinova_raw.MoveHome()

traj = kinova_raw.TrajectoryPoint()
traj.InitStruct()
traj.Position.Type = kinova_raw.ANGULAR_VELOCITY
traj.Position.Actuators.Actuator6 = 48


kinova_raw.SendBasicTrajectory(traj)
for i in range(300):
    time.sleep(0.005)

kinova_raw.CloseCommunication()
kinova_raw.CloseAPI()


# traj2 = kinova_raw.TrajectoryPoint()
# traj2.Position.Type = kinova_raw.ANGULAR_POSITION
# traj2.Position.Fingers.Finger1 = 0
# traj2.Position.Fingers.Finger2 = 30
# traj2.Position.Fingers.Finger2 = 60
# kinova_raw.SendBasicTrajectory(traj2)
