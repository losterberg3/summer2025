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

#include <webots/lidar.h>
#include <webots/motor.h>
#include <webots/robot.h>
#include <webots/position_sensor.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TIME_STEP 64
#define BASE_SPEED 1.5
#define IS_INVALID(v) (isnan(v) || isinf(v))


//delay function
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
  FILE *map_file = fopen("map_points.csv", "w");
  
  double x_r = 0.0;
  double y_r = 0.0;
  double xr = 0.0;
  double yr = 0.0;
  double theta_r = 0.0;
  double prev_left = 0.0;
  double prev_right = 0.0;
  double wheel_radius = 0.033;
  double axle = 0.160;

  // get and enable the lidar
  WbDeviceTag lidar = wb_robot_get_device("LDS-01");
  wb_lidar_enable(lidar, TIME_STEP);
  wb_lidar_enable_point_cloud(lidar);
  //double max_range = wb_lidar_get_max_range(lidar);

  // get the motors and enable velocity control
  WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
  WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");  
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_velocity(right_motor, 3.0);
  wb_motor_set_velocity(left_motor, 3.0);
  
  WbDeviceTag left_encoder = wb_robot_get_device("left wheel sensor");
  WbDeviceTag right_encoder = wb_robot_get_device("right wheel sensor");
  wb_position_sensor_enable(left_encoder, TIME_STEP);
  wb_position_sensor_enable(right_encoder, TIME_STEP);
  
  wb_robot_step(TIME_STEP);
  
  prev_left = wb_position_sensor_get_value(left_encoder);
  prev_right = wb_position_sensor_get_value(right_encoder);
 
  while (wb_robot_step(TIME_STEP) != -1) {
    const WbLidarPoint *points = wb_lidar_get_point_cloud(lidar);
    
    double left = wb_position_sensor_get_value(left_encoder);
    double right = wb_position_sensor_get_value(right_encoder);
    
    double dl = (left - prev_left) * wheel_radius;
    double dr = (right - prev_right) * wheel_radius;

    prev_left = left;
    prev_right = right;
    
    double dcenter = (dl + dr) / 2;
    double dtheta = (dr - dl) / axle; //tangent small angle assumption
    
    theta_r = theta_r + dtheta;
    x_r += dcenter * cos(theta_r);
    y_r += dcenter * sin(theta_r);
    
    int n = wb_lidar_get_number_of_points(lidar);
    for (int i = 0; i < n; i++) {
      double prevx = xr;
      double prevy = yr;
      double xr = points[i].x;
      double yr = points[i].y;
      double angle = (2.0 * M_PI) * i / n;  // i-th beam angle
      
      if (IS_INVALID(xr) || IS_INVALID(yr)) {
        xr = prevx;
        yr = prevy;
      }
      
      double Xw = x_r + xr*cos(theta_r) - yr*sin(theta_r);
      double Yw = y_r + yr*cos(theta_r) + xr*sin(theta_r);
      
      fprintf(map_file, "%f,%f,%f,%f,%f,%f,%f,%f\n", Xw, Yw, xr, yr, angle, x_r, y_r, theta_r);
    }
      
    delay(100);
  }  
  wb_robot_cleanup();

  return 0;
}
