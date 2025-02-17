from otp.ai.AIBaseGlobal import *
from otp.otpbase import OTPGlobals
from direct.fsm import ClassicFSM
from direct.fsm import State
from direct.distributed import DistributedNodeAI
from direct.task import Task

class DistributedAvatarAI(DistributedNodeAI.DistributedNodeAI):

    def __init__(self, air):
        DistributedNodeAI.DistributedNodeAI.__init__(self, air)
        self.hp = 0
        self.maxHp = 0

    def b_setName(self, name):
        self.setName(name)
        self.d_setName(name)

    def d_setName(self, name):
        self.sendUpdate('setName', [name])

    def setName(self, name):
        self.name = name

    def getName(self):
        return self.name

    def b_setMaxHp(self, maxHp):
        if (maxHp > 137):
            self.air.writeServerEvent('suspicious', self.doId, 'Toon tried to go over 137 laff.')
            self.d_setMaxHp(137)
            self.setMaxHp(137)
        else:
            self.d_setMaxHp(maxHp)
            self.setMaxHp(maxHp)

    def d_setMaxHp(self, maxHp):
        if (maxHp > 137):
            self.air.writeServerEvent('suspicious', self.doId, 'Toon tried to go over 137 laff.')
        else:
            self.sendUpdate('setMaxHp', [maxHp])

    def setMaxHp(self, maxHp):
        self.maxHp = maxHp

    def getMaxHp(self):
        return self.maxHp

    def b_setHp(self, hp):
        self.d_setHp(hp)
        self.setHp(hp)

    def d_setHp(self, hp):
        self.sendUpdate('setHp', [hp])

    def setHp(self, hp):
        self.hp = hp

    def getHp(self):
        return self.hp

    def b_setLocationName(self, locationName):
        self.d_setLocationName(locationName)
        self.setLocationName(locationName)

    def d_setLocationName(self, locationName):
        pass

    def setLocationName(self, locationName):
        self.locationName = locationName

    def getLocationName(self):
        return self.locationName

    def b_setActivity(self, activity):
        self.d_setActivity(activity)
        self.setActivity(activity)

    def d_setActivity(self, activity):
        pass

    def setActivity(self, activity):
        self.activity = activity

    def getActivity(self):
        return self.activity

    def toonUp(self, num):
        if self.hp >= self.maxHp:
            return
        self.hp = min(self.hp + num, self.maxHp)
        self.b_setHp(self.hp)

    def getRadius(self):
        return OTPGlobals.AvatarDefaultRadius

    def checkAvOnShard(self, avId):
        senderId = self.air.getAvatarIdFromSender()
        onShard = False
        if simbase.air.doId2do.get(avId):
            onShard = True
        self.sendUpdateToAvatarId(senderId, 'confirmAvOnShard', [avId, onShard])

    def setParentStr(self, parentToken):
        if parentToken:
            senderId = self.air.getAvatarIdFromSender()
            self.air.writeServerEvent('Admin chat warning', senderId, 'using setParentStr to send "%s"' % parentToken)
            self.notify.warning('Admin chat warning: %s using setParentStr to send "%s"' % (senderId, parentToken))
        DistributedNodeAI.DistributedNodeAI.setParentStr(self, parentToken)

from otp.ai.MagicWordGlobal import *
    
@magicWord(chains=[CHAIN_MOD], types=[int])
def hp(hpVal = -2):
    toon = spellbook.getTarget()
    
    if hpVal == -2:
        toon.b_setHp(toon.maxHp)
        return
        
    if not -1 <= hpVal <= 137:
        return 'Laff must be between -1 and 137!'
        
    toon.b_setHp(hpVal)
    
@magicWord(chains=[CHAIN_DISABLED_ON_LIVE], types=[int])
def maxHp(hpVal):
    if not 15 <= hpVal <= 137:
        return 'Laff must be between 15 and 137!'
        
    toon = spellbook.getTarget()
    toon.b_setMaxHp(hpVal)
    toon.toonUp(hpVal)
    