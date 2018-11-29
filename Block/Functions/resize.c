unsigned int * resize(unsigned int * matrix, unsigned int width, unsigned int height, unsigned int newWidth, unsigned int newHeight){
    unsigned int * newMatrix = calloc(width * height, sizeof(unsigned int));
    float ratioX = (float) width / newWidth;
    float ratioY = (float) height / newHeight;

    for (unsigned int i = 0; i < newWidth; i++){
        for (unsigned int j = 0; j < newHeight; j++){
            if ((float) i * ratioX == (int) ((float) i * ratioX) && (float) j * ratioY == (int) ((float) j * ratioY)){
                newMatrix[i*newWidth+j] = matrix[(int) (i (float) * ratioX), (int) (j (float) * ratioY)
            }
            else {
                //newMatrix[i*newWidth+j] = 
            }
        }
    }
    return newMatrix;
}
