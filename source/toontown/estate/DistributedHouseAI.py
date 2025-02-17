from direct.directnotify import DirectNotifyGlobal
from direct.distributed.DistributedObjectAI import DistributedObjectAI
from toontown.catalog.CatalogItem import CatalogItem, Customization
from toontown.catalog.CatalogItemList import CatalogItemList
from toontown.estate.DistributedHouseInteriorAI import DistributedHouseInteriorAI
from toontown.estate.DistributedHouseDoorAI import DistributedHouseDoorAI
from toontown.building import DoorTypes
from otp.ai.MagicWordGlobal import *

from DistributedMailboxAI import DistributedMailboxAI

class DistributedHouseAI(DistributedObjectAI):
    notify = DirectNotifyGlobal.directNotify.newCategory("DistributedHouseAI")
    
    def __init__(self, air):
        DistributedObjectAI.__init__(self, air)

        self.houseType = 0
        self.gardenPos = 0
        self.avatarId = 0
        self.name = ''
        self.color = 0
        self.housePos = 0
        self.isInteriorInitialized = 0

        self.atticItems = ''
        self.interiorItems = ''
        self.interiorWallpaper = ''
        self.atticWallpaper = ''
        self.interiorWindows = ''
        self.atticWindows = ''
        self.deletedItems = ''
        
        self.mailbox = None
        
    def announceGenerate(self):
        DistributedObjectAI.announceGenerate(self)
        self.interiorZone = self.air.allocateZone()
            
        self.door = DistributedHouseDoorAI(self.air, self.doId, DoorTypes.EXT_STANDARD, swing = 3)
        self.door.generateWithRequired(self.zoneId)

        self.interior = DistributedHouseInteriorAI(self.air, self)
        self.interior.setHouseIndex(self.housePos)
        self.interior.setHouseId(self.getDoId())
        self.interior.generateWithRequired(self.interiorZone)
        
        self.interiorDoor = DistributedHouseDoorAI(self.air, self.interior.doId, DoorTypes.INT_STANDARD, swing = 3)
        self.interiorDoor.generateWithRequired(self.interiorZone)
        
        self.door.setOtherDoor(self.interiorDoor)
        self.interiorDoor.setOtherDoor(self.door)
        self.door.zoneId = self.zoneId
        self.interiorDoor.zoneId = self.interiorZone

        if not self.isInteriorInitialized:
            self.notify.debug('Initializing interior...')
            self.interior.initialize()
            self.b_setInteriorInitialized(1)

        self.mailbox = DistributedMailboxAI(self.air, self)
        self.mailbox.generateWithRequired(self.zoneId)
        
        self.sendUpdate('setHouseReady', [])

    def delete(self):
        if self.mailbox:
            self.mailbox.requestDelete()
            self.mailbox = None
            
        self.door.requestDelete()
        self.interiorDoor.requestDelete()
        self.interior.requestDelete()
        self.air.deallocateZone(self.interiorZone)
        DistributedObjectAI.delete(self)

    def setHousePos(self, pos):
        self.housePos = pos
        
    def d_setHousePos(self, pos):
        self.sendUpdate('setHousePos', [pos])
        
    def b_setHousePos(self, pos):
        self.setHousePos(pos)
        self.d_setHousePos(pos)
        
    def getHousePos(self):
        return self.housePos

    def setHouseType(self, type):
        self.houseType = type
        
    def d_setHouseType(self, type):
        self.sendUpdate('setHouseType', [type])
    
    def b_setHouseType(self, type):
        self.setHouseType(type)
        self.d_setHouseType(type)
        
    def getHouseType(self):
        return self.houseType

    def setGardenPos(self, pos):
        self.gardenPos = pos
        
    def d_setGardenPos(self, pos):
        self.sendUpdate('setGardenPos', [pos])
        
    def b_setGardenPos(self, pos):
        self.setGardenPow(pos)
        self.d_setGardenPos(pos)
        
    def getGardenPos(self):
        return self.gardenPos

    def setAvatarId(self, avId):
        self.avatarId = avId
        
    def d_setAvatarId(self, avId):
        self.sendUpdate('setAvatarId', [avId])
        
    def b_setAvatarId(self, avId):
        self.setAvatarId(avId)
        self.d_setAvatarId(avId)
        
    def getAvatarId(self):
        return self.avatarId

    def setName(self, name):
        self.name = name
        
    def d_setName(self, name):
        self.sendUpdate('setName', [name])
        
    def b_setName(self, name):
        self.setName(name)
        self.d_setName(name)
        
    def getName(self):
        return self.name

    def setColor(self, color):
        self.color = color
        
    def d_setColor(self, color):
        self.sendUpdate('setColor', [color])
        
    def b_setColor(self, color):
        self.setColor(color)
        self.d_setColor(color)
        
    def getColor(self):
        return self.color

    def setAtticItems(self, atticItems):
        self.atticItems = atticItems

    def d_setAtticItems(self, atticItems):
        self.sendUpdate('setAtticItems', [atticItems])

    def b_setAtticItems(self, atticItems):
        self.setAtticItems(atticItems)
        self.d_setAtticItems(atticItems)

    def getAtticItems(self):
        return self.atticItems
        
    def setInteriorItems(self, interiorItems):
        self.interiorItems = interiorItems

    def d_setInteriorItems(self, interiorItems):
        self.sendUpdate('setInteriorItems', [interiorItems])

    def b_setInteriorItems(self, interiorItems):
        self.setInteriorItems(interiorItems)
        self.d_setInteriorItems(interiorItems)
        
    def getInteriorItems(self):
        return self.interiorItems

    def setAtticWallpaper(self, atticWallpaper):
        self.atticWallpaper = atticWallpaper

    def d_setAtticWallpaper(self, atticWallpaper):
        self.sendUpdate('setAtticWallpaper', [atticWallpaper])

    def b_setAtticWallpaper(self, atticWallpaper):
        self.setAtticWallpaper(atticWallpaper)
        self.d_setAtticWallpaper(atticWallpaper)
        
    def getAtticWallpaper(self):
        return self.atticWallpaper

    def setInteriorWallpaper(self, interiorWallpaper):
        self.interiorWallpaper = interiorWallpaper

    def d_setInteriorWallpaper(self, interiorWallpaper):
        self.sendUpdate('setInteriorWallpaper', [interiorWallpaper])

    def b_setInteriorWallpaper(self, interiorWallpaper):
        self.setInteriorWallpaper(interiorWallpaper)
        self.d_setInteriorWallpaper(interiorWallpaper)

    def getInteriorWallpaper(self):
        return self.interiorWallpaper

    def setAtticWindows(self, atticWindows):
        self.atticWindows = atticWindows

    def d_setAtticWindows(self, atticWindows):
        self.sendUpdate('setAtticWindows', [atticWindows])

    def b_setAtticWindows(self, atticWindows):
        self.setAtticWindows(atticWindows)
        self.d_setAtticWindows(atticWindows)

    def getAtticWindows(self):
        return self.atticWindows
        
    def setInteriorWindows(self, interiorWindows):
        self.interiorWindows = interiorWindows

    def d_setInteriorWindows(self, interiorWindows):
        self.sendUpdate('setInteriorWindows', [interiorWindows])

    def b_setInteriorWindows(self, interiorWindows):
        self.setInteriorWindows(interiorWindows)
        self.d_setInteriorWindows(interiorWindows)

    def getInteriorWindows(self):
        return self.interiorWindows

    def setDeletedItems(self, deletedItems):
        self.deletedItems = deletedItems

    def d_setDeletedItems(self, deletedItems):
        self.sendUpdate('setDeletedItems', [deletedItems])

    def b_setDeletedItems(self, deletedItems):
        self.setDeletedItems(deletedItems)
        self.d_setDeletedItems(deletedItems)

    def getDeletedItems(self):
        return self.deletedItems

    def setInteriorInitialized(self, initialized):
        self.isInteriorInitialized = initialized

    def d_setInteriorInitialized(self, initialized):
        self.sendUpdate('setInteriorInitialized', [initialized])

    def b_setInteriorInitialized(self, initialized):
        self.setInteriorInitialized(initialized)
        self.d_setInteriorInitialized(initialized)

    def getInteriorInitialized(self):
        return self.isInteriorInitialized

    def setCannonEnabled(self, todo0):
        pass
        
    def getCannonEnabled(self):
        return 0
        
    def addWallpaper(self, item):
        x = self.interior.furnitureManager.atticWallpaper
        x.append(item)
        self.b_setAtticWallpaper(x.getBlob())
        self.onUpdate()
        
    def addWindow(self, item):
        x = self.interior.furnitureManager.atticWindows
        x.append(item)
        self.b_setAtticWindows(x.getBlob())
        self.onUpdate()
    
    def addAtticItem(self, item):
        x = self.interior.furnitureManager.atticItems
        x.append(item)
        self.b_setAtticItems(x.getBlob())
        self.onUpdate()
        
    def onUpdate(self):
        messenger.send('houseUpdated-%d' % self.doId)
            
@magicWord(access=ACCESS_MOD, accessOther=ACCESS_ADMIN, types=[int])
def houseType(type=0):
    """Set target house type (must be spawned!). Default (if left blank) is 0 (normal house)."""
    if not 0 <= type <= 5:
        return "Invalid house type!"
    if spellbook.getTarget().getHouseId() in simbase.air.doId2do:
        house = simbase.air.doId2do[spellbook.getTarget().getHouseId()]
        house.b_setHouseType(type)
        return "House type set to %d." % type
    return "House not loaded. Could not set type."
