#pragma once

#include <BaselineWalkingController/State.h>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <rclcpp/rclcpp.hpp>

namespace BWC
{
/** \brief FSM state to send footstep via ROS topic. */
struct RosWalkState : State
{
public:
  /** \brief Start. */
  void start(mc_control::fsm::Controller & ctl) override;

  /** \brief Run. */
  bool run(mc_control::fsm::Controller & ctl) override;

  /** \brief Teardown. */
  void teardown(mc_control::fsm::Controller & ctl) override;

protected:
  /** \brief Set goal pose from ROS topic. */
  void setGoal();

  /** \brief Walk to the goal pose. */
  void walkToGoal();

  /** \brief ROS callback of pose topic. */
  void poseCallback(const geometry_msgs::msg::PoseStamped::SharedPtr poseMsg);

protected:
  //! List of frame names representing world coordinates
  const std::vector<std::string> worldFrameNames_ = {"world", "map", "robot_map"};

  //! Goal foot midpose (x [m], y [m], theta [rad])
  Eigen::Vector3d goalFootMidTrans_ = {0, 0, 0};

  //! Goal pose offset (x [m], y [m], theta [rad])
  Eigen::Vector3d goalOffset_ = {0, 0, 0};

  //! ROS variables
  //! @{
  std::shared_ptr<rclcpp::Node> nh_;
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr poseSub_;
  std::shared_ptr<geometry_msgs::msg::PoseStamped> poseMsg_;
  //! @}
};
} // namespace BWC
