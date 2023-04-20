import logging

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

while True:
    try:
        myInput = input('Please enter your score:')
        if myInput == 'q':
            break
        score = float(myInput)
        if score > 100:
            raise Exception('😨 Your score is too high!!')
        elif score >= 90:
            print('A')
        elif score >= 70:
            print('B')
        elif score >= 60:
            print('C')
        elif score < 60 and score >= 0:
            print('D')
        else:
            raise Exception('🤪 Please do not enter negative numbers')
    except ValueError:
        logger.error('😥 Please enter number')
    except Exception as ex:
        logger.error(ex)
