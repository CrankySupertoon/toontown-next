from direct.directnotify import DirectNotifyGlobal
from toontown.battle import BattlePlace
from direct.gui.DirectGui import *
from direct.fsm import ClassicFSM, State
from direct.fsm import State
from otp.distributed.TelemetryLimiter import RotationLimitToH, TLGatherAllAvs
from toontown.toonbase import ToontownGlobals, TTLocalizer
from toontown.building import Elevator
from pandac.PandaModules import *
from otp.nametag import NametagGlobals

class TowersLobby(BattlePlace.BattlePlace):
    notify = DirectNotifyGlobal.directNotify.newCategory('TowersLobby')

    def __init__(self, loader, parentFSM, doneEvent):
        BattlePlace.BattlePlace.__init__(self, loader, doneEvent)
        self.parentFSM = parentFSM
        self.elevatorDoneEvent = 'elevatorDone'

    def load(self):
        self.fsm = ClassicFSM.ClassicFSM('TowersLobby', [State.State('start', self.enterStart, self.exitStart, ['walk',
          'tunnelIn',
          'teleportIn',
          'doorIn']),
         State.State('walk', self.enterWalk, self.exitWalk, ['stickerBook',
          'teleportOut',
          'tunnelOut',
          'DFA',
          'doorOut',
          'elevator',
          'stopped',
          'WaitForBattle',
          'battle']),
         State.State('stopped', self.enterStopped, self.exitStopped, ['walk', 'teleportOut', 'elevator']),
         State.State('stickerBook', self.enterStickerBook, self.exitStickerBook, ['walk',
          'DFA',
          'WaitForBattle',
          'battle',
          'elevator']),
         State.State('WaitForBattle', self.enterWaitForBattle, self.exitWaitForBattle, ['battle', 'walk']),
         State.State('battle', self.enterBattle, self.exitBattle, ['walk', 'teleportOut', 'died']),
         State.State('DFA', self.enterDFA, self.exitDFA, ['DFAReject', 'teleportOut', 'tunnelOut']),
         State.State('DFAReject', self.enterDFAReject, self.exitDFAReject, ['walk']),
         State.State('teleportIn', self.enterTeleportIn, self.exitTeleportIn, ['walk']),
         State.State('teleportOut', self.enterTeleportOut, self.exitTeleportOut, ['teleportIn', 'final', 'WaitForBattle']),
         State.State('doorIn', self.enterDoorIn, self.exitDoorIn, ['walk']),
         State.State('doorOut', self.enterDoorOut, self.exitDoorOut, ['walk']),
         State.State('died', self.enterDied, self.exitDied, ['quietZone']),
         State.State('tunnelIn', self.enterTunnelIn, self.exitTunnelIn, ['walk']),
         State.State('tunnelOut', self.enterTunnelOut, self.exitTunnelOut, ['final']),
         State.State('elevator', self.enterElevator, self.exitElevator, ['walk', 'stopped']),
         State.State('final', self.enterFinal, self.exitFinal, ['start'])], 'start', 'final')
        self.parentFSM.getStateNamed('towersLobby').addChild(self.fsm)
        BattlePlace.BattlePlace.load(self)

    def unload(self):
        self.parentFSM.getStateNamed('towersLobby').removeChild(self.fsm)
        del self.fsm
        BattlePlace.BattlePlace.unload(self)

    def enter(self, requestStatus):
        self.zoneId = requestStatus['zoneId']
        BattlePlace.BattlePlace.enter(self)
        self.fsm.enterInitialState()
        base.playMusic(self.loader.music, looping=1, volume=0.8)
        self.loader.geom.reparentTo(render)
        self.nodeList = [self.loader.geom]
        self.loader.hood.startSky()
        self._telemLimiter = TLGatherAllAvs('TowersLobby', RotationLimitToH)
        self.accept('doorDoneEvent', self.handleDoorDoneEvent)
        self.accept('DistributedDoor_doorTrigger', self.handleDoorTrigger)
        NametagGlobals.setMasterArrowsOn(1)
        self.tunnelOriginList = base.cr.hoodMgr.addLinkTunnelHooks(self, self.nodeList, self.zoneId)
        how = requestStatus['how']
        self.fsm.request(how, [requestStatus])

    def exit(self):
        self._telemLimiter.destroy()
        del self._telemLimiter
        self.loader.hood.stopSky()
        self.fsm.requestFinalState()
        self.loader.music.stop()
        for node in self.tunnelOriginList:
            node.removeNode()

        del self.tunnelOriginList
        del self.nodeList
        self.ignoreAll()
        BattlePlace.BattlePlace.exit(self)

    def enterTunnelOut(self, requestStatus):
        fromZoneId = self.zoneId - self.zoneId % 100
        tunnelName = base.cr.hoodMgr.makeLinkTunnelName(self.loader.hood.id, fromZoneId)
        requestStatus['tunnelName'] = tunnelName
        BattlePlace.BattlePlace.enterTunnelOut(self, requestStatus)

    def enterTeleportIn(self, requestStatus):
        BattlePlace.BattlePlace.enterTeleportIn(self, requestStatus)

    def enterTeleportOut(self, requestStatus):
        BattlePlace.BattlePlace.enterTeleportOut(self, requestStatus, self.__teleportOutDone)

    def __teleportOutDone(self, requestStatus):
        hoodId = requestStatus['hoodId']
        zoneId = requestStatus['zoneId']
        avId = requestStatus['avId']
        shardId = requestStatus['shardId']
        if hoodId == self.loader.hood.hoodId and zoneId == self.zoneId and shardId == None:
            self.fsm.request('teleportIn', [requestStatus])
        elif hoodId == ToontownGlobals.MyEstate:
            self.getEstateZoneAndGoHome(requestStatus)
        else:
            self.doneStatus = requestStatus
            messenger.send(self.doneEvent)
        return

    def exitTeleportOut(self):
        BattlePlace.BattlePlace.exitTeleportOut(self)

    def enterElevator(self, distElevator, skipDFABoard = 0):
        self.accept(self.elevatorDoneEvent, self.handleElevatorDone)
        self.elevator = Elevator.Elevator(self.fsm.getStateNamed('elevator'), self.elevatorDoneEvent, distElevator)
        if skipDFABoard:
            self.elevator.skipDFABoard = 1
        distElevator.elevatorFSM = self.elevator
        self.elevator.load()
        self.elevator.enter()

    def exitElevator(self):
        self.ignore(self.elevatorDoneEvent)
        self.elevator.unload()
        self.elevator.exit()
        del self.elevator

    def detectedElevatorCollision(self, distElevator):
        self.fsm.request('elevator', [distElevator])

    def handleElevatorDone(self, doneStatus):
        self.notify.debug('handling elevator done event')
        print doneStatus
        where = doneStatus['where']
        if where == 'reject':
            if hasattr(base.localAvatar, 'elevatorNotifier') and base.localAvatar.elevatorNotifier.isNotifierOpen():
                pass
            else:
                self.fsm.request('walk')
        elif where == 'exit':
            self.fsm.request('walk')
        elif where == 'suitInterior':
            self.doneStatus = doneStatus
            messenger.send(self.doneEvent)
        else:
            self.notify.error('Unknown mode: ' + where + ' in handleElevatorDone')
        
    def enterZoneStreetBattle(self, newZoneId):
        # hqs must ignore this
        return
