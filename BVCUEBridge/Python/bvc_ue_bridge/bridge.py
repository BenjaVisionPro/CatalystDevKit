"""
This Module contains functions for managing the bridge
"""

import unreal

from . import ( utils )

# module cache to track recently closed tools
global bridgeThread

from time import sleep
from threading import Thread
 
# custom thread class
class BVCBridgeThread(Thread):
	# override the run function
	def run(self):
		sleep(1)
		
		import gtoolkit_bridge as pb
		
		print("STARTING BenjaVision Catalyst DevKit Bridge...")
		args = pb.bridge_args()
		args["port"]=10500
		args["bind_any_interface"]=True
		pb.setup_bridge(args)
		print(args)
		
		pb.run_bridge()
		print("STOPPED BenjaVision Catalyst DevKit Bridge Stopped.")


def shutdown():
    bridgeThread.stop()
    bridgeThread.join()


def startup():
	check_installation()
	# create the thread
	bridgeThread = BVCBridgeThread()
	# start the thread
	bridgeThread.start()


import pkg_resources

def check_installation():
	required = {'gtoolkit_bridge'}
	installed = {pkg.key for pkg in pkg_resources.working_set}
	missing = required - installed

	if len(missing) > 0:
		utils.pip_install(missing)
	else:
		unreal.log("All python requirements already satisfied")
