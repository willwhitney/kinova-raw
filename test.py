import kinova
import time

delta = 0.1

kinova.start()
kinova.move_cartesian_delta(delta, delta, delta)
time.sleep(10)
kinova.move_cartesian_delta(delta, delta, delta)

kinova.close()
