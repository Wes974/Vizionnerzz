unsigned int *  matrixToList(unsigned int matrix[3][3]) {             //Convert a 2 dimensional matrix into a 1 dimensional List.
    size_t lineLength = sizeof(matrix)/sizeof(matrix[0][0]);        //Width of Image
    size_t columnLength = sizeof(matrix[0])/sizeof(matrix[0][0]);   //Heigth of Image
    unsigned int list[lineLength];
    int i = 0;
    while (i < lineLength){
        int j = 0;
        int value = 0;
        while (j < columnLength){
            if(matrix[i][j] == 1){                                  //If the column contain at least 1 black pixel, the corresponding position in the list is black.
                value = 1;
            }
            j = j + 1;
        }
        list[i] = value;
        i = i + 1;
    }
    return list;
}

unsigned int thresholdDefine(unsigned int list[]){                  //Find the threshold between the space between characters and the space between words.
    unsigned int num = 0;
    unsigned int denum = 0;
    unsigned int prevBlack = 0;
    for(int i = 0; i < sizeof(list)/sizeof(list[0]); i++){
        if(list[i] == 0){
            num++;
            if(prevBlack){
                denum++;
            }
        }
        else{
            prevBlack = 0;
        }
    }
    return num/denum;                                               //return the average between the number of white pixels and the number of spaces to find the 
                                                                    //average space size.
}

unsigned int ** whatToSave(unsigned int threshold, unsigned int list[], unsigned int matrix[][]){    //find the positions between the begining and the end of a 
                                                                                                    //word and call the cut function to return the list containing
                                                                                                    //all the word.
    unsigned int pos1 = 0;
    unsigned int pos2 = 0;
    unsigned int inAWord = 1;
    unsigned int words = []
    unsigned int numberOfWords = 0;
    for(int i = 0; i < sizeof(list)/sizeof(list[0]); i++){
        if(lost[i] == 1){
            inAWord = 1;
            pos2 = i;
        }
        if(list[i] == 0 && inAWord){
            if(pos2 - pos1 > threshold){
                words[numberOfWords] = cutWord(pos1, pos2, matrix)
                numberOfWords++;
            }
        }
        if(list[i] == 0){
            pos1 = i;
            inAWord = 0;
        }
    }
    return words;
}

unsigned int * cutWords(unsigned int pos1, unsigned int pos2, unsigned int matrix[][]){             //use the position of the begining and the ned of a word and
                                                                                                    //return the word (a matrix)
    unsigned int word[sizeof(matrix[][]/sizeofmatrix[0][0])][pos2 - pos1];
    for(int i = pos1;i < pos2;i++){
        for(int j = 0; j < sizeof(list)/sizeof(list[0]); j++){
            word[i][j] = matrix[i][j]
        }
    }
    return word;
}

