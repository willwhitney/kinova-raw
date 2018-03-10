import kinova
import time

# delta = 0.1
#
# kinova.start()
# kinova.move_cartesian_delta(delta, delta, delta)
# time.sleep(10)
# kinova.move_cartesian_delta(delta, delta, delta)
#
# kinova.close()

import kinova
kinova.start()
# kinova.move_home()

position = kinova.get_angular_position()
new_angles = list(position.Actuators)
# new_angles = [
#     position.Actuators.Actuator1,
#     position.Actuators.Actuator2,
#     position.Actuators.Actuator3,
#     position.Actuators.Actuator4,
#     position.Actuators.Actuator5,
#     position.Actuators.Actuator6,
# ]

# new_angles[5] += 20.0
# kinova.move_angular(new_angles)


# angle_deltas = [0.0] * 6
# angle_deltas[5] += 20.0
# angle_deltas[0] += 20.0
# angle_deltas[1] += -20.0
# kinova.move_angular_delta(angle_deltas)

import random
angles = [0.0, 0.5, 1.0]
random.shuffle(angles)
kinova.move_fingers(angles)
