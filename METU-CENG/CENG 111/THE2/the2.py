Number = list(input())

if Number[5] == 'X':
    Number[5] = '10'

if '?' in Number:
    Unknown = Number.index('?')

    if Unknown == 0:
        Sum = (3 * int(Number[1])) + (5 * int(Number[2])) + (7 * int(Number[3]))
        Calc = int(Number[5]) - Sum
        Number[0] = str((Calc * 6) % 11)

    elif Unknown == 1:
        Sum = (2 * int(Number[0])) + (5 * int(Number[2])) + (7 * int(Number[3]))
        Calc = int(Number[5]) - Sum
        Number[1] = str((Calc * 4) % 11)

    elif Unknown == 2:
        Sum = (2 * int(Number[0])) + (3 * int(Number[1])) + (7 * int(Number[3]))
        Calc = int(Number[5]) - Sum
        Number[2] = str((Calc * 9) % 11)

    elif Unknown == 3:
        Sum = (2 * int(Number[0])) + (3 * int(Number[1])) + (5 * int(Number[2]))
        Calc = int(Number[5]) - Sum
        Number[3] = str((Calc * 8) % 11)

    elif Unknown == 5:
        Sum = (2 * int(Number[0])) + (3 * int(Number[1])) + (5 * int(Number[2])) + (7 * int(Number[3]))
        Calc = Sum % 11
        Number[5] = str(Calc)

    if Number[5] == '10':
        Number[5] = 'X'

    print(''.join(Number))

else:
    Sum = (2 * int(Number[0])) + (3 * int(Number[1])) + (5 * int(Number[2])) + (7 * int(Number[3]))
    Calc = Sum % 11

    if int(Number[5]) == Calc:
        print('VALID')

    else:
        print('INVALID')
