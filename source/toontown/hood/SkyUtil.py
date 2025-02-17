from pandac.PandaModules import *
from toontown.toonbase.ToontownGlobals import *
from direct.task.Task import Task
from direct.directnotify import DirectNotifyGlobal
notify = DirectNotifyGlobal.directNotify.newCategory('SkyUtil')

def cloudSkyTrack(task):
    task.h += globalClock.getDt() * 0.25
    if task.cloud1.isEmpty() or task.cloud2.isEmpty():
        notify.warning("Couln't find clouds!")
        return Task.done
    task.cloud1.setH(task.h)
    task.cloud2.setH(-(task.h) * 0.80)
    return Task.cont

def startCloudSky(hood, parent = camera, effects = CompassEffect.PRot | CompassEffect.PZ):
    hood.sky.reparentTo(parent)
    hood.sky.setDepthTest(0)
    hood.sky.setDepthWrite(0)
    hood.sky.setBin('background', 100)
    hood.sky.find('**/Sky').reparentTo(hood.sky, -1)
    hood.sky.reparentTo(parent)
    hood.sky.setZ(0.0)
    hood.sky.setHpr(0.0, 0.0, 0.0)
    ce = CompassEffect.make(NodePath(), effects)
    hood.sky.node().setEffect(ce)
    skyTrackTask = Task(hood.skyTrack)
    skyTrackTask.h = 0
    skyTrackTask.cloud1 = hood.sky.find('**/cloud1')
    skyTrackTask.cloud2 = hood.sky.find('**/cloud2')
    if not skyTrackTask.cloud1.isEmpty() and not skyTrackTask.cloud2.isEmpty():
        taskMgr.add(skyTrackTask, 'skyTrack')
    else:
        notify.warning("Couln't find clouds!")

def bankCloudSkyTrack(task):
    task.h += globalClock.getDt() * 0.25
    if task.cloud1.isEmpty() or task.cloud2.isEmpty():
        notify.warning("Couln't find clouds!")
        return Task.done
    task.cloud1.setH(task.h)
    task.cloud2.setH(-(task.h) * 1.0)
    return Task.cont

def startBankSky(self, parent = render, effects = CompassEffect.PRot | CompassEffect.PZ):
    self.bankSky.reparentTo(parent)
    self.bankSky.setDepthTest(0)
    self.bankSky.setDepthWrite(0)
    self.bankSky.setBin('background', -1)
    self.bankSky.find('**/Sky').reparentTo(self.bankSky, -1)
    self.bankSky.reparentTo(parent)
    self.bankSky.setZ(0.0)
    self.bankSky.setHpr(0.0, 0.0, 0.0)
    ce = CompassEffect.make(NodePath(), effects)
    self.bankSky.node().setEffect(ce)
    skyTrackTask = Task(self.bankSkyTrack)
    skyTrackTask.h = 0
    skyTrackTask.cloud1 = self.bankSky.find('**/cloud1')
    skyTrackTask.cloud2 = self.bankSky.find('**/cloud2')
    if not skyTrackTask.cloud1.isEmpty() and not skyTrackTask.cloud2.isEmpty():
        taskMgr.add(skyTrackTask, 'bankSkyTrack')
    else:
        notify.warning("Couln't find clouds!")
