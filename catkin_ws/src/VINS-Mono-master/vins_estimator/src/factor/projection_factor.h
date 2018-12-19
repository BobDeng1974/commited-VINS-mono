#pragma once

#include <ros/assert.h>
#include <ceres/ceres.h>
#include <Eigen/Dense>
#include "../utility/utility.h"
#include "../utility/tic_toc.h"
#include "../parameters.h"
//2: 残差长度(err_x, err_y)
//7: 第1个优化参数pose_i的长度(para_Pose[imu_i]=(px,py,pz,qx,qy,qz,qw) )
//7: 第2个优化参数pose_j的长度(para_Pose[imu_j])
//7: 第3个优化参数外参的长度(para_Ex_Pose[0])
//1: 第4个优化参数feature_inverse_depth的长度(para_Feature[feature_index])
class ProjectionFactor : public ceres::SizedCostFunction<2, 7, 7, 7, 1>
{
  public:
    ProjectionFactor(const Eigen::Vector3d &_pts_i, const Eigen::Vector3d &_pts_j);
    virtual bool Evaluate(double const *const *parameters, double *residuals, double **jacobians) const;
    void check(double **parameters);

    Eigen::Vector3d pts_i, pts_j;
    Eigen::Matrix<double, 2, 3> tangent_base;
    static Eigen::Matrix2d sqrt_info;
    static double sum_t;
};
