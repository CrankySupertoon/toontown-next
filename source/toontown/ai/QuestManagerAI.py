from direct.directnotify.DirectNotifyGlobal import directNotify
from otp.ai.MagicWordGlobal import *
from toontown.hood import ZoneUtil
from toontown.quest import Quests
from toontown.uberdog import TopToonsGlobals
import random

class QuestManagerAI:
    notify = directNotify.newCategory('QuestManagerAI')
    
    def __init__(self, air):
        self.air = air

    def requestInteract(self, avId, npc):
        av = self.air.doId2do.get(avId)
        if not av:
            self.notify.warning('Got requestInteract with unknown avId: %s' % avId)
            return
                        
        # check if the avatar wants to turn in a quest
        quests = av.getQuests()
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            klass = Quests.getQuest(quest[0])
            
            if not klass:
                self.notify.debug('Quest %s has no class.' % quest[0])
                continue
                
            if klass.getCompletionStatus(av, quest, npc) == Quests.COMPLETE:
                # complete quest, the avatar is turning it in
                self.notify.debug('Toon %s completed quest %s' % (av.doId, quest[0]))
                messenger.send('topToonsManager-event', [av.doId, TopToonsGlobals.CAT_TASKS, 1])
                
                # fill the laff
                av.toonUp(av.maxHp)
                
                if isinstance(klass, Quests.TrackChoiceQuest):
                    npc.presentTrackChoice(avId, quest[0], klass.getChoices())
                    return 1
                    
                nextQuest = Quests.getNextQuest(quest[0], npc, av)
                if nextQuest[0] != Quests.NA:
                    self.__goToNextQuest(av, npc, quest[0], nextQuest)
                    
                else:
                    npc.completeQuest(avId, quest[0], quest[-2])
                    self.__questCompleted(av, quest[0])
                    
                return 1
                
        if self.__considerProgressTier(av):
            npc.rejectAvatarTierNotDone(avId)
            return 0
                
        # give choices if the av doesn't have enough quests already
        if len(quests) / 5 < av.getQuestCarryLimit():
            choices = Quests.chooseBestQuests(av.getRewardTier(), npc, av)
            if choices:
                npc.presentQuestChoice(avId, choices)
                return 1
        
        return 0

    def avatarChoseQuest(self, avId, npc, questId, reward, _):
        av = self.air.doId2do.get(avId)
        if not av:
            return
            
        fromNpc = Quests.getQuestFromNpcId(questId)
        toNpc = Quests.getQuestToNpcId(questId)
        
        if reward in (110, 1000):
            toNpc = Quests.ToonTailor
        
        npc.assignQuest(avId, questId, reward, toNpc)
        
        progress = 0
        quest = [questId, fromNpc, toNpc, reward, progress]
        
        av.addQuest(quest, reward, True)
        
        taskMgr.remove(npc.uniqueName('clearMovie'))

    def avatarChoseTrack(self, avId, npc, quest, track):
        av = self.air.doId2do.get(avId)
        if not av:
            return
            
        av.b_setTrackProgress(track, 0)
                
        npc.completeQuest(avId, quest, Quests.getRewardIdFromTrackId(track))
        av.removeQuest(quest)

    def avatarCancelled(self, npcId):
        npc = self.air.doId2do.get(npcId)
        if npc:
            taskMgr.remove(npc.uniqueName('clearMovie'))

    def __goToNextQuest(self, av, npc, oldQuestId, nextQuest):
        quests = av.getQuests()
        newQuests = []
        
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            
            if quest[0] == oldQuestId:
                quest[0] = nextQuest[0]
                quest[2] = nextQuest[1]
                quest[4] = 0
                
            newQuests.append(quest)
            
        npc.incompleteQuest(av.doId, nextQuest[0], Quests.QUEST, nextQuest[1])
        av.b_setQuests(newQuests)

    def __questCompleted(self, av, completeQuestId):
        quests = av.getQuests()
        
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            
            if quest[0] == completeQuestId:
                av.removeQuest(quest[0])
                self.__applyReward(av, quest[0], quest[-2])
                return
                
        self.notify.warning('Toon %s completed unknown quest: %s' % (av.doId, completeQuestId))
        
    def __applyReward(self, av, questId, rewardId):
        Quests.getReward(rewardId).sendRewardAI(av)

        transId = Quests.transformReward(rewardId, av)
        
        tier, rewardList = av.getRewardHistory()
        
        if tier == 0: # Tutorial
            rewardList.append(rewardId)
            
        if transId != rewardId:
            rewardList.append(transId)
            
        av.b_setRewardHistory(tier, rewardList)

    def __considerProgressTier(self, av):
        tier = av.getRewardHistory()[0]
        
        hasAllRewards = Quests.avatarHasAllRequiredRewards(av, tier)
        if hasAllRewards:
            if not av.getQuests():
                tier = min(Quests.ELDER_TIER, tier + 1)
                av.b_setRewardHistory(tier, [])
                return 0
                
            return av.getRewardTier() < Quests.ELDER_TIER
            
        return 0

    def toonRodeTrolley(self, avId):
        av = self.air.doId2do[avId]
        
        rode = False
        
        quests = av.getQuests()
        newQuests = []
        
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            klass = Quests.getQuest(quest[0])
            
            if not klass:
                continue
                            
            if isinstance(klass, Quests.TrolleyQuest):
               if klass.getCompletionStatus(av, quest) != Quests.COMPLETE:
                    quest[4] += 1
                    rode = True
            
            newQuests.append(quest)
            
        av.b_setQuests(newQuests)
        return rode

    def toonUsedPhone(self, avId):
        av = self.air.doId2do[avId]
        
        quests = av.getQuests()
        newQuests = []
        
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            klass = Quests.getQuest(quest[0])
            
            if not klass:
                continue
                            
            if isinstance(klass, Quests.PhoneQuest):
               if klass.getCompletionStatus(av, quest) != Quests.COMPLETE:
                    quest[4] += 1
            
            newQuests.append(quest)
            
        av.b_setQuests(newQuests)

    def toonCaughtFishingItem(self, av):
        quests = av.getQuests()
        newQuests = []
        
        itemId = -1
        for i in xrange(0, len(quests), 5):
            quest = quests[i : i + 5]
            klass = Quests.getQuest(quest[0])
            if itemId == -1:
                if klass.__class__ == Quests.RecoverItemQuest and hasattr(klass, 'getItem'):
                    if klass.getHolder() == Quests.AnyFish:
                        if klass.getCompletionStatus(av, quest) != Quests.COMPLETE:
                            minChance = klass.getPercentChance()
                            chance = random.randint(minChance - 40, 100)
                            if chance <= minChance:
                                quest[4] += 1
                                itemId = klass.getItem()
                                
            newQuests.append(quest)
            
        av.b_setQuests(newQuests)
        return itemId

    def recoverItems(self, av, suits, zoneId):
        zoneId = ZoneUtil.getBranchZone(zoneId)
        
        quests = av.getQuests()
        newQuests = []
        
        recovered = []
        unrecovered = []
        
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            klass = Quests.getQuest(quest[0])
            
            if klass.getCompletionStatus(av, quest) == Quests.INCOMPLETE:
                if isinstance(klass, Quests.RecoverItemQuest):
                    if klass.getHolder() != Quests.AnyFish:
                        item = klass.getItem()
                        
                        for suit in suits:
                            if klass.getCompletionStatus(av, quest) == Quests.COMPLETE:
                                break
                            
                            if klass.doesCogCount(av.doId, suit, zoneId, suit['activeToons']):
                                if random.random() <= klass.getPercentChance() / 100.0:
                                    quest[4] += 1
                                    recovered.append(item)
                                    
                                else:
                                    unrecovered.append(item)
                                    
                            else:
                                self.notify.debug('Recover: Suit %s at %s does not count' % (suit, zoneId))
                                    
            newQuests.append(quest)
            
        av.b_setQuests(newQuests)
        
        return recovered, unrecovered

    def toonKilledBuilding(self, av, track, _, height, zoneId, activeToons):
        if self.air.topToonsMgr:
            self.air.topToonsMgr.toonKilledBldg(av, track, height)
            
        quests = av.getQuests()
        newQuests = []
        
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            klass = Quests.getQuest(quest[0])
            
            if not klass:
                continue
                            
            if isinstance(klass, Quests.BuildingQuest):
                if klass.getCompletionStatus(av, quest) != Quests.COMPLETE:
                    if klass.doesBuildingCount(av.doId, track, height, zoneId, activeToons):
                        quest[4] += 1
            
            newQuests.append(quest)
            
        av.b_setQuests(newQuests)

    def toonDefeatedFactory(self, av, fact, activeToons):
        if self.air.topToonsMgr:
            self.air.topToonsMgr.toonKilledFactory(av, 'factory')
            
        quests = av.getQuests()
        newQuests = []
        
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            klass = Quests.getQuest(quest[0])
            
            if not klass:
                continue
                            
            if isinstance(klass, Quests.FactoryQuest):
               if klass.getCompletionStatus(av, quest) != Quests.COMPLETE:
                    quest[4] += 1
            
            newQuests.append(quest)
            
        av.b_setQuests(newQuests)
        
    def toonDefeatedMint(self, av, mint, activeToons):
        if self.air.topToonsMgr:
            self.air.topToonsMgr.toonKilledFactory(av, 'mint')
            
        quests = av.getQuests()
        newQuests = []
        
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            klass = Quests.getQuest(quest[0])
            
            if not klass:
                continue
                            
            if isinstance(klass, Quests.MintQuest):
               if klass.getCompletionStatus(av, quest) != Quests.COMPLETE:
                    quest[4] += 1
            
            newQuests.append(quest)
            
        av.b_setQuests(newQuests)
        
    def toonDefeatedStage(self, av, stage, activeToons):
        pass

    def toonKilledCogs(self, av, suits, zoneId, activeToons):
        if self.air.topToonsMgr:
            self.air.topToonsMgr.toonKilledCogs(av, suits)
            
        quests = av.getQuests()
        newQuests = []
        
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            klass = Quests.getQuest(quest[0])
            
            if not klass:
                continue
                            
            if isinstance(klass, Quests.CogQuest):
                for suit in suits:
                    if klass.getCompletionStatus(av, quest) == Quests.COMPLETE:
                        break
                        
                    if klass.doesCogCount(av.doId, suit, zoneId, suit['activeToons']):
                        quest[4] += 1
            
            newQuests.append(quest)
            
        av.b_setQuests(newQuests)
        
    def toonRecoveredCogSuitPart(self, av, zoneId, avList):
        pass
        
    def toonKilledCogdo(self, av, track, _, numFloors, zoneId, activeToons):
        if self.air.topToonsMgr:
            self.air.topToonsMgr.toonKilledOffice(av, track)
            
        quests = av.getQuests()
        newQuests = []
        
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            klass = Quests.getQuest(quest[0])
            
            if not klass:
                continue
                            
            if isinstance(klass, Quests.CogdoQuest):
               if klass.getCompletionStatus(av, quest) != Quests.COMPLETE:
                    if klass.doesOfficeCount(av.doId, track, zoneId, activeToons):
                        quest[4] += 1
            
            newQuests.append(quest)
            
        av.b_setQuests(newQuests)
        
    def toonKilledBoss(self, av, boss):
        if self.air.topToonsMgr:
            self.air.topToonsMgr.toonKilledBoss(av, boss)
            
        quests = av.getQuests()
        newQuests = []
        
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            klass = Quests.getQuest(quest[0])
            
            if not klass:
                continue
                            
            if isinstance(klass, Quests.BossQuest):
               if klass.getCompletionStatus(av, quest) != Quests.COMPLETE:
                    if klass.doesBossCount(boss):
                        quest[4] += 1
            
            newQuests.append(quest)
            
        av.b_setQuests(newQuests)

    def hasTailorClothingTicket(self, av, npc):
        quests = av.getQuests()
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            if quest[2] == Quests.ToonTailor:
                return 1
                
        return 0
                
    def removeClothingTicket(self, av, npc):                        
        quests = av.getQuests()
        for i in xrange(0, len(quests), 5):
            quest = quests[i:i + 5]
            if quest[2] == Quests.ToonTailor:
                self.__questCompleted(av, quest[0])
                return 1
                
        return 0
   
