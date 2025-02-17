from direct.directnotify import DirectNotifyGlobal
from toontown.battle import BattlePlace
from direct.fsm import ClassicFSM, State
from direct.fsm import State
from toontown.toonbase import ToontownGlobals
from toontown.building import Elevator
from pandac.PandaModules import *
from toontown.coghq import CogHQExterior

class BossbotHQExterior(CogHQExterior.CogHQExterior):
    notify = DirectNotifyGlobal.directNotify.newCategory('BossbotHQExterior')

    def __init__(self, loader, parentFSM, doneEvent):
        CogHQExterior.CogHQExterior.__init__(self, loader, parentFSM, doneEvent)
        self.elevatorDoneEvent = 'elevatorDone'
        self.trains = None
        self.fsm.addState(State.State('elevator', self.enterElevator, self.exitElevator, ['walk', 'stopped']))
        state = self.fsm.getStateNamed('walk')
        state.addTransition('elevator')
        state = self.fsm.getStateNamed('stopped')
        state.addTransition('elevator')
        state = self.fsm.getStateNamed('stickerBook')
        state.addTransition('elevator')
    
    def enter(self, *args):
        base.accept('sendtotwlb', twlobby)
        CogHQExterior.CogHQExterior.enter(self, *args)
        
    def exit(self):
        base.ignore('sendtotwlb')
        CogHQExterior.CogHQExterior.exit(self)

    def enterElevator(self, distElevator, skipDFABoard = 0):
        self.accept(self.elevatorDoneEvent, self.handleElevatorDone)
        self.elevator = Elevator.Elevator(self.fsm.getStateNamed('elevator'), self.elevatorDoneEvent, distElevator)
        if skipDFABoard:
            self.elevator.skipDFABoard = 1
        self.elevator.setReverseBoardingCamera(True)
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
        where = doneStatus['where']
        if where == 'reject':
            if hasattr(base.localAvatar, 'elevatorNotifier') and base.localAvatar.elevatorNotifier.isNotifierOpen():
                pass
            else:
                self.fsm.request('walk')
        elif where == 'exit':
            self.fsm.request('walk')
        elif where == 'countryClubInterior':
            self.doneStatus = doneStatus
            messenger.send(self.doneEvent)
        else:
            self.notify.error('Unknown mode: ' + where + ' in handleElevatorDone')

from otp.ai.MagicWordGlobal import *
@magicWord(access=ACCESS_MOD)
def twlobby():
    place = base.cr.playGame.getPlace()
    if not isinstance(place, BossbotHQExterior):
        return "Bad place! Go to BBHQ!"
        
    if place.fsm.getCurrentState().getName() != "walk":
        return "Not in walk state: %s" % place.fsm.getCurrentState().getName()
        
    place.fsm.request('teleportOut', [{
            'where': 'towersLobby',
            'how': 'teleportIn',
            'hoodId': ToontownGlobals.BossbotHQ,
            'zoneId': ToontownGlobals.TowersLobby,
            'shardId': None,
            'avId': -1}])
            