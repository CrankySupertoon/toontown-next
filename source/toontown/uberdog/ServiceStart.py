import setup

from pandac.PandaModules import *
from direct.showbase import PythonUtil

import argparse, __builtin__, os

parser = argparse.ArgumentParser()
parser.add_argument('--base-channel', help='The base channel that the server may use.')
parser.add_argument('--max-channels', help='The number of channels the server may use.')
parser.add_argument('--stateserver', help="The control channel of this UD's designated State Server.")
parser.add_argument('--astron-ip', help="The IP address of the Astron Message Director to connect to.")
parser.add_argument('--eventlogger-ip', default='localhost:7197', help="The IP address of the Astron Event Logger to log to.")

defaultPrc = 'dev.prc'
if os.path.isfile('../prod.prc'):
    defaultPrc = '../prod.prc'
    
parser.add_argument('--config', default=defaultPrc, help="PRC file(s) to load.")
args = parser.parse_args()

loadPrcFileData('cmd', 'air-base-channel 100000') # default for UD

if args.config:
    prc = args.config
    loadPrcFile(prc)
    
if os.path.isfile('extra.prc'):
    loadPrcFile('extra.prc')

localconfig = ''
if args.base_channel: localconfig += 'air-base-channel %s\n' % args.base_channel
if args.max_channels: localconfig += 'air-channel-allocation %s\n' % args.max_channels
if args.stateserver: localconfig += 'air-stateserver %s\n' % args.stateserver
if args.astron_ip: localconfig += 'air-connect %s\n' % args.astron_ip
if args.eventlogger_ip: localconfig += 'eventlog-host %s\n' % args.eventlogger_ip
loadPrcFileData('cmd', localconfig)

class game:
    name = 'uberDog'
    process = 'server'
__builtin__.game = game

from otp.ai.AIBaseGlobal import *
print config
from toontown.uberdog.ToontownUberRepository import ToontownUberRepository
simbase.air = ToontownUberRepository(config.GetInt('air-base-channel', 400000000), config.GetInt('air-stateserver', 10000))
host = config.GetString('air-connect', '127.0.0.1')
port = 7199
if ':' in host:
    host, port = host.split(':', 1)
    port = int(port)
simbase.air.connect(host, port)

try:
    run()
except SystemExit:
    raise
except Exception:
    info = PythonUtil.describeException()
    simbase.air.writeServerEvent('uberdog-exception', simbase.air.getAvatarIdFromSender(), simbase.air.getAccountIdFromSender(), info)
    raise