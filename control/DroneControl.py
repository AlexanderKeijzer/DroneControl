import DroneControlControl as dc
#import tensorflow

def main():
    print('starting...')
    dc.start()
    dc.step()
    dc.step()
    dc.kill()

if __name__ == '__main__':
    main()