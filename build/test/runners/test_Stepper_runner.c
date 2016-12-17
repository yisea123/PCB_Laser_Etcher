/* AUTOGENERATED FILE. DO NOT EDIT. */

//=======Test Runner Used To Run Each Test Below=====
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT() && !TEST_IS_IGNORED) \
  { \
    tearDown(); \
  } \
  UnityConcludeTest(); \
}

//=======Automagically Detected Files To Include=====
#include "unity.h"
#include <setjmp.h>
#include <stdio.h>

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

//=======External Functions This Runner Calls=====
extern void setUp(void);
extern void tearDown(void);
extern void test_TIM2_IRQHandler_the_function_is_called_by_CPU(void);
extern void test_initStepper_reset_and_initilize_all_of_the_data(void);
extern void test_sleep_the_timer_interrupt_is_disable(void);
extern void test_wakeup_the_timer_interrupt_is_enabled(void);
extern void test_TIM2_IRQHandler_IRQ_to_request_block_when_buffer_block_didnt_contain_any_block(void);
extern void test_TIM2_IRQHandler_IRQ_to_request_block_when_buffer_block_contain_blocks(void);
extern void test_TIM2_IRQHandler_no_more_block_for_IRQ_to_request_and_IRQ_will_go_to_sleep(void);
extern void test_transferInfoToStExecutor_when_IRQ_successfully_get_a_block_and_transfer_info_to_st_executor_from_block(void);
extern void test_TIM2_IRQHandler_get_block_from_block_buffer_and_transfer_block_info_into_st_executor(void);
extern void test_bresenhamAlgorithm_when_dx_is_10_and_dy_is_10_(void);
extern void test_bresenhamAlgorithm_when_dx_is_20_and_dy_is_15_(void);
extern void test_executeStepDisplament_XYZ_direations_are_positive_(void);
extern void test_executeStepDisplament_XYZ_direations_are_negative_(void);
extern void test_executeStepDisplacementProcess_the_functon_is_called_and_using_for_loop(void);
extern void test_getStepStatus_when_x_y_z_rest(void);
extern void test_getStepStatus_when_x_y_z_move_(void);
extern void test_getMoveDireaction_when_x_y_z_are_moving_right_direation(void);
extern void test_getMoveDireaction_when_x_y_z_are_moving_left_direation(void);
extern void test_planningDataSending_XYZ_direations_are_negative_(void);
extern void test_planningDataSending_XYZ_direations_are_positive_(void);
extern void test_planningDataSending_XYZ_motor_take_a_rest_(void);
extern void test_executeStepDisplacementProcess_planningDataSending_the_functon_is_called_and_using_for_loop(void);
extern void test_executeStepDisplacementProcess_planningDataSending_sendResetStep_the_functon_is_called_and_using_for_loop(void);
extern void test_TIM2_IRQHandler_and_executeStepDisplacementProcess_simulate_when_TIM_interrupt_occur(void);
extern void test_motorRateControlProcess_when_motor_moving_step_is_finish_the_current_block_will_be_discarded(void);
extern void test_setTickPerStepEventToTimer_if_cycle_15000000_the_actual_cycle_is_58593_and_prescale_is_256(void);
extern void test_setTickPerStepEventToTimer_if_cycle_72000000_the_actual_cycle_is_35156_and_prescale_is_2047(void);
extern void test_setTickPerStepEventToTimer_if_cycle_50000_the_actual_cycle_is_50000_and_prescale_is_0(void);
extern void test_setTickPerStepEventToTimer_if_cycle_1_the_actual_cycle_is_1_and_prescale_is_0(void);
extern void test_setStepEventPerMin_the_steps_per_min_is_80000_the_cycle_will_be_54000(void);
extern void test_setStepEventPerMin_the_steps_per_min_is_100_less_than_800_and_steps_per_min_will_become_800(void);
extern void test_iterateCycleCounter_when_currentRate_is_80000_after_the_function_in_several_loop_cyclePerStepConter_will_remain_6000(void);
extern void test_iterateCycleCounter_currentRate_is_100_after_the_function_in_several_loop_cyclePerStepConter_will_remain_9366(void);
extern void test_acceleratreRate_when_currentRate_is_80000_after_the_function_in_several_loop_the_currentRate_will_be_increased_to_80500(void);
extern void test_acceleratreRate_when_currentRate_is_160000_the_currentRate_does_not_increase_any_more(void);
extern void test_accelerateRate_the_currentRate_will_increase_from_80000_to_160000_the_total_step_is(void);
extern void test_nominalRate_if_currentRate_is_not_equal_nominalRate_the_currentRate_will_be_equal_to_nominalRate(void);
extern void test_nominalRate_if_currentRate_is_equal_nominalRate_the_currentRate_will_be_remain(void);
extern void test_decelerationAbjustment_if_currentRate_is_more_than_minSafeRate_the_currentRate_will_be_mimus_by_increment_resolution(void);
extern void test_decelerationAbjustment_if_currentRate_is_less_than_minSafeRate_the_currentRate_will_be_divide_by_2(void);
extern void test_decelerationAbjustment_if_currentRate_is_less_than_finalRate_the_currentRate_will_become_finalRate(void);
extern void test_initializeDeccelerate_when_the_currentRate_is_equal_to_nominalRate_the_cyclePerStepCounter_will_be_set_to_0(void);
extern void test_initializeDeccelerate_when_the_currentRate_is_not_equal_to_nominalRate_the_cyclePerStepCounter_will_be_set_to_cyclesPerAccelerationTick_divide_by_2(void);
extern void test_deccelerateRate_when_the_currentRate_is_equal_to_nominalRate_the_cyclePerStepCounter_will_be_set_to_0(void);
extern void test_deccelerateRate_when_the_currentRate_is_not_equal_to_nominalRate_the_cyclePerStepCounter_will_be_set_to_cyclesPerAccelerationTick_divide_by_2(void);
extern void test_accelerateAndDeccelerateEvent_(void);
extern void test_motorRateControlProcess_(void);
extern void test_TIM2_IRQHandler_Add_a_block_into_blockBuffer_(void);