@magicWord(chains=[CHAIN_HEAD])   
def catsk():
    ''' Complete all quests immediately '''
    av = spellbook.getInvoker()
    quests = av.getQuests()
    
    for i in xrange(0, len(quests), 5):
        av.air.questManager._QuestManagerAI__questCompleted(av, quests[i])
        
@magicWord(types=[int], accessOther=ACCESS_ADMIN)   
def questtier(v = 0):
    if not 0 <= v <= 255:
        return 'Bad value. Must be in range 0-255 (uint8)'

    av = spellbook.getTarget()
    av.b_setRewardHistory(v, [])
    av.b_setQuestHistory([])
    av.b_setQuests([])
    
@magicWord(types=[int, int, str], accessOther=ACCESS_ADMIN)
def questprog(index, val=1, mode='set'):
    if mode not in ('set', 'add', 'sub'):
        return 'Invalid mode. Must be set, add or sub!'
        
    av = spellbook.getTarget()
    
    quests = av.getQuests()
    index = index * 5 + 4
    if index >= len(quests):
        return 'Invalid index! TIP: It starts from 0!'
        
    def f(q):
        x = []
        for i in xrange(0, len(q), 5):
            quest = q[i:i + 5]
            x.append(quest)
            
        return x
        
    if mode == 'set':
        quests[index] = val
        av.b_setQuests(f(quests))
        r = 'Set progress'
        
    elif mode == 'add':
        quests[index] += val
        av.b_setQuests(f(quests))
        r = 'Added progress'
        
    else:
        if quests[index] - val < 0:
            r = 'You can\'t remove this much!'
        
        else:
            quests[index] -= val
            av.b_setQuests(f(quests))
            r = 'Removed progress'
    
    return r
    
@magicWord(chains=[CHAIN_MOD])
def getquests():
    av = spellbook.getTarget()
    quests = av.getQuests()
    out = ''
    for i in xrange(0, len(quests), 5):
        quest = quests[i:i + 5]
        q = Quests.getQuest(quest[0])
        if q:
            reward = '???'
            r = Quests.getReward(quest[-2])
            if r:
                reward = r.getPosterString()
            out += '%d: %s [%s]\n' % (i // 5 + 1, q.getPosterString(), reward)
    
    return out
    