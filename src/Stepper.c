#include "Stepper.h"


stepper_t stExecutor;
block_t *currentBlock; 
uint8_t wakeUpState;
uint8_t outputBits; 

#define max(a,b) ((a<b)?b:a)
#define min(a,b) ((a>b)?a:b)

void TIM2_IRQHandler(void){
  TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
 // static int i;
 // if(i = (~i)){
   // GPIO_SetBits(GPIOC, GPIO_Pin_13); // LED ON
 // }else{
   // GPIO_ResetBits(GPIOC, GPIO_Pin_13); // LED OFF
 // }

 	triggerOutputData();
 stExecutorInitProcess();
 if(currentBlock != NULL){
  executeStepDisplacementProcess();
 }
 sendResetStep();
}


void motorRateControlProcess(void){
  
  if(stExecutor.stepEventsCompleted < stExecutor.eventCount){
    
  }else{
    discardCurrentBlock();
    currentBlock = NULL;
  }
  
}

#define IsStillAccelerate (stExecutor.stepEventsCompleted < currentBlock->accelerateUntil)
#define IsStillDeccelerate (stExecutor.stepEventsCompleted > currentBlock->deccelerateAfter)

void accelerateAndDeccelerateEvent(void){
  if(IsStillAccelerate){
    //accelerateRate();
  }else if(IsStillDeccelerate){
    //deccelerateRate();
  }else{
    //nominalRate();
  }
}

uint32_t setCyclePerStepEventToTimer(uint32_t cycle){
   uint16_t prescale = 1;
   uint32_t actualCycle;
  while(cycle > 0xffff){
    cycle >>= 1;
    prescale *= 2;
  }
  actualCycle = cycle;
  if(cycle != 1){
    cycle -= 1;
  }
  TIM_SetCounter(TIM2,cycle);
  TIM_SetAutoreload(TIM2,prescale-1);
  return actualCycle;
}

void setStepEventPerMin(uint32_t stepsPerMin){
    
  if(stepsPerMin < MINIMUM_STEPS_PER_MINUTE){
    stepsPerMin = MINIMUM_STEPS_PER_MINUTE;
  }
  stExecutor.cyclePerStepEvent = setCyclePerStepEventToTimer((TIMER_FREQUENCY/stepsPerMin)*60);
}


int iterateCycleCounter(){
  stExecutor.cyclePerStepCounter += stExecutor.cyclePerStepEvent;
  printf(" stExecutor.cyclePerStepCounter = %d\n",stExecutor.cyclePerStepCounter);
  if(stExecutor.cyclePerStepCounter > CYCLES_PER_ACCELERATION_TICK){
    stExecutor.cyclePerStepCounter -= CYCLES_PER_ACCELERATION_TICK;
    return true;
  }else{
    return false;
  }
  
  
}

void accelerateRate(void){
  
  
  
}

void deccelerateRate(void){
  
  
  
}

void nominalRate(void){
  
  
  
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

// For testing purpose
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

// For testing purpose
void blockConfig(block_t* block,uint8_t dir,uint32_t stepX, uint32_t stepY, uint32_t stepZ){
    block->stepEventCount = max(stepX,max(stepY,stepZ));
    block->directionBits = dir;
    block->steps[X_AXIS] = stepX;
    block->steps[Y_AXIS] = stepY;
    block->steps[Z_AXIS] = stepZ;
}