//=======Test Reset Option=====
void resetTest(void);
void resetTest(void)
{
  tearDown();
  setUp();
}


//=======MAIN=====
int main(void)
{
  UnityBegin("test_Stepper.c");
  RUN_TEST(test_TIM2_IRQHandler_the_function_is_called_by_CPU, 81);
  RUN_TEST(test_initStepper_reset_and_initilize_all_of_the_data, 95);
  RUN_TEST(test_sleep_the_timer_interrupt_is_disable, 108);
  RUN_TEST(test_wakeup_the_timer_interrupt_is_enabled, 113);
  RUN_TEST(test_TIM2_IRQHandler_IRQ_to_request_block_when_buffer_block_didnt_contain_any_block, 129);
  RUN_TEST(test_TIM2_IRQHandler_IRQ_to_request_block_when_buffer_block_contain_blocks, 144);
  RUN_TEST(test_TIM2_IRQHandler_no_more_block_for_IRQ_to_request_and_IRQ_will_go_to_sleep, 163);
  RUN_TEST(test_transferInfoToStExecutor_when_IRQ_successfully_get_a_block_and_transfer_info_to_st_executor_from_block, 170);
  RUN_TEST(test_TIM2_IRQHandler_get_block_from_block_buffer_and_transfer_block_info_into_st_executor, 207);
  RUN_TEST(test_bresenhamAlgorithm_when_dx_is_10_and_dy_is_10_, 243);
  RUN_TEST(test_bresenhamAlgorithm_when_dx_is_20_and_dy_is_15_, 277);
  RUN_TEST(test_executeStepDisplament_XYZ_direations_are_positive_, 313);
  RUN_TEST(test_executeStepDisplament_XYZ_direations_are_negative_, 369);
  RUN_TEST(test_executeStepDisplacementProcess_the_functon_is_called_and_using_for_loop, 412);
  RUN_TEST(test_getStepStatus_when_x_y_z_rest, 455);
  RUN_TEST(test_getStepStatus_when_x_y_z_move_, 462);
  RUN_TEST(test_getMoveDireaction_when_x_y_z_are_moving_right_direation, 469);
  RUN_TEST(test_getMoveDireaction_when_x_y_z_are_moving_left_direation, 476);
  RUN_TEST(test_planningDataSending_XYZ_direations_are_negative_, 483);
  RUN_TEST(test_planningDataSending_XYZ_direations_are_positive_, 494);
  RUN_TEST(test_planningDataSending_XYZ_motor_take_a_rest_, 505);
  RUN_TEST(test_executeStepDisplacementProcess_planningDataSending_the_functon_is_called_and_using_for_loop, 519);
  RUN_TEST(test_executeStepDisplacementProcess_planningDataSending_sendResetStep_the_functon_is_called_and_using_for_loop, 551);
  RUN_TEST(test_TIM2_IRQHandler_and_executeStepDisplacementProcess_simulate_when_TIM_interrupt_occur, 577);
  RUN_TEST(test_motorRateControlProcess_when_motor_moving_step_is_finish_the_current_block_will_be_discarded, 601);
  RUN_TEST(test_setTickPerStepEventToTimer_if_cycle_15000000_the_actual_cycle_is_58593_and_prescale_is_256, 615);
  RUN_TEST(test_setTickPerStepEventToTimer_if_cycle_72000000_the_actual_cycle_is_35156_and_prescale_is_2047, 621);
  RUN_TEST(test_setTickPerStepEventToTimer_if_cycle_50000_the_actual_cycle_is_50000_and_prescale_is_0, 627);
  RUN_TEST(test_setTickPerStepEventToTimer_if_cycle_1_the_actual_cycle_is_1_and_prescale_is_0, 633);
  RUN_TEST(test_setStepEventPerMin_the_steps_per_min_is_80000_the_cycle_will_be_54000, 639);
  RUN_TEST(test_setStepEventPerMin_the_steps_per_min_is_100_less_than_800_and_steps_per_min_will_become_800, 646);
  RUN_TEST(test_iterateCycleCounter_when_currentRate_is_80000_after_the_function_in_several_loop_cyclePerStepConter_will_remain_6000, 654);
  RUN_TEST(test_iterateCycleCounter_currentRate_is_100_after_the_function_in_several_loop_cyclePerStepConter_will_remain_9366, 669);
  RUN_TEST(test_acceleratreRate_when_currentRate_is_80000_after_the_function_in_several_loop_the_currentRate_will_be_increased_to_80500, 695);
  RUN_TEST(test_acceleratreRate_when_currentRate_is_160000_the_currentRate_does_not_increase_any_more, 711);
  RUN_TEST(test_accelerateRate_the_currentRate_will_increase_from_80000_to_160000_the_total_step_is, 726);
  RUN_TEST(test_nominalRate_if_currentRate_is_not_equal_nominalRate_the_currentRate_will_be_equal_to_nominalRate, 747);
  RUN_TEST(test_nominalRate_if_currentRate_is_equal_nominalRate_the_currentRate_will_be_remain, 758);
  RUN_TEST(test_decelerationAbjustment_if_currentRate_is_more_than_minSafeRate_the_currentRate_will_be_mimus_by_increment_resolution, 772);
  RUN_TEST(test_decelerationAbjustment_if_currentRate_is_less_than_minSafeRate_the_currentRate_will_be_divide_by_2, 787);
  RUN_TEST(test_decelerationAbjustment_if_currentRate_is_less_than_finalRate_the_currentRate_will_become_finalRate, 803);
  RUN_TEST(test_initializeDeccelerate_when_the_currentRate_is_equal_to_nominalRate_the_cyclePerStepCounter_will_be_set_to_0, 817);
  RUN_TEST(test_initializeDeccelerate_when_the_currentRate_is_not_equal_to_nominalRate_the_cyclePerStepCounter_will_be_set_to_cyclesPerAccelerationTick_divide_by_2, 829);
  RUN_TEST(test_deccelerateRate_when_the_currentRate_is_equal_to_nominalRate_the_cyclePerStepCounter_will_be_set_to_0, 844);
  RUN_TEST(test_deccelerateRate_when_the_currentRate_is_not_equal_to_nominalRate_the_cyclePerStepCounter_will_be_set_to_cyclesPerAccelerationTick_divide_by_2, 859);
  RUN_TEST(test_accelerateAndDeccelerateEvent_, 876);
  RUN_TEST(test_motorRateControlProcess_, 970);
  RUN_TEST(test_TIM2_IRQHandler_Add_a_block_into_blockBuffer_, 1068);

  return (UnityEnd());
}
