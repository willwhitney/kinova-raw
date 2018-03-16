import time

import kinova_raw as raw

import ipdb

ERROR_TBL = {}
for name, value in raw.__dict__.items():
    if "error" in name.lower() and type(value) is int and value is not 1:
        ERROR_TBL[value] = name

def maybe_err(result):
    if type(result) is int:
        if result in ERROR_TBL:
            raise Exception(ERROR_TBL[result])
    return result

def start():
    raw.InitAPI()
    raw.InitCommunication()
    raw.InitFingers()

def get_angular_position():
    position = raw.AngularPosition()
    position.InitStruct()
    maybe_err(raw.GetAngularPosition(position))
    return position

def get_cartesian_position():
    position = raw.CartesianPosition()
    position.InitStruct()
    maybe_err(raw.GetCartesianPosition(position))
    return position

def add_trajectory_point(point):
    maybe_err(raw.SendBasicTrajectory(point))

def move_cartesian_delta(deltas):
    assert(len(deltas) == 3)

    position = get_cartesian_position()
    coords = position.Coordinates
    move_cartesian([coord + delta for coord, delta in zip(coords, deltas)])

def move_cartesian(coordinates):
    assert(len(coordinates) == 3)

    # start with the current position so we don't move fingers or wrist
    position = get_cartesian_position()
    for i in range(len(coordinates)):
        position.Coordinates[i] = coordinates[i]

    trajectory_point = raw.TrajectoryPoint()
    trajectory_point.InitStruct()
    trajectory_point.Type = raw.CARTESIAN_POSITION
    trajectory_point.Position.CartesianPosition = position.Coordinates
    trajectory_point.Position.Fingers = position.Fingers
    add_trajectory_point(trajectory_point)

def move_angular(angles):
    assert(len(angles) == 6)

    # start with the current position so we don't move the fingers
    position = get_angular_position()
    for i in range(len(position.Actuators)):
        # i+1 because the actuator names start with Actuator1
        position.Actuators[i] = angles[i]

    trajectory_point = raw.TrajectoryPoint()
    trajectory_point.InitStruct()
    trajectory_point.Position.Type = raw.ANGULAR_POSITION
    trajectory_point.Position.Actuators = position.Actuators
    trajectory_point.Position.Fingers = position.Fingers
    add_trajectory_point(trajectory_point)

def move_angular_delta(deltas):
    assert(len(deltas) == 6)

    position = get_angular_position()
    angles = list(position.Actuators)
    move_angular([angle + delta for angle, delta in zip(angles, deltas)])

def move_fingers(angles):
    assert(len(angles) == 3)

    position = get_angular_position()
    finger_pos = position.Fingers
    for i in range(len(finger_pos)):
        finger_pos[i] = angles[i] * 6800.0

    trajectory_point = raw.TrajectoryPoint()
    trajectory_point.InitStruct()
    trajectory_point.Position.Type = raw.ANGULAR_POSITION
    trajectory_point.Position.Actuators = position.Actuators
    trajectory_point.Position.Fingers = finger_pos
    add_trajectory_point(trajectory_point)

def move_fingers_delta(deltas):
    assert(len(deltas) == 3)

    position = get_angular_position()
    finger_pos = position.Fingers
    move_fingers([angle/6800. + delta for angle, delta in zip(finger_pos, deltas)])

def clear_trajectory_queue():
    raw.EraseAllTrajectories()

def move_home():
    maybe_err(raw.MoveHome())

def close():
    raw.CloseCommunication()
    raw.CloseAPI()
