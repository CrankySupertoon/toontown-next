import DistributedElevator
import DistributedBossElevator
from ElevatorConstants import *
from direct.directnotify import DirectNotifyGlobal
from toontown.toonbase import TTLocalizer

class DistributedVPElevator(DistributedBossElevator.DistributedBossElevator):
    notify = DirectNotifyGlobal.directNotify.newCategory('DistributedVPElevator')
    deferFor = 1
    
    def __init__(self, cr):
        print "vpelevator"
        DistributedBossElevator.DistributedBossElevator.__init__(self, cr)
        print "vpelevator2"
        self.type = ELEVATOR_VP
        self.countdownTime = ElevatorData[self.type]['countdown']

    def setupElevator(self):
        print "vp_setup elevator"
        self.elevatorModel = loader.loadModel('phase_9/models/cogHQ/cogHQ_elevator')
        icon = self.elevatorModel.find('**/big_frame/')
        icon.hide()
        self.leftDoor = self.elevatorModel.find('**/left-door')
        if self.leftDoor.isEmpty():
            self.leftDoor = self.elevatorModel.find('**/left_door')
        self.rightDoor = self.elevatorModel.find('**/right-door')
        if self.rightDoor.isEmpty():
            self.rightDoor = self.elevatorModel.find('**/right_door')
        geom = base.cr.playGame.hood.loader.geom
        locator = geom.find('**/elevator_locator')
        self.elevatorModel.reparentTo(locator)
        self.elevatorModel.setH(180)
        DistributedElevator.DistributedElevator.setupElevator(self)

    def getDestName(self):
        return TTLocalizer.ElevatorSellBotBoss
