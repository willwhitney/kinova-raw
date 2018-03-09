import kinova_raw as raw

raw.InitAPI()
raw.InitCommunication()

raw.MoveHome()

raw.CloseCommunication()
raw.CloseAPI()
