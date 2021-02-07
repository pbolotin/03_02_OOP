#include "GameProcess.h"
#include <stdio.h>

GameProcess::GameProcess() {
    printf("GameProcess constructor, initialize game\n");
}

GameProcess::~GameProcess() {
    printf("GameProcess Destructor, finalize game\n");
}
