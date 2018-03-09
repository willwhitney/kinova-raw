import time

import kinova_raw as raw

ERROR_TBL = {}
for name, value in raw.__dict__.iteritems():
    if "error" in name.lower() and type(value) is int and value is not 1:
        ERROR_TBL[value] = name

def maybe_err(result):
    if type(result) is int:
        if result in ERROR_TBL:
            raise Exception(ERROR_TBL[result])
    return result

# for name, value in raw.__dict__.iteritems():
#     if callable(value):



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

def move_cartesian_delta(x, y, z):
    position = get_cartesian_position()
    position.Coordinates.X += x
    position.Coordinates.Y += y
    position.Coordinates.Z += z

    trajectory_point = raw.TrajectoryPoint()
    trajectory_point.InitStruct()
    trajectory_point.Type = raw.CARTESIAN_POSITION
    trajectory_point.Position.CartesianPosition = position.Coordinates
    add_trajectory_point(trajectory_point)


def move_home():
    raw.MoveHome()

def close():
    raw.CloseCommunication()
    raw.CloseAPI()
