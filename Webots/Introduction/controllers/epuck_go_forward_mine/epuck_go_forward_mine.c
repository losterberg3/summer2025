/*
 * Copyright 1996-2024 Cyberbotics Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/lidar.h>

#define TIME_STEP 64
#define MAX_SPEED 6.28


void delay(int ms) {
  int steps = ms / TIME_STEP;
  if (ms % TIME_STEP != 0) steps++;

  for (int i = 0; i < steps; i++) {
    if (wb_robot_step(TIME_STEP) == -1)
      break;
  }
}

 
int main(int argc, char **argv) {
  wb_robot_init();

  // get a handler to the motors and set target position to infinity (speed control)
  WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");
  WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  
  // lidar
  WbDeviceTag lidar = wb_robot_get_device("LDS-01");
  wb_lidar_enable(lidar, TIME_STEP);
  wb_lidar_enable_point_cloud(lidar);
  const WbLidarPoint *points = wb_lidar_get_point_cloud(lidar);
  
  // set up the motor speeds at 10% of the MAX_SPEED.
  wb_motor_set_velocity(left_motor, 0.1 * MAX_SPEED);
  wb_motor_set_velocity(right_motor, -0.1 * MAX_SPEED);

  
  float x, y, z;
  while (wb_robot_step(TIME_STEP) != -1) {
    x = points[0].x;
    y = points[0].y;
    z = points[0].z;
    printf("Beam 1 x, y, z pos: %d, %d, %d.\n", x, y, z);
  }
  
  wb_motor_set_velocity(left_motor, 0 * MAX_SPEED);
  wb_motor_set_velocity(right_motor, 0 * MAX_SPEED);

  wb_robot_cleanup();

  return 0;
}
