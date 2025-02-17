from direct.showbase import GarbageReport
from otp.ai.AIBaseGlobal import *
from otp.avatar import DistributedAvatarAI
from otp.avatar import PlayerBase
from otp.distributed.ClsendTracker import ClsendTracker
from otp.otpbase import OTPGlobals
from otp.ai.MagicWordGlobal import *

class DistributedPlayerAI(DistributedAvatarAI.DistributedAvatarAI, PlayerBase.PlayerBase, ClsendTracker):
    def __init__(self, air):
        DistributedAvatarAI.DistributedAvatarAI.__init__(self, air)
        PlayerBase.PlayerBase.__init__(self)
        ClsendTracker.__init__(self)
        self.friendsList = []
        self.DISLname = ''
        self.DISLid = 0
        self.adminAccess = 0

    if __dev__:

        def generate(self):
            self._sentExitServerEvent = False
            DistributedAvatarAI.DistributedAvatarAI.generate(self)

    def announceGenerate(self):
        DistributedAvatarAI.DistributedAvatarAI.announceGenerate(self)
        ClsendTracker.announceGenerate(self)
        self._doPlayerEnter()

    def _announceArrival(self):
        self.sendUpdate('arrivedOnDistrict', [self.air.districtId])

    def _announceExit(self):
        self.sendUpdate('arrivedOnDistrict', [0])

    def _sendExitServerEvent(self):
        self.air.writeServerEvent('avatarExit', self.doId, '')
        if __dev__:
            self._sentExitServerEvent = True

    def delete(self):
        if __dev__:
            del self._sentExitServerEvent
        self._doPlayerExit()
        ClsendTracker.destroy(self)
        if __dev__:
            GarbageReport.checkForGarbageLeaks()
        DistributedAvatarAI.DistributedAvatarAI.delete(self)

    def isPlayerControlled(self):
        return True

    def setLocation(self, parentId, zoneId):
        DistributedAvatarAI.DistributedAvatarAI.setLocation(self, parentId, zoneId)
        if self.isPlayerControlled():
            if not self.air._isValidPlayerLocation(parentId, zoneId):
                self.notify.info('booting player %s for doing setLocation to (%s, %s)' % (self.doId, parentId, zoneId))
                self.air.writeServerEvent('suspicious', self.doId, 'invalid setLocation: (%s, %s)' % (parentId, zoneId))
                self.requestDelete()

    def _doPlayerEnter(self):
        self.incrementPopulation()
        self._announceArrival()

    def _doPlayerExit(self):
        self._announceExit()
        self.decrementPopulation()

    def incrementPopulation(self):
        self.air.incrementPopulation()

    def decrementPopulation(self):
        simbase.air.decrementPopulation()

    def b_setChat(self, chatString, chatFlags):
        self.setChat(chatString, chatFlags)
        self.d_setChat(chatString, chatFlags)

    def d_setChat(self, chatString, chatFlags):
        self.sendUpdate('setChat', [chatString, chatFlags])

    def setChat(self, chatString, chatFlags):
        pass

    def d_setMaxHp(self, maxHp):
        DistributedAvatarAI.DistributedAvatarAI.d_setMaxHp(self, maxHp)
        self.air.writeServerEvent('setMaxHp', self.doId, '%s' % maxHp)

    def d_setSystemMessage(self, aboutId, chatString):
        self.sendUpdate('setSystemMessage', [aboutId, chatString])

    def d_setCommonChatFlags(self, flags):
        self.sendUpdate('setCommonChatFlags', [flags])

    def setCommonChatFlags(self, flags):
        pass

    def d_friendsNotify(self, avId, status):
        self.sendUpdate('friendsNotify', [avId, status])

    def friendsNotify(self, avId, status):
        pass

    def setAccountName(self, accountName):
        self.accountName = accountName

    def getAccountName(self):
        return self.accountName

    def setDISLid(self, id):
        self.DISLid = id

    def d_setFriendsList(self, friendsList):
        self.sendUpdate('setFriendsList', [friendsList])

    def setFriendsList(self, friendsList):
        self.friendsList = friendsList
        self.notify.debug('setting friends list to %s' % self.friendsList)

    def getFriendsList(self):
        return self.friendsList

    def setAdminAccess(self, access):
        self.adminAccess = access

    def getAdminAccess(self):
        return self.adminAccess

    def extendFriendsList(self, friendId, friendCode):
        for i in range(len(self.friendsList)):
            friendPair = self.friendsList[i]
            if friendPair[0] == friendId:
                self.friendsList[i] = (friendId, friendCode)
                return

        self.friendsList.append((friendId, friendCode))

@magicWord(chains=[CHAIN_ADM], types=[str])
def smsg(text):
    """Send a whisper to the whole district (system), un-prefixed."""
    for doId in simbase.air.doId2do:
        if str(doId)[:2] == '10': # Non-NPC?
            do = simbase.air.doId2do.get(doId)
            if isinstance(do, DistributedPlayerAI): # Toon?
                do.d_setSystemMessage(0, text)

@magicWord(chains=[CHAIN_ADM], types=[str])
def smsgall(text):
    """Send a system message to all clients connected to the server."""
    simbase.air.sendSysMsgToAll(text)

@magicWord(chains=[CHAIN_ADM], types=[str])
def gwhis(text):
    """Send a whisper to the whole district, prefixed with 'ADMIN Name:'."""
    text = 'ADMIN ' + spellbook.getInvoker().getName() + ': ' + text # Prepend text with Invoker's toon name.
    for doId in simbase.air.doId2do:
        if str(doId)[:2] == '10': # Non-NPC?
            do = simbase.air.doId2do.get(doId)
            if isinstance(do, DistributedPlayerAI): # Toon?
                do.d_setSystemMessage(0, text)

@magicWord(chains=[CHAIN_ADM], types=[str])
def gwhisall(text):
    """Send a system message to all clients, prefixed with 'ADMIN Name:'."""
    text = 'ADMIN ' + spellbook.getInvoker().getName() + ': ' + text
    simbase.air.sendSysMsgToAll(text)

@magicWord(chains=[CHAIN_MOD])
def accId():
    """Get the accountId from the target player."""
    accountId = spellbook.getTarget().DISLid
    return "%s has the accountId of %d" % (spellbook.getTarget().getName(), accountId)

@magicWord(chains=[CHAIN_HEAD], types=[int])
def setAdminAccess(access=ACCESS_MOD):
    if access >= spellbook.getInvokerAccess():
        return "You can't make others higher or equal to you!"
        
    if spellbook.getTarget() == spellbook.getInvoker():
        return "You can't edit your own level!"
        
    accountId = spellbook.getTarget().DISLid
    spellbook.getTarget().setAdminAccess(access)
    simbase.air.dbInterface.updateObject(simbase.air.dbId, accountId,
                                         simbase.air.dclassesByName['AccountAI'],
                                         {'ADMIN_ACCESS': access})
