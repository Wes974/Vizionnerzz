unsigned int *  matrixToList(unsigned int matrix[][]) {
    size_t lineLength = sizeof(matrix)/sizeof(matrix[0][0]);
    size_t columnLength = sizeof(matrix[0])/sizeof(matrix[0][0]);
    unsigned int list[lineLength];
    int i = 0;
    while (i < lineLength){
        int j = 0;
        int value = 0;
        while (j < columnLength){
            if(matrix[i][j] == 1){
                value = 1;
            }
            j = j + 1;
        }
        list[i] = value;
        i = i + 1;
    }
    return list;
}

unsigned int thresholdDefine(unsigned int list[]);
