import datetime; 

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def info(msg):
    print(f"[{datetime.datetime.now()}{bcolors.OKGREEN}  INFO{bcolors.ENDC}] {msg}")

def warn(msg):
    print(f"[{datetime.datetime.now()}{bcolors.WARNING}  WARN{bcolors.ENDC}] {msg}")

def error(msg):
    print(f"[{datetime.datetime.now()}{bcolors.FAIL} ERROR{bcolors.ENDC}] {msg}")

if __name__ == '__main__':
    info("hello")
    warn("hello")
    error("hello")
