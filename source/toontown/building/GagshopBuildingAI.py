# File: G (Python 2.4)

from pandac.PandaModules import *
from direct.directnotify import DirectNotifyGlobal
import DistributedDoorAI
import DistributedGagshopInteriorAI
import FADoorCodes
import DoorTypes
from toontown.quest import Quests

class GagshopBuildingAI:
    
    def __init__(self, air, exteriorZone, interiorZone, blockNumber):
        self.air = air
        self.exteriorZone = exteriorZone
        self.interiorZone = interiorZone
        self.setup(blockNumber)

    
    def cleanup(self):
        self.door.requestDelete()
        del self.door
        self.insideDoor.requestDelete()
        del self.insideDoor
        self.interior.requestDelete()
        del self.interior

    
    def setup(self, blockNumber):
        self.interior = DistributedGagshopInteriorAI.DistributedGagshopInteriorAI(blockNumber, self.air, self.interiorZone)
        self.interior.generateWithRequired(self.interiorZone)
        door = DistributedDoorAI.DistributedDoorAI(self.air, blockNumber, DoorTypes.EXT_STANDARD)
        insideDoor = DistributedDoorAI.DistributedDoorAI(self.air, blockNumber + 500, DoorTypes.INT_STANDARD)
        door.setOtherDoor(insideDoor)
        insideDoor.setOtherDoor(door)
        door.zoneId = self.exteriorZone
        insideDoor.zoneId = self.interiorZone
        door.generateWithRequired(self.exteriorZone)
        insideDoor.generateWithRequired(self.interiorZone)
        self.door = door
        self.insideDoor = insideDoor


