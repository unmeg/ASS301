A = [4,19, 5, 6, 1, 2, 3, 17, 12, 13, 14]

def partition(array, l, h):
    pivotval = array[l]
    pivotloc = l
    for j in range(l+1, h):
        
        # print('j = {} and the val is {}'.format(j, array[j]))
        # print('pivotvalue is {}'.format(pivotval))
        # print('pivotloc is {}'.format(pivotloc))

        print('Compare {} to {}'.format(array[j], pivotval))

        if array[j] < pivotval:
            print('update pivotloc from {} to {}'.format(pivotloc, (pivotloc+1)))
            pivotloc = pivotloc+1
            temp1 = array[pivotloc]
            temp2 = array[j]
            print('in: switch {} and {}'.format(temp1, temp2))
            array[pivotloc] = temp2
            array[j] = temp1
            print(array)

    temp1 = array[pivotloc]
    temp2 = array[l]
    print('out: switch {} and {}'.format(temp1, temp2))
    array[pivotloc] = temp2
    array[l] = temp1
    print(array)

l = 0
h = 9
print(A)
partition(A, l, h)
print(A)
print('\n\n\n NEW TRIAL \n\n\n')
A = [4,19, 5, 6, 1, 2, 3, 17, 12, 13, 14]
print(A)
partition(A, l+1, h)
print(A)