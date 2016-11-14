#include "Stepper.h"


stepper_t stExecutor;
block_t *currentBlock; 
uint8_t wakeUpState;
uint8_t outputBits; 

void TIM2_IRQHandler(void){
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	triggerOutputData();
  stExecutorInitProcess();
  if(currentBlock != NULL){
   executeStepDisplacementProcess();
  }
	
}

void stepperInit(void){ 
  currentBlock = NULL;
  memset(&stExecutor, 0, sizeof(stExecutor));
}

void sleep(void){
  NVIC_DisableIRQ(TIM2_IRQn);
  wakeUpState = 0;  
}

void wakeUp(void){
  NVIC_EnableIRQ(TIM2_IRQn);
  wakeUpState = 1;
}



void transferInfoToStExecutor(block_t* block){
  stExecutor.steps[X_AXIS] = block->steps[X_AXIS];
  stExecutor.steps[Y_AXIS] = block->steps[Y_AXIS];
  stExecutor.steps[Z_AXIS] = block->steps[Z_AXIS];
  stExecutor.error[X_AXIS] = -(block->stepEventCount>>1);//block->steps[X_AXIS] - block->stepEventCount;//-(block->stepEventCount>>1);
  stExecutor.error[Y_AXIS] = stExecutor.error[X_AXIS];//block->steps[Y_AXIS] - block->stepEventCount;//stExecutor.error[X_AXIS];
  stExecutor.error[Z_AXIS] = stExecutor.error[X_AXIS];//block->steps[Z_AXIS] - block->stepEventCount;//stExecutor.error[X_AXIS];
  stExecutor.xyzDireation = block->directionBits;
  stExecutor.eventCount = block->stepEventCount;
  stExecutor.stepEventsCompleted = 0;
  
}



void stExecutorInitProcess(void){

 if(currentBlock == NULL){
   currentBlock = getCurrentBlock();
   if(currentBlock != NULL){
     transferInfoToStExecutor(currentBlock);
   }else{
     sleep();
   }
 }
  
}

void executeStepDisplacementProcess(void){
  outputBits = stExecutor.xyzDireation;
  outputBits |= executeStepDisplacement(X_AXIS);
  outputBits |= executeStepDisplacement(Y_AXIS);
  outputBits |= executeStepDisplacement(Z_AXIS);
  planningDataSending();
  sendResetStep();
  stExecutor.stepEventsCompleted++;
}

uint8_t getStepStatus(int axis){
  if(getOutputFlagStatus(outputBits,axis)){
    return MOTOR_STEP_HIGH;
  }else{
    return MOTOR_STEP_LOW;
  }  
}

uint8_t getMoveDireaction(int axis){
  if(getDireationFlag(outputBits,axis)){
    return MOTOR_RIGHT;
  }else{
    return MOTOR_LEFT;
  } 
}

void planningDataSending(void){ 
  motorInfoBuffer[X_MOTOR_RESET] = getMotorInfo(motorX,getMoveDireaction(X_AXIS),MOTOR_STEP_LOW);
	motorInfoBuffer[Y_MOTOR_RESET] = getMotorInfo(motorY,getMoveDireaction(Y_AXIS),MOTOR_STEP_LOW);
	motorInfoBuffer[Z_MOTOR_RESET] = getMotorInfo(motorZ,getMoveDireaction(Z_AXIS),MOTOR_STEP_LOW);
	motorInfoBuffer[X_MOTOR_SET] = getMotorInfo(motorX,getMoveDireaction(X_AXIS),getStepStatus(X_AXIS));
	motorInfoBuffer[Y_MOTOR_SET] = getMotorInfo(motorY,getMoveDireaction(Y_AXIS),getStepStatus(Y_AXIS));
	motorInfoBuffer[Z_MOTOR_SET] = getMotorInfo(motorZ,getMoveDireaction(Z_AXIS),getStepStatus(Z_AXIS));
}

uint8_t executeStepDisplacement(int axis){
  uint8_t output = 0;
  int steps,eventCount,direactionBit,stepBit;
  eventCount = stExecutor.eventCount;
  if(axis == X_AXIS){
    steps = stExecutor.steps[X_AXIS];
    direactionBit = X_DIRECTION_BIT;
    stepBit = X_STEP_BIT;
  }else if(axis == Y_AXIS){
    steps = stExecutor.steps[Y_AXIS];
    direactionBit = Y_DIRECTION_BIT;
    stepBit = Y_STEP_BIT;
  }else if(axis == Z_AXIS){
    steps = stExecutor.steps[Z_AXIS];
    direactionBit = Z_DIRECTION_BIT;
    stepBit = Z_STEP_BIT;
  }

  if(iterate(&stExecutor.error[axis],eventCount,steps)){
     output = (1 << stepBit);
     if(stExecutor.xyzDireation & (1<<direactionBit) ){
        sys.position[axis]--;
     }else{
        sys.position[axis]++;
     }
  }
  return output;
}

uint32_t bresenhamAlgorithm(int32_t* error,uint32_t dx,uint32_t dy, int* status){
  int increment = 0;
  *error += dy;
  if(*error > 0 ){
    increment = 1;
    *error -= dx;
  }
  *status = increment;
  return increment;
}

uint32_t iterate(int32_t* error,uint32_t dx,uint32_t dy){
  int increment = 0;
  *error += dy;
  if(*error > 0 ){
    *error -= dx;
    return true;
  }
  return false;
}


int getStatus(uint8_t reg,int stepBit){
   int bitstatus;
   if((reg & (1<<stepBit)) != 0){
     bitstatus = true;
   }else{
    bitstatus = false;
   }
   return bitstatus;
}

int getOutputFlagStatus(uint8_t reg,int axis){ 
  int stepBit;
  if(axis == X_AXIS){
    stepBit = X_STEP_BIT;
  }else if(axis == Y_AXIS){
    stepBit = Y_STEP_BIT;
  }else if(axis == Z_AXIS){
    stepBit = Z_STEP_BIT;
  }
  return getStatus(reg,stepBit);
}

int getDireationFlag(uint8_t reg,int axis){
  int dir;
  if(axis == X_AXIS){
    dir = X_DIRECTION_BIT;
  }else if(axis == Y_AXIS){
    dir = Y_DIRECTION_BIT;
  }else if(axis == Z_AXIS){
    dir = Z_DIRECTION_BIT;
  }
  return getStatus(reg,dir);
}

